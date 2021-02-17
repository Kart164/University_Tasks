using System;
using System.Collections.Generic;
using System.Text;

namespace Task18_19
{
    public class Persona:Phonebook
    {
        public Persona(string name,string number, string adress) 
        {
            Name = name;
            Number = number;
            Adress = adress;
        }
        public override string Show()
        {
            return base.Show();
        }
        public override bool IsMatch(string criterion, string compareTo)
        {
            if (base.IsMatch(criterion, compareTo))
                return true;
            else return false;
        }
    }
}
