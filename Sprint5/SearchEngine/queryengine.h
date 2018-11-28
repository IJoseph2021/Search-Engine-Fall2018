#ifndef QUERYENGINE_H
#define QUERYENGINE_H
#include "indexerface.h"
#include "avlindex.h"
#include "hashindex.h"
#include <iostream>
#include "StemmerFiles/porter2_stemmer.h"


class QueryEngine
{
private:
    IndexerFace* avS;
    IndexerFace* haS;
    IndexerFace* avD;
    IndexerFace* haD;
    bool type;
public:
    QueryEngine();
    QueryEngine(IndexerFace*& avS, IndexerFace*& haSx, IndexerFace*& avDx, IndexerFace*& haDx, bool& typex);
    void takeQuery();
    void run();
    bool compareAND();
    bool compareNOT();
    bool compareOR();

};

#endif // QUERYENGINE_H
