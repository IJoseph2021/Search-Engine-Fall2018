//owner: patrick
#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

using namespace std;
template <typename fontenot>
class AVLTree {
private:
    //templated treeNode class for the tree
    template<typename mark>
    class TreeNode
    {
    //public to the tree only
    public:
        fontenot data;
        TreeNode<mark>* left;
        TreeNode<mark>* right;
        int height;

        TreeNode(): left(nullptr), right(nullptr), height(0){}
        TreeNode(mark val): data(val), left(nullptr), right(nullptr), height(0){}

        //create a tree node from a value and pointers to the nodes to its left and right
        TreeNode(mark val, TreeNode* l, TreeNode* r): data(val), left(l), right(r)
        {
            if (left == nullptr && right != nullptr)
            {
                height = right->height;
            }
            else if (right == nullptr && left != nullptr)
            {
                height = left->height;
            }
            else if (right != nullptr  && left != nullptr)
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
        }

        TreeNode(const TreeNode<mark>& val)
        {
            left = nullptr;
            right = nullptr;
            data = val.data;
            if (val.left != nullptr)
                left = new TreeNode(*val.left);
            if (val.right != nullptr)
                right = new TreeNode(*val.right);
        }

        TreeNode& operator =(const TreeNode<mark>& val)
        {
            data = val.data;

            if (val.left != nullptr)
            {
                TreeNode<mark>* left2 = left;
                left = new TreeNode<mark>(*val.left);
                delete left2;
            }

            if (val.right != nullptr)
            {
                TreeNode<mark>* right2 = right;
                right = new TreeNode<mark>(*val.right);
                delete right2;
            }
            return *this;
        }

        //note that deleting a node will delete all of its descendants
        ~TreeNode()
        {
            if (left != nullptr)
                delete left;
            if (right != nullptr)
                delete right;
        }
    };

    //resume AVLTree class
private:
    //tree root and node counter
    TreeNode<fontenot>* root;
    int nodes;

public:
    AVLTree():root(nullptr), nodes(0){}
    AVLTree(const AVLTree<fontenot>& val);
    AVLTree& operator=(const AVLTree<fontenot>& val);
    ~AVLTree();
    void printInOrder(ostream &out);
    void insert(const fontenot& val);
    void clear();
    fontenot& findMin();
    fontenot& findMax();
    bool contains(fontenot val);
    void remove(fontenot val);
    fontenot& find(fontenot val);

private:
    void printInOrder(ostream& out, TreeNode<fontenot>* t);
    void insert(const fontenot& val, TreeNode<fontenot> *& t);
    void rotateWithLeftChild(TreeNode<fontenot>*& k2);
    void doubleWithLeftChild(TreeNode<fontenot>*& k3);
    void rotateWithRightChild(TreeNode<fontenot>*& k2);
    void doubleWithRightChild(TreeNode<fontenot>*& k3);
    int max(int l, int r);
    int height(TreeNode<fontenot> *t);
    bool contains(TreeNode<fontenot>*&t, fontenot val);
    void remove(TreeNode<fontenot>*& toRemove);
    TreeNode<fontenot>& find(fontenot &val, TreeNode<fontenot> *t);
    AVLTree<fontenot>::TreeNode<fontenot> *copyNodes(TreeNode<fontenot> *t);
};

template<typename fontenot>
AVLTree<fontenot>::AVLTree(const AVLTree<fontenot>& val)
{
    root = copyNodes(val.root);
}

template<typename fontenot>
AVLTree<fontenot>& AVLTree<fontenot>::operator =(const AVLTree<fontenot>& val)
{
     root = copyNodes(val.root);
}

template<typename fontenot>
AVLTree<fontenot>::~AVLTree()
{
    delete root;
    root = nullptr;
}

template<typename fontenot>
void AVLTree<fontenot>::printInOrder(ostream& out)
{
    if (root != nullptr)
        printInOrder(out, root);
    else
        out << "Empty tree" << endl;
}

template<typename fontenot>
void AVLTree<fontenot>::insert(const fontenot &val)
{
    insert(val, root);
    nodes++;
}

template <typename fontenot>
void AVLTree<fontenot>::clear()
{
    delete root;
    root = nullptr;
    nodes = 0;
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

template <typename fontenot>
fontenot& AVLTree<fontenot>::findMin()
{
    TreeNode<fontenot>* temp = root;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }
    return temp->data;
}

template <typename fontenot>
fontenot& AVLTree<fontenot>::findMax()
{
    TreeNode<fontenot>* temp = root;
    while (temp->right != nullptr)
    {
        temp = temp->right;
    }
    return temp->data;
}

template <typename fontenot>
bool AVLTree<fontenot>::contains(fontenot val)
{
    if (root == nullptr)
        return false;
    else
        return contains(root, val);
}

template <typename fontenot>
bool AVLTree<fontenot>::contains(TreeNode<fontenot> *& t, fontenot val)
{
    if (t->data == val)
        return true;
    else if (t->data > val)
    {
        if (t->left != nullptr)
            return contains(t->left, val);
        else
            return false;
    }
    else if (t->data < val)
    {
        if (t->right != nullptr)
            return contains(t->right, val);
        else
            return false;
    }
    else
    {
        return false;
    }
}

template <typename fontenot>
void AVLTree<fontenot>::remove(fontenot val)
{
    TreeNode<fontenot>* toRemove = new TreeNode<fontenot>;
    toRemove = find(val, root);
    remove(toRemove);
}

template <typename fontenot>
void AVLTree<fontenot>::remove(TreeNode<fontenot>*& toRemove)
{
    if (toRemove->height == 0)
    {
        delete toRemove;
        return;
    }
    else if (toRemove->height == 1 && (toRemove->left == nullptr || toRemove->right == nullptr))
    {
        if (toRemove->left == nullptr)
            toRemove = toRemove->right;
        else
            toRemove = toRemove->left;
        return;
    }
}

template <typename fontenot>
fontenot& AVLTree<fontenot>::find(fontenot val)
{
    return find(val,root).data;
}

template <typename fontenot>
AVLTree<fontenot>::TreeNode<fontenot>& AVLTree<fontenot>::find(fontenot& val, TreeNode<fontenot>* t)
{
    if (t->data == val)
        return *t;
    if (t->data > val)
    {
        if (t->left != nullptr)
            return find(val, t->left);
        else
            throw logic_error("Value not in tree [in find()]");
    }
    if (t->data < val)
    {
        if (t->right != nullptr)
            return find(val, t->right);
        else
            throw logic_error("Value not in tree [in find()]");
    }
}

template <typename fontenot>
AVLTree<fontenot>::TreeNode<fontenot>* AVLTree<fontenot>::copyNodes(TreeNode<fontenot> *t)
{
    if (t!= nullptr)
    {
        TreeNode<fontenot>* left = copyNodes(t->left);
        TreeNode<fontenot>* right = copyNodes(t->right);
        return new TreeNode<fontenot>(t->data, left, right);
    }
    else
    {
        return nullptr;
    }

}

#endif // AVLTREE_H
