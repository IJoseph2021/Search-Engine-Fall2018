#include <iostream>
#include <cstring>
#include <string>
#include <streambuf>
#include <vector>
#include <stdexcept>
#include <dirent.h>
#include "document.h"
#include "rapidjson.h"

using namespace std;
using namespace rapidjson;

#ifndef PARSER_H
#define PARSER_H


class Parser
{
private:
    string path;
    string extn;
    vector<string> get_files_at_path_with_extn();
    void parseHTML(string html, string fileN, int& count); //needs to also have instance of IndexerFace

public:
    Parser(string p, string ex = ".json");
    string getPath();
    string getExt();
    void parse(int& count);

};

#endif // PARSER_H
