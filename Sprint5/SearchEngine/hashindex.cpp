//owner: Isaac
//created:11/16/2018

#include "hashindex.h"
#include "indexerface.h"
#include "word.h"
#include "docu.h"
#include <vector>
#include <string>
#include <exception>

using namespace std;

//constructor
HashIndex::HashIndex(){

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

    try{
        wordTable.find(a).addDoc(docname);
    }
    //if an object is not found with that word then add it to the tree
    catch(exception e){
        wordTree.insert(a);
    }

    //wordTree.insert(a);
}

vector <docu> HashIndex::findDocWithWord(string a){
    //make temp object to allow search in tree
    word b(a, "Fontenot");
    //if an object of that word is found, then return that object's vector
    try{
        return wordTree.find(b).returnDocVector();
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
    //return object with that string if found
    try{
        return wordTree.find(b);
    }
    //else inform user
    catch (exception e){
        cout<<"Value not in tree [in find()]"<<endl;
    }
}


//overloaded virtual function
//return size of data structure
int HashIndex::returnSize(){
    return wordTree.returnNumberNodes();
}

//overloadd virtual function
//print data structure
void HashIndex::printIndex(ostream &out){
    wordTree.printInOrder(out);
}
//copy constructor
HashIndex::HashIndex(const HashIndex& a){
    this->wordTree = a.wordTree;
}

//overloaded assignment operator
HashIndex& HashIndex::operator=(const HashIndex& a){
    this->wordTree = a.wordTree;
    return *this;
}
