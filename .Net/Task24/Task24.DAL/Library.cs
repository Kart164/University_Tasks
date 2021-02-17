using System;
using System.Collections.Generic;
using System.IO;
using Task24.Common;

namespace Task24.DAL
{
    public class Library
    {
        public List<Book> ReadingHall { private set; get; }
        public List<Magazine> Magazines { private set; get; }
        public List<Book> RareBooks { private set; get; }
        public List<Subscription> Subscriptions { private set; get; }
        
        public Library(string path)
        {
            ReadingHall = new List<Book>();
            RareBooks = new List<Book>();
            Magazines = new List<Magazine>();
            Subscriptions = new List<Subscription>();
            using (StreamReader fileIn = new StreamReader(path))
            {
                int type = 0;
                string str;
                while (fileIn.Peek() > 1)
                {
                    Marker:
                    str = fileIn.ReadLine();
                    if (str.Equals("Reading Hall"))
                    {
                        type = 1;
                        goto Marker;
                    }
                    if (str.Equals("Rare Books"))
                    {
                        type = 2;
                        goto Marker;
                    }
                    if (str.Equals("Magazines"))
                    {
                        type = 3;
                        goto Marker;
                    }
                    if (str.Equals("Subscribes"))
                    {
                        type = 4;
                        goto Marker;
                    }
                    if (type == 1)
                    {
                        var str2 = str.Split(",", StringSplitOptions.RemoveEmptyEntries);
                        ReadingHall.Add(new Book(str2[0], str2[1], str2[2], DateTime.Parse("1.1." + str2[3])));
                    }
                    if (type == 2)
                    {
                        var str2 = str.Split(",", StringSplitOptions.RemoveEmptyEntries);
                        RareBooks.Add(new Book(str2[0], str2[1], str2[2], DateTime.Parse("1.1." + str2[3])));
                    }
                    if (type == 3)
                    {
                        var str2 = str.Split(",", StringSplitOptions.RemoveEmptyEntries);
                        Magazines.Add(new Magazine(DateTime.Parse(str2[1]), str2[0]));
                    }
                    if (type == 4)
                    {
                        var str2 = str.Split(",", StringSplitOptions.RemoveEmptyEntries);
                        Subscriptions.Add(new Subscription(str2[1], str2[0], DateTime.Parse(str2[2])));
                    }
                }
            }
        }
        public void AddToReadingHall(Book book)
        {
            ReadingHall.Add(book);
        }
        public void AddToMagazines(Magazine mag)
        {
            Magazines.Add(mag);
        }
        public void AddToRareBooks (Book book)
        {
            RareBooks.Add(book);
        }
        public void AddToSubscriptions(Subscription sub)
        {
            Subscriptions.Add(sub);
        }
        public bool DeleteFromReadingHall(string book)
        {
            Book m = ReadingHall.Find(x => book.Equals(x.Name));
            if (m != default(Book))
            {
                ReadingHall.Remove(m);
                return true;
            }
            else return false;
        }
        public bool DeleteFromMagazines(string mag)
        {
            Magazine m = Magazines.Find(x => mag.Equals(x.Name));
            if (m != default(Magazine))
            {
                Magazines.Remove(m);
                return true;
            }
            else return false;
        }
        public bool DeleteFromRareBooks(string book)
        {
            Book m = RareBooks.Find(x => book.Equals(x.Name));
            if (m != default(Book))
            {
                RareBooks.Remove(m);
                return true;
            }
            else return false;
        }
        public bool DeleteFromSubscriptions(string name, string surname)
        {
            Subscription m = Subscriptions.Find(x => name.Equals(x.Name)&& surname.Equals(x.Surname));
            if (m != default(Subscription))
            {
                Subscriptions.Remove(m);
                return true;
            }
            else return false;
        }
        public List<Book> FindInReadingHall(string aut)
        {
            return ReadingHall.FindAll(x => x.Author.Equals(aut));
        }
        public List<Book> FindInRareBooks(string aut)
        {
            return RareBooks.FindAll(x => x.Author.Equals(aut));
        }
        public List<Book> FindInBothFunds(string aut)
        {
            var res = FindInReadingHall(aut);
            res.AddRange(FindInRareBooks(aut));
            return res;
        }
    }
}
