using System;
using System.Text.RegularExpressions;
using System.IO;
using System.Collections.Generic;

namespace Task18_19
{
    class Program
    {
        //Regex RegNumber = new Regex(@"(\+)?([0-9]{1,3})?((\([1-9]{2,3}\))|[0-9]{3})?([0-9]{6,8})");

        static void Main(string[] args)
        {
            var list = new List<Phonebook>();
            using (var filein = new StreamReader(new FileStream(@"C:\test\inp.txt", FileMode.Open, FileAccess.Read)))
            {
                string[] tmpmas;
                while (filein.Peek() > 1)
                {
                    var str = filein.ReadLine();
                    
                    if (!str.Equals(null))
                    {
                        tmpmas = str.Split(' ', StringSplitOptions.RemoveEmptyEntries);
                        if (tmpmas.Length == 3)
                        {
                            list.Add(new Persona(tmpmas[0], tmpmas[1], tmpmas[2]));
                        }
                        if (tmpmas.Length == 4)
                        {
                            list.Add(new Friend(tmpmas[0], tmpmas[1], tmpmas[2], DateTime.Parse(tmpmas[3])));
                        }
                        if (tmpmas.Length == 7)
                        {
                            list.Add(new Company(tmpmas[0], tmpmas[1], tmpmas[2], tmpmas[3],
                                new Persona(tmpmas[4], tmpmas[5], tmpmas[6])));
                        }
                    }
                }
            }
            foreach(var item in list)
            {
                Console.WriteLine( item.Show() ); 
            }
            list.Sort();
            Console.WriteLine("Sorted List:");
            foreach (var item in list)
            {
                Console.WriteLine(item.Show());
            }
            Console.WriteLine("enter Name to find:");
            var name = Console.ReadLine();
            var res = Find(name,list);
            using(var fileout= new StreamWriter(new FileStream(@"C:\test\out.txt", FileMode.Create, FileAccess.Write))){
                if (!res.Equals(null))
                {
                    fileout.WriteLine($"{res.Show()}");
                }
                else fileout.WriteLine("no match(");
            }
        }
        static Phonebook Find(string obj,List<Phonebook> list)
        {
            Phonebook result;
            foreach(var item in list)
            {
                if (item.IsMatch("Name", obj))
                {
                    result = item;
                    return result;
                }
            }
            return null;
            
        }
    }
}
