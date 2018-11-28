/*
 * Interface for AVLTree and HashTable
 * Owner: Isaac
 * created 11/16/2018
 *
 *
 *
 *
*/


#ifndef INDEXERFACE_H
#define INDEXERFACE_H

#include <string>
#include "word.h"
#include "docu.h"
#include <vector>


class IndexerFace {
private:

public:
    virtual void insert(std::string val, std::string prev, std::string docname) = 0;
    virtual word& findWord(std::string a, std::string prev) = 0;
    virtual vector<docu> findDocWithWord(std::string a) = 0;
    virtual int returnSize() = 0;
    virtual void printIndex(ostream &out, int& wordCount, int& docCount) = 0;
    virtual void clearStuff() = 0;
    virtual void readIndexNoPrev(int& wordCount, int& docCount) = 0;
    virtual void readIndexWithPrev(int& wordCount, int& docCount) = 0;
};

#endif // INDEXERFACE_H
