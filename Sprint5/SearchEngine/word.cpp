#include "word.h"

word::word()
{

}

word::word(string prev, string curr)
{
    previous = prev;
    thisWord = curr;
}

word::word(string prev, string curr, string doc)
{
    previous = prev;
    thisWord = curr;
    docu tempDoc(doc);
    documents.push_back(tempDoc);
}
word::word(const word& val)
{
    thisWord = val.thisWord;
    previous = val.previous;
    for (int i = 0; i < val.documents.size(); i++)
    {
        documents.push_back(val.documents[i]);
    }
}

word& word::operator=(const word& val)
{
    thisWord = val.thisWord;
    previous = val.previous;
    for (int i = 0; i < val.documents.size(); i++)
    {
        documents.push_back(val.documents[i]);
    }
}

word::~word()
{
    documents.clear();
}

word& word::operator +(const word& val)
{
    //if words are the same
    if (thisWord.compare(val.thisWord) == 0)
    {
        for (int i = 0; i < val.documents.size(); i++)
        {
            bool found = false;
            int j;
            for (j = 0; j < documents.size(); j++)
            {
                if (documents[j] == val.documents[i])
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                documents.push_back(val.documents[i]);
            }
            else
            {
                documents[j].useCount++;
            }
        }
    }
    else
    {
        throw logic_error("not the same word in word::operator+");
    }
    return *this;
}
bool word::operator < (const word& val)
{
    if (thisWord.compare(val.thisWord) < 0)
        return true;
    else
        return false;
}
bool word::operator > (const word& val)
{
    if (thisWord.compare(val.thisWord) > 0)
        return true;
    else
        return false;
}
bool word::operator==(const word& val)
{
    if (thisWord.compare(val.thisWord) == 0)
        return true;
    else
        return false;
}

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

void word::addDoc(string docName)
{
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


