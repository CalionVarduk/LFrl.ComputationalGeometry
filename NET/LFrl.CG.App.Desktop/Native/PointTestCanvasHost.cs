using LFrl.CG.NET.Interop.OGL;
using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Interop;

namespace LFrl.CG.App.Desktop.Native
{
    public struct CanvasPoint
    {
        public float X;
        public float Y;
    }

    public class PointTestCanvasHost : HwndHost
    {
        public PointTestCanvas Canvas { get; private set; }
        private FrameworkElement _parent;

        public event EventHandler<CanvasPoint> CursorPointChange;
        public event EventHandler<CanvasPoint> TranslationChange;
        public event EventHandler<CanvasPoint> ScaleChange;
        public event EventHandler<CanvasPoint> OriginChange;
        public event EventHandler<CanvasPoint> SizeChange;

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
            // TODO: these special messages should be handled by the Interop PointTestCanvas class
            // contracts (and message types) should be defined as separate structs/enums, if needed
            // either marshal delegates to unmanaged cpp or expose public method for handling messages
            // Interop class should publish a .NET event
            if (msg == 0x0400 + 1) // cursor relative to bounds
            {
                handled = true;
                var xData = BitConverter.GetBytes(wParam.ToInt64());
                var yData = BitConverter.GetBytes(lParam.ToInt64());
                var point = new CanvasPoint
                {
                    X = BitConverter.ToSingle(xData, 0),
                    Y = BitConverter.ToSingle(yData, 0)
                };
                CursorPointChange?.Invoke(this, point);
                return IntPtr.Zero;
            }
            if (msg == 0x0400 + 2) // scaled translation
            {
                handled = true;
                var xData = BitConverter.GetBytes(wParam.ToInt64());
                var yData = BitConverter.GetBytes(lParam.ToInt64());
                var point = new CanvasPoint
                {
                    X = BitConverter.ToSingle(xData, 0),
                    Y = BitConverter.ToSingle(yData, 0)
                };
                TranslationChange?.Invoke(this, point);
                return IntPtr.Zero;
            }
            if (msg == 0x0400 + 3) // scaled scale
            {
                handled = true;
                var xData = BitConverter.GetBytes(wParam.ToInt64());
                var yData = BitConverter.GetBytes(lParam.ToInt64());
                var point = new CanvasPoint
                {
                    X = BitConverter.ToSingle(xData, 0),
                    Y = BitConverter.ToSingle(yData, 0)
                };
                ScaleChange?.Invoke(this, point);
                return IntPtr.Zero;
            }
            if (msg == 0x0400 + 4) // scaled bounds origin
            {
                handled = true;
                var xData = BitConverter.GetBytes(wParam.ToInt64());
                var yData = BitConverter.GetBytes(lParam.ToInt64());
                var point = new CanvasPoint
                {
                    X = BitConverter.ToSingle(xData, 0),
                    Y = BitConverter.ToSingle(yData, 0)
                };
                OriginChange?.Invoke(this, point);
                return IntPtr.Zero;
            }
            if (msg == 0x0400 + 5) // scaled bounds size
            {
                handled = true;
                var xData = BitConverter.GetBytes(wParam.ToInt64());
                var yData = BitConverter.GetBytes(lParam.ToInt64());
                var point = new CanvasPoint
                {
                    X = BitConverter.ToSingle(xData, 0),
                    Y = BitConverter.ToSingle(yData, 0)
                };
                SizeChange?.Invoke(this, point);
                return IntPtr.Zero;
            }

            handled = false;
            return IntPtr.Zero;
        }
    }
}
