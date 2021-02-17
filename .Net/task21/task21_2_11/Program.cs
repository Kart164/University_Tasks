using System;
using System.IO;

namespace task21_2_11
{
    class Program
    {
        static void Main(string[] args)
        {
            BinaryTree tree = new BinaryTree();	//инициализируем дерево
            //на основе данных файла создаем дерево
            using (StreamReader fileIn = new StreamReader(Directory.GetCurrentDirectory()+@"\input1.txt"))
            {
                string line = fileIn.ReadToEnd();
                string[] data = line.Split(' ');
                foreach (string item in data)
                {
                    tree.Add(int.Parse(item));
                }
            }
            tree.Preorder();
            Console.WriteLine();
            bool res = tree.Task();
            tree.Preorder();

            BinaryTree tree2 = new BinaryTree();	//инициализируем дерево
            //на основе данных файла создаем дерево
            using (StreamReader fileIn = new StreamReader(Directory.GetCurrentDirectory() + @"\input2.txt"))
            {
                string line = fileIn.ReadToEnd();
                string[] data = line.Split(' ');
                foreach (string item in data)
                {
                    tree2.Add(int.Parse(item));
                }
            }
            Console.WriteLine();
            tree2.Preorder();
            Console.WriteLine();
            res = tree2.Task();
            tree2.Preorder();

            Console.ReadKey();
        }
    }
}
