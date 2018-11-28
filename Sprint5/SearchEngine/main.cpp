/*Author: Nathan Srirama
 * Created (meaning actual UI created) 11/25/18
 * 11/26/18 Added pointers to index data structures
 * 11/27/18 Added functionality to swap between user and maitenance mode
 *          Functionality for clearing index
 *          Functionality for adding opinions
 *
 *
 */

#include <iostream>
#include "parser.h"
#include "StemmerFiles/porter2_stemmer.h"
#include "avltree.h"
#include "word.h"
#include "stopper.h"
#include "indexerface.h"
#include "avlindex.h"
#include "hashtable.h"
#include "hashindex.h"
#include <fstream>

using namespace std;

void maitenanceMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool &type, int &wordCount, int &fileCount);
void userMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool &type, int &wordCount, int &fileCount);

int main(int argc, char* argv[])
{
//    cout << "PARSING DOCS" << endl;

//    int x = 0;

//    clock_t start;
//    float duration;
//    start = clock();
//    Parser dirParser(argv[1], "../StopWordList.txt");

    int fileCount = 0;
    int wordCount = 0;

    IndexerFace* avlSingle = new AVLIndex();
    IndexerFace* avlDouble = new AVLIndex();

    IndexerFace* hashTSingle = new HashIndex(500009);
    IndexerFace* hashTDouble = new HashIndex(500009);
    bool type = true;       //true is AVLTree / false is HashTable

    avlDouble->readIndexWithPrev();
    avlSingle->readIndexNoPrev();
//    int numFiles = dirParser.parse(x, fr);
//    duration = (clock() - start) / (float) CLOCKS_PER_SEC;

//    string adju = argv[2];
//    Porter2Stemmer::stem(adju);

//    cout << "Number of words parsed: " << x << endl;
//    cout << "Number of unique words: " << fr->returnSize() << endl;
//    cout << "Number of documents parsed: " << numFiles << endl;
//    cout << "Number of documents " << argv[2] << " was found in: ";
//    int numDocs = fr->findWord(adju).getNumDocs();
//    cout << numDocs << endl;
//    cout<<"time: "<<duration<<endl;
//    fr->clearStuff();
//    delete fr;
    int choice;
    bool flag = true;
    while(flag) {
        cout << "Welcome to the Rule of Three's Search Engine!" << endl;
        cout << "Select your mode (Enter an int): \n\n1. Maitenance Mode \n2. User Mode \n3. Exit" << endl;
        cin >> choice;

        switch(choice) {
        case 1:
            maitenanceMode(avlSingle, hashTSingle, avlDouble, hashTDouble, type, wordCount, fileCount);
            break;
        case 2:
            userMode(avlSingle, hashTSingle, avlDouble, hashTDouble, type, wordCount, fileCount);
            break;
        case 3:
            flag = false;
            break;
        default:
            cout << "You entered an invalid number" << endl;
        } //end switch
    } //end while
    return 0;
} //end main

void maitenanceMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool type, int &wordCount, int &fileCount) {
    bool maitFlag = true;
    int maitChoice;
    while(maitFlag) {
        cout << "1. Add Opinions to Index \n2. Clear the Index \n3. Exit" << endl;
        cin >> maitChoice;

        switch(maitChoice) {
        case 1: {
            cout << "Enter the file path: " << endl;
            string path;
            cin >> path;
            Parser dirParser(path, "../StopWordList.txt");
            if(type) {
                fileCount += dirParser.parse(wordCount, avD);           //print
                ofstream oFile("Index.txt");
                //avD->setWords(wordCount);
                //avD->setDocs(fileCount);
                avD->printIndex(oFile);
                avS->clearStuff();
                avS->readIndexNoPrev();
                oFile.close();
            } else {
                fileCount += dirParser.parse(wordCount, haD);
                ofstream oFile("Index.txt");
                //haD->setWords(wordCount);
                //haD->setDocs(fileCount);
                haD->printIndex(oFile);
                haS->clearStuff();
                haS->readIndexNoPrev();
                oFile.close();
            }
            break;
        } //case 1
        case 2: {
            if(type) {
                avS->clearStuff();
                avD->clearStuff();
            } else {
                haS->clearStuff();
                haD->clearStuff();
            }
            break;
        } //case 2
        case 3: {
            maitFlag = false;
            break;
        } //case 3
        default:
            cout << "You entered an invalid number \n\n" << endl;
        } //end switch
    } //end while
} //end maitenance mode


void userMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool type, int &wordCount, int &fileCount) {
    bool userFlag = true;
    int userChoice;
    while(userFlag) {
        cout << "1. Choose Which Data Structure to use \n2. Search any (properly formatted) query \n3. Get Statistics about our Search Engine \n4. Exit" << endl;
        cin >> userChoice;

        switch(userChoice) {
        case 1: {
            cout << "Do you want a(n) \n1. AVLTree \n2. Hash Table" << endl;
            int dataStruc;
            cin >>dataStruc;
            if(dataStruc == 1) {
                type = true;
                if(avD->isEmpty()) {
                    //Parser dirParser("../../../scotus", "../StopWordList.txt");
                    wordCount = 0;
                    fileCount = 0;
                    //fileCount = dirParser.parse(wordCount, avD);

                    //avD->setWords(wordCount);
                    //avD->setDocs(fileCount);
                    //avD->printIndex(oFile);
                    //avS->clearStuff();
                    avD->readIndexWithPrev();
                    avS->readIndexNoPrev();
                    //oFile.close();
                }
            } else if(dataStruc == 2) {
                type = false;
                if(haD->isEmpty()) {
                    //Parser dirParser("../../../scotus", "../StopWordList.txt");
                    wordCount = 0;
                    fileCount = 0;
                    //fileCount = dirParser.parse(wordCount, haD);
                    //ofstream oFile("Index.txt");
                    //haD->setWords(wordCount);
                    //haD->setDocs(fileCount);
                    //haD->printIndex(oFile);
                    //haS->clearStuff();
                    haD->readIndexWithPrev();
                    haS->readIndexNoPrev();
                    //oFile.close();
                }
            } else {
                cout << "You entered an invalid number \n\n" << endl;
            }
            break;
        } //case 1
        case 2: {

            break;
        } //case 2
        case 3: {
            cout << "Rule of Three Search Engine Statistics" << endl;
            cout << "Total Number of Opinions Indexed: " << fileCount << endl;
            int avg = wordCount/fileCount;
            cout << "Average Number of Words Indexed per Opinion: " << avg << endl;
            break;
        } //case 3
        default:
            cout << "You entered an invalid number \n\n" << endl;
        } //end switch
    } //end while
} //end userMode
