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
    virtual void insert(std::string val, std::string docname) = 0;
    virtual word& findWord(std::string a) = 0;
    virtual vector<docu> findDocWithWord(std::string a) = 0;
    virtual int returnSize() = 0;
    virtual void printIndex(ostream &out) = 0;
    virtual void clearStuff() = 0;
    virtual bool isEmpty() = 0;
    virtual int getWords() = 0;
    virtual int getDocs() = 0;
};

#endif // INDEXERFACE_H
