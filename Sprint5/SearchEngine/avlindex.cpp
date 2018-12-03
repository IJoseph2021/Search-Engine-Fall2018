//owner: Isaac
//created:11/16/2018

#include "avlindex.h"
#include "indexerface.h"
#include "word.h"
#include "docu.h"
#include <vector>
#include <string>
#include <exception>
#include <fstream>

using namespace std;

//constructor
AVLIndex::AVLIndex(){

}
void AVLIndex::clearStuff(){
    wordTree.~AVLTree();
}

//destructor
AVLIndex::~AVLIndex(){
    wordTree.~AVLTree();
}

//overloaded insert
void AVLIndex::insert(string val, string prev, string docname){
    //create temp object a and search tree to see if an object with the same word already exists in the tree
    //if it does then just update the documents in that object
    word a(prev, val, docname);
    try{
        wordTree.find(a).addDoc(docname);
    }
    //if an object is not found with that word then add it to the tree
    catch(exception e){
        wordTree.insert(a);
    }

    //wordTree.insert(a);
}

vector <docu> AVLIndex::findDocWithWord(string a){
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

word& AVLIndex::findWord(string a, string prev){
    //create temp object to allow search in tree
    word b(prev, a);
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
int AVLIndex::returnSize(){
    return wordTree.returnNumberNodes();
}

//overloadd virtual function
//print data structure
void AVLIndex::printIndex(ostream &out, int &wordCount, int &docCount){
    out << wordCount << endl;
    out << docCount << endl;
    wordTree.printLevelOrder(out);
}
//copy constructor
AVLIndex::AVLIndex(const AVLIndex& a){
    this->wordTree = a.wordTree;
}

//overloaded assignment operator
AVLIndex& AVLIndex::operator=(const AVLIndex& a){
    this->wordTree = a.wordTree;
    return *this;
}

void AVLIndex::readIndexNoPrev(int& wordCount, int& docCount)
{
    cout << "READING SINGLE INDEX" << endl;
    ifstream ifile ("../Index.txt"); //"../../../Index.txt"
    streampos file_length = ifile.tellg();
    ifile.seekg(0, ios::end);
    file_length = ifile.tellg() - file_length;
    long file_len = (long)file_length;
    //cout<<"file length:"<<file_length<<endl;
    //ifile.clear();
    ifile.seekg(0, ios::beg);
    char* str = new char[file_len];
    //char str[file_len];
    ifile.read(str, file_len);
    //while (!ifile.eof())
    //{
        string thisWord = "";
        string prev = "";
        string docs = "";
        string firstNumber = "";
        string secondNumber = "";
        int j = 0;
        while(str[j] != '\n'){
            firstNumber += str[j];
            j++;
        }
        j++;
        while(str[j] != '\n'){
            secondNumber += str[j];
            j++;
        }
        j++;

        wordCount = stoi(firstNumber, nullptr, 10);
        docCount = stoi(secondNumber, nullptr, 10);

        for(int i = j; i<file_len; i++){
            while(str[i] != '|'){
                thisWord += str[i];
                i++;
            }
            i++;
            while(str[i] != '|'){
                prev += str[i];
                i++;
            }
            i += 3;
            word currWord(thisWord);
            prev = "";
            thisWord = "";
            while(str[i] != '\n'){
                docs += str[i];
                i++;
            }
            while(!docs.empty())
            {
                int pos = docs.find('|');
                string thisDoc = docs.substr(0, pos);
                docs.erase(0, pos+1);
                pos = docs.find('|');
                int uses = stoi(docs.substr(0, pos), nullptr, 10);
                docs.erase(0,pos+1);
                docu doc(thisDoc, uses);
                currWord.addDoc(doc);
                pos = docs.find('|');
                docs.erase(0, pos+1);
            }


            try{
                AVLTree<word>::TreeNode<word>* temp = wordTree.findStar(currWord);
                for (int i = 0; i < currWord.getNumDocs(); i++)
                    temp->data.addDoc(currWord.getLitDoc(i));
            }
            //if an object is not found with that word then add it to the tree
            catch(exception e){
                wordTree.insert(currWord);
            }

        }
    }


void AVLIndex::readIndexWithPrev(int& wordCount, int& docCount)
{
    cout << "READING DOUBLE INDEX" << endl;
    ifstream ifile ("../Index.txt"); //"../../../Index.txt"
    streampos file_length = ifile.tellg();
    ifile.seekg(0, ios::end);
    file_length = ifile.tellg() - file_length;
    long file_len = (long)file_length;
    //cout<<"file length:"<<file_length<<endl;
    //ifile.clear();
    ifile.seekg(0, ios::beg);
    char* str = new char[file_len];
    //char str[file_len];
    ifile.read(str, file_len);
    //while (!ifile.eof())
    //{
        string thisWord = "";
        string prev = "";
        string docs = "";
        string firstNumber = "";
        string secondNumber = "";
        int j = 0;
        while(str[j] != '\n'){
            firstNumber += str[j];
            j++;
        }
        j++;
        while(str[j] != '\n'){
            secondNumber += str[j];
            j++;
        }
        j++;

        wordCount = stoi(firstNumber, nullptr, 10);

        docCount = stoi(secondNumber, nullptr, 10);

        for(int i = j; i<file_len; i++){
            while(str[i] != '|'){
                thisWord += str[i];
                i++;
            }
            i++;
            while(str[i] != '|'){
                prev += str[i];
                i++;
            }
            i = i + 3;
            word currWord(prev, thisWord);
            prev = "";
            thisWord = "";
            while(str[i] != '\n'){
                docs += str[i];
                i++;
            }
            while(!docs.empty())
            {
                int pos = docs.find('|');
                string thisDoc = docs.substr(0, pos);
                docs.erase(0, pos+1);
                pos = docs.find('|');
                int uses = stoi(docs.substr(0, pos), nullptr, 10);
                docs.erase(0,pos+1);
                docu doc(thisDoc, uses);
                currWord.addDoc(doc);
                pos = docs.find('|');
                docs.erase(0, pos+1);
            }

            try{
                wordTree.find(currWord);
                for (int i = 0; i < currWord.getNumDocs(); i++)
                    wordTree.find(currWord).addDoc(currWord.getLitDoc(i));
            }
            //if an object is not found with that word then add it to the tree
            catch(exception e){
                wordTree.insert(currWord);
            }
        }
}

bool AVLIndex::isEmpty() {
    return this->wordTree.isEmpty();
}
