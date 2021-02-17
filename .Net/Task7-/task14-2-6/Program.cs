using System;
using System.Collections.Generic;
using System.IO;

namespace task14_2_6
{
    class Program
    {
        static void Main(string[] args)
        {
            var list = new List<Item>();
            string str;
            Console.Write("enter n:");
            int n = int.Parse(Console.ReadLine());
            using (var reader = new StreamReader(@"C:\test\input.txt"))
            {
                while (reader.Peek() >= 0)
                {
                    str = reader.ReadLine();
                    var splt = str.Split(" ", StringSplitOptions.RemoveEmptyEntries);
                    list.Add(new Item(splt[0], float.Parse(splt[1]), splt[2], int.Parse(splt[3])));
                }
            }
            list.Sort();
            Item[] items = list.ToArray();
            list.Clear();
            foreach(Item item in items)
            {
                if (item.count < n)
                {
                    list.Add(item);
                }
                else break;
            }
            using (var writer = new StreamWriter(@"C:\test\output.txt"))
            {
                foreach (var item in list)
                {
                    writer.WriteLine($"{item.name} {item.cost} {item.grade} {item.count}");
                }
                
            }
        }
        public struct Item : IComparable<Item>
        {
            public string name;
            public float cost;
            public string grade;
            public int count;
            public Item(string name,float cost,string grade,int count)
            {
                this.name = name;
                this.cost = cost;
                this.grade = grade;
                this.count = count;
            }
            public int CompareTo(Item item)
            {
                if (this.count >= item.count)
                {
                    if (this.count == item.count)
                        return 0;
                    else return 1;
                }
                else return -1;
            }
        }
    }
}
