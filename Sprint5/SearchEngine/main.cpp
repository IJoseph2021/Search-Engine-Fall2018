#include <iostream>
#include "StemmerFiles/porter2_stemmer.h"
#include "avltree.h"
#include "word.h"
#include <iostream>

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

    tree.clear();
    tree.printInOrder(cout);
}

void stem(string& toStem)
{
    Porter2Stemmer::stem(toStem);
}

void testWord()
{
    string mark = "Mark";
    string fonty = "Fontenot";
    string fileName = "file";
    word tester(mark, fonty, fileName);
    cout << tester;

    tester.addDoc("file2");
    cout << tester;

    tester.addDoc("file2");
    cout << tester;

    docu testDoc("file3");
    docu testDoc2("file3");
    tester.addDoc(testDoc);
    cout << tester;
    tester.addDoc(testDoc2);
    cout << tester;

    word tester2("Mark", "Fontenot", "file4");
    cout << tester2;

    tester = tester + tester2;
    cout << tester;

}

int main(int argc, char* argv[])
{
    /*cout << "Testing stemmer:" << endl;
    string toStem = "crackalacking";
    stem(toStem);
    cout << toStem << endl;

    cout << "\nTesting tree:" << endl;
    testTree();*/
    testWord();
    return 0;
}
