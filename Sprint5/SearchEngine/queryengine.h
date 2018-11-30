/*
 * owner: Patrick DeVries
 * created 11/28/18
 * */

#ifndef QUERYENGINE_H
#define QUERYENGINE_H
#include "indexerface.h"
#include "avlindex.h"
#include "hashindex.h"
#include <iostream>
#include "StemmerFiles/porter2_stemmer.h"
#include <myhtml/api.h>
#include "docu.h"
#include "stopper.h"
#include "rapidjson.h"
#include "document.h"


class QueryEngine
{
private:
    void printDAndP(string html);
    void getPorD(string html, int &j, string &raw, string thing);
    //void getD(string html, int &j, string &raw);
public:
    QueryEngine();
    void takeQuery(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type, word &docTracker, bool &searching);
    void run(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type);
    void printResults(word& wordTracker);
    void calculateTop(word& wordTracker, docu documents[]);
    void printDoc(docu document);
    void swapDocs(docu& x, docu& y);
};

#endif // QUERYENGINE_H
