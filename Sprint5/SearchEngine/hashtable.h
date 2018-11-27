//owner: Isaac Joseph
//created: 11/26/2018
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include <functional>

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

#endif // HASHTABLE_H
