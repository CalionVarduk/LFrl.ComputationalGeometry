#addin nuget:?package=Cake.FileHelpers&version=3.1.0

//////////////////////////////////////////////////////////////////////
// ARGUMENTS
//////////////////////////////////////////////////////////////////////

var target = Argument("target", "ConsoleCpp");
var configuration = Argument("configuration", "Debug");
var platform = Argument("platform", "x64");
var outputDir = Argument("outputdir", "");

//////////////////////////////////////////////////////////////////////
// PREPARATION
//////////////////////////////////////////////////////////////////////

var potentialStartUpProjects = new HashSet<string>(new[] { "LFrl.Console.Cpp", "LFrl.Console.NET", "LFrl.CG.App.Desktop" });
var copyFileExt = new HashSet<string>(new[] { ".dll", ".pdb", ".config", ".exe" });

var globber = new GlobberSettings {
	FilePredicate = info => info.Path.HasExtension && copyFileExt.Contains(info.Path.GetExtension().ToLower())
};
var shadersGlobber = new GlobberSettings {
	FilePredicate = info => info.Path.HasExtension && info.Path.GetExtension().ToLower() == ".glsl"
};

var startUpProject = target == "ConsoleNET" ? "LFrl.Console.NET" : target == "ConsoleCpp" ? "LFrl.Console.Cpp" : target == "Desktop" ? "LFrl.CG.App.Desktop" : "";
var solutionFileName = "LFrl.ComputationalGeometry";
var solutionFilePath = new FilePath("./" + solutionFileName + ".sln");
var buildDir = Directory("./bin/" + platform + "/" + configuration + (string.IsNullOrEmpty(outputDir) ? "" : "/" + outputDir));

Information(Environment.NewLine + "[" + DateTime.Now + ", '" + solutionFileName + "']");

Information(Environment.NewLine + "Target: " + target);
Information("VS solution file path: " + solutionFilePath.ToString());
Information("Build directory: " + buildDir.ToString());

if (!string.IsNullOrEmpty(startUpProject)) { 
	Information("StartUp project: " + startUpProject);
}

var projects = FileReadLines(solutionFilePath)
	.Where(line => line.StartsWith("Project"))
	.Select(line =>
	{
		var firstIndex = line.IndexOf('"', line.IndexOf('=') + 1);
		var secondIndex = line.IndexOf('"', firstIndex + 1);
		
		var projectName = line.Substring(firstIndex + 1, secondIndex - firstIndex - 1);
		
		firstIndex = line.IndexOf('"', secondIndex + 1);
		secondIndex = line.IndexOf('"', firstIndex + 1);
		
		var projectFilePath = line.Substring(firstIndex + 1, secondIndex - firstIndex - 1);
		
		var projectFileExtStartIndex = projectFilePath.LastIndexOf('.');
		if (projectFileExtStartIndex == -1)
			return (Name: projectName, Type: "Unknown", BaseDir: null, BuildDir: null, IsStartUp: false);
		
		var projectFilePathExt = projectFilePath.Substring(projectFileExtStartIndex + 1);
		var projectFileDir = projectFilePath.Substring(0, projectFilePath.LastIndexOfAny(new[] { '\\', '/' }));
		
		var projectType = projectFilePathExt == "csproj" ? "C#" : projectFilePathExt == "vcxproj" ? "C++" : "Unknown";
		if (projectType == "Unknown")
			return (Name: projectName, Type: "Unknown", BaseDir: Directory(projectFileDir), BuildDir: null, IsStartUp: false);
		
		var projectBuildDir = Directory(projectFileDir + "/bin/" + (projectType == "C#" || platform.ToLower() != "x86" ? platform : "Win32") + "/" + configuration);
		
		return (Name: projectName, Type: projectType, BaseDir: Directory(projectFileDir), BuildDir: projectBuildDir, IsStartUp: potentialStartUpProjects.Contains(projectName));
	})
	.Where(x => x.Type != "Unknown")
	.ToDictionary(x => x.Name, x => (Type: x.Type, BaseDir: x.BaseDir, BuildDir: x.BuildDir, IsStartUp: x.IsStartUp));

Information(Environment.NewLine + "Located " + projects.Count + " project(s):");
foreach (var project in projects) {
	Information("Name: " + project.Key + ", Base directory: " + project.Value.BaseDir + ", Build directory: " + project.Value.BuildDir + ", Type: " + project.Value.Type);
}

//////////////////////////////////////////////////////////////////////
// TASKS
//////////////////////////////////////////////////////////////////////

