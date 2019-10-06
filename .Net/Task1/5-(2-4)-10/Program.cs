using System;

namespace _5__2_4__10
{
    class Program
    {
        static void Main(string[] args)
        {
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


            //int sum = 0;
            //for (int i = a; i <=b; i+=h)
            //{
            //    sum += FPow(i, counter);
            //    counter++;

            //}
            //Console.WriteLine(sum);


            ////первый вариант для всех чисел
            //for (int i = a; i <= b-2; i++)
            //{
            //    for (int j = i+1; j <= b-1; j++)
            //    {
            //        for (int k = j+1; k <= b; k++)
            //        {
            //            if (i * i + j * j == k * k)
            //            {
            //                Console.WriteLine($"{i} {j} {k}");
            //            }
            //        }
            //    }
            //}

            //for (int i = a; i < b; i++)//для простых троек
            //{
            //    int x=2*i+1,
            //        y=2*i*(i+1),
            //        z = 2*i+2*i+1;
            //    if (x > b || y > b || z > b)
            //    {
            //        break;
            //    }
            //    Console.WriteLine($"{x} {y} {z}");
            //}

            counter = 0;
            while(counter < a/2)
            {
                if (FPow(2, counter) > a)
                {
                    Console.WriteLine($"2^{counter-1}<={a}<2^{counter}");
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
