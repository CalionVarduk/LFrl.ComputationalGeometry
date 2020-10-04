using System;
using System.Runtime.InteropServices;

namespace LFrl.CG.NET.Interop.Internal.Api
{
    public static class Store
    {
        [DllImport(Constants.LFrl_CG_Cpp_API_DllPath, EntryPoint = Constants.LFrl_CG_API_Store_Add, CallingConvention = CallingConvention.Cdecl)]
        public static extern ActionResult Add(IntPtr handle);

        [DllImport(Constants.LFrl_CG_Cpp_API_DllPath, EntryPoint = Constants.LFrl_CG_API_Store_Contains, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool Contains(IntPtr handle);

        [DllImport(Constants.LFrl_CG_Cpp_API_DllPath, EntryPoint = Constants.LFrl_CG_API_Store_GetSize, CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetSize();

        [DllImport(Constants.LFrl_CG_Cpp_API_DllPath, EntryPoint = Constants.LFrl_CG_API_Store_Delete, CallingConvention = CallingConvention.Cdecl)]
        public static extern ActionResult Delete(IntPtr handle);
    }
}
