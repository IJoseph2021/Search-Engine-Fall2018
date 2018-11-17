/*Author: Nathan Srirama
 * created 11/09/18
 * 11/13/18 added RapidJSON
 * 11/15/18 Started HTML parsing to add to Index data structure
 */
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
//#include "json.hpp"

using namespace std;
using namespace rapidjson;
//using json = nlohmann::json;

Parser::Parser(string p, string ex)
{
    path = p;
    extn = ex;
    //vector <vector<string>> (40);
}

void Parser::parse(int& count) {
    ifstream iFile;
    string openPath;

    vector<string> files = get_files_at_path_with_extn();


    for(unsigned int j = 0; j < files.size(); j++) {
        iFile.open(this->getPath()+ "/" + files[j]);
        if(iFile.is_open()) {
            Document doc;

            iFile.seekg(0, ios::end);
            long file_length = iFile.tellg();
            iFile.clear();
            iFile.seekg(0, ios::beg);

            char str[file_length];

            iFile.read(str, file_length);
            doc.Parse<kParseStopWhenDoneFlag>(str);

            if(doc["html"].IsString()) {      //All files have html member but some are written as NULL
                parseHTML(doc["html"].GetString(), files[j], count);
            }

            iFile.close();
        } //end iFile is_open
    } //end for loop
} //end parse function

void Parser::parseHTML(string html, string fileN, int& count) {
    int find;
    string word = "";
    string previousString;
    for(unsigned int j = 0; j < html.length(); j++) {
        if(isspace((int)html[j]) == 0 && !ispunct(html[j])) {
            word += html[j];
        } else {
            //only do shit if string is != ""
            if(!word.empty()) {
                find = word.find_last_of(">");
                if(find != -1)
                    word = word.substr(find+1, word.length()-find);

                find = word.find_first_of("<");
                if(find == -1 && !word.empty()) {
                    count++;
                    //make word object
                    //update previousString
                }

                word = "";
            }

        }  //finding complete word
    }  //end for loop through buffer
} //end parseHTML

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


