#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>
#include <dirent.h>

using namespace std;

#ifndef PARSER_H
#define PARSER_H


class Parser
{
private:
    string path;
    string extn;
    //templatize?
    vector <vector<string>> stopWord;
public:
    Parser(string p, string ex = ".json");
    string getPath();
    string getExt();
    void parse();
    vector<string> get_files_at_path_with_extn();
    void readStopWords(char* filename);
    //templatize
    bool isStopWord(string a);
};

#endif // PARSER_H
