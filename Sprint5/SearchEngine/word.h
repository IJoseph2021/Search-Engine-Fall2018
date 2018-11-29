//owner:Patrick
//created 11/13/18
#ifndef WORD_H
#define WORD_H
#include <vector>
#include "docu.h"
#include <string>
#include <iostream>
#include <hashtable.h>
#include <functional>

using namespace std;

class word
{
    template <typename fontenot>
    friend class AVLTree;
    friend class HashTable<int, string>;
private:
    string thisWord;
    string previous;
    //vector<docu> documents;
    hash<string> str_hash;
    HashTable <int, docu> documents;
public:
    word();
    word(const word& val);
    //word(string prev, string curr);
    word(string curr);
    word(string prev, string curr, string doc);
    word(string curr, string doc);
    word& operator=(const word& val);
    ~word();
    word& operator+(const word& val);
    bool operator<(const word& val);
    bool operator>(const word& val);
    bool operator==(const word& val);
    friend ostream& operator<<(ostream& out, const word& w);
    int getNumDocs() const;
    string getPrev() const;
    string getWord() const;
    docu getDoc(int x) const;
    docu getDoc(int a, int b) const;
    docu& getLitDoc(int x);
    void addDoc(string docName);
    void addDoc(docu& doc);
    vector<docu> returnDocVector();
    word& operator &(const word& val);
    word& operator |(const word& val);
    word& logicalNot(const word& val);
    int getNumUses();
};

#endif // WORD_H