Task("Clean")
	.Does(() =>
{
	Information("Cleaning '" + buildDir.ToString() + "' directory...");
	CleanDirectory(buildDir);
	Information("'" + buildDir.ToString() + "' directory cleaned.");
	
	foreach (var project in projects) {
		Information(Environment.NewLine +  "Cleaning '" + project.Value.BuildDir.ToString() + "' directory...");
		CleanDirectory(project.Value.BuildDir);
		Information("'" + project.Value.BuildDir.ToString() + "' directory cleaned.");
	}
});

Task("Restore-NuGet-Packages")
	.IsDependentOn("Clean")
	.Does(() =>
{
	Information("Restoring NuGet packages..." + Environment.NewLine);
	NuGetRestore(solutionFilePath.ToString());
	Information(Environment.NewLine + "NuGet packages restored.");
});

Task("Build")
	.IsDependentOn("Restore-NuGet-Packages")
	.Does(() =>
{
	Information("Building '" + solutionFileName + "' solution..." + Environment.NewLine);
	if(IsRunningOnWindows())
	{
		MSBuild(solutionFilePath.ToString(), settings =>
		{
			settings.SetConfiguration(configuration);
			Information("MS build configuration: " + settings.Configuration);
			
			try
			{
				var platformTarget = (PlatformTarget)Enum.Parse(typeof(PlatformTarget), platform, true);
				settings.SetPlatformTarget(platformTarget);
				Information("MS build platform target: " + settings.PlatformTarget.ToString() + Environment.NewLine);
			}
			catch { }
		});
	}
	else
	{
		throw new Exception("Windows is the only supported platform right now.");
	}
})
.OnError(exception =>
{
	Information(Environment.NewLine + "Build error occurred:");
	Information(exception);
	throw exception;
})
.Finally(() =>
{
	Information(Environment.NewLine + "'" + solutionFileName + "' build finished.");
});

Task("Copy-Output-To-Build-Dir")
	.IsDependentOn("Build")
	.Does(() =>
{
	var isStartUpDefined = !string.IsNullOrEmpty(startUpProject);
	foreach (var project in projects) {
		if (project.Value.IsStartUp && (!isStartUpDefined || project.Key != startUpProject)) {
			continue;
		}
		Information(Environment.NewLine + "Copying '" + project.Key + "' project's output to '" + buildDir.ToString() + "' directory...");
		foreach (var file in GetFiles(project.Value.BuildDir.ToString() + "/**/*.*", globber)) {
			var targetPath = file.FullPath.Replace(project.Value.BuildDir.ToString(), buildDir.ToString());
			var netstandardIndex = targetPath.IndexOf("netstandard");
			if (netstandardIndex != -1) {
				targetPath = targetPath.Remove(netstandardIndex, targetPath.IndexOfAny(new[] { '\\', '/' }, netstandardIndex + 11) - netstandardIndex + 1);
			}
			CopyFile(file, new FilePath(targetPath));
			Information("Copied '" + file.FullPath + "' to '" + targetPath + "'.");
		}
		if (project.Value.Type == "C++") {
			var shadersDir = Directory(buildDir.ToString() + "/shaders");	
			foreach (var file in GetFiles(project.Value.BaseDir.ToString() + "/src/shaders/*.*", shadersGlobber)) {
				var targetPath = file.FullPath.Replace(Directory(project.Value.BaseDir.ToString() + "/src"), buildDir.ToString());
				if (!DirectoryExists(shadersDir)) {
					CleanDirectory(shadersDir);
				}
				CopyFile(file, new FilePath(targetPath));
				Information("Copied '" + file.FullPath + "' to '" + targetPath + "'.");
			}
		}
		Information("Copying '" + project.Key + "' project's output finished.");
	}
});

Task("Copy-Build-Dir-To-Start-Up-Project")
	.IsDependentOn("Copy-Output-To-Build-Dir")
	.Does(() =>
{
	Information(Environment.NewLine + "Copying '" + buildDir.ToString() + "' directory to '" + startUpProject + "' start up project's output directory...");
	var startUpInfo = projects[startUpProject];
	CopyDirectory(buildDir, startUpInfo.BuildDir);
	Information("Copying '" + buildDir.ToString() + "' to start up project's output directory finished.");
});

//////////////////////////////////////////////////////////////////////
// TASK TARGETS
//////////////////////////////////////////////////////////////////////

Task("CleanUp")
    .IsDependentOn("Clean");

Task("NoStartUp")
    .IsDependentOn("Copy-Output-To-Build-Dir");
	
Task("ConsoleNET")
    .IsDependentOn("Copy-Build-Dir-To-Start-Up-Project");
	
Task("ConsoleCpp")
    .IsDependentOn("Copy-Build-Dir-To-Start-Up-Project");
	
Task("Desktop")
    .IsDependentOn("Copy-Build-Dir-To-Start-Up-Project");

//////////////////////////////////////////////////////////////////////
// EXECUTION
//////////////////////////////////////////////////////////////////////

RunTarget(target);