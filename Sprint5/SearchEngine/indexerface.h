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
#include <vector>


class IndexerFace {
private:

public:
    /**
     * @brief insert - pure virtual function that inserts a word into the respective data structure
     * @param val - current word string to insert
     * @param prev - previous word string to insert
     * @param docname - document name to insert
     */
    virtual void insert(std::string val, std::string prev, std::string docname) = 0;
    /**
     * findWord - pure virtual function to find a word in the respective data
     * structure by searching for a word with the same thisWord and previous strings
     * @param a - thisWord to find
     * @param prev - previous word to find
     * @return - returns the word as a literal if found
     */
    virtual word& findWord(std::string a, std::string prev) = 0;
    /**
     * @brief findDocWithWord - pure virtual function that returns the underlying list of documents stored
     * within a word that is found that has the thisWord value of a
     * @param a - thisWord to find
     * @return - returns the full list of documents
     */
    virtual vector<string> findDocWithWord(std::string a) = 0;
    /**
     * @brief returnSize - pure virtual function that returns the number of unique words in the respective data structure
     * @return - returns an int value for the number of words
     */
    virtual int returnSize() = 0;
    /**
     * @brief printIndex - pure virtual function that prints the index it is called upon to a provided ostream
     * @param out - ostream to print to
     * @param wordCount - word count to print to index file
     * @param docCount - document count to print to index file
     */
    virtual void printIndex(ostream &out, int& wordCount, int& docCount) = 0;
    /**
     * @brief clearStuff - pure virtual function which will clear the respective data structure
     */
    virtual void clearStuff() = 0;
    /**
     * readIndexNoPrev - pure virtual function which will read from the index into
     * the respective data structure and combine the indexed words into a single-word searching index
     * wherein each word read in has a previous value taht is equal to thisWord
     * @param wordCount - word count is passed so it can be updated upon reading
     * @param docCount - document count is passed so it can be updated upon reading
     */
    virtual void readIndexNoPrev(int& wordCount, int& docCount) = 0;
    /**
     * readIndexWithPrev - pure virtual function which will read from the index into
     * the respective data structure into a double-word searching index wherein each word
     * is unique and has a true previous word
     * @param wordCount - word count is passed so it can be updated upon reading
     * @param docCount - document count is passed so it can be updated upon reading
     */
    virtual void readIndexWithPrev(int& wordCount, int& docCount) = 0;
    /**
     * @brief isEmpty - pure virtual function which checks if the given data structure is empty
     * @return - returns a bool, true if empty
     */
    virtual bool isEmpty() = 0;
};

#endif // INDEXERFACE_H
