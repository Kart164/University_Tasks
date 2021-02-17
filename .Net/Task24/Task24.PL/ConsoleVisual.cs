using System;
using System.Collections.Generic;
using System.IO;
using Task24.BLL;
using Task24.Common;

namespace Task24.PL
{
    public class ConsoleVisual
    {
        public LibraryManager Manager { private set; get; }
        public string path2 { private set; get; }

        public ConsoleVisual(string path,string path2)
        {
            this.path2 = path2;
            Manager = new LibraryManager(path);
        }



        public void Menu()
        {
            
            Console.WriteLine("a. Add book to Reading hall");
            Console.WriteLine("b. Add book to Rare books");
            Console.WriteLine("c. Add magazine to Magazines");
            Console.WriteLine("d. Add subscribe to Subscribes");
            Console.WriteLine("e. Find books of author in Reading Hall");
            Console.WriteLine("f. Find books of author in Rare Books");
            Console.WriteLine("g. Find books of author in both funds");
            Console.WriteLine("h. Delete book from Reading Hall");
            Console.WriteLine("i. Delete book from Rare Books");
            Console.WriteLine("j. Delete magazine from Magazines");
            Console.WriteLine("k. Delete subscribe from Subscribes");
            Console.WriteLine("l. Print catalog");
            Console.WriteLine("m. Print Reading Hall fund");
            Console.WriteLine("n. Print Rare Books fund");
            Console.WriteLine("o. Print Magazines fund");
            Console.WriteLine("p. Print Subscribes fund");
            Console.WriteLine("q. Exit");
            Console.WriteLine("enter symb:" );
            var input = Console.ReadLine();
            switch (input)
            {
                case "a":
                    var book = CreateBook();
                    if (book != null)
                    {
                        Manager.AddToReadingHall(book);
                    }
                    Menu();
                    break;
                case "b":
                    book = CreateBook();
                    if (book != null)
                    {
                        Manager.AddToRareBooks(book);
                    }
                    Menu();
                    break;
                case "c":
                    var mag = CreateMagazine();
                    if (mag!=null)
                    {
                        Manager.AddToMagazines(mag);
                    }
                    Menu();
                    break;
                case "d":
                    var sub = CreateSubscription();
                    if (sub != null)
                    {
                        Manager.AddToSubscriptions(sub);
                    }
                    Menu();
                    break;
                case "e":
                    Console.WriteLine("enter author or exit");
                    var aut = Console.ReadLine();
                    if (!aut.Equals("exit"))
                    {
                        foreach (var item in Manager.FindInReadingHall(aut))
                        {
                            Console.WriteLine($"{item.Author} {item.Name} {item.Publisher} {item.Date.Year}");
                        }
                    }
                    Menu();
                    break;
                case "f":
                    Console.WriteLine("enter author or exit");
                    aut = Console.ReadLine();
                    if (!aut.Equals("exit"))
                    {
                        foreach(var item in Manager.FindInRareBooks(aut))
                        {
                            Console.WriteLine($"{item.Author} {item.Name} {item.Publisher} {item.Date.Year}");
                        }
                    }
                    Menu();
                    break;
                case "g":
                    Console.WriteLine("enter author or exit");
                    aut = Console.ReadLine();
                    if (!aut.Equals("exit"))
                    {
                        foreach (var item in Manager.FindInBothFunds(aut))
                        {
                            Console.WriteLine($"{item.Author} {item.Name} {item.Publisher} {item.Date.Year}");
                        }
                    }
                    Menu();
                    break;
                case "h":
                    Console.WriteLine("enter name of the book or exit");
                    var name = Console.ReadLine();
                    if (!name.Equals("exit"))
                        if (Manager.DeleteFromReadingHall(name))
                            Console.WriteLine("deleted");
                        else Console.WriteLine("no matches");
                    Menu();
                    break;
                case "i":
                    Console.WriteLine("enter name of the book or exit");
                    name = Console.ReadLine();
                    if (!name.Equals("exit"))
                        if (Manager.DeleteFromRareBooks(name))
                            Console.WriteLine("deleted");
                        else Console.WriteLine("no matches");
                    Menu();
                    break;
                case "j":
                    Console.WriteLine("enter name of the magazine or exit");
                    name = Console.ReadLine();
                    if (!name.Equals("exit"))
                        if (Manager.DeleteFromMagazines(name))
                            Console.WriteLine("deleted");
                        else Console.WriteLine("no matches");
                    Menu();
                    break;
                case "k":
                    Console.WriteLine("enter surname of the subscriber or exit");
                    var surname = Console.ReadLine();
                    if (!surname.Equals("exit")) {
                        Console.WriteLine("write name of the subscriber");
                        name = Console.ReadLine();
                        if (Manager.DeleteFromSubscriptions(name,surname))
                            Console.WriteLine("deleted");
                        else Console.WriteLine("no matches");
                    }
                    Menu();
                    break;
                case "l":
                    PrintCatalog();
                    Menu();
                    break;
                case "m":
                    PrintReadingHall();
                    Menu();
                    break;
                case "n":
                    PrintRareBooks();
                    Menu();
                    break;
                case "o":
                    PrintMagazines();
                    Menu();
                    break;
                case "p":
                    PrintSubscriptions();
                    Menu();
                    break;
                case "q":
                    Exit();
                    break;
                default:
                    Menu();
                    break;
            }
        }
        private Book CreateBook()
        {
            Console.WriteLine("write author (Pushkin A.S.) or write exit:");
            string author = Console.ReadLine();
            if (!author.Equals("exit"))
            {
                Console.WriteLine("write book name:");
                string name = Console.ReadLine();
                Console.WriteLine("write publisher");
                string publisher = Console.ReadLine();
                Console.WriteLine("write year of publishing");
                string year = "1.1." + Console.ReadLine();
                return new Book(author, name, publisher, DateTime.Parse(year));
            }
            else return default(Book);
        }
        private Magazine CreateMagazine()
        {
            Console.WriteLine("write name of a magazine or write exit");
            string name = Console.ReadLine();
            if (!name.Equals("exit"))
            {
                Console.WriteLine("enter the date of publishing (12.10.2017 for example)");
                var date = DateTime.Parse(Console.ReadLine());
                return new Magazine(date, name);
            }
            else return default(Magazine);
        }
        private Subscription CreateSubscription()
        {
            Console.WriteLine("write Surname or exit");
            string surname = Console.ReadLine();
            if (!surname.Equals("exit"))
            {
                Console.WriteLine("enter name");
                string name = Console.ReadLine();
                return new Subscription(name, surname, DateTime.Now);
            }
            else return default(Subscription);
        }
        private void PrintCatalog()
        {
            Console.WriteLine("Reading Hall:");
            PrintReadingHall();
            Console.WriteLine("Rare Books:");
            PrintRareBooks();
            Console.WriteLine("Magazines:");
            PrintMagazines();
            Console.WriteLine("Subscriptions:");
            PrintSubscriptions();
        }
        private void PrintReadingHall()
        {
            foreach (var item in Manager.GetReadingHall())
            {
                Console.WriteLine($"{item.Author} {item.Name} {item.Publisher} {item.Date.Year}");
            }
        }
        private void PrintRareBooks()
        {
            foreach (var item in Manager.GetRareBooks())
            {
                Console.WriteLine($"{item.Author} {item.Name} {item.Publisher} {item.Date.Year}");
            }
        }
        private void PrintMagazines()
        {
            foreach(var item in Manager.GetMagazines())
            {
                Console.WriteLine($"{item.Name} {item.Date.ToShortDateString()}");
            }
        }
        private void PrintSubscriptions()
        {
            foreach (var item in Manager.GetSubscriptions())
            {
                Console.WriteLine($"{item.Surname} {item.Name} {item.Date.ToShortDateString()}");
            }
        }
        private void Exit()
        {
            
            using (StreamWriter fileout = new StreamWriter(path2))
            {
                fileout.WriteLine("Reading Hall");
                foreach (var item in Manager.GetCatalog().ReadingHall)
                {
                    fileout.WriteLine($"{item.Author},{item.Name},{item.Publisher},{item.Date.Year}");
                }
                fileout.WriteLine("Rare Books");
                foreach (var item in Manager.GetCatalog().RareBooks)
                {
                    fileout.WriteLine($"{item.Author},{item.Name},{item.Publisher},{item.Date.Year}");
                }
                fileout.WriteLine("Magazines");
                foreach (var item in Manager.GetCatalog().Magazines)
                {
                    fileout.WriteLine($"{item.Name},{item.Date.ToShortDateString()}");
                }
                fileout.WriteLine("Subscribes");
                foreach (var item in Manager.GetCatalog().Subscriptions)
                {
                    fileout.WriteLine($"{item.Surname},{item.Name},{item.Date.ToShortDateString()}");
                }
            }
        }
    }
}
