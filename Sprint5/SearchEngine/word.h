#ifndef WORD_H
#define WORD_H
#include <vector>
#include "docu.h"
#include <string>
#include <iostream>

using namespace std;

class word
{
    friend class AVLTree;
private:
    string thisWord;
    string previous;
    vector<docu> documents;
public:
    word();
    word(const word& val);
    word& operator=(const word& val);
    ~word();
    word& operator+(const word& val);
    bool operator<(const word& val);
    bool operator>(const word& val);
    bool operator==(const word& val);
    friend ostream& operator<<(ostream& out, const word& w);
    int getNumDocs();
    string getPrev();
    string getWord();
    docu& getDoc(int x);

};

#endif // WORD_H
