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
public:
    Parser(string p, string ex = ".json");
    string getPath();
    string getExt();
    void parse();
    vector<string> get_files_at_path_with_extn();
};

#endif // PARSER_H
