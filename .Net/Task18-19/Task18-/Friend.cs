using System;
using System.Collections.Generic;
using System.Text;

namespace Task18_19
{
    public class Friend:Phonebook
    {
        public DateTime DOB { private set; get; }
        public Friend(string name,string number, string adress, DateTime dob)
        {
            Name = name;
            Number = number;
            Adress = adress;
            DOB = dob;
        }
        public override string Show()
        {
            return base.Show()+$" {DOB.ToShortDateString()}";
        }
        public override bool IsMatch(string criterion, string compareTo)
        {
            if (base.IsMatch(criterion, compareTo))
                return true;
            else if (criterion.Equals("DOB"))
                if (DateTime.Parse(compareTo).Equals(DOB))
                    return true;
                else return false;
            else return false;
        }
    }
}
