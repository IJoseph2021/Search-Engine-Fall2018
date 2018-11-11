#include <iostream>
#include "avltree.h"

using namespace std;
void testTree()
{
    AVLTree<int> tree;
    for (int i = 0; i < 10; i++)
        tree.insert(i);

    tree.printInOrder(cout);

    cout << tree.findMin() << endl;
    cout << tree.findMax() << endl;

    cout << tree.contains(5) << endl;
    cout << tree.contains(10) << endl;

    AVLTree<int> tree2 = tree;
    tree2.printInOrder(cout);
    tree.clear();
    tree.printInOrder(cout);
}

int main(int argc, char* argv[])
{
    cout << "Hello World!" << endl;
    testTree();
    return 0;
}
