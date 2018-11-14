#ifndef DOCU_H
#define DOCU_H
#include <string>
#include <iostream>

using namespace std;

class docu
{
    friend class word;
private:
    string fileName;
    int useCount;
public:
    docu();
    docu(const docu& val);
    docu& operator=(const docu& val);
    ~docu();
    bool operator==(const docu& val);
    friend ostream& operator<<(ostream& out, docu& d);
    string getFileName();
    int getUseCount();
};

#endif // DOCU_H
