#include "ShaderProgramStore.h"

BEGIN_LFRL_OGL_NAMESPACE

ShaderProgramStore::ShaderProgramStore()
	: base()
{}

ShaderProgramStore::ShaderProgramStore(ShaderProgramStore&& other)
	: base(std::move(other))
{}

ShaderProgramStore& ShaderProgramStore::operator= (ShaderProgramStore&& other)
{
	base::operator=(std::move(other));
	return *this;
}

ShaderProgram* ShaderProgramStore::Create(std::string const& name)
{
	auto program = new ShaderProgram();
	auto initResult = program->Initialize();

	if (initResult != ShaderProgram::ActionResult::OK)
	{
		delete program;
		return nullptr;
	}
	if (!Insert(name, program))
	{
		delete program;
		return nullptr;
	}
	return program;
}

ShaderProgram* ShaderProgramStore::GetOrCreate(std::string const& name)
{
	auto program = Get(name);
	return program == nullptr ? Create(name) : program;
}

END_LFRL_OGL_NAMESPACE
