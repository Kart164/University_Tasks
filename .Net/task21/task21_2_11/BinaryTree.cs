using System;
using System.Collections.Generic;
using System.Text;

namespace task21_2_11
{
    public class BinaryTree	//класс, реализующий АТД «дерево бинарного поиска со счетчиком вершин в дереве»
    {
        //вложенный класс, отвечающий за узлы и операции допустимы для дерева бинарного
        //поиска
        private class Node
        {
            public object inf;	//информационное поле
            public int counter;
            public Node left;	//ссылка на левое поддерево
            public Node rigth;	//ссылка на правое поддерево

            //конструктор вложенного класса, создает узел дерева
            public Node(object nodeInf)
            {
                inf = nodeInf;
                counter = 1;
                left = null;
                rigth = null;
            }

            //добавляет узел в дерево так, чтобы дерево оставалось деревом бинарного поиска
            public static void Add(ref Node r, object nodeInf)
            {
                if (r == null)
                {
                    r = new Node(nodeInf);
                }
                else
                {
                    r.counter++;
                    if (((IComparable)(r.inf)).CompareTo(nodeInf) > 0)
                    {
                        Add(ref r.left, nodeInf);
                    }
                    else
                    {
                        Add(ref r.rigth, nodeInf);
                    }
                }
            }

            public static void Preorder(Node r)	//прямой обход дерева
            {
                if (r != null)
                {
                    Console.Write("({0}, {1}) ", r.inf, r.counter);
                    Preorder(r.left);
                    Preorder(r.rigth);
                }
            }

            public static void Inorder(Node r)	//симметричный обход дерева
            {
                if (r != null)
                {
                    Inorder(r.left);
                    Console.Write("({0}, {1}) ", r.inf, r.counter);
                    Inorder(r.rigth);
                }
            }

            public static void Postorder(Node r)	//обратный обход дерева
            {
                if (r != null)
                {
                    Postorder(r.left);
                    Postorder(r.rigth);
                    Console.Write("({0}, {1}) ", r.inf, r.counter);
                }
            }


            public static void Part(ref Node t, int k)
            {
                int x = (t.left == null) ? 0 : t.left.counter;
                if (x > k)
                {
                    Part(ref t.left, k);
                    RotationRigth(ref t);
                    //Console.WriteLine("Ротация вправо");
                }
                if (x < k)
                {
                    Part(ref t.rigth, k - x - 1);
                    //Console.WriteLine("Ротация влево");
                    RotationLeft(ref t);
                }
                //if (x == k) Console.WriteLine("Выбран элемент ({0}, {1})", t.inf, t.counter); 
            }



            public static void Balancer(ref Node t)
            {
                if (t == null || t.counter == 1) return;
                Part(ref t, t.counter / 2);
                //Preorder(t);
                //Console.WriteLine();
                Balancer(ref t.left);
                Balancer(ref t.rigth);

            }

            //неявная балансировка дерева бинарного поиска
            public static void InsertRandom(ref Node r, object nodeInf, Random rnd)
            {
                if (r == null)
                {
                    r = new Node(nodeInf);
                }
                else
                {
                    if (rnd.Next() < int.MaxValue / (r.counter + 1))
                    {
                        InsertToRoot(ref r, nodeInf);
                    }
                    else
                    {
                        r.counter++;
                        if (((IComparable)(r.inf)).CompareTo(nodeInf) > 0)
                        {
                            InsertRandom(ref r.left, nodeInf, rnd);
                        }
                        else
                        {
                            InsertRandom(ref r.rigth, nodeInf, rnd);
                        }
                    }
                }
            }

            //поиск ключевого узла в дереве
            public static void Search(Node r, object key, out Node item)
            {
                if (r == null)
                {
                    item = null;
                }
                else
                {
                    if (((IComparable)(r.inf)).CompareTo(key) == 0)
                    {
                        item = r;
                    }
                    else
                    {
                        if (((IComparable)(r.inf)).CompareTo(key) > 0)
                        {
                            Search(r.left, key, out item);
                        }
                        else
                        {
                            Search(r.rigth, key, out item);
                        }
                    }
                }
            }

            //самоорганизующийся поиск ключевого узла в дереве
            public static void SearchToRoot(ref Node r, object key)
            {
                if (r != null)
                {
                    if (((IComparable)(r.inf)).CompareTo(key) == 0)
                    {
                        return;
                    }
                    else
                    {
                        if (((IComparable)(r.inf)).CompareTo(key) > 0)
                        {
                            SearchToRoot(ref r.left, key);
                            RotationRigth(ref r);

                        }
                        else
                        {
                            SearchToRoot(ref r.rigth, key);
                            RotationLeft(ref r);
                        }
                    }
                }
            }

            public static void Count(ref Node r)
            {
                r.counter = 1;
                if (r.left != null) r.counter += r.left.counter;
                if (r.rigth != null) r.counter += r.rigth.counter;
            }

            public static void RotationRigth(ref Node t)
            {
                Node x = t.left;
                t.left = x.rigth;
                x.rigth = t;

                Count(ref t);
                Count(ref x);

                t = x;


            }

            public static void RotationLeft(ref Node t)
            {
                Node x = t.rigth;
                t.rigth = x.left;
                x.left = t;

                Count(ref t);
                Count(ref x);

                t = x;


            }

