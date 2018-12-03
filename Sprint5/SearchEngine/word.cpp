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
    documents.push_back(doc);
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
        documents.push_back(val.getDoc(i));
    }
    return *this;
}

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
       (previous.compare(val.previous) == 0))
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
        out << w.getDoc(i);
    }
    out << "|";
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

string word::getDoc(int x) const
{
    return documents[x];
}

string &word::getLitDoc(int x)
{
    return documents[x];
}

//add a new document to the word's document vector with the name of docName
void word::addDoc(string docName)
{
    documents.push_back(docName);
}

word& word::operator &(const word& val)
{
    thisWord = thisWord + "&" + val.thisWord;
    for (unsigned int i = 0; i < documents.size(); i++)
    {
        for (unsigned int j = 0; j < val.documents.size(); j++)
        {
            if (documents[i].compare(val.documents[j]) == 0)
            {
                documents.erase(documents.begin() + i--);
                break;
            }
        }
    }
}
word& word::operator |(const word& val)
{
    thisWord = thisWord + "|" + val.thisWord;
    for(unsigned int i = 0; i < val.documents.size(); i++)
    {
        documents.push_back(val.documents[i]);
    }
    return *this;
}

word& word::logicalNot(const word& val)
{

    thisWord = thisWord + "~" + val.thisWord;
    for(unsigned int i = 0; i < documents.size(); i++)
    {
        for(unsigned int j = 0; j < val.documents.size(); j++)
        {
            if (documents[i].compare(val.documents[j]) == 0)
            {
                documents.erase(documents.begin() + i--);
            }
        }
    }
    return *this;
}

int word::getNumUses()
{
    return documents.size();
}

int word::getDocUses(int x)
{
    int found = 0;
    for (int i = 0; i < documents.size(); i++)
    {
        if (documents[x].compare(documents[i]))
            found++;
    }
    return found;
}

vector<string>& word::returnDocVector()
{
    return documents;
}
