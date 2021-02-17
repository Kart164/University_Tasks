using System;
using System.Collections.Generic;
using Task24.Common;
using Task24.DAL;

namespace Task24.BLL
{
    public class LibraryManager
    {
        private Library Library { get; set; }

        public LibraryManager(string path)
        {
            Library = new Library(path);
        }

        public void AddToReadingHall(Book book)
        {
            Library.AddToReadingHall(book);
        }
        public void AddToMagazines(Magazine mag)
        {
            Library.AddToMagazines(mag);
        }
        public void AddToRareBooks(Book book)
        {
            Library.AddToRareBooks(book);
        }
        public void AddToSubscriptions(Subscription sub)
        {
            Library.AddToSubscriptions(sub);
        }
        public bool DeleteFromReadingHall(string book)
        {
            return Library.DeleteFromReadingHall(book);
        }
        public bool DeleteFromMagazines(string mag)
        {
            return Library.DeleteFromMagazines(mag);
        }
        public bool DeleteFromRareBooks(string book)
        {
            return Library.DeleteFromRareBooks(book);
        }
        public bool DeleteFromSubscriptions(string name, string surname)
        {
            return Library.DeleteFromSubscriptions(name, surname);
        }
        public List<Book> FindInReadingHall(string aut)
        {
            return Library.FindInReadingHall(aut);
        }
        public List<Book> FindInRareBooks(string aut)
        {
            return Library.FindInRareBooks(aut);
        }
        public List<Book> FindInBothFunds(string aut)
        {
            return Library.FindInBothFunds(aut);
        }
        public List<Book> GetReadingHall()
        {
            return Library.ReadingHall;
        }
        public List<Book> GetRareBooks()
        {
            return Library.RareBooks;
        }
        public List<Magazine> GetMagazines()
        {
            return Library.Magazines;
        }
        public List<Subscription> GetSubscriptions()
        {
            return Library.Subscriptions;
        }
        public (List<Book> ReadingHall,List<Book>RareBooks, List<Magazine> Magazines,List<Subscription> Subscriptions) GetCatalog() 
        {
            return (Library.ReadingHall, Library.RareBooks, Library.Magazines, Library.Subscriptions);
        }
    }
}
