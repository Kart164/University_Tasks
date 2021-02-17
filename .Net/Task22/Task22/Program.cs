using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task22
{
    class Program
    {
        static void Main(string[] args)
        {
            Graph g = new Graph(Directory.GetCurrentDirectory()+@"/text.txt");
            Console.WriteLine("Graph:");
            g.Show();

            g.Dijkstr(2);
            Console.ReadLine();
        }
    }

}
