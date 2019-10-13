using System;

namespace Task7_
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("enter n:");
            int n = int.Parse(Console.ReadLine());
            var matrix = new int[n,n];
            var rand = new Random();
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    matrix[i, j] = rand.Next(99);
                }
            }

            
            
            ////Поменять местами элементы главной и побочной диагонали
            //PrintMas(matrix, n,n);
            //int temp;
            //for (int i = 0; i < n; i++)
            //{
            //    temp = matrix[i, i];
            //    matrix[i, i]= matrix[i, (n-1)-i];
            //    matrix[i, (n-1) - i] = temp;
            //}
            //Console.WriteLine();
            //PrintMas(matrix, n,n);


            //Удалить из массива элементы с номера k1 по номер k2
            //Console.Write("enter n for t5-5:");
            //n = int.Parse(Console.ReadLine());
            //Console.Write("enter k1:");
            //var k1 = int.Parse(Console.ReadLine());
            //Console.Write("enter k2:");
            //var k2 = int.Parse(Console.ReadLine());
            //var mas = new int[n];
            //for (int i = 0; i < n; i++)
            //{
            //    mas[i] = rand.Next(99);
            //}
            //PrintMas(mas);
            //DeleteElements(mas, k1, k2);
            //Console.WriteLine();
            //PrintMas(mas);


            //Вставить строку из нулей после всех строк, в которых нет ни одного нуля.
            Console.Write("enter n for t6-5:");
            n = int.Parse(Console.ReadLine());
            var matrix1 = new int[n, n];
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    matrix1[i, j] = int.Parse(Console.ReadLine());
                }
            }
            PrintMas(matrix1,n,n);
            int x = n;
            bool flag = false;
            for (int i = 0; i < x; ++i)
            {
                for (int j = 0; j < n; j++)
                {
                    if (matrix1[i, j] == 0)
                    {
                        flag = true;
                    }
                }
                if (flag)
                {
                    matrix1 = Insert0String(matrix1, i, x, n);
                    x++;
                    flag = false;
                    i++;
                }
            }
            Console.WriteLine();
            PrintMas(matrix1, x, n);



            Console.ReadKey();
        }

        static void DeleteElements(int[] mas,int k1, int k2)
        {
            int incr = k2;
            for (int i = k1; i < mas.Length-(k2-k1+1); i++)
            {
                mas[i] = mas[incr + 1];
                incr++;
            }
            for (int i = mas.Length-(k2-k1+1); i < mas.Length; i++)
            {
                mas[i] = 0;
            }
        }
        static int[,] Insert0String(int[,] mas,int index,int x,int y)
        {
            var temp = new int[x+1, y];
            for (int i = 0; i < x; i++)
            {
                if (i == index)
                {
                    for (int k = 0; k < y; k++)
                    {
                        temp[i, k] = 0;
                    }
                    i++;

                }
                else
                for (int j = 0; j < y; j++)
                {
                    temp[i,j]= mas[i,j];
                }
            }
            return temp;
        }
        static void PrintMas(int[] mas)
        {
            for (int i = 0; i < mas.Length; i++)
            {
                Console.Write($"{mas[i]} ");
            }
        }
        static void PrintMas(int[,] mas, int x,int y)
        {
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    Console.Write($"{mas[i,j]} ");
                }
                Console.WriteLine();
            }
        }
    }
}
