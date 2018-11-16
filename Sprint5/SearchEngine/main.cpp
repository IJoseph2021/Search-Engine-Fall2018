#include <iostream>
#include "parser.h"
#include <ctime>
using namespace std;

int main(int argc, char* argv[])
{
    clock_t start;
    float duration;

    cout << "Hello World!" << endl;

    start = clock();
    Parser dirParser("../../../scotus");
    dirParser.parse();

    duration = (clock() - start) / (float) CLOCKS_PER_SEC;
    cout << duration << endl;
    return 0;
}
