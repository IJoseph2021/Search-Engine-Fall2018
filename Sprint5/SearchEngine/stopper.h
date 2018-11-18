#ifndef STOPPER_H
#define STOPPER_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>
#include <dirent.h>
#include "avltree.h"
using namespace std;


class Stopper
{
private:
    //vector <vector<string>> stopWord ;
    AVLTree <string> stopWord;
public:
    Stopper();
    bool isStopWord(string a);
    void readStopWords(char* filename);
};

#endif // STOPPER_H
