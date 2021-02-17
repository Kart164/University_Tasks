using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace task15_1_15
{
    class Program
    {
        static void Main(string[] args)
        {
            var list = new List<int>();
            using (var filein= new StreamReader(@"C:\test\inp.txt"))
            {
                while (filein.Peek() >1)
                {
                    list.Add(int.Parse(filein.ReadLine()));
                }
            }
            var sortedNum = list.Where(n => n / 10 >= 1).OrderBy(n => n).Select(n=>n+1);
            using (var fileOut = new StreamWriter(@"C:\test\out.txt"))
            {
                foreach (var item in sortedNum)
                {
                    fileOut.WriteLine(item);
                }
            }

        }
    }
}
