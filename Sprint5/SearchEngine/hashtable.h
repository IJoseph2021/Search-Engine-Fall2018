//owner: Isaac Joseph
//created: 11/26/2018
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>
#include <typeinfo>

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

    mark& returnKey(){
        return key;
    }

    fontenot& returnValue(){
        return value;
    }
};

template<typename mark, typename fontenot>
class HashTable{
private:
    vector<vector<HashNode<mark, fontenot>>> table;
    int capacity;
    int size;

public:
    HashTable();
    HashTable(int a);
    ~HashTable();
    HashTable(const HashTable<mark, fontenot>& a);
    HashTable& operator =(const HashTable<mark, fontenot>& a);
    int hashResize(mark& key);
    void insertNode(mark key, fontenot& value);
    void removeNode(mark key, fontenot value);
    void clearTable();
    bool isEmpty();
    fontenot& find(mark& key, fontenot& value);
    fontenot* findStar(mark& key, fontenot& value);
    void printOut(ostream &out);
    int returnSize();
    void stats();
    void reSize(int a);
};

template<typename mark, typename fontenot>
HashTable<mark, fontenot>::HashTable(){

}

template<typename mark, typename fontenot>
void HashTable<mark, fontenot>::reSize(int a){
    table.resize(a);
    capacity = a;
}


template<typename mark, typename fontenot>
HashTable<mark, fontenot>::HashTable(int a){
    capacity = a;
    table.resize(capacity);
    size = 0;
}
template<typename mark, typename fontenot>
HashTable<mark, fontenot>::HashTable(const HashTable<mark, fontenot>& a){
    this->capacity = a.capacity;
    for(int i =0; i<a.capacity; i++){
        for(int j = 0; j<a.table[i].size(); j++){
            this->table[i][j] = a.table[i][j];
            this->size++;
        }
    }
}

template<typename mark, typename fontenot>
HashTable<mark, fontenot>& HashTable<mark, fontenot>::operator =(const HashTable<mark, fontenot>& a){
    this->capacity = a.capacity;
    for(int i =0; i<a.capacity; i++){
        for(unsigned int j = 0; j<a.table[i].size(); j++){
            this->table[i][j] = a.table[i][j];
            this->size++;
        }
    }
    return *this;
}

//how this destructor work?
//will vectors do it themselves
template<typename mark, typename fontenot>
HashTable<mark, fontenot>::~HashTable(){
    clearTable();
}

template<typename mark, typename fontenot>
int HashTable<mark, fontenot>::hashResize(mark &key){
    return key % capacity;
}


template<typename mark, typename fontenot>
void HashTable<mark, fontenot>::insertNode(mark key, fontenot &value){
    //cout<<"key: "<<key<<endl;
    HashNode<mark, fontenot> temp = HashNode<mark, fontenot>(key, value);
    int index = hashResize(key);
    bool check = false;
    for(unsigned int i = 0; i<table[index].size(); i++){
        if(temp.returnValue() == (table[index][i]).returnValue()){
            check = true;
        }
    }
    if(check == false){
        table[index].push_back(temp);
        size++;
    }
    else{
        cout<<"val already inserted"<<endl;
    }
}

template<typename mark, typename fontenot>
void HashTable<mark, fontenot>::removeNode(mark key, fontenot value){
    int index = hashResize(key);
    for(int i = 0; i<table[index].size();i++){
        if(value == table[index][i]){
            table[index][i] = NULL;
        }
    }
}

template<typename mark, typename fontenot>
fontenot &HashTable<mark, fontenot>::find(mark& key, fontenot& value){
    int index = hashResize(key);
    for(unsigned int i = 0; i<table[index].size(); i++){
        if(value == table[index][i].returnValue()){
            return table[index][i].returnValue();
        }
    }
    throw logic_error("Value not in tree [in find()]");
}

template<typename mark, typename fontenot>
bool  HashTable<mark, fontenot>::isEmpty(){
    if(size == 0){
        return true;
    }
    else{
        return false;
    }
}

template<typename mark, typename fontenot>
int HashTable<mark, fontenot>::returnSize(){
    return size;
}

template<typename mark, typename fontenot>
void HashTable<mark, fontenot>::clearTable(){
    table.clear();
}

template<typename mark, typename fontenot>
void HashTable<mark, fontenot>::printOut(ostream &out){
    for(unsigned int i =0; i<table.size(); i++){
        for(unsigned int j = 0; j<table[i].size(); j++){
            out<<table[i][j].returnValue()<<endl;
        }
    }
}

template<typename mark, typename fontenot>
void HashTable<mark, fontenot>::stats(){
    cout<<"Hash Table Stats: "<<endl;
    float counter = 0;
    for(int i = 0; i<capacity;i++){
        if(table[i].size() != 0){
            counter++;
        }
    }
    cout<<"Number of indices used: "<<counter<<endl;
    cout<<"Total Capacity: "<<capacity<<endl;
    float ratio = (float) (counter*100) / (float) capacity;
    cout<<ratio<<"% used"<<endl;

    float collisionCounterSum = 0;
    float collisionCounter = 0;
    float largestCollision = 0;
    for(int i = 0; i<capacity;i++){
        if(table[i].size() > 1){
            collisionCounter++;
            collisionCounterSum = collisionCounterSum + table[i].size();
            if(table[i].size()>largestCollision){
                largestCollision = table[i].size();
            }
        }
    }
    float p = 100;
    float collisionRatio = (collisionCounter*p)/counter;
    float averageCollision = collisionCounterSum/collisionCounter;
    cout<<"Of the used indices, collisions occured in: "<<collisionRatio<<"%"<<endl;
    cout<<"For indices that had collisions, the average length was: "<<averageCollision<<endl;
    cout<<"The largest collision is: "<<largestCollision<<endl;
}

template<typename mark, typename fontenot>
fontenot* HashTable<mark, fontenot>::findStar(mark& key, fontenot& value){
    int index = hashResize(key);

    for(unsigned int i = 0; i<table[index].size(); i++){
        if(value == table[index][i].returnValue()){
            fontenot* a = new fontenot(table[index][i].returnValue());
            return a;
        }
    }
    throw logic_error("Value not in tree [in find()]");
}
#endif // HASHTABLE_H
