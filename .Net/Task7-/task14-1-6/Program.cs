using System;

namespace task14_1_6
{
    class Program
    {
        static void Main(string[] args)
        {
            int x, y, z;
            double maxd=-1;
            int k=-1, a=-1;
            SPoint[] mas=new SPoint[10];
            var rand = new Random();
            for (int i = 0; i < 10; i++)
            {
                x = rand.Next(-99, 99);
                y = rand.Next(-99, 99);
                z = rand.Next(-99, 99);
                mas[i] = new SPoint(x, y, z);
            }
            for (int i = 0; i < mas.Length-1; i++)
            {
                for (int j = i+1; j < mas.Length-1; j++)
                {
                    if (mas[i].Distance(mas[j]) > maxd)
                    {
                        maxd = mas[i].Distance(mas[j]);
                        a = i;
                        k = j;
                    }
                }
            }
            if (k != -1 && a != -1)
            {
                mas[a].Print();
                mas[k].Print();
            }
        }
    }
    public struct SPoint
    {
        int x, y, z;
        public SPoint(int x,int y, int z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
        public double Distance(SPoint point)
        {
            return Math.Sqrt((this.x - point.x) * (this.x - point.x) + (this.y - point.y) * (this.y - point.y)
                + (this.z - point.z) * (this.z - point.z));
        }
        public void Print()
        {
            Console.WriteLine($"point: {x} {y} {z}");
        }
    }
}
