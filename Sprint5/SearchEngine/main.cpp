/*Author: Nathan Srirama
 * Created (meaning actual UI created) 11/25/18
 * 11/26/18 Added pointers to index data structures
 * 11/27/18 Added functionality to swap between user and maitenance mode
 *          Functionality for clearing index
 *          Functionality for adding opinions
 * 11/28/18 Merged with Master to have QueryEngine and HashIndex
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
#include "queryengine.h"

using namespace std;


void maintenanceMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool &type, int &wordCount, int &fileCount);
void userMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool &type, int &wordCount, int &fileCount);

int main(int argc, char* argv[])
{
      cout << "PARSING DOCS" << endl;

      int x = 0;
      //int numFiles;
      clock_t start;
      float duration;
      start = clock();
      Parser dirParser(argv[1], "../StopWordList.txt");

    int fileCount = 0;
    int wordCount = 0;
    ofstream myFile("FinalIndex.txt");
    //IndexerFace* avlSingle = new AVLIndex();
    //IndexerFace* avlDouble = new AVLIndex();

    //IndexerFace* hashTSingle = new HashIndex(10000019);
    //IndexerFace* hashTDouble = new HashIndex(10000019);
    bool type = true;       //true is AVLTree / false is HashTable
    IndexerFace* fr  = new AVLIndex();
    //avlDouble->readIndexWithPrev(wordCount, fileCount);
    //avlSingle->readIndexNoPrev(wordCount, fileCount);
    int numFiles = dirParser.parse(x, fr);
    duration = (clock() - start) / (float) CLOCKS_PER_SEC;
    //fr->readIndexWithPrev(x, numFiles);
     string adju = argv[2];
     Porter2Stemmer::stem(adju);

     cout << "Number of words parsed: " << x << endl;
     cout << "Number of unique words: " << fr->returnSize() << endl;
     cout << "Number of documents parsed: " << numFiles << endl;
     cout << "Number of documents " << argv[2] << " was found in: ";
     int numDocs = fr->findWord(adju, adju).getNumDocs();
     cout << numDocs << endl;
     cout<<"time: "<<duration<<endl;
     //fr->printIndex(myFile, x, numFiles);
     fr->clearStuff();
//    delete fr;
    /*int choice;
    bool flag = true;
    while(flag) {
        cout << "Welcome to the Rule of Three's Search Engine!" << endl;
        cout << "Select your mode (Enter an int): \n\n1. Maitenance Mode \n2. User Mode \n3. Exit" << endl;
        cin >> choice;

        switch(choice) {
        case 1:
            maintenanceMode(avlSingle, hashTSingle, avlDouble, hashTDouble, type, wordCount, fileCount);
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
    return 0;*/
} //end main

void maintenanceMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool& type, int &wordCount, int &fileCount) {
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
                ofstream oFile("../Index.txt");
                //avD->setWords(wordCount);
                //avD->setDocs(fileCount);
                avD->printIndex(oFile, wordCount, fileCount);
                avS->clearStuff();
                avS->readIndexNoPrev(wordCount, fileCount);
                oFile.close();
            } else {
                fileCount += dirParser.parse(wordCount, haD);
                ofstream oFile("../Index.txt");
                //haD->setWords(wordCount);
                //haD->setDocs(fileCount);
                haD->printIndex(oFile, wordCount, fileCount);
                haS->clearStuff();
                haS->readIndexNoPrev(wordCount, fileCount);
                oFile.close();
            }
            break;
        } //case 1
        case 2: {
            if(type) {
                avS->clearStuff();
                avD->clearStuff();
                wordCount = 0;
                fileCount = 0;
            } else {
                haS->clearStuff();
                haD->clearStuff();
                wordCount = 0;
                fileCount = 0;
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


void userMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool& type, int &wordCount, int &fileCount) {
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
                    avD->readIndexWithPrev(wordCount, fileCount);
                    avS->readIndexNoPrev(wordCount, fileCount);
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
                    haD->readIndexWithPrev(wordCount, fileCount);
                    haS->readIndexNoPrev(wordCount, fileCount);
                    //oFile.close();
                }
            } else {
                cout << "You entered an invalid number \n\n" << endl;
            }
            break;
        } //case 1
        case 2: {
            QueryEngine* qe = new QueryEngine();
            qe->run(avS, haS, avD, haD, type);
            break;
        } //case 2
        case 3: {
            cout << "Rule of Three Search Engine Statistics" << endl;
            cout << "Total Number of Opinions Indexed: " << fileCount << endl;
            int avg = wordCount/fileCount;
            cout << "Average Number of Words Indexed per Opinion: " << avg << endl;
            break;
        } //case 3
        case 4:{
            userFlag = false;
            break;
        }//case 4
        default:
            cout << "You entered an invalid number \n\n" << endl;
        } //end switch
    } //end while
} //end userMode
