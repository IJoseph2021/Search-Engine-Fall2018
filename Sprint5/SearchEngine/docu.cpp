#include "docu.h"

docu::docu()
{

}
docu::docu(string name)
{
    fileName = name;
    useCount = 1;
}
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

bool docu::operator ==(const docu& val)
{
    if (fileName.compare(val.fileName) == 0)
        return true;
    else
        return false;
}

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
