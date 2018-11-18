/*Author: Nathan Srirama
 * created 11/09/18
 * 11/13/18 added RapidJSON
 * 11/15/18 Started HTML parsing to add to Index data structure
 * 11/16/18 Finished HTML parsing, ready to merge with word class and data structures
 * 11/17/18 Trees, Index Interface, Stopper & stemmer merged into Parser, parsing complete
 *          Starting to work on efficiency
 */
#include "parser.h"
#include <algorithm>
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
#include "StemmerFiles/porter2_stemmer.h"
//#include "json.hpp"

using namespace std;
using namespace rapidjson;
//using json = nlohmann::json;

Parser::Parser(string p, char* st, string ex)
{
    path = p;
    extn = ex;
    stahp.readStopWords(st);
}


/*
 * parse handles all parse functionality. Reads all files to be parsed from directory into vector of strings,
 * then iterates through vector. FIles are opened and read into a DOM tree, from which the html attribrute is
 * retreived and passed to HTML parser to be parsed into Tree data structure
 */

void Parser::parse(int& count, IndexerFace*& index) {        //count used solely to find number of words parsed
    ifstream iFile;
    string openPath;

    vector<string> files = get_files_at_path_with_extn();


    for(unsigned int j = 0; j < 1000/*files.size()*/; j++) {
        iFile.open(this->getPath()+ "/" + files[j]);
        if(iFile.is_open()) {
            Document doc;

            iFile.seekg(0, ios::end);
            long file_length = iFile.tellg();
            iFile.clear();
            iFile.seekg(0, ios::beg);

            char str[file_length];

            iFile.read(str, file_length);
            doc.Parse<kParseStopWhenDoneFlag>(str);                 //reads string buffer into a DOM tree separated by JSON tags
            if(doc["html"].IsString()) {      //All files have html member but some are written as NULL
                parseHTML(doc["html"].GetString(), files[j], count, index);    //pass HTML off to separate parser, along with document name
            }                                                           //and counter for words parsed

            iFile.close();
        } //end iFile is_open
    } //end for loop
} //end parse function

/*
 * takes string representing the HTML document, file name, and integer count for total words parsed
 * the html is parsed using character comparisons, and strings are built until spaces are found.
 * at that point tags are parsed out, and if a string remains it is stored in the Tree alongside
 * the document it was found in. Punctuation is handled to an extent.
 */
void Parser::parseHTML(string html, string fileN, int& count, IndexerFace*& index) {
    int find;
    string word = "";
    string previousString;
    for(unsigned int j = 0; j < html.length(); j++) {
        if(isspace((int)html[j]) == 0) {
            if(checkPunct(html[j]))
                word += html[j];
        } else {
            //only do shit if string is != ""
            if(!word.empty()) {
                find = word.find_last_of(">");
                if(find != -1)
                    word = word.substr(find+1, word.length()-find);

                find = word.find_first_of("<");
                if(find == -1 && !word.empty()) {
                    if(!stahp.isStopWord(word)) {
                        count++;
                        Porter2Stemmer::stem(word);
                        index->insert(word, fileN);
                        //previousString = word
                        //cout << word <<endl;
                        //make word object
                        //update previousString
                    }
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

inline bool Parser::checkPunct(char a) {
    return (a!='.' && a!=',' && a!='\"' && a!=';' && a!=':' && a!='?' && a!='/' && a!='*' && a!='(' && a!=')');
}

string Parser::getPath() { return path; }
string Parser::getExt() { return extn; }


