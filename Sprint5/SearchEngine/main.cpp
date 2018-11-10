#include <iostream>
#include "parser.h"
using namespace std;

int main(int argc, char* argv[])
{
    cout << "Hello World!" << endl;

    Parser dirParser("../../../scotus");
    dirParser.parse();

    return 0;
}
