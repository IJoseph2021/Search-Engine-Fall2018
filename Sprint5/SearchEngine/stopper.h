#ifndef STOPPER_H
#define STOPPER_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>
#include <dirent.h>
#include <set>
#include "avltree.h"
using namespace std;


class Stopper
{
private:
    //vector <vector<string>> stopWord ;
    /**
     * @brief stopWord AVLTree that holds all stopwords
     */
    AVLTree <string> stopWord;
    //set<string> stopWord;
public:
    /**
     * @brief Stopper constructor for stopper class
     */
    Stopper();

    /** checks if a word is a data structure
     * @brief isStopWord
     * @param[in] a word to be checked
     * @return boolean
     */
    bool isStopWord(string &a);

    /** reads stopwords into AVLtree
     * @brief readStopWords
     * @param[in] filename filepath and name of file contatining stopwords
     */
    void readStopWords(char* filename);
};

#endif // STOPPER_H
