using System;
using System.Collections.Generic;
using System.Text;

namespace Task24.Common
{
    public class Book: AbstractBook
    {
        public string Author { private set; get; }
        public string Name { private set; get; }
        public string Publisher { private set; get; }
        public DateTime Date { private set; get; }

        public Book(string aut, string name, string publ, DateTime date)
        {
            Author = aut;
            Name = name;
            Publisher = publ;
            Date = date;
        }
    }
}
