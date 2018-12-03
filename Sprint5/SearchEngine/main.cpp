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

/** Mode that allows users to clear the current index and parse additional files
 * @brief maintenanceMode
 * @param[in,out] avS AVLTree index for single word searches
 * @param[in,out] haS HashTable index for single word searches
 * @param[in,out] avD AVLTree index for double word searches
 * @param[in,out] haD HashTable index for double word searches
 * @param[in,out] type controls which data structure is used for searching
 * @param[in,out] wordCount keeps track of current number of parsed words
 * @param[in,out] fileCount keeps track of current number of files parsed
 */
void maintenanceMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool &type, int &wordCount, int &fileCount);

/** Mode that allows users to choose which data structure to use, search documents, and print some stats on the search engine
 * @brief userMode
 * @param[in,out] avS AVLTree index for single word searches
 * @param[in,out] haS HashTable index for single word searches
 * @param[in,out] avD AVLTree index for double word searches
 * @param[in,out] haD HashTable index for double word searches
 * @param[in,out] type controls which data structure is used for searching
 * @param[in,out] wordCount keeps track of current number of parsed words
 * @param[in,out] fileCount keeps track of current number of files parsed
 */
void userMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool &type, int &wordCount, int &fileCount);

int main(int argc, char* argv[])
{
    int fileCount = 0;
    int wordCount = 0;

    IndexerFace* avlSingle = new AVLIndex();
    IndexerFace* avlDouble = new AVLIndex();

    IndexerFace* hashTSingle = new HashIndex(500009);
    IndexerFace* hashTDouble = new HashIndex(500009);
    bool type = true;       //true is AVLTree / false is HashTable

    avlDouble->readIndexWithPrev(wordCount, fileCount);
    avlSingle->readIndexNoPrev(wordCount, fileCount);

    int choice;
    bool flag = true;
    while(flag) {
        cout << "Welcome to the Rule of Three's Search Engine!" << endl;

        if(type)
            cout << "(Currently using an AVLTree)" << endl;
        else
            cout << "(Currently using a HashTable)" << endl;

        cout << "Select your mode (Enter an int): \n1. Maitenance Mode \n2. User Mode \n3. Exit \nEnter Choice: ";
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
    avlSingle->clearStuff();
    avlDouble->clearStuff();
    hashTSingle->clearStuff();
    hashTDouble->clearStuff();
    return 0;
} //end main

void maintenanceMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool& type, int &wordCount, int &fileCount) {
    bool maitFlag = true;
    int maitChoice;
    while(maitFlag) {
        cout << "\n\n MAITENANCE MODE" << endl;
        if(type)
            cout << "(Currently using an AVLTree)" << endl;
        else
            cout << "(Currently using a HashTable)" << endl;
        cout << "1. Add Opinions to Index \n2. Clear the Index \n3. Exit \nEnter Choice: ";
        cin >> maitChoice;

        switch(maitChoice) {
        case 1: {
            cout << "Enter the file path: " << endl;
            string path;
            cin >> path;
            Parser dirParser(path, "../StopWordList.txt");
            cout << "PARSING DOCS..." << endl;
            if(type) {
                fileCount += dirParser.parseNew(wordCount, avD, avS);           //print
                ofstream oFile("../../../Index.txt"); //"../Index.txt"
                //avD->setWords(wordCount);
                //avD->setDocs(fileCount);
                avD->printIndex(oFile, wordCount, fileCount);
                //avS->clearStuff();
                //avS->readIndexNoPrev(wordCount, fileCount);
                oFile.close();
            } else {
                fileCount += dirParser.parseNew(wordCount, haD, haS);
                ofstream oFile("../../../Index.txt"); //"../Index.txt"
                //haD->setWords(wordCount);
                //haD->setDocs(fileCount);
                haD->printIndex(oFile, wordCount, fileCount);
                //haS->clearStuff();
                //haS->readIndexNoPrev(wordCount, fileCount);
                oFile.close();
            }
            break;
        } //case 1
        case 2: {
            if(type) {
                cout << "Clearing AVLTree..." << endl;
                avS->clearStuff();
                avD->clearStuff();
                wordCount = 0;
                fileCount = 0;
            } else {
                cout << "Clearing HashTable..." << endl;
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
    cout << endl << endl;
} //end maitenance mode


void userMode(IndexerFace* avS, IndexerFace* haS, IndexerFace* avD, IndexerFace* haD, bool& type, int &wordCount, int &fileCount) {
    bool userFlag = true;
    int userChoice;
    while(userFlag) {
        cout << "\n\n USER MODE \n1. Choose Which Data Structure to use \n2. Search any (properly formatted) query \n3. Get Statistics about our Search Engine \n4. Exit" << endl;
        cin >> userChoice;

        switch(userChoice) {
        case 1: {
            if(type)
                cout << "\n\n(Currently using an AVLTree)" << endl;
            else
                cout << "\n\n(Currently using a HashTable)" << endl;
            cout << "Do you want a(n) \n1. AVLTree \n2. Hash Table \nEnter Choice: ";
            int dataStruc;
            cin >>dataStruc;
            if(dataStruc == 1) {
                type = true;
                if(avD->isEmpty()) {
                    cout << "AVLTree currently empty, LOADING..." << endl;
                    //Parser dirParser("../../../scotus", "../StopWordList.txt");
                    wordCount = 0;
                    fileCount = 0;
                    avD->readIndexWithPrev(wordCount, fileCount);
                    avS->readIndexNoPrev(wordCount, fileCount);
                    //oFile.close();
                }
            } else if(dataStruc == 2) {
                type = false;
                if(haD->isEmpty()) {
                    cout << "HashTable currently empty, LOADING..." << endl;
                    //Parser dirParser("../../../scotus", "../StopWordList.txt");
                    wordCount = 0;
                    fileCount = 0;
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
            cout << "\nRule of Three Search Engine Statistics" << endl;
            cout << "Total Number of Opinions Indexed: " << fileCount << endl;
            cout << "Total Number of Words Indexed: " << wordCount << endl;
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
    cout << endl << endl;
} //end userMode
