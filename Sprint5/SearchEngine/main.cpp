#include <iostream>
#include "StemmerFiles/porter2_stemmer.h"
#include "avltree.h"
using namespace std;
void testTree()
{
    AVLTree<int> tree;
    for (int i = 0; i < 10; i++)
        tree.insert(i);

    tree.printInOrder(cout);

    cout << tree.findMin() << endl;
    cout << tree.findMax() << endl << endl;

    cout << tree.contains(5) << endl;
    cout << tree.contains(10) << endl << endl;

    cout << endl;
    AVLTree<int> tree2 = tree;
    tree2.printInOrder(cout);

    cout << endl << tree.find(4) << endl;
    tree.find(4)++;
    tree.printInOrder(cout);

    tree.clear();
    tree.printInOrder(cout);
}

void stem(string& toStem)
{
    Porter2Stemmer::stem(toStem);
}

int main(int argc, char* argv[])
{
    cout << "Testing stemmer:" << endl;
    string toStem = "adjudication";
    stem(toStem);
    cout << toStem << endl;

    cout << "\nTesting tree:" << endl;
    testTree();
    return 0;
}
