using System;

namespace _3_4_16_15_
{
    class Program
    {
        static void Main(string[] args)
        {
            for (int i = 10; i < 100; i++)
            {
                if ((i / 10) % 2 == 1 && (i % 10) % 2 == 1)
                {
                    Console.WriteLine(i);
                }
            }
            Console.ReadKey();
        }
    }
}
