//owner: patrick

//Edited 11/17/18 by Nathan Srirama
//       Fixed Tree balancing, case 2 and 3 did not work correctly
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
            else{
                height = 0;
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
    void insert(fontenot& val);
    void clear();
    fontenot& findMin();
    fontenot& findMax();
    bool contains(fontenot val);
    void remove(fontenot val);
    fontenot& find(fontenot val);
    int returnNumberNodes();

private:
    void printInOrder(ostream& out, TreeNode<fontenot>* t);
    void insert(fontenot &val, TreeNode<fontenot> *& t);
    void rotateWithLeftChild(TreeNode<fontenot>*& k2);
    void doubleWithLeftChild(TreeNode<fontenot>*& k3);
    void rotateWithRightChild(TreeNode<fontenot>*& k2);
    void doubleWithRightChild(TreeNode<fontenot>*& k3);
    int max(int l, int r);
    int height(TreeNode<fontenot> *t);
    bool contains(TreeNode<fontenot>*&t, fontenot& val);
    void remove(TreeNode<fontenot>*& toRemove);
    TreeNode<fontenot>& find(fontenot &val, TreeNode<fontenot> *t);
    AVLTree<fontenot>::TreeNode<fontenot> *copyNodes(TreeNode<fontenot> *t);
    void clear(TreeNode<fontenot>*& t);
};

template <typename fontenot>
void AVLTree<fontenot>::clear(TreeNode<fontenot>*& t){
    if(t!=nullptr){
        clear(t->left);
        clear(t->right);
        delete t;
    }
    t= nullptr;
}

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
    //only delete root because nodes delete all descendants
    clear();
    /*delete root;
    root = nullptr;*/
    nodes = 0;
}

//print items of a tree in orer
template<typename fontenot>
void AVLTree<fontenot>::printInOrder(ostream& out)
{
    if (root != nullptr)
        printInOrder(out, root);
    else
        throw logic_error("Empty tree in AVLtree:printInOrder");
}

//public insert which calls private recursive insert algorithm
//then increments node counter
template<typename fontenot>
void AVLTree<fontenot>::insert(fontenot &val)
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

//print items of tree in order by recursively calling with left trees
//then printing, then recursively calling with right trees
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

//find where passed value should go by desending the tree via
//recursive calls in the appropriate direction, then checking balance
//and rebalancing as the recursion stack is popped
template<typename fontenot>
void AVLTree<fontenot>::insert(fontenot& val, TreeNode<fontenot> *& t)
{
    //if no value at current node, create node at that point
    if (t == nullptr)
    {
        /*TreeNode<fontenot>* temp = new TreeNode<fontenot>(val);
        t = temp;
        delete temp;*/
        t = new TreeNode<fontenot>(val);
    }
    //if the item already exists in the tree combine it into the existing item
    //this is implemented for the sake of the word class to track duplicate words
    //number of appearances in each document
    else if(val == t->data)
    {
        t->data = t->data + val;
    }

    //if the passed value is less than the value of the current node's data
    else if(val < t->data)
    {
        //descend tree left
        insert(val, t->left);

        //check if balanced at node, if not then balance
        if (height(t->left) - height(t->right)== 2)
        {
            if (val < t->left->data)
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
    }
    //if passed value is greater than the value of the current node's data
    else
    {
        //descend right
        insert(val, t->right);

        //check if balanced, if not then balance
        if (height(t->right) - height(t->left) == 2)
        {
            if (val > t->right->data)
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
    }
    //find new height of node
    t->height = max(height(t->left), height(t->right)) + 1;
}

//rotate with left child balances a tree around an alpha k2 that
//is unbalanced in a case 1 scecnario
template <typename fontenot>
void AVLTree<fontenot>::rotateWithLeftChild(TreeNode<fontenot> *& k2)
{
    //create k1 node to track left item of k2
    TreeNode<fontenot>* k1 = k2->left;

    //swap pointers appropriately
    k2->left = k1->right;
    k1->right = k2;

    //readjust heights
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;         //max(height(k1->left), height(k2)) + 1

    //replace k2 with final k1 node
    k2 = k1;
}

//double with left child solves a case 2 at alpha k3 by first rotating its right
//tree with its right child, creating a case 1, then rotating alpha with its left child
template <typename fontenot>
void AVLTree<fontenot>::doubleWithLeftChild(TreeNode<fontenot> *&k3)
{
    rotateWithRightChild(k3->left);       //rotateWithRightChild(k3->right)
    rotateWithLeftChild(k3);
}

//rotate with right child solves case 4 by rotating alpha k2 with its right child
template <typename fontenot>
void AVLTree<fontenot>::rotateWithRightChild(TreeNode<fontenot> *& k2)
{
    TreeNode<fontenot>* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), height(k1->left)) + 1;            //max(height(k1->right), height(k2)) + 1
    k2 = k1;
}

