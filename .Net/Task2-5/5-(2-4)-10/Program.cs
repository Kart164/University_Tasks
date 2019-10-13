using System;

namespace _5__2_4__10
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("для каждого числа x на отрезке [a, b] с шагом h вывести на экран значение x в n-ной степени");
            Console.Write("enter a:");
            int a = int.Parse(Console.ReadLine());
            Console.Write("enter b:");
            int b = int.Parse(Console.ReadLine());
            Console.Write("enter step:");
            int h = int.Parse(Console.ReadLine());
            int counter = 1;
            for (int i = a; i <= b; i += h)
            {
                Console.WriteLine($"{FPow(i, counter)} ");
                counter++;
            }

            Console.WriteLine("найти сумму всех чисел x^n, где n – порядковый номер числа x на отрезке[a, b] с шагом h");
            int sum = 0;
            counter = 1;
            for (int i = a; i <= b; i += h)
            {
                sum += FPow(i, counter);
                counter++;

            }
            Console.WriteLine(sum);
            for (int i = a; i <= b - 2; i++)
            {
                for (int j = i + 1; j <= b - 1; j++)
                {
                    for (int k = j + 1; k <= b; k++)
                    {
                        if (i * i + j * j == k * k)
                        {
                            Console.WriteLine($"{i} {j} {k}");
                        }
                    }
                }
            }

            counter = 0;
            while(counter != a)
            {
                if (FPow(2, counter) > a)
                {
                    Console.WriteLine("2^{0}<={1}<2^{2}",counter-1,a,counter);
                    break;

                }
                counter++;
            }
            Console.ReadKey();
        }

        static int FPow(int x, int n)
        {
            int count = 1;
            if (n==0)
            {
                return 1;
            }
            while (n > 0)
            {
                if (n % 2 == 0)
                {
                    n /= 2;
                    x *= x;
                }
                else
                {
                    n--;
                    count *= x;
                }
            }
            return count;
        }
    }
}
