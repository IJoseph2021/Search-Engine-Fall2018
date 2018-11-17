#include <iostream>
#include <cstring>
#include <string>
#include <streambuf>
#include <vector>
#include <stdexcept>
#include <dirent.h>
#include "document.h"
#include "rapidjson.h"
#include "stopper.h"
#include "indexerface.h"
#include "avlindex.h"


using namespace std;
using namespace rapidjson;

#ifndef PARSER_H
#define PARSER_H


class Parser
{
private:
    string path;
    string extn;
    Stopper stahp;

    vector<string> get_files_at_path_with_extn();
    void parseHTML(string html, string fileN, int& count, IndexerFace*& index);
    bool checkPunct(char a);

public:
    Parser(string p, char* st, string ex = ".json");
    string getPath();
    string getExt();
    void parse(int& count, IndexerFace*& index);

};

#endif // PARSER_H
