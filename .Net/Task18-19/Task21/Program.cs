using System;
using System.Collections.Generic;
using System.IO;

namespace Task21_11
{
    class Program
    {
        static void Main(string[] args)
        {
            BinaryTree tree = new BinaryTree();
            using (StreamReader fileIn = new StreamReader("c:/test/inp.txt"))
            {
                string line = fileIn.ReadToEnd();
                string[] data = line.Split(' ');
                foreach (string item in data)
                {
                    tree.Add(int.Parse(item));
                }
            }
            Console.WriteLine( tree.Task() );

        }
    }
}
