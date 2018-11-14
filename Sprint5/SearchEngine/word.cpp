#include "word.h"

word::word(){}

//create a word from the previous word and the current word
word::word(string prev, string curr)
{
    previous = prev;
    thisWord = curr;
}

//create a word with both words and the document filename
word::word(string prev, string curr, string doc)
{
    previous = prev;
    thisWord = curr;
    docu tempDoc(doc);
    documents.push_back(tempDoc);
}

//copy constructor
word::word(const word& val)
{
    thisWord = val.thisWord;
    previous = val.previous;
    //create a temporary vector with the contents of val's vector and swap them into documents
    vector<docu> tempVec= val.documents;
    documents.swap(tempVec);
}

word& word::operator=(const word& val)
{
    thisWord = val.thisWord;
    previous = val.previous;
    vector<docu> tempVec= val.documents;
    documents.swap(tempVec);
    return *this;
}

word::~word()
{
    documents.clear();
}

//overloaded + operator which simply merges two words by combining their document vectors,
//adding any new documents and incrementing existing document's use counts
word& word::operator +(const word& val)
{
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
}

//overloaded < operator which compares the value of the current word to the passed word
//returns true if it is smaller
bool word::operator < (const word& val)
{
    if (thisWord.compare(val.thisWord) < 0)
        return true;
    else
        return false;
}

//overloaded > operator functions the same as <
bool word::operator > (const word& val)
{
    if (thisWord.compare(val.thisWord) > 0)
        return true;
    else
        return false;
}

//overloaded comparison operator to see if two words have the same word string
bool word::operator==(const word& val)
{
    if (thisWord.compare(val.thisWord) == 0)
        return true;
    else
        return false;
}

//print the previous word, this word, and document vector to ostream out
ostream& operator<<(ostream& out, const word& w)
{
    out << w.getPrev() << '|' << w.getWord() << "|";
    for (int i = 0; i < w.getNumDocs(); i++)
    {
        out << "-|";
        docu tempDoc = w.getDoc(i);
        out << tempDoc;
    }
    out << endl;
    return out;
}

int word::getNumDocs() const
{
    return documents.size();
}

string word::getPrev() const
{
    return previous;
}

string word::getWord() const
{
    return thisWord;
}

docu word::getDoc(int x) const
{
    return documents[x];
}

//add a new document to the word's document vector with the name of docName
void word::addDoc(string docName)
{
    //loop through documents to see if the document is already contained
    bool found;
    int loc = -1;
    for (int i = 0; i < documents.size(); i++)
    {
        if (documents[i].getFileName().compare(docName)==0)
        {
            found = true;
            loc = i;
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
    }
}

//add an existing document to the word's doc vector with same logic as string version
void word::addDoc(docu& doc)
{
    bool found = false;
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
    }
}


