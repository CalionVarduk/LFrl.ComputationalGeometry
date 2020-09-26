using System;

namespace LFrl.CG.NET.Interop
{
    public struct CombinedActionResult : IEquatable<CombinedActionResult>
    {
        public int Value { get; set; }
        public ActionResult Result => (ActionResult)(Value & ((1 << 16) - 1));
        public ushort Code => (ushort)(Value >> 16);

        public CombinedActionResult(int value)
        {
            Value = value;
        }

        public bool Equals(CombinedActionResult other) =>
            Value == other.Value;

        public override bool Equals(object obj) =>
            obj?.GetType() == GetType() && Equals((CombinedActionResult)obj);

        public override int GetHashCode() =>
            Value.GetHashCode();

        public override string ToString() =>
            $"[{Result} | {Code}]";
    }
}
