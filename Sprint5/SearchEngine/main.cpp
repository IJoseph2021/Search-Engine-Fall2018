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

int main(int argc, char* argv[])
{
    cout << "PARSING DOCS" << endl;

    int x = 0;

    clock_t start;
    float duration;
    start = clock();
    Parser dirParser(argv[1], "../StopWordList.txt");
    IndexerFace* fr = new AVLIndex();
    int numFiles = dirParser.parse(x, fr);
    duration = (clock() - start) / (float) CLOCKS_PER_SEC;

    string adju = argv[2];
    Porter2Stemmer::stem(adju);

    ofstream ofile("Index.txt");
    fr->printIndex(ofile);
    ofile.close();
    fr->clearStuff();

    ofile.open("Index2.txt");
    fr->readIndex();
    fr->printIndex(ofile);
    ofile.close();

    cout << "Number of words parsed: " << x << endl;
    cout << "Number of unique words: " << fr->returnSize() << endl;
    cout << "Number of documents parsed: " << numFiles << endl;
    cout << "Number of documents " << argv[2] << " was found in: ";
    int numDocs = fr->findWord(adju).getNumDocs();
    cout << numDocs << endl;
    cout<<"time: "<<duration<<endl;    

    fr->clearStuff();
    delete fr;

    return 0;
}
