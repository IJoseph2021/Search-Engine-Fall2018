//owner: Isaac
//created:11/16/2018
#ifndef AVLINDEX_H
#define AVLINDEX_H

#include "avltree.h"
#include "indexerface.h"
#include "word.h"
#include "docu.h"
#include <vector>
#include <string>
#include <exception>

using namespace std;

class AVLIndex: public IndexerFace{
private:
    AVLTree <word> wordTree;

public:
    void insert(string val, string docname){
        word a(val, docname);
        try{
            wordTree.find(a).addDoc(docname);
        }
        catch(exception e){
            wordTree.insert(a);
        }
    }
    word& findWord(string a){
        word b(a, "Fontenot");
        try{
            return wordTree.find(b);
        }
        catch (exception e){
            cout<<"Value not in tree [in find()]"<<endl;
        }
    }

    vector<docu> findDocWithWord(string a){
        word b(a, "Fontenot");
        try{
            return wordTree.find(b).returnDocVector();
        }
        catch (exception e){
            cout<<"Value not in tree [in find()]"<<endl;
            return vector <docu> c;
        }
    }
    int returnSize(){
        return wordTree.returnNumberNodes();
    }
};

#endif // AVLINDEX_H
