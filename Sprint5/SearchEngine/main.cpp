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

    Parser dirParser(argv[1], "../../StopWordList.txt");
    IndexerFace* fr = new AVLIndex();
    int numFiles = dirParser.parse(x, fr);

    string adju = argv[2];
    Porter2Stemmer::stem(adju);

    cout << "Number of words parsed: " << x << endl;
    cout << "Number of unique words: " << fr->returnSize() << endl;
    cout << "Number of documents parsed: " << numFiles << endl;
    cout << "Number of documents " << argv[2] << " was found in: ";
    int numDocs = fr->findWord(adju).getNumDocs();
    cout << numDocs << endl;

    delete fr;
    return 0;
}
