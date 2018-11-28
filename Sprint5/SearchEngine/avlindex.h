//owner: Isaac
//created:11/16/2018
#ifndef AVLINDEX_H
#define AVLINDEX_H

#include "avltree.h"
#include "indexerface.h"
#include "word.h"
#include "docu.h"
#include <vector>
#include <string>
#include <exception>

using namespace std;


//inherit from Pure Virtual class IndexerFace
class AVLIndex: public IndexerFace{
private:
    //specific implementation of AVLTree template
    AVLTree <word> wordTree;
public:
    //constructor
    AVLIndex();
    //destructor
    ~AVLIndex();
    //overloaded copy constructor
    AVLIndex(const AVLIndex& a);
    //overloaded assignment operator
    AVLIndex& operator=(const AVLIndex& a);
    //overload pure virtual insert
    void insert(string val, string prev, string docname);
    //overload pure virtual
    word& findWord(string a, string prev);
    //overloaded pure virtual
    vector<docu> findDocWithWord(string a);
    //overloaded pure virtual
    int returnSize();
    //overlaoded pure virtual
    void printIndex(ostream &out, int& wordCount, int& docCount);
    void clearStuff();
    void readIndexNoPrev(int &wordCount, int &docCount);
    void readIndexWithPrev(int& wordCount, int& docCount);
};

#endif // AVLINDEX_H
