#include "queryengine.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rapidjson.h"

QueryEngine::QueryEngine()
{
}
void QueryEngine::takeQuery(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type, word& docTracker, bool& searching)
{
    vector<string> unstemmedQueries;
    vector<string> queries;
    string query = "";
    cout << "Enter your query to search or EXIT to exit" << endl;
    cin.ignore();
    getline(cin, query);
    Stopper stop;
    stop.readStopWords("../StopWordList.txt");
    while (!query.empty())
    {
        string temp = "";
        int pos = query.find(" ");
        if (pos == -1)
        {
            temp = query;
            query.erase(0, query.length());
        }
        else
        {
            temp = query.substr(0, pos);
            query.erase(0, pos+1);
        }
        if (temp.compare("AND") !=0 && temp.compare("OR") != 0 && temp.compare("NOT") != 0 && temp.compare("EXIT") != 0)
        {
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            if (!stop.isStopWord(temp))
                unstemmedQueries.push_back(temp);
        }
        else
            unstemmedQueries.push_back(temp);
    }
    queries = unstemmedQueries;
    if (queries[0].compare("EXIT") == 0)
    {
        searching = false;
        return;
    }
    for (int i = 0; i < queries.size(); i++)
    {
        Porter2Stemmer::stem(queries[i]);
    }
    bool leading = false;
    bool AND = false;
    bool OR = false;
    bool NOT = false;
    for (int i = 0; i < queries.size(); i++)
    {
        try
        {
            if (!leading)
            {
                AND = false;
                OR = false;
                NOT = false;
            }

            string firstWord="";
            string secondWord="";
            bool twoWords = (queries[i].at(0) == '[');
            if (twoWords)
            {
                firstWord = queries[i].substr(1, queries[i].length() -1);
                i++;
                secondWord = queries[i].substr(0, queries[i].length() -2);
                Porter2Stemmer::stem(secondWord);
            }

            if (queries[i].compare("AND") == 0)
            {
                if (i == 0)
                {
                    leading = true;
                    AND = true;
                }
                else
                {
                    if (twoWords)
                    {
                        if (type)
                            docTracker & avD->findWord(secondWord, firstWord);
                        else
                            docTracker & haD->findWord(secondWord, firstWord);
                    }
                    else
                    {
                        i++;
                        if (type)
                            docTracker & avS->findWord(queries[i], queries[i]);
                        else
                            docTracker & haS->findWord(queries[i], queries[i]);
                    }
                }
            }
            else if (queries[i].compare("OR") == 0)
            {
                if (i == 0)
                {
                    leading = true;
                    OR = true;
                }
                else
                {
                    if (twoWords)
                    {
                        if (type)
                            docTracker | avD->findWord(secondWord, firstWord);
                        else
                            docTracker | haD->findWord(secondWord, firstWord);
                    }
                    else
                    {
                        i++;
                        if (type)
                            docTracker | avS->findWord(queries[i], queries[i]);
                        else
                            docTracker | haS->findWord(queries[i], queries[i]);
                    }
                }
            }
            else if (queries[i].compare("NOT") == 0)
            {
                if (i == 0)
                {
                    leading = true;
                    NOT = true;
                }
                else
                {
                    if (twoWords)
                    {
                        if (type)
                            docTracker.logicalNot(avS->findWord(secondWord, firstWord));
                        else
                            docTracker.logicalNot(haS->findWord(secondWord, firstWord));
                    }
                    else
                    {
                        i++;
                        if (type)
                            docTracker.logicalNot(avS->findWord(queries[i], queries[i]));
                        else
                            docTracker.logicalNot(haS->findWord(queries[i], queries[i]));
                    }
                }
            }
            else
            {
                if (leading)
                {
                    if (i == 1)
                    {
                        if (twoWords)
                        {
                            if (type)
                                docTracker = avD->findWord(secondWord, firstWord);
                            else
                                docTracker = haD->findWord(secondWord, firstWord);
                        }
                        else
                        {
                            if (type)
                                docTracker = avS->findWord(queries[i], queries[i]);
                            else
                                docTracker = haS->findWord(queries[i], queries[i]);
                        }
                    }
                    else if (AND)
                    {
                        if (twoWords)
                        {
                            if (type)
                                docTracker & avD->findWord(secondWord, firstWord);
                            else
                                docTracker & haD->findWord(secondWord, firstWord);
                        }
                        else
                        {
                            if (type)
                                docTracker & avS->findWord(queries[i], queries[i]);
                            else
                                docTracker & haS->findWord(queries[i], queries[i]);
                        }
                    }
                    else if (OR)
                    {
                        if (twoWords)
                        {
                            if (type)
                                docTracker | avD->findWord(secondWord, firstWord);
                            else
                                docTracker | haD->findWord(secondWord, firstWord);
                        }
                        else
                        {
                            if (type)
                                docTracker | avS->findWord(queries[i], queries[i]);
                            else
                                docTracker | haS->findWord(queries[i], queries[i]);
                        }
                    }
                    else if(NOT)
                    {
                        if (twoWords)
                        {
                            if (type)
                                docTracker.logicalNot(avD->findWord(secondWord, firstWord));
                            else
                                docTracker.logicalNot(haD->findWord(secondWord, firstWord));
                        }
                        else
                        {
                            if (type)
                                docTracker.logicalNot(avS->findWord(queries[i], queries[i]));
                            else
                                docTracker.logicalNot(haS->findWord(queries[i], queries[i]));
                        }
                    }
                }
                else
                {
                    if (twoWords)
                    {
                        if (type)
                            docTracker = avD->findWord(secondWord, firstWord);
                        else
                            docTracker = haD->findWord(secondWord, firstWord);
                    }
                    else
                    {
                        if (type)
                            docTracker = avS->findWord(queries[i], queries[i]);
                        else
                            docTracker = haS->findWord(queries[i], queries[i]);
                    }
                }
            }
        }
        catch(exception e)
        {
            cout << "The word " << unstemmedQueries[i] << " was not found in the index." << endl;
        }
    }
}
void QueryEngine::run(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type)
{
    bool searching = true;
    word tracker("","");
    while (searching)
    {
        takeQuery(avS, haS, avD, haD, type, tracker, searching);
        if (searching)
            printResults(tracker);
    }
}

