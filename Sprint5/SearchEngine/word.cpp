#include "word.h"

word::word(){}

//create a word from the previous word and the current word
/*word::word(string prev, string curr)
{
    previous = prev;
    thisWord = curr;
}*/


word::word(string curr)
{
    previous = curr;
    thisWord = curr;
}

//create a word with both words and the document filename
word::word(string prev, string curr, string doc)
{
    previous = prev;
    thisWord = curr;
    docu tempDoc(doc);
    documents.reSize(64000);
    int x  = str_hash(doc);
    if(x<0){
        x = -1*x;
    }
    documents.insertNode(x, tempDoc);
    //documents.push_back(tempDoc);
}

word::word(string prev, string curr){
    thisWord = curr;
    previous = prev;
}

//copy constructor
word::word(const word& val)
{
    thisWord = val.thisWord;
    previous = val.previous;
    //create a temporary vector with the contents of val's vector and swap them into documents
    documents = val.documents;
}

word& word::operator=(const word& val)
{
    thisWord = val.thisWord;
    previous = val.previous;
    documents = val.documents;
    return *this;
}

word::~word()
{
    documents.clearTable();
}

//overloaded + operator which simply merges two words by combining their document vectors,
//adding any new documents and incrementing existing document's use counts
/*word& word::operator +(word& val)
{
    hash<string>str_hash;
    for(int i =0; i<val.documents.returnSize(); i++){
        for(int j = 0; j<val.documents[i].size(); j++){
            int x = str_hash(documents.returnObject(i,j).getFileName());
            if(x<0){
                x = -1*x;
            }
            try{
                documents.find(x, documents.returnObject(i, j)).useCount++;
            }
            //if an object is not found with that word then add it to the tree
            catch(exception e){
                documents.insertNode(x, val.getDoc(i, j));
            }
        }
    }
    //loop through all docs in the rhs word and see if they are already contained
    //set found flag and location if found

    for (int i = 0; i < val.getNumDocs(); i++)
    {
        bool found = false;;
        bool loc;
        for (int j = 0; j < getNumDocs(); j++)
        {
            if (val.getDoc(i).getFileName().compare(documents[j].getFileName()) == 0)
            {
                found = true;
                loc = i;
                break;
            }
        }
        //if the doc was already in the lhs's documents vector
        //increment its use count, otherwise pushback
        if (found)
        {
            documents[loc].useCount++;
        }
        else
        {
            documents.push_back(val.getDoc(i));
        }
    }
    return *this;
}*/

//overloaded < operator which compares the value of the current word to the passed word
//returns true if it is smaller
bool word::operator < (const word& val)
{
    if (thisWord.compare(val.thisWord) < 0)
        return true;
    else if ((thisWord.compare(val.thisWord) == 0 && previous.compare(val.previous) < 0))
        return true;
    else
        return false;
}

//overloaded > operator functions the same as <
bool word::operator > (const word& val)
{
    if (thisWord.compare(val.thisWord) > 0)
        return true;
    else if ((thisWord.compare(val.thisWord) == 0 && previous.compare(val.previous) > 0))
        return true;
    else
        return false;
}

//overloaded comparison operator to see if two words have the same word string
bool word::operator==(const word& val)
{
    if ((thisWord.compare(val.thisWord) == 0) &&
       ((previous.compare(val.previous) == 0) || val.previous.compare("s34rch") == 0))
        return true;
    else
        return false;
}

//print the previous word, this word, and document vector to ostream out
ostream& operator<<(ostream& out, const word& w)
{
    out << w.getWord() << '|' << w.getPrev() << "|";
    for (int i = 0; i < w.getNumDocs(); i++)
    {
        out << "-|";
        docu tempDoc = w.getDoc(i);
        out << tempDoc;
    }
    return out;
}

int word::getNumDocs() const
{
    return documents.returnSize();
}

string word::getPrev() const
{
    return previous;
}

string word::getWord() const
{
    return thisWord;
}

/*docu word::getDoc(int x) const
{
    return documents[x];
}*/

docu word::getDoc(int a, int b)
{
    return documents.returnObject(a, b);
}

docu& word::getLitDoc(int x, int y)
{
    return documents.returnObject(x, y);
}

