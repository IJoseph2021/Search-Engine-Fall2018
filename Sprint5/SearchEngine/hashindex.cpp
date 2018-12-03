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
void HashIndex::insert(string val, string prev, string docname){
    //create temp object a and search tree to see if an object with the same word already exists in the tree
    //if it does then just update the documents in that object
    word a(prev, val, docname);
    hash<string>str_hash;
    int x = str_hash(val + prev);
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

word& HashIndex::findWord(string a, string prev){
    //create temp object to allow search in tree
    word b(prev, a);
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
        cout<<"Value not in hash [in find()]"<<endl;
    }
}


//overloaded virtual function
//return size of data structure
int HashIndex::returnSize(){
    return wordTable.returnSize();
}

//overloadd virtual function
//print data structure
void HashIndex::printIndex(ostream &out, int &wordCount, int &docCount){
    out << wordCount << endl;
    out << docCount << endl;
    wordTable.printOut(out);
    //wordTable.stats();
}

void HashIndex::readIndexNoPrev(int &wordCount, int &docCount)
{
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
            firstNumber = firstNumber + str[j];
            j++;
        }
        j++;
        while(str[j] != '\n'){
            secondNumber = secondNumber + str[j];
            j++;
        }
        j++;

        wordCount = stoi(firstNumber, nullptr, 10);

        docCount = stoi(secondNumber, nullptr, 10);

        for(int i = j; i<file_len; i++){
            while(str[i] != '|'){
                thisWord = thisWord + str[i];
                i++;
            }
            i++;
            while(str[i] != '|'){
                prev = prev + str[i];
                i++;
            }
            i = i + 3;
            word currWord(thisWord);
            prev = "";
            thisWord = "";
            while(str[i] != '\n'){
                docs = docs + str[i];
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

            int x = str_hash(currWord.getWord());
            if(x<0){
                x = -1*x;
            }
            try{
                word* temp = wordTable.findStar(x, currWord);
                for (int i = 0; i < currWord.getNumDocs(); i++)
                    (*temp).addDoc(currWord.getLitDoc(i));
            }
            //if an object is not found with that word then add it to the tree
            catch(exception e){
                wordTable.insertNode(x, currWord);
            }
        }
}

void HashIndex::readIndexWithPrev(int &wordCount, int &docCount)
{
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
            firstNumber = firstNumber + str[j];
            j++;
        }
        j++;
        while(str[j] != '\n'){
            secondNumber = secondNumber + str[j];
            j++;
        }
        j++;

        wordCount = stoi(firstNumber, nullptr, 10);
        docCount = stoi(secondNumber, nullptr, 10);

        for(int i = j; i<file_len; i++){
            while(str[i] != '|'){
                thisWord = thisWord + str[i];
                i++;
            }
            i++;
            while(str[i] != '|'){
                prev = prev + str[i];
                i++;
            }
            i = i + 3;
            word currWord(thisWord, prev);
            prev = "";
            thisWord = "";
            while(str[i] != '\n'){
                docs = docs + str[i];
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
            int x = str_hash(currWord.getPrev()+currWord.getWord());
            if(x<0){
                x = -1*x;
            }
            try{
                wordTable.find(x, currWord);
                for (int i = 0; i < currWord.getNumDocs(); i++)
                    wordTable.find(x, currWord).addDoc(currWord.getLitDoc(i));
            }
            //if an object is not found with that word then add it to the tree
            catch(exception e){
                wordTable.insertNode(x, currWord);
            }
        }
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

bool HashIndex::isEmpty() {
    return this->wordTable.isEmpty();
}

