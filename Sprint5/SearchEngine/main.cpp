#include <iostream>
#include "parser.h"
#include <ctime>
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
    Stopper k;
    k.readStopWords("StopWordList.txt");

    clock_t start;
    float duration;

    int x = 0;

    start = clock();
    Parser dirParser(argv[1], "../../StopWordList.txt");
    IndexerFace* fr = new AVLIndex();
    int numFiles = dirParser.parse(x, fr);
    //fr->printIndex(cout);

    string adju = argv[2];
    Porter2Stemmer::stem(adju);

    cout << "Number of words parsed: " << x << endl;
    cout << "Number of unique words: " << fr->returnSize() << endl;
    cout << "Number of documents parsed: " << numFiles << endl;
    cout << "Number of documents " << argv[2] << " was found in: ";
    cout << fr->findWord(adju).getNumDocs() << endl;

    duration = (clock() - start) / (float) CLOCKS_PER_SEC;
    cout << duration << endl;

    return 0;
}
