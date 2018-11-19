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
    //stopWord.resize(100);
}



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
            for(int i = 0; i<hold.length(); i++){
               if(hold[i] == ' ' || hold[i] == '\r'){
                    hold.erase(i);
                }
            }
            temp.push_back(hold);
        }
    }
    for(int i =0; i<temp.size(); i++){
            for(int j =0; j<i; j++){
                if(temp[i] == temp[j]){
                    check = true;
                }
            }
            if(temp[i] != " " && check == false){
                temp2.push_back(temp[i]);
            }
            check = false;
    }
    for(int i = 0; i<temp2.size() ; i++){
        if(temp2[i].length() != 0){
            //stopWord[temp2[i].length() - 1].push_back(temp2[i]);
            stopWord.insert(temp2[i]);
        }
    }
}


bool Stopper::isStopWord(string &a){
    transform(a.begin(), a.end(), a.begin(), ::tolower);
    /*int x = a.length() - 1;
    for(int i = 0; i<stopWord[x].size(); i++){
        if(a == stopWord[x][i] || a == "\n"){
            return true;
        }
    }*/
    return stopWord.contains(a);
//    if(stopWord.find(a) != stopWord.end())
//        return true;
//    else
//        return false;
    //return false;
}
