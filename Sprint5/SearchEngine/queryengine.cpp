#include "queryengine.h"

QueryEngine::QueryEngine()
{
}
void QueryEngine::takeQuery(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type, word& docTracker, bool& searching)
{
    vector<string> unstemmedQueries;
    vector<string> queries;
    string query = "";
    cout << "Enter your query." << endl;
    getline(cin, query);
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
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
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
    while (searching)
    {
        word tracker("","");
        takeQuery(avS, haS, avD, haD, type, tracker, searching);

        if (searching)
            printResults(tracker);
    }
}
void QueryEngine::printResults( word &wordTracker)
{
    cout << wordTracker << endl;
}
