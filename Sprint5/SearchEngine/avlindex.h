//owner: Isaac
//created:11/16/2018
#ifndef AVLINDEX_H
#define AVLINDEX_H

#include "avltree.h"
#include "indexerface.h"
#include "word.h"
#include <vector>
#include <string>
#include <exception>

using namespace std;


//inherit from Pure Virtual class IndexerFace
class AVLIndex: public IndexerFace{
private:
    //specific implementation of AVLTree template
    AVLTree <word> wordTree; ///!< avl tree that stores index info
public:
    //constructor
    AVLIndex();
    //destructor
    ~AVLIndex();
    //overloaded copy constructor
    AVLIndex(const AVLIndex& a);
    //overloaded assignment operator
    AVLIndex& operator=(const AVLIndex& a);
    /**
     * @brief insert - overloaded virtual function that inserts a word into the AVL tree
     * @param val - current word string to insert
     * @param prev - previous word string to insert
     * @param docname - document name to insert
     */
    void insert(string val, string prev, string docname);
    /**
     * findWord - overloaded virtual function to find a word in the AVL tree
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
    vector<string> findDocWithWord(string a);
    /**
     * @brief returnSize - overloaded virtual function that returns the number of unique words in the AVL tree
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
     * @brief clearStuff - overloaded virtual function which will clear the AVL tree
     */
    void clearStuff();
    /**
     * readIndexNoPrev - overloaded virtual function which will read from the index into
     * the AVL trees and combine the indexed words into a single-word searching index
     * wherein each word read in has a previous value taht is equal to thisWord
     * @param wordCount - word count is passed so it can be updated upon reading
     * @param docCount - document count is passed so it can be updated upon reading
     */
    void readIndexNoPrev(int &wordCount, int &docCount);
    /**
     * readIndexWithPrev - overloaded virtual function which will read from the index into
     * the AVl tree into a double-word searching index wherein each word
     * is unique and has a true previous word
     * @param wordCount - word count is passed so it can be updated upon reading
     * @param docCount - document count is passed so it can be updated upon reading
     */
    void readIndexWithPrev(int& wordCount, int& docCount);
    /**
     * @brief isEmpty - overloaded virtual function which checks if the AVl tree is empty
     * @return - returns a bool, true if empty
     */
    bool isEmpty();
};

#endif // AVLINDEX_H
