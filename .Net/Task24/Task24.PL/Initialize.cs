using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Task24.PL
{
    static class Initialize
    {
        static void Main()
        {
            var vis = new ConsoleVisual(Directory.GetCurrentDirectory()+@"\inp1.txt", Directory.GetCurrentDirectory() + @"\out1.txt");
            vis.Menu();
        }
    }
}
