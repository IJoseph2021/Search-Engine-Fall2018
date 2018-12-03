#include <iostream>
#include <cstring>
#include <string>
#include <streambuf>
#include <vector>
#include <stdexcept>
#include <dirent.h>
#include <map>
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
    string path; //!< the filepath in which the files waiting to be parsed reside
    string extn; //!< the extension appended to files
    Stopper stahp; //!< Stopper that gets rid of stopwords at parsetime

    /**
     * @brief get_files_at_path_with_extn finds files to parse from path
     */
    vector<string> get_files_at_path_with_extn();

    /** This function parses the HTML within a .json file using a buffer
     * @brief parseHTML
     * @param[in] html buffer containing an entire HTML file
     * @param[in] fileN file name
     * @param[in,out] count current count of words parsed
     * @param[in,out] aStem map of words already stemmed
     * @param[in,out] index Data structure to insert words into
     */
    void parseHTML(string html, string fileN, int& count, map<string, string>& aStem, IndexerFace*& index);
    void parseNewHTML(string html, string fileN, int& count, map<string, string>& aStem, IndexerFace*& d, IndexerFace*& s);

    /** Function to stem words
     * @brief stemWord
     * @param[in] word word to stem
     * @param[in,out] aStem map of words already stemmed
     */
    string stemWord(string word, map<string, string>& aStem);

    /** Function to ignore punctuation when parsing
     * @brief checkPunct
     * @param[in] a character to be compared to punctuation
     */
    bool checkPunct(char a);

public:
    /** Constructor to create a parsing object
     * @brief Parser
     * @param[in] p path to files
     * @param[in] st path to stopwordlist.txt
     * @param[in] ex extension on files
     */
    Parser(string p, char* st, string ex = ".json");
    string getPath();
    string getExt();
    int parse(int& count, IndexerFace*& index);
    int parseNew(int& count, IndexerFace*& d, IndexerFace*& s);

};

#endif // PARSER_H
