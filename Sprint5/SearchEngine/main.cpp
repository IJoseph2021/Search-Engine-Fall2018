#include <iostream>
#include "StemmerFiles/porter2_stemmer.h"
using namespace std;

void stem(string& toStem)
{
    Porter2Stemmer::stem(toStem);
}

int main(int argc, char* argv[])
{
    string toStem = "crackalacking";
    stem(toStem);
    cout << toStem << endl;
    cout << "Hello World!" << endl;
    return 0;
}