void QueryEngine::printResults( word &wordTracker)
{
    bool looking = true;
    while(looking)
    {
        docu documents[15];
        calculateTop(wordTracker, documents);
        for (int i = 0; i < 15; i++)
        {

            if (i < wordTracker.getNumDocs())
            {
                cout << i+1 << ". ";
                printDoc(documents[i]);
            }
        }
        string response;
        int responseI;
        cout << "Enter the doc number to choose a doc or enter \"EXIT\" to exit" << endl;
        cin >> response;
        if (response.compare("EXIT") == 0)
        {
            looking = false;
        }
        else
        {
            try
            {
            responseI = stoi(response, nullptr, 10);
            }
            catch(exception e)
            {
                cout << "Not a valid entry" << endl;
            }
        }
    }
}

void QueryEngine::calculateTop(word &wordTracker, docu documents[15])
{
    for (int i = 0; i < wordTracker.getNumDocs() -1; i++)
    {
        for (int j = 0; j < wordTracker.getNumDocs() - i - 1; j++)
        {
            if (wordTracker.getDoc(j).getUseCount() < wordTracker.getDoc(j+1).getUseCount())
            {
               swapDocs(wordTracker.getLitDoc(j), wordTracker.getLitDoc(j+1));
            }
        }
    }
    for (int i = 0; i < 15; i++)
    {
        if (i < wordTracker.getNumDocs())
            documents[i] = wordTracker.getDoc(i);
    }
}

void QueryEngine::swapDocs(docu& x, docu& y)
{
    docu temp = x;
    x = y;
    y = temp;
}

void QueryEngine::printDoc(docu document)
{
    ifstream ifile(document.getFileName());
    if (ifile.is_open())
    {

    }
    ifile.close();
    cout << "Used in " << document.getFileName() << " " << document.getUseCount() << " times." << endl;
}

