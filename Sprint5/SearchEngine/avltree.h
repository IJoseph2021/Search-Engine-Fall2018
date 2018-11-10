//owner: patrick
#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

using namespace std;
template <typename fontenot>
class AVLTree {
private:
    template<typename T>
    class TreeNode
    {
    public:
        fontenot data;
        TreeNode<T>* left;
        TreeNode<T>* right;
        int height;

        TreeNode(): left(nullptr), right(nullptr), height(0){}
        TreeNode(T val): data(val), left(nullptr), right(nullptr), height(0){}
        TreeNode(T val, TreeNode* l, TreeNode* r): data(val), left(l), right(r)
        {
            if (left->height > right->height)
            {
                height = left->height+1;
            }
            else
            {
                height = right->height+1;
            }
        }

    };

    TreeNode<fontenot>* root;

public:
    AVLTree():root(nullptr){}
    AVLTree(const AVLTree<fontenot>& rhs);
    AVLTree operator=(const AVLTree<fontenot>& val);
    ~AVLTree();
    void printInOrder(ostream &out);
    void insert(const fontenot& val);

private:
    void printInOrder(ostream& out, TreeNode<fontenot>* t);
    void insert(const fontenot& val, TreeNode<fontenot> *& t);
    void rotateWithLeftChild(TreeNode<fontenot>*& k2);
    void doubleWithLeftChild(TreeNode<fontenot>*& k3);
    void rotateWithRightChild(TreeNode<fontenot>*& k2);
    void doubleWithRightChild(TreeNode<fontenot>*& k3);
    int max(int l, int r);
    int height(TreeNode<fontenot> *t);
};

template<typename fontenot>
AVLTree<fontenot>::AVLTree(const AVLTree<fontenot>& rhs)
{
    root = nullptr;
    *this = rhs;
}

template<typename fontenot>
AVLTree<fontenot>::~AVLTree()
{

}

template<typename fontenot>
void AVLTree<fontenot>::printInOrder(ostream& out)
{
    printInOrder(out, root);
}

template<typename fontenot>
void AVLTree<fontenot>::insert(const fontenot &val)
{
    insert(val, root);
}

template <typename fontenot>
void AVLTree<fontenot>::printInOrder(ostream &out, TreeNode<fontenot>* t)
{
    if (t != nullptr)
    {
        if (t->left != nullptr)
            printInOrder(out, t->left);

        out << t->data << endl;

        if (t->right != nullptr)
            printInOrder(out, t->right);
    }
}


template<typename fontenot>
void AVLTree<fontenot>::insert(const fontenot& val, TreeNode<fontenot> *& t)
{
    if (t == nullptr)
    {
        t = new TreeNode<fontenot>(val);
    }
    else if(val < t->data)
    {
        insert(val, t->left);
        if (height(t->left) - height(t->right)== 2)
        {
            if (val < t->left->data)
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
    }
    else if (val > t->data)
    {
        insert(val, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
            if (val > t->right->data)
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
    }
    else
    {
        t->data = t->data + val;
    }

    t->height = max(height(t->left), height(t->right)) + 1;
}

template <typename fontenot>
void AVLTree<fontenot>::rotateWithLeftChild(TreeNode<fontenot> *& k2)
{
    TreeNode<fontenot>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k2)) + 1;
    k2 = k1;
}

template <typename fontenot>
void AVLTree<fontenot>::doubleWithLeftChild(TreeNode<fontenot> *&k3)
{
    rotateWithRightChild(k3->right);
    rotateWithLeftChild(k3);
}

template <typename fontenot>
void AVLTree<fontenot>::rotateWithRightChild(TreeNode<fontenot> *& k2)
{
    TreeNode<fontenot>* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), height(k2)) + 1;
    k2 = k1;
}

template <typename fontenot>
void AVLTree<fontenot>::doubleWithRightChild(TreeNode<fontenot> *&k3)
{
    rotateWithLeftChild(k3->left);
    rotateWithRightChild(k3);
}

template <typename fontenot>
int AVLTree<fontenot>::max(int l, int r)
{
    {
        if (l > r)
            return l;
        else
            return r;
    }
}

template <typename fontenot>
int AVLTree<fontenot>::height(TreeNode<fontenot> *t)
{
    if (t == nullptr)
        return -1;
    else
        return t->height;
}

#endif // AVLTREE_H
