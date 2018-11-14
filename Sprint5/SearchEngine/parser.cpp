#include "parser.h"
#include <iostream>
#include <cstring>
#include <string>
#include <streambuf>
#include <vector>
#include <stdexcept>
#include <dirent.h>
#include <fstream>
#include "document.h"
#include "rapidjson.h"
#include "istreamwrapper.h"

using namespace std;
using namespace rapidjson;

Parser::Parser(string p, string ex)
{
    path = p;
    extn = ex;
    vector <vector<string>> (40);
}

void Parser::parse() {
    ifstream iFile;
    string openPath;

    vector<string> files = get_files_at_path_with_extn();

    for(int j = 0; j < 2/*files.size()*/; j++) {
        openPath = this->getPath()+ "/" + files[j];
        iFile.open(openPath);
        if(iFile.is_open()) {
            Document doc;
            //IStreamWrapper iws(iFile);
            iFile.seekg(0, ios::end);
            long file_length = iFile.tellg();
            iFile.clear();
            iFile.seekg(0, ios::beg);

            char str[file_length];
            iFile.read(str, file_length);
            doc.Parse(str);
            //cout << doc["plaintext"].GetString() << endl;
            //cout << doc["html"].GetString() << endl;
            iFile.close();
        }
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


