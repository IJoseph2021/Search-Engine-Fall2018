#include "parser.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>
#include <dirent.h>
#include <fstream>

using namespace std;

Parser::Parser(string p, string ex)
{
    path = p;
    extn = ex;
    vector <vector<string>> (40);
}

void Parser::parse() {
    vector<string> files = get_files_at_path_with_extn();

    for(int j = 0; j < files.size(); j++) {
        cout << files[j] << endl;

    }
}

vector<string> Parser::get_files_at_path_with_extn() {
    vector<string> result;
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            int len = strlen(ent->d_name);
            if (ent->d_type == DT_REG &&
                len > extn.length() && strcmp(ent->d_name + len - extn.length(), extn.c_str()) == 0)
                result.push_back(ent->d_name);
        }
        closedir(dir);
    }
    else {
        throw invalid_argument("Provided path could not be opened");
    }
    return result;
}

string Parser::getPath() { return path; }
string Parser::getExt() { return extn; }


