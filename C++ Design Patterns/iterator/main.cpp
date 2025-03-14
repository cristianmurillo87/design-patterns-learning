/*
 * Iterator Design Pattern
 *
 * The Iterator pattern provides a way to access the elements of an
 * aggregate object sequentially without exposing its underlying representation.
 * It is useful for traversing collections of objects.
 * In this example, the BinaryTree class uses the Iterator pattern to traverse 
 * the nodes of a binary tree in pre-order.
 */

#include <iostream>
#include <vector>

template<typename T>
struct BinaryTree;

template<typename T> 
struct Node
{
    T value = T();
    Node<T> *left {nullptr}, *right{nullptr}, *parent{nullptr};
    BinaryTree<T>* tree{nullptr};

    Node(T value)
        : value(value) {}

    Node(T value, Node<T>* left, Node<T>* right)
        : value(value), left(left), right(right)
    {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }

    void set_tree(BinaryTree<T> *t)
    {
        tree = t;
        if(left) left->set_tree(t);
        if(right) right->set_tree(t);
    }

    ~Node()
    {
        if(left) delete left;
        if(right) delete right;
    }
};

template<typename T>
struct BinaryTree
{
    Node<T>* root{nullptr};

    BinaryTree(Node<T>* root)
        : root(root), pre_order(*this)
    {
        root->set_tree(this);
    }

    ~BinaryTree()
    {
        if(root) delete root;
    }

    template<typename U>
    struct PreOrderIterator
    {
        Node<U>* current;

        PreOrderIterator(Node<U>* current)
            : current(current) {}

        bool operator!=(const PreOrderIterator<U>& other)
        {
            return current != other.current;
        }

        PreOrderIterator<U>& operator++()
        {
            if(current->right)
            {
                current = current->right;
                while(current->left)
                    current = current->left;
            }
            else
            {
                Node<T>* p = current->parent;
                while(p && current == p->right)
                {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        Node<U>& operator*() { return *current; }
    };

    typedef PreOrderIterator<T> iterator;

    iterator begin()
    {
        Node<T>* n = root;
        if(n)
            while(n->left)
                n = n->left;
        return iterator{n};
    }

    iterator end()
    {
        return iterator{nullptr};
    }

    class PreOrderTreeTraversal
    {
        BinaryTree<T>& tree;
    public:
        PreOrderTreeTraversal(BinaryTree<T>& tree)
            : tree(tree) {}

        iterator begin() { return tree.begin(); }
        iterator end() { return tree.end(); }
    } pre_order;

};

int main()
{
    BinaryTree<std::string> family{
        new Node<std::string>{"me",
            new Node<std::string>{"mother",
                new Node<std::string>{"mother's mother"},
                new Node<std::string>{"mother's father"}
            },
            new Node<std::string>{"father"}
        }
    };

    for(auto it = family.begin(); it != family.end(); ++it)
    {
        std::cout << (*it).value << "\n";
    }
    std::cout << std::endl;
    
    return 0;
}