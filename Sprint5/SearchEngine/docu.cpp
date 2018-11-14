#include "docu.h"

docu::docu(){}

//create a document from a passed filename string
docu::docu(string name)
{
    fileName = name;
    useCount = 1;
}

//copy constructor
docu::docu(const docu& val)
{
    fileName = val.fileName;
    useCount = val.useCount;
}
docu& docu::operator=(const docu& val)
{
    fileName = val.fileName;
    useCount = val.useCount;
}
docu::~docu()
{
    useCount = 0;
}

//overloaded comparison which returns true if the two docs have the same filename
bool docu::operator ==(const docu& val)
{
    if (fileName.compare(val.fileName) == 0)
        return true;
    else
        return false;
}

//overloaded stream insertion which prints the file name and
//its usecount in a particular word to ostream out
ostream& operator<<(ostream& out, docu& d)
{
    out << d.getFileName();
    out << '|';
    out << d.getUseCount();
    out << '|';
    return out;
}

string docu::getFileName() const
{
    return fileName;
}

int docu::getUseCount() const
{
    return useCount;
}
