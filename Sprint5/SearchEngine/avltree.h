//owner: patrick
#ifndef AVLTREE_H
#define AVLTREE_H

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
    void insert(const fontenot& val, TreeNode<fontenot> *& t);
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
void AVLTree<fontenot>::insert(const fontenot& val, TreeNode<fontenot> *& t)
{
    if (t == nullptr)
    {
        t = new TreeNode<fontenot>(val);
    }
    else if(val < t->data)
    {
        insert(val, t->left);
        if (t->left->height - t->right->height == 2)
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
        if (t->right->height - t->left->height == 2)
        {
            if (val < t->right->data)
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
    }
    else
    {
        t->data = t->data + val;
    }


}
#endif // AVLTREE_H
