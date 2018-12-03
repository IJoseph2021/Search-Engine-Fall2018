#ifndef HASHINDEX_H
#define HASHINDEX_H
//owner: Isaac
//created 11/16/2018
#include "hashtable.h"
#include "indexerface.h"
#include "word.h"
#include "docu.h"
#include <vector>
#include <string>
#include <exception>
#include <functional>

using namespace std;


//inherit from Pure Virtual class IndexerFace
class HashIndex: public IndexerFace{
private:
    //specific implementation of AVLTree template
    HashTable <int, word> wordTable;
    int wordCount;
    int docCount;
    hash<string> str_hash;
public:
    //constructor
    HashIndex(int a);
    //destructor
    ~HashIndex();
    //overloaded copy constructor
    HashIndex(const HashIndex& a);
    //overloaded assignment operator
    HashIndex& operator=(const HashIndex& a);
    //overload pure virtual insert
    void insert(string val, string prev, string docname);
    //overload pure virtual
    word& findWord(string a, string prev);
    //overloaded pure virtual
    HashTable<int, docu> findDocWithWord(string a);
    //overloaded pure virtual
    int returnSize();
    //overlaoded pure virtual
    void printIndex(ostream &out, int& wordCount, int& docCount);
    void clearStuff();
    virtual void readIndexNoPrev(int& wordCount, int& docCount);
    virtual void readIndexWithPrev(int& wordCount, int& docCount);
    bool isEmpty();
};
#endif // HASHINDEX_H
