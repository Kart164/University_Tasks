using System;

namespace task17_5
{
    class Program
    {
        static void Main(string[] args)
        {
            var ex1 = new IntArray(5);
            ex1.FillArray();
            ex1.Print();
            Console.WriteLine();
            //Console.WriteLine(!ex1);
            //ex1.Sort(0,4);
            //ex1.Print();
            //Console.WriteLine();
            //ex1=ex1* 2;
            //Console.WriteLine();
            //ex1.Print();
            //ex1++;
            //Console.WriteLine();
            //ex1.Print();
            //ex1--;
            //Console.WriteLine();
            //ex1.Print();
            //Console.WriteLine();
            var rand = new Random();
            var mas = new int[7];
            for (int i = 0; i < 7; i++)
            {
                mas[i] = rand.Next(0, 99);
                Console.Write($"{mas[i]} ");
            }
            Console.WriteLine();
            IntArray ex2 = mas;
            ex2.Print();
            mas = ex1;
            Console.WriteLine();
            for (int i = 0; i < mas.Length; i++)
            {
                Console.Write($"{mas[i]} ");   
            }
        }
    }
    public class IntArray
    {
        public int[] intArray;
        public int myConst;
        public IntArray(int n)
        {
            intArray = new int[n];
            myConst = 1;
        }
        public IntArray(IntArray x)
        {
            intArray = new int[x.Length];
            x.intArray.CopyTo(this.intArray,0);
            myConst = 1;
        }
        public IntArray(int[] x)
        {
            intArray = new int[x.Length];
            Array.Copy(x, 0, this.intArray,0,x.Length);
        }
        public void FillArray()
        {
            for (int i = 0; i < intArray.Length; i++)
            {
                Console.Write("enter element: ");
                intArray[i] = int.Parse(Console.ReadLine());
            }
        }
        public void Print()
        {
            for (int i = 0; i < intArray.Length; i++)
            {
                Console.Write($"{intArray[i]} ");
            }
        }
        public void Sort(long first,long last)
        {
            int mid = intArray[(last - first) / 2 + first];
            int temp;
            long i = first, j = last;
            while (i <= j)
            {
                while (intArray[i] < mid && i <= last) ++i;
                while (intArray[j] > mid && j >= first) --j;
                if (i <= j)
                {
                    temp = intArray[i];
                    intArray[i] = intArray[j];
                    intArray[j] = temp;
                    ++i; --j;
                }
            }
            if (j > first) Sort(first, j);
            if (i < last) Sort (i, last);
        }

        public int Length { get => intArray.Length; }
        public int Increase { 
            set
            {
                myConst = value;
                for (int i = 0; i < intArray.Length; i++)
                {
                    intArray[i] *= myConst;
                }
            }
        }
        public int this[int i] //индексатор
        {
            get
            {
                if (i < 0 || i >= intArray.Length)
                {
                Console.WriteLine("Индекс {0} выходит за границы массива", i);
                    return 0;
                }
                else
                {
                    return intArray[i];
                }
            }
            set
            {
                if (i < 0 || i >= intArray.Length)
                {
                    Console.WriteLine("Индекс {0} выходит за границы массива", i);
                }
                else
                {
                        intArray[i] = value;
                }
            }
        }

        public static IntArray operator ++(IntArray x)
        {
            var temp = new IntArray(x);
            for (int i = 0; i < x.Length; i++)
            {
                temp[i] = x[i] + 1;
            }
            return temp;
        }
        public static IntArray operator --(IntArray x)
        {
            var temp = new IntArray(x);
            for (int i = 0; i < x.Length; i++)
            {
                temp[i] = x[i] - 1;
            }
            return temp;
        }
        public static IntArray operator *(IntArray x,int My)
        {
            var temp = new IntArray(x);
            temp.myConst = My;
            temp.Increase=temp.myConst;
            return temp;
        }
        public static bool operator !(IntArray x)
        {
            for (int i = 1; i < x.Length; i++)
            {
                if (x[i - 1] > x[i])
                    return false;
            }
            return true;
        }
        public static implicit operator IntArray(int[] a)
        {
            return new IntArray(a);
        }
        public static implicit operator int[] (IntArray x)
        {
            var array = new int[x.Length];
            x.intArray.CopyTo(array, 0);
            return array;
        }
    }
}
