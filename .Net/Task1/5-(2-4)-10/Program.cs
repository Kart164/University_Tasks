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
            //for(int i = a; i <= b; i += h)
            //{
            //    Console.WriteLine($"{FPow(i,counter)} ");
            //    counter++;
            //}


            //int sum = 0;
            //for (int i = a; i <=b; i+=h)
            //{
            //    sum += FPow(i, counter);
            //    counter++;

            //}
            //Console.WriteLine(sum);


            int 
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
