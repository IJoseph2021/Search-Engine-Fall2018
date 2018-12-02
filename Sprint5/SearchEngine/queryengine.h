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
    /**
     * @brief printDAndP - reads and prints a documents date and parties
     * @param html - html of the document info
     */
    void printDAndP(string html);
    void getPorD(string html, int &j, string &raw, string thing);
    //void getD(string html, int &j, string &raw);
public:
    QueryEngine();
    /**
     * @brief takeQuery - takes a query from the user and does the requested operations
     * on the word docTracker which is used to store the requested documents
     * @param docTracker - tracks what documents apply to the query
     * @param searching - tracks if the user is still entering queries
     */
    void takeQuery(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type, word &docTracker, bool &searching);
    /**
     * @brief run - runs the query engine on passed in indexes depending on user requested structure type
     * @param type - structure to use, true if avl, false if hash
     */
    void run(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type);
    /**
     * @brief printResults - prints the documents of wordTracker in order and prompts for which one to print
     * @param wordTracker - word that tracks documents
     */
    void printResults(word& wordTracker);
    /**
     * @brief calculateTop - takes a document array and bubble sorts the top 15 most
     * relevant documents in a word by use count
     * @param wordTracker - word that holds documents
     * @param documents - top 15 document vector
     */
    void calculateTop(word& wordTracker, docu documents[]);
    /**
     * @brief printDoc - prints info about a document
     * @param document - the document to print
     */
    void printDoc(docu document);
    /**
     * @brief swapDocs - swaps the order of two documents in a word for bubble sort
     * @param x - first document
     * @param y - second document
     */
    void swapDocs(docu& x, docu& y);
};

#endif // QUERYENGINE_H
