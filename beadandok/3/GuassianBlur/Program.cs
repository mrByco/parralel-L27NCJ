using System;
using System.Threading;
using System.IO;
using System.Runtime.InteropServices;
using static System.Net.WebRequestMethods;
using System.Net.NetworkInformation;
using System.Net;
using System.Xml.Linq;
using GuassianBlur;

namespace GaussianBlur
{
    class Program
    {

        // function to compute the Gaussian kernel
        static void ComputeKernel(float[] kernel, int radius)
        {
            int kernelDiameter = radius * 2 + 1;
            float sigma = radius / 3.0f;
            float s = 2.0f * sigma * sigma;
            float sum = 0.0f;
            for (int i = -radius; i <= radius; i++)
            {
                for (int j = -radius; j <= radius; j++)
                {
                    float r = (float)Math.Sqrt(i * i + j * j);
                    kernel[(i + radius) * kernelDiameter + (j + radius)] = (float)Math.Exp(-r * r / s) / (float)Math.Sqrt(Math.PI * s);
                    sum += kernel[(i + radius) * kernelDiameter + (j + radius)];
                }
            }
            for (int i = 0; i < kernelDiameter * kernelDiameter; i++)
            {
                kernel[i] /= sum;
            }
        }

        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: ExeName <radius> <numThreads>");
                return;
            }

            int radius = int.Parse(args[0]);
            int numThreads = int.Parse(args[1]);

            long startTime = CurrentTimestampMs();

            int width = 640;
            int height = 480;
            float[] input = new float[width * height];
            float[] output = new float[width * height];

            Random rand = new Random();
            for (int i = 0; i < width * height; i++)
            {
                input[i] = (float)rand.NextDouble();
            }

            BlurImage(input, output, width, height, radius, numThreads);

            long endTime = CurrentTimestampMs();
            Console.WriteLine("{0}", endTime - startTime);

            using (FileStream fs = new FileStream("output.raw", FileMode.Create))
            {
                byte[] bytes = new byte[width * height * sizeof(float)];
                GCHandle handle = GCHandle.Alloc(output, GCHandleType.Pinned);
                try
                {
                    IntPtr ptr = handle.AddrOfPinnedObject();
                    Marshal.Copy(ptr, bytes, 0, bytes.Length);
                    fs.Write(bytes, 0, bytes.Length);
                }
                finally
                {
                    handle.Free();
                }
            }
        }

        static void BlurRange(object arg)
        {
            ThreadArgs args = (ThreadArgs)arg;
            float[] input = args.Input;
            float[] output = args.Output;
            int width = args.Width;
            int height = args.Height;
            int radius = args.Radius;
            int start = args.Start;
            int end = args.End;
            float[] kernel = new float[(radius * 2 + 1) * (radius * 2 + 1)];
            ComputeKernel(kernel, radius);

            for (int y = start; y < end; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    float sum = 0.0f;

                    for (int ky = -radius; ky <= radius; ky++)
                    {
                        for (int kx = -radius; kx <= radius; kx++)
                        {
                            int nky = y + ky;
                            int nkx = x + kx;
                            if (nky >= 0 && nky < height && nkx >= 0 && nkx < width)
                            {
                                sum += input[nky * width + nkx] * kernel[(ky + radius) * (radius * 2 + 1) + (kx + radius)];
                            }
                        }
                    }

                    output[y * width + x] = sum;
                }
            }
        }

        static void BlurImage(float[] input, float[] output, int width, int height, int radius, int numThreads)
        {
            Thread[] threads = new Thread[numThreads];
            ThreadArgs[] args = new ThreadArgs[numThreads];
            int chunkSize = height / numThreads;

            for (int i = 0; i < numThreads; i++)
            {
                args[i] = new ThreadArgs()
                {
                    Start = i * chunkSize,
                    End = (i == numThreads - 1) ? height : (i + 1) * chunkSize,
                    Width = width,
                    Height = height,
                    Radius = radius,
                    Input = input,
                    Output = output
                };

                threads[i] = new Thread(new ParameterizedThreadStart(BlurRange));
                threads[i].Start(args[i]);
            }

            for (int i = 0; i < numThreads; i++)
            {
                threads[i].Join();
            }
        }

        static long CurrentTimestampMs()
        {
            return DateTime.UtcNow.Ticks / TimeSpan.TicksPerMillisecond;
        }
    }
}


