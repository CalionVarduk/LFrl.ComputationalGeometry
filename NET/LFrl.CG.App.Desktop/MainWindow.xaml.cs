using LFrl.CG.App.Desktop.Native;
using LFrl.CG.NET.Interop.Internal.Api;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace LFrl.CG.App.Desktop
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private PointTestCanvasHost _host;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var result1 = Utility.SetupGL();
            var result2 = Utility.SetupWinApi();

            _host = new PointTestCanvasHost();
            host.Child = _host;

            _host.CursorPointChange += (s, p) =>
            {
                CursorText.Text = $"CURSOR: [X: {p.X.ToString("0.00")}, Y: {p.Y.ToString("0.00")}]";
            };
            _host.TranslationChange += (s, p) =>
            {
                TranslationText.Text = $"TRANSLATION: [X: {p.X.ToString("0.00")}, Y: {p.Y.ToString("0.00")}]";
            };
            _host.ScaleChange += (s, p) =>
            {
                ScaleText.Text = $"SCALE: [X: {p.X.ToString("0.00")}, Y: {p.Y.ToString("0.00")}]";
            };
            _host.OriginChange += (s, p) =>
            {
                BoundsOriginText.Text = $"BOUNDS ORIGIN: [X: {p.X.ToString("0.00")}, Y: {p.Y.ToString("0.00")}]";
            };
            _host.SizeChange += (s, p) =>
            {
                BoundsSizeText.Text = $"BOUNDS SIZE: [X: {p.X.ToString("0.00")}, Y: {p.Y.ToString("0.00")}]";
            };
        }
    }
}
