using System;
using System.Collections.Generic;
using System.Text;

namespace Task18_19
{
    public class Company:Phonebook
    {
        
        public string Fax { private set; get; }
        public Persona Contact { private set; get; }

        public Company(string name,string number,string adress,string fax,Persona contact)
        {
            Name = name;
            Number = number;
            Adress = adress;
            Fax = fax;
            Contact = contact;
        }
        public override string Show()
        {
            return base.Show() + $" {Fax} {Contact.Show()}";
        }
        public override bool IsMatch(string criterion, string compareTo)
        {
            if (base.IsMatch(criterion, compareTo))
                return true;
            else {
                if (criterion.Equals("Fax") & Fax.Equals(compareTo))
                    return true;
                if (Contact.IsMatch(criterion, compareTo))
                    return true;
                else return false;
            }            
        }
    }
}