//double with right child solves case 3 by rotating alpha k3's left child with its left child
//creating a case 4, then solving that by rotating k3 with its right child
template <typename fontenot>
void AVLTree<fontenot>::doubleWithRightChild(TreeNode<fontenot> *&k3)
{
    rotateWithLeftChild(k3->right);         //rotateWithLeftChild(k3->left)
    rotateWithRightChild(k3);
}

//find which of two values is the largest
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

//get the height with precaution for uninitialized nodes
template <typename fontenot>
inline int AVLTree<fontenot>::height(TreeNode<fontenot> *t)
{
    if (t == nullptr)
        return -1;
    else
        return t->height;
}

//find smallest item in the tree by descending all the way left
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

//find largest item in the tree by descending all the way right
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

//public contains function to call private contains function if tree exists
template <typename fontenot>
bool AVLTree<fontenot>::contains(fontenot val)
{
    if (root == nullptr)
        return false;
    else
        return contains(root, val);
}

//private recursive contains which uses binary search to search the avl
//tree for an item and return true if it exists
template <typename fontenot>
bool AVLTree<fontenot>::contains(TreeNode<fontenot> *& t, fontenot &val)
{
    //return that it exists if this node data is the value
    if (t->data == val)
        return true;
    //if value is smaller than node data descend left
    else if (t->data > val)
    {
        if (t->left != nullptr)
            return contains(t->left, val);
        //if the value is smaller than node data but there is no left, return false
        else
            return false;
    }
    //if value is greater than node data descent right
    else if (t->data < val)
    {
        if (t->right != nullptr)
            return contains(t->right, val);
        //if value is larger than node data but there is no rigt, return false
        else
            return false;
    }
    else
    {
        return false;
    }
}

//public remove function to recursively call remove funciton
template <typename fontenot>
void AVLTree<fontenot>::remove(fontenot val)
{
    TreeNode<fontenot>* toRemove = new TreeNode<fontenot>;
    toRemove = find(val, root);
    remove(toRemove);
}

//private remove function which can delete leaves
template <typename fontenot>
void AVLTree<fontenot>::remove(TreeNode<fontenot>*& toRemove)
{
    //if node is a leaf simply delete
    if (toRemove->height == 0)
    {
        delete toRemove;
        return;
    }
    else
    {
        throw logic_error("Not a leaf in AVLTree:remove()");
    }
}

//public find function to call recursive binary search on root and return the foudn item
template <typename fontenot>
fontenot& AVLTree<fontenot>::find(fontenot val)
{
    if (root == nullptr)
    {
        throw logic_error("Value not in tree [in find()]");
    }
    return find(val,root).data;
}

//private search function which binary searches for an item by stepping through the tree using comparisons
//and returning the item it ends on
template <typename fontenot>
AVLTree<fontenot>::TreeNode<fontenot>& AVLTree<fontenot>::find(fontenot& val, TreeNode<fontenot>* t)
{
    //if this is the target value return the node
    if (t->data == val)
        return *t;
    //if the value is less than the current node go left
    else if (t->data > val)
    {
        if (t->left != nullptr)
            return find(val, t->left);
        else
            //if the value is less than the current node but there is no left node throw error
            throw logic_error("Value not in tree [in find()]");
    }
    //if the value is greater than the current node go right
    else if (t->data < val)
    {
        if (t->right != nullptr)
            return find(val, t->right);
       else
            //if the value is greater but there is no right node throw error
            throw logic_error("Value not in tree [in find()]");
    }
}

//copy nodes used for operator= and copy constructor to
//recursively create deep copies of a passed tree's nodes
template <typename fontenot>
AVLTree<fontenot>::TreeNode<fontenot>* AVLTree<fontenot>::copyNodes(TreeNode<fontenot> *t)
{
    //if the node exists
    if (t!= nullptr)
    {
        //create copy of left
        TreeNode<fontenot>* left = copyNodes(t->left);
        //create copy of right
        TreeNode<fontenot>* right = copyNodes(t->right);
        //return the values as a new node
        return new TreeNode<fontenot>(t->data, left, right);
    }
    //if node does not exists return a nullptr
    else
    {
        return nullptr;
    }
}

template <typename fontenot>
int AVLTree<fontenot>::returnNumberNodes(){
    return nodes;
}

#endif // AVLTREE_H
