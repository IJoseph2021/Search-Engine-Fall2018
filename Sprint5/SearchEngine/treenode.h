#ifndef TREENODE_H
#define TREENODE_H

template <typename fontenot>
class TreeNode {
private:
    fontenot data;
    TreeNode<fontenot>* left;
    TreeNode<fontenot>* right;

public:
    fontenot getData();
};

#endif // TREENODE_H
