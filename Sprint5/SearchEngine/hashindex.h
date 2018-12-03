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
    //int wordCount;
    //int docCount;
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
    /**
     * @brief insert - overloaded virtual function that inserts a word into the hash table
     * @param val - current word string to insert
     * @param prev - previous word string to insert
     * @param docname - document name to insert
     */
    void insert(string val, string prev, string docname);
    /**
     * findWord - overloaded virtual function to find a word in the hash table
     * by searching for a word with the same thisWord and previous strings
     * @param a - thisWord to find
     * @param prev - previous word to find
     * @return - returns the word as a literal if found
     */
    word& findWord(string a, string prev);
    /**
     * @brief findDocWithWord - overloaded virtual function that returns the underlying list of documents stored
     * within a word that is found that has the thisWord value of a
     * @param a - thisWord to find
     * @return - returns the full list of documents
     */
    vector<docu> findDocWithWord(string a);
    /**
     * @brief returnSize - overloaded virtual function that returns the number of unique words in the hash
     * @return - returns an int value for the number of words
     */
    int returnSize();
    /**
     * @brief printIndex - overloaded virtual function that prints the index it is called upon to a provided ostream
     * @param out - ostream to print to
     * @param wordCount - word count to print to index file
     * @param docCount - document count to print to index file
     */
    void printIndex(ostream &out, int& wordCount, int& docCount);
    /**
     * @brief clearStuff - overloaded virtual function which will clear the hash
     */
    void clearStuff();
    /**
     * readIndexNoPrev - overloaded virtual function which will read from the index into
     * the hash and combine the indexed words into a single-word searching index
     * wherein each word read in has a previous value taht is equal to thisWord
     * @param wordCount - word count is passed so it can be updated upon reading
     * @param docCount - document count is passed so it can be updated upon reading
     */
    virtual void readIndexNoPrev(int& wordCount, int& docCount);
    /**
     * readIndexWithPrev - overloaded virtual function which will read from the index into
     * the hash into a double-word searching index wherein each word
     * is unique and has a true previous word
     * @param wordCount - word count is passed so it can be updated upon reading
     * @param docCount - document count is passed so it can be updated upon reading
     */
    virtual void readIndexWithPrev(int& wordCount, int& docCount);
    /**
     * @brief isEmpty - overloaded virtual function which checks if the hash is empty
     * @return - returns a bool, true if empty
     */
    bool isEmpty();
};
#endif // HASHINDEX_H
