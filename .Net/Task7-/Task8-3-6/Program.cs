using System;
using System.Text;

namespace Task8_3_6
{
    class Program
    {
        static void Main(string[] args)
        {
            //Удалить из сообщения все слова, содержащие данный символ (без учета регистра).
            //Eyes like a car crash, I know I shouldn't look, but I can't turn away.
            Console.Write("enter string:");
            var str = Console.ReadLine();
            str = str.ToLower();
            Console.Write("enter char:");
            char symb = char.Parse(Console.ReadLine());
            var words = str.Split(' ','.',',','!');
            int n = words.Length;
            
            for (int i = 0; i < n; i++)
            {
                if (words[i].IndexOf(symb) != -1 || words[i]==" " || words[i] == "")
                {
                    for (int j = i; j < n-1; j++)
                    {
                        words[j] = words[j + 1];
                    }
                    n--;
                    i--;
                }
            }
            Console.WriteLine("result:");
            for (int i = 0; i < n; i++)
            {
                Console.Write($"{words[i]} ");
            }
        }
    }
}
