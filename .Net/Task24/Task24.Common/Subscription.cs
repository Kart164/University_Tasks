using System;
using System.Collections.Generic;
using System.Text;

namespace Task24.Common
{
    public class Subscription
    {
        public string Name { private set; get; }
        public string Surname { private set; get; }
        public DateTime Date { private set; get; }
        public List<AbstractBook> Books { private set; get; }
        public Subscription(string name, string surname, DateTime date)
        {
            Name = name;
            Surname = surname;
            Date = date;
            Books = new List<AbstractBook>();
        }
    }
    
}
