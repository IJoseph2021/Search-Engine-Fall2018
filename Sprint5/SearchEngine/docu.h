//owner:Patrick
//created: 11/13/18
#ifndef DOCU_H
#define DOCU_H
#include <string>
#include <iostream>

using namespace std;

class docu
{
    friend class word;
private:
    string fileName; ///!< file name and path of the document
    int useCount; ///!< times this document was used in a given word
public:
    docu();
    /**
     * @brief docu - constructs a document from a file path alone
     * @param name - the file path
     */
    docu(string name);
    /**
     * @brief docu - constructs a document from a file path and use count
     * @param name - file path
     * @param used - use count
     */
    docu(string name, int used);
    /**
     * @brief docu - copy constructor
     * @param val - document to copy
     */
    docu(const docu& val);
    /**
     * @brief operator = - overloaded =
     * @param val - document to copy
     * @return - returns document to allow chained =
     */
    docu& operator=(const docu& val);
    ~docu();
    /**
     * @brief operator == - overloaded equivilancy compairson
     * @param val - document to compare against
     * @return - returns a bool, true if equal
     */
    bool operator==(const docu& val);
    /**
     * @brief operator << - overloaded stream insertion operator
     * @param out - ostream to print to
     * @param d - document to print
     * @return - returns the ostream to allow chained prints
     */
    friend ostream& operator<<(ostream& out, docu& d);
    string getFileName() const;
    int getUseCount() const;
};

#endif // DOCU_H
