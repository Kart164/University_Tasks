using System;

namespace _4_6_7_5
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("enter N:");
            int n = int.Parse(Console.ReadLine());
            Console.Write("enter C:");
            int c = int.Parse(Console.ReadLine());
            Console.Write("enter D:");
            int d = int.Parse(Console.ReadLine());
            for (int i = 1; i <= n; i++)
            {
                if (n % i == 0 && ((c % i == 0 && d % i == 0) || (i % c == 0 && i % d == 0)))
                {
                    Console.WriteLine(i);
                }
            }


            Console.Write("enter a:");
            int a = int.Parse(Console.ReadLine());
            Console.Write("enter b:");
            int b = int.Parse(Console.ReadLine());

            for (int i = a; i < b; i++)
            {
                int k = 0;
                int sum = 0;
                for (int j = 1; j <= Math.Sqrt(i); ++j)
                {
                    if (i % j == 0) //если j делитель i
                    {
                        if (j * j == i) //если j нет парного делителя
                            sum += j;
                        else
                            sum += j + (i / j);
                    }
                }
                for (int l = 2; l <= Math.Sqrt(sum); ++l) //проверка наличия не простых множителей в итоговой сумме
                {
                    if (sum % l == 0)
                        ++k;
                }
                if (k == 0)
                    Console.WriteLine(i);

            }
            Console.ReadKey();

        }
    }
}