//add a new document to the word's document vector with the name of docName
void word::addDoc(string docName)
{
    //loop through documents to see if the document is already contained
    docu a(docName);
    int x = str_hash(docName);
    if(x<0){
        x = -1*x;
    }
    try{
        documents.find(x, a).useCount++;
    }
    //if an object is not found with that word then add it to the tree
    catch(exception e){
        documents.insertNode(x, a);
    }
    /*bool found = false;
    int loc = -1;
    for (int i = 0; i < documents.size(); i++)
    {
        if (documents[i].getFileName().compare(docName)==0)
        {
            found = true;
            loc = i;
            break;
        }
    }

    //if not already added add a doc with the doc name, else increment uses
    if (!found)
    {
        docu tempDoc = docu(docName);
        documents.push_back(tempDoc);
    }
    else
    {
        documents[loc].useCount++;
    }*/
}

//add an existing document to the word's doc vector with same logic as string version
void word::addDoc(docu& doc)
{
    int x = str_hash(doc.fileName);
    if(x<0){
        x = -1*x;
    }
    try{
        documents.find(x, doc).useCount++;
    }
    //if an object is not found with that word then add it to the tree
    catch(exception e){
        documents.insertNode(x, doc);
    }
    /*bool found = false;
    int loc;
    for (int i = 0; i < documents.size(); i++)
    {
        if (documents[i].getFileName().compare(doc.getFileName()) == 0)
        {
            found = true;
            loc = i;
        }
    }

    if (!found)
    {
        documents.push_back(doc);
    }
    else
    {
        documents[loc].useCount++;
    }*/
}

HashTable<int, docu> word::returnDocVector(){
    return documents;
}

word& word::operator &(const word& val)
{
    thisWord = thisWord + "&" + val.thisWord;
    for(int i = 0; i < documents.returnCapacity(); i++){
        for(int j = 0; j<documents[i].size(); j++){
            int x = str_hash(documents.returnObject(i, j).getFileName());
            if(x<0){
                x = -1*x;
            }

            if(val.documents.contains(x, documents.returnObject(i, j)) == false){
                documents.removeNode(x, documents.returnObject(i, j));
            }
        }
    }
    /*for(int i = 0; i < documents.returnCapacity(); i++)
    {
        bool found = false;
        for(int j = 0; j < val.documents.size(); j++)
        {
            if (documents[i].getFileName().compare(val.documents[j].getFileName()) == 0)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            documents.erase(documents.begin() + i);
            i--;
        }
    }*/
    return *this;
}

word& word::operator |(const word& val)
{
    thisWord = thisWord + "|" + val.thisWord;
    for(int i = 0; i < documents.returnCapacity(); i++){
        for(int j = 0; j<documents[i].size(); j++){
            int x = str_hash(documents.returnObject(i, j).getFileName());
            if(x<0){
                x = -1*x;
            }

            if(val.documents.contains(x, documents.returnObject(i, j)) == false){
                documents.insertNode(x, documents.returnObject(i, j));
            }
        }
    }
    /*for(int i = 0; i < val.documents.size(); i++)
    {
        bool found = false;
        for (int j = 0; j < documents.size(); j++)
        {
            if (documents[j].getFileName().compare(val.documents[i].getFileName()) == 0)
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            docu temp = val.documents[i];
            documents.push_back(temp);
        }
    }*/
    return *this;
}

word& word::logicalNot(const word& val)
{

    thisWord = thisWord + "~" + val.thisWord;
    for(int i = 0; i < documents.returnCapacity(); i++){
        for(int j = 0; j<documents[i].size(); j++){
            int x = str_hash(documents.returnObject(i, j).getFileName());
            if(x<0){
                x = -1*x;
            }

            if(val.documents.contains(x, documents.returnObject(i, j)) == true){
                documents.removeNode(x, documents.returnObject(i, j));
            }
        }
    }
    /*for(int i = 0; i < documents.size(); i++)
    {
        bool found = false;
        for(int j = 0; j < val.documents.size(); j++)
        {
            if (documents[i].getFileName().compare(val.documents[j].getFileName()) == 0)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            documents.erase(documents.begin() + i);
            i--;
        }
    }*/
    return *this;
}

int word::getNumUses()
{
    int uses = 0;
    for (int i = 0; i < documents.returnCapacity(); i++)
    {
        for(int j =0; j<documents[i].size(); i++){
            uses+= documents.returnObject(i, j).getUseCount();
        }
    }
    return uses;
}

