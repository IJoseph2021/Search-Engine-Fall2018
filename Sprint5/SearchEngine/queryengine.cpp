#include "queryengine.h"

QueryEngine::QueryEngine()
{
}
void QueryEngine::takeQuery(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type, word& docTracker)
{
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
        Porter2Stemmer::stem(temp);
        if (temp.compare("AND") !=0 && temp.compare("OR") != 0 && temp.compare("NOT") != 0)
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        queries.push_back(temp);
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
                secondWord = queries[i].substr(0, queries[i].length() -1);
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
                    i++;
                    if (type)
                        docTracker & avS->findWord(queries[i], queries[i]);
                    else
                        docTracker & haS->findWord(queries[i], queries[i]);
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
                    i++;
                    if (type)
                        docTracker | avS->findWord(queries[i], queries[i]);
                    else
                        docTracker | haS->findWord(queries[i], queries[i]);

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
                    i++;
                    if (type)
                        docTracker.logicalNot(avS->findWord(queries[i], queries[i]));
                    else
                        docTracker.logicalNot(haS->findWord(queries[i], queries[i]));
                }
            }
            else
            {
                if (leading)
                {
                    if (i == 1)
                    {
                        if (type)
                            docTracker = avS->findWord(queries[i], queries[i]);
                        else
                            docTracker = haS->findWord(queries[i], queries[i]);
                    }
                    else if (AND)
                    {
                        if (type)
                            docTracker & avS->findWord(queries[i], queries[i]);
                        else
                            docTracker & haS->findWord(queries[i], queries[i]);
                    }
                    else if (OR)
                    {
                        if (type)
                            docTracker | avS->findWord(queries[i], queries[i]);
                        else
                            docTracker | haS->findWord(queries[i], queries[i]);
                    }
                    else if(NOT)
                    {
                        if (type)
                            docTracker.logicalNot(avS->findWord(queries[i], queries[i]));
                        else
                            docTracker.logicalNot(haS->findWord(queries[i], queries[i]));
                    }
                }
                else
                {
                    if (type)
                        docTracker= avS->findWord(queries[i], queries[i]);
                    else
                        docTracker = haS->findWord(queries[i], queries[i]);
                }
            }
        }
        catch(exception e)
        {
            cout << "The word " << queries[i] << " was not found in the index." << endl;
        }

    }

}
void QueryEngine::run(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type)
{
    bool searching = true;
    while (searching)
    {
        word tracker("","");
        takeQuery(avS, haS, avD, haD, type, tracker);

        printResults(avS, haS, avD, haD, type, tracker);
    }

}
void QueryEngine::printResults(IndexerFace *&avS, IndexerFace *&haS, IndexerFace *&avD, IndexerFace *&haD, bool &type, word &wordTracker)
{
    cout << wordTracker << endl;
}
