#include "stopper.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <dirent.h>
#include <set>

using namespace std;

Stopper::Stopper()
{

}


/** opens the file containing stopwords, makes sure the text file is formatted correctly.
 *  If it isn't the file is fixed before the tree is loaded. Then the tree is loaded with
 *  stop words so that it can be used.
 * @brief Stopper::readStopWords
 * @param[in] filename filepath and name of file contatining stopwords
 */
void Stopper::readStopWords(char *filename){
    ifstream input;
    input.open(filename);
    vector <string> temp;
    vector <string> temp2;
    bool check = false;
    if(input.is_open()){
        string hold;
        while(!input.eof()){
            getline(input, hold);
            for(unsigned int i = 0; i<hold.length(); i++){
               if(hold[i] == ' ' || hold[i] == '\r'){
                    hold.erase(i);
                }
            }
            temp.push_back(hold);
        }
    }
    for(unsigned int i =0; i<temp.size(); i++){
            for(unsigned int j =0; j<i; j++){
                if(temp[i] == temp[j]){
                    check = true;
                }
            }
            if(temp[i] != " " && check == false){
                temp2.push_back(temp[i]);
            }
            check = false;
    }
    for(unsigned int i = 0; i<temp2.size() ; i++){
        if(temp2[i].length() != 0){
            //stopWord[temp2[i].length() - 1].push_back(temp2[i]);
            stopWord.insert(temp2[i]);
        }
    }
}

/** the tree is searched to see if it is there, if it is returns true, returns
 *  false otherwise
 * @brief Stopper::isStopWord
 * @param[in] a word to be compared
 * @return
 */
bool Stopper::isStopWord(string &a){
    transform(a.begin(), a.end(), a.begin(), ::tolower);

    return stopWord.contains(a);
}
