#include <iostream>
#include "avltree.h"

using namespace std;
void testTree()
{
    AVLTree<int> tree;
    for (int i = 0; i < 10; i++)
        tree.insert(i);

    tree.printInOrder(cout);
}

int main(int argc, char* argv[])
{
    cout << "Hello World!" << endl;
    testTree();
    return 0;
}
