#include <iostream>
<<<<<<< HEAD
#include "StemmerFiles/porter2_stemmer.h"
=======
#include "avltree.h"

>>>>>>> feature/indexer-Data-Structures
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

void stem(string& toStem)
{
    Porter2Stemmer::stem(toStem);
}

int main(int argc, char* argv[])
{
    string toStem = "crackalacking";
    stem(toStem);
    cout << toStem << endl;
    cout << "Hello World!" << endl;
    testTree();
    return 0;
}
