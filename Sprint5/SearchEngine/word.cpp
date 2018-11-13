#include "word.h"

word::word()
{

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
    if (thisWord.compare(val.thisWord) == 0)
    {
        for (int i = 0; i < val.documents.size(); i++)
        {
            bool found = false;
            int j;
            for (j = 0; j < documents.size(); j++)
            {
                if (documents[i] == val.documents[j])
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

ostream & operator <<(ostream out, word& w)
{
    out << w.getPrev() << '|' << w.getWord() << "|";
    for (int i = 0; i < w.getNumDocs(); i++)
    {
        out << w.getDoc(i) << '|';
    }
    out << endl;
    return out;
}

int word::getNumDocs()
{
    return documents.size();
}

string word::getPrev()
{
    return previous;
}

string word::getWord()
{
    return thisWord;
}

docu& word::getDoc(int x)
{
    return documents[x];
}