            public static void InsertToRoot(ref Node t, object item)
            {
                if (t == null)
                {
                    t = new Node(item);
                }
                else
                {
                    t.counter++;
                    if (((IComparable)(t.inf)).CompareTo(item) > 0)
                    {
                        InsertToRoot(ref t.left, item);
                        RotationRigth(ref t);
                    }
                    else
                    {
                        InsertToRoot(ref t.rigth, item);
                        RotationLeft(ref t);
                    }
                }
            }
            private static void Del(Node t, ref Node tr)
            {
                if (tr.rigth != null)
                {
                    Del(t, ref tr.rigth);
                }
                else
                {
                    t.inf = tr.inf;
                    tr = tr.left;
                }
            }
            public static void Delete(ref Node t, object key)
            {
                if (t == null)
                {
                    throw new Exception("Данное значение в дереве отсутствует");
                }
                else
                {
                    if (((IComparable)(t.inf)).CompareTo(key) > 0)
                    {
                        Delete(ref t.left, key);
                    }
                    else
                    {
                        if (((IComparable)(t.inf)).CompareTo(key) < 0)
                        {
                            Delete(ref t.rigth, key);
                        }
                        else
                        {
                            if (t.left == null)
                            {
                                t = t.rigth;
                            }
                            else
                            {
                            if (t.rigth == null)
                                {
                                    t = t.left;
                                }
                                else
                                {
                                    Del(t, ref t.left);
                                }
                            }
                        }
                    }
                }
            }

            public static void HelpFunc(Node r)// функция для прохода по дереву и дальнейшему удалению нужного листа
            {
                if (r.counter>2)
                {
                    if (r.left.counter >= r.rigth.counter)
                    {
                        if (r.counter <= 3)
                        {
                            if (r.left != null & r.rigth != null)
                            {
                                Console.WriteLine("число для удаления {0}", r.rigth.inf);
                                Delete(ref r, r.rigth.inf);
                                r.counter--;
                            }
                            else
                            {
                                if (r.left == null)
                                {
                                    Console.WriteLine("число для удаления {0}", r.rigth.inf);
                                    Delete(ref r, r.rigth.inf);
                                    r.counter--;
                                }
                                else
                                {
                                    Console.WriteLine("число для удаления {0}", r.left.inf);
                                    Delete(ref r, r.left.inf);
                                    r.counter--;
                                }
                            }
                        }
                        else HelpFunc(r.left);
                    }
                    else if (r.rigth.counter > r.left.counter)
                    {
                        if (r.counter <= 3)
                        {
                            if (r.left != null & r.rigth != null)
                            {
                                Console.WriteLine("число для удаления {0}", r.rigth.inf);
                                Delete(ref r, r.rigth.inf);
                                r.counter--;
                            }
                            else
                            {
                                if (r.left == null)
                                {
                                    Console.WriteLine("число для удаления {0}", r.rigth.inf);
                                    Delete(ref r, r.rigth.inf);
                                    r.counter--;
                                }
                                else
                                {
                                    Console.WriteLine("число для удаления {0}", r.left.inf);
                                    Delete(ref r, r.left.inf);
                                    r.counter--;
                                }
                            }

                        }
                        else HelpFunc(r.rigth);
                    }
                }
                else
                {
                    
                        if (r.left == null)
                        {
                            Console.WriteLine("число для удаления {0}", r.rigth.inf);
                            Delete(ref r, r.rigth.inf);
                        r.counter--;
                    }
                        else
                        {
                            Console.WriteLine("число для удаления {0}", r.left.inf);
                            Delete(ref r, r.left.inf);
                        r.counter--;
                    }
                    
                }
               
            }
        }		//конец вложенного класса

        Node tree;		//ссылка на корень дерева

        //свойство позволяет получить доступ к значению информационного поля корня дерева 
        public object Inf
        {
            set { tree.inf = value; }
            get { return tree.inf; }
        }

        public int Counter
        {
            get { return tree.counter; }

        }


        public BinaryTree()	//открытый конструктор
        {
            tree = null;
        }

        private BinaryTree(Node r) //закрытый конструктор
        {
            tree = r;
        }

        public void Add(object nodeInf)	//добавление узла в дерево
        {
            Node.Add(ref tree, nodeInf);
        }
        public void Delete(object key)
        {
            Node.Delete(ref tree, key);
        }
        //организация различных способов обхода дерева
        public void Preorder()
        {
            Node.Preorder(tree);
        }

        public void Inorder()
        {
            Node.Inorder(tree);
        }

        public void Postorder()
        {
            Node.Postorder(tree);
        }

        //поиск ключевого узла в дереве
        public BinaryTree Search(object key)
        {
            Node.Search(tree, key, out Node r);
            BinaryTree t = new BinaryTree(r);
            return t;
        }

        //Самоорганизующийся поиск ключевого узла в дереве
        public void SearchToRoot(object key)
        {
            Node.SearchToRoot(ref tree, key);


        }


        public void InsertToRoot(object item)
        {
            Node.InsertToRoot(ref tree, item);
        }


        public void Balancer()
        {
            Node.Balancer(ref tree);

        }
        public void InsertRandom(object nodeInf)
        {
            Random rnd = new Random();
            Node.InsertRandom(ref tree, nodeInf, rnd);
        }








        //работа алгоритма основывается на определении сбалансированного дерева
        //если разница в 2 узла, то он работает и удаляет лист с наиболее густой ветки
        //удаление приоритетно с левой стороны
        public bool Task()
        {
            if (Math.Abs(tree.rigth.counter - tree.left.counter)<=1) 
            {
                Console.WriteLine("дерево сбалансировано");
                return false;
            }
            else
            {
               if(Math.Abs(tree.rigth.counter - tree.left.counter) > 2)
                {
                    Console.WriteLine("сбалансировать удалением одного нельзя");
                    return false;
                }
                if (tree.rigth.counter > tree.left.counter)
                {
                    Node.HelpFunc(tree.rigth);
                    return true;
                }
                else
                {
                    Node.HelpFunc(tree.left);
                    return true;
                }

            }
        }


    }
}
