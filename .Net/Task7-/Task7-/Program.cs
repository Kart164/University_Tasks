using System;
using System.Collections.Generic;

namespace Task7_
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("enter n:");
            int n = int.Parse(Console.ReadLine());
            var matrix = new int[n, n];
            var rand = new Random();
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    matrix[i, j] = rand.Next(99);
                }
            }



            //Console.WriteLine("Поменять местами элементы главной и побочной диагонали");
            //PrintMas(matrix);
            //int temp;
            //for (int i = 0; i < n; i++)
            //{
            //    temp = matrix[i, i];
            //    matrix[i, i] = matrix[i, (n - 1) - i];
            //    matrix[i, (n - 1) - i] = temp;
            //}
            //Console.WriteLine();
            //PrintMas(matrix);


            //Console.WriteLine("Удалить из массива элементы с номера k1 по номер k2");
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


            Console.WriteLine("Вставить строку из нулей после всех строк, в которых нет ни одного нуля.");
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
            PrintMas(matrix1);
            var flag = true;
            var index = new List<int>();
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; j++)
                {
                    if (matrix1[i, j] == 0)
                    {
                        flag = false;
                        break;
                    }

                }
                if (flag)
                index.Add(i);
                flag = true;
            }
            matrix1 = Insert0String(matrix1,index);
            Console.WriteLine();
            PrintMas(matrix1);



            Console.ReadKey();
        }

        static void DeleteElements(int[] mas, int k1, int k2)
        {
            int incr = k2;
            if (k2 < mas.Length)
            {
                for (int i = k1; i < mas.Length - (k2 - k1 + 1); i++)
                {
                    mas[i] = mas[incr + 1];
                    incr++;
                }
                for (int i = mas.Length - (k2 - k1 + 1); i < mas.Length; i++)
                {
                    mas[i] = 0;
                }
            }
            else
            {
                for (int i = k1; i < mas.Length; i++)
                {
                    mas[i] = 0;
                }
            }
        }
        static int[,] Insert0String(int[,] mas, List<int> index)
        {
            var temp = new int[ mas.GetLength(0)+index.Count, mas.GetLength(1)];
            int k = 0;
            for (int i = 0; i < mas.GetLength(0); i++)
            {
                for (int j = 0; j < mas.GetLength(1); j++)
                {
                    temp[i, j] = mas[i, j];
                }
            }
            foreach (var item in index)
            {
                for (int i = temp.GetLength(0)-1; i >item+k ; i--)
                {
                    for (int j = 0; j < temp.GetLength(1); j++)
                    {
                        temp[i, j] = temp[i - 1, j];
                    }
                }
                k++;
                for (int i = 0; i < temp.GetLength(1); i++)
                {
                    temp[item+k, i] = 0;
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
        static void PrintMas(int[,] mas)
        {
            for (int i = 0; i < mas.GetLength(0); i++)
            {
                for (int j = 0; j < mas.GetLength(1); j++)
                {
                    Console.Write($"{mas[i, j]} ");
                }
                Console.WriteLine();
            }
        }
    }
}

