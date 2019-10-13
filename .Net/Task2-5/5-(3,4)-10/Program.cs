using System;

namespace _5__3_4__10
{
    class Program
    {
        static void Main(string[] args)
        {
            int d = 1, x, n, c;
            Console.Write("enter n=");
            n = int.Parse(Console.ReadLine());
            Console.Write("enter x=");
            x = int.Parse(Console.ReadLine());
            Console.Write(Fun1(x, d, n));


            Console.Write("enter n=");
            c = int.Parse(Console.ReadLine());
            Fun2(c);

            Console.ReadKey();
        }
        static double Fun1(int x, int d, int n)
        {
            if (d == n)
            {
                return (double)x / (d + x);
            }
            else
            {
                return (double)x / (d + Fun1(x, d + 1, n));
            }
        }
        static void Stroka(int n)
        {
            for (int i = 0; i < n; i++)
            {
                Console.Write('*');
            }
            Console.WriteLine();
        }
        static void Fun2(int n)
        {
            if (n > 0)
            {
                Stroka(n);
                Fun2(--n);
            }
            
        }
    }
    
}
