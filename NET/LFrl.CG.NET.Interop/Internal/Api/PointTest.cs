using System;
using System.Runtime.InteropServices;

namespace LFrl.CG.NET.Interop.Internal.Api
{
    public static class PointTest
    {
        [DllImport(Constants.LFrl_CG_Cpp_API_DllPath, EntryPoint = Constants.LFrl_CG_API_PointTest_GLCanvas_Create, CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr Create(IntPtr parentHandle, int width, int height);

        [DllImport(Constants.LFrl_CG_Cpp_API_DllPath, EntryPoint = Constants.LFrl_CG_API_PointTest_GLCanvas_Dispose, CallingConvention = CallingConvention.Cdecl)]
        internal static extern ActionResult Dispose(IntPtr handle);

        [DllImport(Constants.LFrl_CG_Cpp_API_DllPath, EntryPoint = Constants.LFrl_CG_API_PointTest_GLCanvas_GetHwnd, CallingConvention = CallingConvention.Cdecl)]
        internal static extern ActionResult GetWindowHandle(IntPtr handle, [Out] out IntPtr result);
    }
}
