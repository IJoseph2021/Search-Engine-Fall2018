#include <iostream>
#include "parser.h"
#include "StemmerFiles/porter2_stemmer.h"
#include "avltree.h"
#include "word.h"
#include "stopper.h"
#include "indexerface.h"
#include "avlindex.h"
#include <fstream>

using namespace std;

void maitenanceMode(IndexerFace* av, IndexerFace* ha, bool type);
void userMode(IndexerFace* av, IndexerFace* ha, bool type);

int main(int argc, char* argv[])
{
//    cout << "PARSING DOCS" << endl;

//    int x = 0;

//    clock_t start;
//    float duration;
//    start = clock();
//    Parser dirParser(argv[1], "../StopWordList.txt");
    IndexerFace* avl = new AVLIndex();
    IndexerFace* hashT = new HashIndex();
    bool type = true;       //true is AVLTree / false is HashTable
//    int numFiles = dirParser.parse(x, fr);
//    duration = (clock() - start) / (float) CLOCKS_PER_SEC;

//    string adju = argv[2];
//    Porter2Stemmer::stem(adju);

//    cout << "Number of words parsed: " << x << endl;
//    cout << "Number of unique words: " << fr->returnSize() << endl;
//    cout << "Number of documents parsed: " << numFiles << endl;
//    cout << "Number of documents " << argv[2] << " was found in: ";
//    int numDocs = fr->findWord(adju).getNumDocs();
//    cout << numDocs << endl;
//    cout<<"time: "<<duration<<endl;
//    fr->clearStuff();
//    delete fr;
    int choice;
    bool flag = true;
    while(flag) {
        cout << "Welcome to the Rule of Three's Search Engine!" << endl;
        cout << "Select your mode (Enter an int): \n\n1. Maitenance Mode \n2. User Mode \n3. Exit" << endl;
        cin >> choice;

        switch(choice) {
        case 1:
            maitenanceMode(avl, hashT, type);
            break;
        case 2:
            userMode(avl, hashT, type);
            break;
        case 3:
            flag = false;
        } //end switch
    } //end while
    return 0;
} //end main

maitenanceMode(IndexerFace* av, IndexerFace* ha, bool type) {
    bool maitFlag = true;
    int maitChoice;
    while(maitFlag) {
        cout << "1. Add Opinions to Index \n2. Clear the Index \n3. Exit" << endl;
        cin >> maitChoice;

        switch(maitChoice) {
        case 1:
            int numFiles;
            cout << "Enter the file path: " << endl;
            string path;
            cin >> path;
            Parser dirParser(path, "../StopWordList.txt");
            if(type)
                numFiles = dirParser.parse(x, av);
            else
                numFiles = dirParser.parse(x, ha);
            break;
        case 2:
            if(type)
                av->clearStuff();
            else
                ha->clearStuff();
            break;
        case 3:
            maitFlag = false;
        } //end switch
    } //end while
} //end maitenance mode


userMode(IndexerFace* av, IndexerFace* ha, bool type) {
    bool userFlag = true;
    int userChoice;
    while(userFlag) {
        cout << "1. Choose Which Data Structure to use \n2. Search any (properly formatted) query \n3. Get Statistics about our Search Engine \n4. Exit" << endl;
        cin >> userChoice;

        switch(userChoice) {
        case 1:
            cout << "Do you want a(n) \n1. AVLTree \n2. Hash Table" << endl;
            int dataStruc;
            cin >>dataStruc;
            if(dataStruc == 1)
                type = true;
            else if(dataStruc == 2)
                type = false;
            else
                cout << "You entered an invalid number" << endl;
            break;
        } //end switch
    } //end while
} //end userMode
