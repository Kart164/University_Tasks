using System;
using System.Diagnostics;
using System.Text;

namespace task12_6
{
    class Program
    {
        static void Main(string[] args)
        {
            var randstr = new StringBuilder();
            var rand = new Random();
            int a;
            for (int i = 0; i < 9999; i++)
            {
                a = rand.Next(1,4);
                switch (a) 
                {
                    case 1:
                        randstr.Append("a");
                        break;
                    case 2:
                        randstr.Append("b");
                        break;
                    case 3:
                        randstr.Append("c");
                        break;
                }   
            }
            string str = randstr.ToString();
            randstr.Clear();
            string str1;
            for (int i = 0; i < 99; i++)
            {
                a = rand.Next(1, 4);
                switch (a)
                {
                    case 1:
                        randstr.Append("a");
                        break;
                    case 2:
                        randstr.Append("b");
                        break;
                    case 3:
                        randstr.Append("c");
                        break;
                }
            }
            str1 = randstr.ToString();
            const long P = 37;
            long[] pwp = new long[str.Length];
            pwp[0] = 1;
            for (int i = 1; i < str.Length; i++)
            {
                pwp[i] = pwp[i - 1] * P;
            }
            long[] h = new long[str.Length];
            for (int i = 0; i < str.Length; i++)
            {
                h[i] = (str[i] - 'a' + 1) * pwp[i];
                if (i > 0)
                    h[i] += h[i - 1];
            }
            long h_s = 0;
            
            for (int i = 0; i < str1.Length; i++)
            {
                h_s += (str1[i] - 'a' + 1) * pwp[i];
            }
            var watch = new Stopwatch();
            watch.Start();
            for (int i = 0; i+str1.Length-1 < str.Length; i++)
            {
                long cur_h = h[i + str1.Length - 1];
                if (i > 0)
                {
                    cur_h -= h[i - 1];
                }
                if(cur_h == h_s * pwp[i])
                {
                    Console.WriteLine("{0} ",i);
                }
            }
            watch.Stop();
            Console.WriteLine($"кол-во тактов: {watch.ElapsedTicks}");




            watch.Reset();
            Console.WriteLine("string:");
            str1 = Console.ReadLine();
            pwp = new long[str.Length];
            pwp[0] = 1;
            for (int i = 1; i < str.Length; i++)
            {
                pwp[i] = pwp[i - 1] * P;
            }
            h = new long[str.Length];
            for (int i = 0; i < str.Length; i++)
            {
                h[i] = (str[i] - 'a' + 1) * pwp[i];
                if (i > 0)
                    h[i] += h[i - 1];
            }
            h_s = 0;

            for (int i = 0; i < str1.Length; i++)
            {
                h_s += (str1[i] - 'a' + 1) * pwp[i];
            }
            watch.Start();
            for (int i = 0; i + str1.Length - 1 < str.Length; i++)
            {
                long cur_h = h[i + str1.Length - 1];
                if (i > 0)
                {
                    cur_h -= h[i - 1];
                }
                if (cur_h == h_s * pwp[i])
                {
                    Console.WriteLine("{0} ", i);
                }
            }
            watch.Stop();
            Console.WriteLine($"кол-во тактов: {watch.ElapsedTicks}");
        }
    }
}
