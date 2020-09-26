using LFrl.CG.NET.Interop.Internal.Api;
using System;

namespace LFrl.CG.NET.Interop.Internal
{
    public abstract class InteropObject : IDisposable
    {
        public bool IsDisposed => Handle == IntPtr.Zero;
        protected IntPtr Handle { get; private set; }

        protected InteropObject(IntPtr handle)
        {
            Handle = handle;
        }

        public void Dispose()
        {
            if (IsDisposed)
                return;

            ReleaseManagedResources();
            ReleaseUnmanagedResources();
            Handle = IntPtr.Zero;
            GC.SuppressFinalize(this);
        }

        ~InteropObject()
        {
            ReleaseUnmanagedResources();
            Handle = IntPtr.Zero;
        }

        protected virtual void ReleaseManagedResources() { }
        protected virtual void ReleaseUnmanagedResources()
        {
            Store.Delete(Handle);
        }
    }
}
