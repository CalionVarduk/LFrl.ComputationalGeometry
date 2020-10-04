using System.Runtime.InteropServices;

namespace LFrl.CG.NET.Interop.Internal.Api
{
    public static class Utility
    {
        [DllImport(Constants.LFrl_CG_Cpp_API_DllPath, EntryPoint = Constants.LFrl_CG_API_Utility_SetupGL, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetupGL();

        [DllImport(Constants.LFrl_CG_Cpp_API_DllPath, EntryPoint = Constants.LFrl_CG_API_Utility_Setup_WinApi, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetupWinApi();

        [DllImport(Constants.LFrl_CG_Cpp_API_DllPath, EntryPoint = Constants.LFrl_CG_API_Utility_Dispose_WinApi, CallingConvention = CallingConvention.Cdecl)]
        public static extern int DisposeWinApi();
    }
}
