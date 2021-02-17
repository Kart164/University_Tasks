using System;
using System.IO;

namespace Task9_2_6
{
    class Program
    {
        static void Main(string[] args)
        {
            //Даны два файла с числами. Получить новый файл, каждый компонент которого равен
            //среднему арифметическому значению соответствующих компонентов заданных файлов
            //(количество компонентов в исходных файлах одинаковое).

            var path1 = @"C:\test\file1.txt";
            var path2 = @"C:\test\file2.txt";
            var path3 = @"C:\test\result.txt";
            using (var file1 = new FileStream(path1, FileMode.Open, FileAccess.Read))
            {
                using (var file2 = new FileStream(path2, FileMode.Open, FileAccess.Read))
                {
                    using (var file3 = new FileStream(path3, FileMode.OpenOrCreate, FileAccess.Write))
                    {
                        using (var reader1 = new StreamReader(file1))
                        {
                            using (var reader2 = new StreamReader(file2))
                            {
                                using (var writer = new StreamWriter(file3))
                                {
                                    string str1 = "", str2 = "";
                                    while (reader1.Peek() >= 0)
                                    {
                                        str1 = reader1.ReadLine();
                                    }
                                    while (reader2.Peek() >= 0)
                                    {
                                        str2 = reader2.ReadLine();
                                    }
                                    var mas1 = str1.Split();
                                    var mas2 = str2.Split();
                                    float sum = 0;
                                    for (int i = 0; i < mas1.Length; i++)
                                    {
                                        sum = int.Parse(mas1[i]) + int.Parse(mas2[i]);
                                        writer.WriteLine($"{sum / 2}");
                                        Console.WriteLine($"{sum / 2}");
                                        sum = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }


            Console.WriteLine();
        }
    }
}
