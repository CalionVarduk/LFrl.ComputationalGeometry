using LFrl.CG.NET.Interop.Internal;
using LFrl.CG.NET.Interop.Internal.Api;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LFrl.Console.NET
{
    class Program
    {
        static void Main(string[] args)
        {
            var o = Marshal.StringToHGlobalAnsi("abcdefg");
            var r = Store.Add(o);
            var s = Store.GetSize();
            var r2 = Store.Delete(o);
        }
    }
}
