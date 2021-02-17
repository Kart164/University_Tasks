using System;
using System.Collections.Generic;
using System.Text;

namespace Task24.Common
{
    public class Magazine: AbstractBook
    {
        public DateTime Date { private set; get; }
        public string Name { private set; get; }
        
        public Magazine(DateTime date, string name)
        {
            Name = name;
            Date = date;
        }
    }
}
