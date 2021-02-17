using System;
using System.Collections.Generic;
using System.Text;

namespace Task21_11
{
    public class BinaryTree //класс, реализующий АТД «дерево бинарного поиска»
    {
        //вложенный класс, отвечающий за узлы и операции допустимы для дерева бинарного
        //поиска
        private class Node
        {
            public object inf; //информационное поле
            public Node left; //ссылка на левое поддерево
            public Node rigth; //ссылка на правое поддерево
                               //конструктор вложенного класса, создает узел дерева
            public Node(object nodeInf)
            {
                inf = nodeInf;
                left = null;
                rigth = null;
            }

            public static void Part(ref Node t, int k)
            {
                int x = (t.left == null) ? 0 : t.left.counter;
                if (x > k)
                {
                    Part(ref t.left, k);
                    RotationRigth(ref t);
                }
                if (x < k)
                {
                    Part(ref t.rigth, k - x - 1);
                    RotationLeft(ref t);
                }
            }
            public static void Balancer(ref Node t)
            {
                if (t == null || t.counter == 1) return; //если дерево пустое или узел-лист, то
                                                         //балансировка закончена
                Part(ref t, t.counter / 2); //иначе вызываем метод, который помещает к-тый узел в
                                            //корень дерева (к= t.counter / 2)
                                            //затем балансируем левое и правое поддерево
                Balancer(ref t.left);
                Balancer(ref t.rigth);
            }
            public static Node JoinTree(Node a, Node b)
            {
                if (b == null) return a;
                if (a == null) return b;
                InsertToRoot(ref b, a.inf);
                b.left = JoinTree(a.left, b.left);
                b.rigth = JoinTree(a.rigth, b.rigth);
                return b;
            }
            public static void RotationRigth(ref Node t)
            {
                Node x = t.left;
                t.left = x.rigth; //1
                x.rigth = t; //2
                t = x;
            }
            public static void RotationLeft(ref Node t)
            {
                Node x = t.rigth;
                t.rigth = x.left;
                x.left = t;
                t = x;
            }
            public static void InsertToRoot(ref Node t, object item)
            {
                if (t == null)
                {
                    t = new Node(item);
                }
                else if (((IComparable)(t.inf)).CompareTo(item) > 0)
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

            public static bool IsTarget(Node node)
            {
                if (node.rigth != null & node.left != null)
                {
                    return true;
                }
                else return false;
            }
            public static void Task(Node r,List<Node> nodes) //прямой обход дерева
            {
                if (r != null)
                {
                    if (Node.IsTarget(r))
                    {
                        nodes.Add(r);
                    }
                    
                    Task(r.left,nodes);
                    Task(r.rigth,nodes);
                }
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
            
            public static void Preorder(Node r) //прямой обход дерева
            {
                if (r != null)
                {
                    Console.Write("{0} ", r.inf);
                    Preorder(r.left);
                    Preorder(r.rigth);
                }
            }
            public static void Inorder(Node r) //симметричный обход дерева
            {
                if (r != null)
                {
                    Inorder(r.left);
                    Console.Write("{0} ", r.inf);
                    Inorder(r.rigth);
                }
            }
            public static void Postorder(Node r) //обратный обход дерева
            {
                if (r != null)
                {
                    Postorder(r.left);
                    Postorder(r.rigth);
                    Console.Write("{0} ", r.inf);
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
            //методы Del и Delete позволяют удалить узел в дереве так, чтобы дерево при этом
            //оставалось деревом бинарного поиска
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
        } //конец вложенного класса
        Node tree; //ссылка на корень дерева
                   //свойство позволяет получить доступ к значению информационного поля корня дерева
        public object Inf
        {
            set { tree.inf = value; }
            get { return tree.inf; }
        }
        public BinaryTree() //открытый конструктор
        {
            tree = null;
        }
        private BinaryTree(Node r) //закрытый конструктор
        {
            tree = r;
        }
        public void Add(object nodeInf) //добавление узла в дерево
        {
            Node.Add(ref tree, nodeInf);
        }

        public void JoinTree(ref BinaryTree b)
        {
            b = new BinaryTree(Node.JoinTree(this.tree, b.tree));
        }
        public void InsertToRoot(object item)
        {
            Node.InsertToRoot(ref tree, item);
        }
        public float Task()
        {
            float res = 0;
            var nodes = new List<Node>();
            Node.Task(tree, nodes);
            if (nodes.Count > 0)
            {
                foreach (var node in nodes)
                {
                    res += (int)node.inf;
                }
                res=res/nodes.Count;
            }
            return res;
            
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
        Node r;
            Node.Search(tree, key, out r);
            BinaryTree t = new BinaryTree(r);
            return t;
        }
        //удаление ключевого узла в дереве
        public void Delete(object key)
        {
            Node.Delete(ref tree, key);
        }
    }
}
