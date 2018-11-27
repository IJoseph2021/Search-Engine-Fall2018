//owner: Isaac Joseph
//created: 11/26/2018
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>

using namespace std;

template<typename mark, typename fontenot>

class HashNode{
private:
    mark key;
    fontenot value;
public:
    HashNode(mark a, fontenot b){
        key = a;
        value = b;
    }

    HashNode(const HashNode<mark, fontenot>& a){
        this->key = a.key;
        this->value = a.value;
    }
    HashNode& operator =(const HashNode<mark, fontenot>& a){
        this->key = a.key;
        this->value = a.value;
    }
    ~HashNode(){

    }
};

template<typename mark, typename fontenot>
class HashTable{
private:
    vector<vector<HashNode<mark, fontenot>>> table();
    int capacity;
    int size;

public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable<mark, fontenot>& a);
    HashTable& operator =(const HashTable<mark, fontenot>& a);
    int hashResize(mark key);
    void insertNode(mark key, fontenot value);
    fontenot removeNode(mark key);
    void clearTable();
    bool isEmpty();
    fontenot find(int key);
    void printOut(ostream &out);
    int returnSize();
};



#endif // HASHTABLE_H
