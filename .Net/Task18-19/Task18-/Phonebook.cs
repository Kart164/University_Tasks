using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;

namespace Task18_19
{
    public abstract class Phonebook:IComparable
    {
        public string Name { protected set; get; }
        public string Number { protected set; get; }
        public string Adress { protected set; get; }
        public virtual string Show()
        {
            return $"{Name} {Number} {Adress}";
        }
        public virtual bool IsMatch(string criterion, string compareTo)
        {
            if (criterion.Equals("Name") & Name.Equals(compareTo))
                return true;
            else {
                if (criterion.Equals("Number") & Number.Equals(compareTo))
                    return true;
                else
                    if (criterion.Equals("Adress") & Adress.Equals(compareTo))
                    return true;
                else return false;
            }
        }
        public int CompareTo(object item) 
        {
            Phonebook obj = (Phonebook)item;
            if (Number.Equals(obj.Number))
            {
                return 0;
            }
            else
            {
                if (string.Compare(Number, obj.Number) == 1)
                {
                    return 1;
                }
                else return -1;
            }
        }
    }
}
