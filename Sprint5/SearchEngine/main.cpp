#include <iostream>
#include "StemmerFiles/porter2_stemmer.h"
#include "avltree.h"
#include "word.h"
#include "stopper.h"
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

    cout << endl << tree.find(4) << endl;
    tree.find(4)++;
    tree.printInOrder(cout);

    tree.clear();
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
    cout << tester << endl;

    tester.addDoc("file2");
    cout << tester << endl;

    tester.addDoc("file2");
    cout << tester << endl;

    docu testDoc("file3");
    docu testDoc2("file3");
    tester.addDoc(testDoc);
    cout << tester << endl;
    tester.addDoc(testDoc2);
    cout << tester << endl;

    word tester2("Mark", "Fontenot", "file4");
    tester2.addDoc("file3");
    tester2.addDoc("file5");
    tester2.addDoc("file5");
    cout << tester2 << endl;

    tester = tester + tester2;
    cout << tester << endl;

    word tester3("Charles", "Sriracha", "file3");
    if (tester3 < tester)
        cout << "< Correct" << endl;
}

void testWordTree()
{
    AVLTree<word> data;
    word first("Mark", "Fontenot", "doc1");
    word second("Charles", "Sriracha", "doc1");
    word third("Karaj", "Watkins", "doc1");
    word fourth("Rick", "Devries", "doc1");
    word fifth("Rick", "Devries", "doc1");
    data.insert(fourth);
    data.insert(first);
    data.insert(second);
    data.insert(third);

    data.printInOrder(cout);
    cout << endl;
    data.insert(fifth);
    data.printInOrder(cout);
    cout << endl;
}

int main(int argc, char* argv[])
{

    cout << "Testing stemmer:" << endl;
    string toStem = "adjudication";
    stem(toStem);
    cout << toStem << endl;

    cout << "\nTesting tree:" << endl;
    testTree();

    cout << "\nTesting words" << endl;
    testWord();

    cout << "\nTesting words in tree" << endl;
    testWordTree();

    Stopper k;

    return 0;
}
