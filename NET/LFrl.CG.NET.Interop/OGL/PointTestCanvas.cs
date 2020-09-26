using LFrl.CG.NET.Interop.Internal;
using LFrl.CG.NET.Interop.Internal.Api;
using System;

namespace LFrl.CG.NET.Interop.OGL
{
    public class PointTestCanvas : InteropObject
    {
        private IntPtr _windowHandle;
        public IntPtr WindowHandle => _windowHandle;

        public PointTestCanvas(IntPtr parentHandle, int width, int height)
            : base(PointTest.Create(parentHandle, width, height))
        {
            PointTest.GetWindowHandle(Handle, out _windowHandle);
        }

        protected override void ReleaseUnmanagedResources()
        {
            PointTest.Dispose(Handle);
            _windowHandle = IntPtr.Zero;
        }
    }
}
