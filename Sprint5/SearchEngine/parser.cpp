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
#include <map>
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

int Parser::parse(int& count, IndexerFace*& index) {        //count used solely to find number of words parsed
    ifstream iFile;
    string openPath;
    //typedef map<string, string> mapType;
    map<string, string> stemmap;

    vector<string> files = get_files_at_path_with_extn();



    for(unsigned int j = 0; j < 000/*files.size()*/; j++) {
        iFile.open(this->getPath()+ "/" + files[j]);
        if(iFile.is_open()) {
            Document doc;
            streampos file_length = iFile.tellg();
            iFile.seekg(0, ios::end);
            file_length = iFile.tellg() - file_length;
            long file_len = (long)file_length;
            //cout<<"file length:"<<file_length<<endl;
            iFile.clear();
            iFile.seekg(0, ios::beg);
            char str[file_len];
            iFile.read(str, file_len);
            doc.Parse<kParseStopWhenDoneFlag>(str);                 //reads string buffer into a DOM tree separated by JSON tags
            if(doc["html"].IsString()) {      //All files have html member but some are written as NULL
                parseHTML(doc["html"].GetString(), this->getPath() +"/" + files[j], count, stemmap, index);    //pass HTML off to separate parser, along with document name
            }                                                           //and counter for words parsed
            iFile.close();

        } //end iFile is_open
    } //end for loop
    return files.size();
} //end parse function

/*
 * takes string representing the HTML document, file name, integer count for total words parsed,
 * and a map for the stemmed words. The html is parsed using character comparisons, and strings
 * are built until spaces are found. At that point tags are parsed out, and if a string remains
 * it is checked against stop words and stemmed with the map. Whatever's left stored in the Tree
 * alongside the document it was found in. Punctuation is handled to an extent.
 */
void Parser::parseHTML(string html, string fileN, int& count, map<string, string>& aStem, IndexerFace*& index) {
    int find;
    string word = "";
    string previousString = "";
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
                        word = stemWord(word, aStem);//Porter2Stemmer::stem(word);
                        index->insert(word, previousString, fileN);
                         previousString = word;
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

inline string Parser::stemWord(string word, map<string, string> &aStem) {
    if(aStem.find(word) != aStem.end()) {
        return aStem[word];
    } else {
        string key = word;
        Porter2Stemmer::stem(word);
        aStem.insert(pair<string, string>(key, word));
        return word;
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

inline bool Parser::checkPunct(char a) {
    return (a!='.' && a!=',' && a!='\"' && a!=';' && a!=':' && a!='?' && a!='/' && a!='*' && a!='(' && a!=')' && a!='|');
}

string Parser::getPath() { return path; }
string Parser::getExt() { return extn; }


