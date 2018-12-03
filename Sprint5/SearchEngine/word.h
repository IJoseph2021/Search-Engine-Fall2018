//owner:Patrick
//created 11/13/18
#ifndef WORD_H
#define WORD_H
#include <vector>
#include "docu.h"
#include <string>
#include <iostream>

using namespace std;

class word
{
    template <typename fontenot>
    friend class AVLTree;
private:
    string thisWord; ///!< value of the word
    string previous; ///!< value of the previous word
    vector<docu> documents; ///!< vector of documents the word appears in
public:
    word();
    /**
     * @brief word - copy constructor
     * @param val - word to copy
     */
    word(const word& val);
    //word(string prev, string curr);
    /**
     * @brief word - constructo a word from a string
     * @param curr - the word being added
     */
    word(string curr);
    /**
     * @brief word - create a word with current word, previous word, and document name
     * @param prev - previous word
     * @param curr - this word
     * @param doc - document name
     */
    word(string prev, string curr, string doc);
    /**
     * @brief word - create a word from the word string and document string, defaulting the previous to be the same as the current
     * @param curr - current word string
     * @param doc - document filepath string
     */
    word(string curr, string doc);
    /**
     * @brief operator = - overloaded =
     * @param val - word to copy
     * @return - reutnrs a word literal to allow chained =
     */
    word& operator=(const word& val);
    ~word();\

    /**
     * @brief operator + - overloaded addition operator that is used to add two equal words, combinding their document vectors
     * @param val - word to add
     * @return  - returns a word literal to allow chained +
     */
    word& operator+(const word& val);
    /**
     * @brief operator < - overloaded < compares primarily this word then previous word alphabetically
     * @param val - word to compare against
     * @return - returns a bool
     */
    bool operator<(const word& val);
    /**
     * @brief operator > - overloaded > compares primarily this word then previous word alphabetically
     * @param val- word to compare against
     * @return - returns a bool
     */
    bool operator>(const word& val);
    /**
     * @brief operator == - overloaded == compares this word and the previous word for equivalency
     * @param val - word to compare
     * @return - returns a bool
     */
    bool operator==(const word& val);
    /**
     * @brief operator << - overloaded stream insertion operator that prints thisWord|previous|-|document vector|
     * @param out - ostream to print to
     * @param w - word to print
     * @return - returns the ostream to allow chained prints
     */
    friend ostream& operator<<(ostream& out, const word& w);
    int getNumDocs() const;
    string getPrev() const;
    string getWord() const;
    /**
     * @brief getDoc - gets a document from the vector
     * @param x - position to get document from
     * @return - retuns a const document copy
     */
    docu getDoc(int x) const;
    /**
     * @brief getLitDoc - gets a literal document from the vector to allow editing
     * @param x - position to get document from
     * @return  - returns a literal document
     */
    docu& getLitDoc(int x);
    /**
     * @brief addDoc - adds a document to the word from its name, if alread contained the
     * use count of the document is incremented
     * @param docName - document name
     */
    void addDoc(string docName);
    /**
     * @brief addDoc - adds a document to the word, if the document path is alread contained the
     * use count of the document is incremented
     * @param doc - document to add
     */

    void addDoc(docu& doc);
    /**
     * @brief returnDocVector - returns the entire document vector
     * @return - returns the documents vector
     */
    vector<docu> returnDocVector();
    /**
     * @brief operator & - logical AND that combines two words' document vectors
     * only keeping documents contained in both words
     * @param val - word to AND
     * @return - returns the word literal to allow chaining
     */
    word& operator &(const word& val);
    /**
     * @brief operator | - logical OR that combines two words' document vectors
     * keeping any document contained in either
     * @param val - word to OR
     * @return - returns the word literal to allow chaining
     */
    word& operator |(const word& val);
    /**
     * @brief logicalNot - logical NOT that removes all documents in the rhs word's vector
     * fromt he lhs word's document vector
     * @param val - word to NOT
     * @return  - reutnrs a word literal to allow chaining
     */
    word& logicalNot(const word& val);
    int getNumUses();
};

#endif // WORD_H
