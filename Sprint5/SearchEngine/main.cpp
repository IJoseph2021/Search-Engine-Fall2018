#include <iostream>
#include "parser.h"
#include "StemmerFiles/porter2_stemmer.h"
#include "avltree.h"
#include "word.h"
#include "stopper.h"
#include "indexerface.h"
#include "avlindex.h"
#include "hashtable.h"
#include <fstream>
#include "queryengine.h"

using namespace std;

int main(int argc, char* argv[])
{

    cout << "PARSING DOCS" << endl;

    int x = 0;

    clock_t start;
    float duration;
    start = clock();
    Parser dirParser(argv[1], "../StopWordList.txt");
    IndexerFace* avD = new AVLIndex();
    int numFiles = dirParser.parse(x, avD);

    duration = (clock() - start) / (float) CLOCKS_PER_SEC;
    cout << "original parse time: " << duration << endl;

    string adju = argv[2];
    Porter2Stemmer::stem(adju);

    //print two word index
    ofstream ofile("Index.txt");
    ofstream ofile2("TestBuffer.txt");

    avD->printIndex(ofile, x, numFiles);
    ofile.close();

    IndexerFace* avS = new AVLIndex();
    //read index to create one word index
    avD->readIndexNoPrev(x, numFiles);
    QueryEngine* qe = new QueryEngine();
    IndexerFace* haS = new AVLIndex();
    IndexerFace* haD = new AVLIndex();
    /*IndexerFace* haS = new HashIndex();
    IndexerFace* haD = new HashIndex();*/
    bool tree = true;
    qe->run(avS, haS, avD, haD, tree);

    cout << "Number of words parsed: " << x << endl;
    cout << "Number of unique words: " << avS->returnSize() << endl;
    //cout << "Number of documents parsed: " << numFiles << endl;
    cout << "Number of documents " << argv[2] << " was found in: ";
    int numDocs = avS->findWord(adju, adju).getNumDocs();
    cout << numDocs << endl;

    duration = (clock() - start) / (float) CLOCKS_PER_SEC;
    cout<<"time: "<<duration<<endl;
    ofile2.close();

    avD->clearStuff();
    delete avD;


    return 0;
}
