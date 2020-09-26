using LFrl.CG.NET.Interop.OGL;
using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Interop;

namespace LFrl.CG.App.Desktop.Native
{
    public class PointTestCanvasHost : HwndHost
    {
        public PointTestCanvas Canvas { get; private set; }
        private FrameworkElement _parent;

        public PointTestCanvasHost() { }

        protected sealed override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            _parent = (Parent as FrameworkElement) ??
                throw new InvalidOperationException($"{typeof(PointTestCanvasHost).Name} parent's class must derive from the {typeof(FrameworkElement).FullName} class.");

            var width = (int)_parent.ActualWidth;
            var height = (int)_parent.ActualHeight;

            Canvas = new PointTestCanvas(hwndParent.Handle, width, height);
            return new HandleRef(this, Canvas.WindowHandle);
        }

        protected sealed override void DestroyWindowCore(HandleRef hwnd)
        {
            Canvas.Dispose();
        }

        protected override IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            handled = false;
            return IntPtr.Zero;
        }
    }
}
