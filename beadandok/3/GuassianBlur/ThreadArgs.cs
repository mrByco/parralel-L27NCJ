using System;
namespace GuassianBlur
{
    class ThreadArgs
    {
        public int Start { get; set; }
        public int End { get; set; }
        public int Width { get; set; }
        public int Height { get; set; }
        public int Radius { get; set; }
        public float[] Input { get; set; }
        public float[] Output { get; set; }
    }
}

