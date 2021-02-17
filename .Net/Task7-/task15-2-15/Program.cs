using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace task15_2_15
{
    class Program
    {
        static void Main(string[] args)
        {
            var list = new List<Client>();
            using(var filein=new StreamReader(@"C:\test\input.txt"))
            {
                while (filein.Peek() > 1)
                {
                    var  str = filein.ReadLine().Split(' ');
                    list.Add(new Client(str[0], str[1], str[2], int.Parse(str[3]), float.Parse(str[4]), int.Parse(str[5])));
                }
            }
            var result = list.Where(n => n.year == DateTime.Now.Year).OrderBy(n => n.amount).Select(n => n);
            using (var fileout= new StreamWriter(@"C:\test\output.txt"))
            {
                foreach (var item in result)
                {
                    fileout.WriteLine(item.ToString());
                }
            }
            

        }
        public struct Client {
            public string surName;
            public string name;
            public string secondName;
            public int accNumber;
            public float amount;
            public int year;
            public Client(string surName,string name,string secondName,int accNumber,float amount,int year)
            {
                this.surName = surName;
                this.name = name;
                this.secondName = secondName;
                this.accNumber = accNumber;
                this.amount = amount;
                this.year = year;
            }
            public override string  ToString()
            {
                string str = $"{this.surName} {this.name} {this.secondName} {this.accNumber} {this.amount} {this.year}";
                return str;
            }

        }

    }
}
