//owner: Isaac
//created:11/16/2018

#include "hashindex.h"
#include "hashtable.h"
#include "indexerface.h"
#include "word.h"
#include "docu.h"
#include <vector>
#include <string>
#include <exception>
#include <functional>

using namespace std;

//constructor
HashIndex::HashIndex(int a){
    wordTable.reSize(a);
}
void HashIndex::clearStuff(){
    wordTable.~HashTable();
}

//destructor
HashIndex::~HashIndex(){
    wordTable.~HashTable();
}

//overloaded insert
void HashIndex::insert(string val, string docname){
    //create temp object a and search tree to see if an object with the same word already exists in the tree
    //if it does then just update the documents in that object
    word a(val, docname);
    hash<string>str_hash;
    int x = str_hash(val);
    if(x<0){
        x = -1*x;
    }
    try{
        wordTable.find(x, a).addDoc(docname);
    }
    //if an object is not found with that word then add it to the tree
    catch(exception e){
        wordTable.insertNode(x, a);
    }
}

vector <docu> HashIndex::findDocWithWord(string a){
    //make temp object to allow search in tree
    word b(a, "Fontenot");
    hash<string>str_hash;
    int x = str_hash(a);
    if(x<0){
        x = -1*x;
    }
    //if an object of that word is found, then return that object's vector
    try{
        return wordTable.find(x, b).returnDocVector();
    }
    //else return an empty vector
    catch (exception e){
        cout<<"Value not in tree [in find()]"<<endl;
        vector <docu> c;
        return c;
    }
}

word& HashIndex::findWord(string a){
    //create temp object to allow search in tree
    word b(a, "Fontenot");
    hash<string>str_hash;
    int x = str_hash(a);
    if(x<0){
        x = -1*x;
    }
    //return object with that string if found
    try{
        return wordTable.find(x, b);
    }
    //else inform user
    catch (exception e){
        cout<<"Value not in tree [in find()]"<<endl;
    }
}


//overloaded virtual function
//return size of data structure
int HashIndex::returnSize(){
    return wordTable.returnSize();
}

//overloadd virtual function
//print data structure
void HashIndex::printIndex(ostream &out){
    //wordTable.printOut(out);
    wordTable.stats();
}
//copy constructor
HashIndex::HashIndex(const HashIndex& a){
    this->wordTable = a.wordTable;
}

//overloaded assignment operator
HashIndex& HashIndex::operator=(const HashIndex& a){
    this->wordTable = a.wordTable;
    return *this;
}
