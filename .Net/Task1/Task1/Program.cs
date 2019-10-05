using System;

namespace Task1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("enter a=");
            double a = Double.Parse(Console.ReadLine()),
                b;
            Console.Write("enter b=");
            b = Double.Parse(Console.ReadLine());
            Console.WriteLine($"c={Math.Sqrt(a * a + b * b)}");

            Console.Write("enter number=");
            int n = int.Parse(Console.ReadLine());
            int m = (n / 10 >= n % 10) ? n % 10 : n / 10;
            Console.WriteLine(m);

            Console.Write("enter y=");
            var y = int.Parse(Console.ReadLine());
            var x = (y%1000)/10;
            Console.WriteLine(x);
            Console.ReadKey();


            for (int i = 10; i < 100; i++)
            {
                if((i/10)%2==1 && (i % 10) % 2 == 1)
                {
                    Console.WriteLine(i);
                }
            }

        }
    }
}
