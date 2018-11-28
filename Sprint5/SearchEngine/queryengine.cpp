#include "queryengine.h"

QueryEngine::QueryEngine()
{
}
void QueryEngine::takeQuery(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type)
{
    vector<string> queries;
    string query = "";
    cout << "Enter your query." << endl;
    cin >> query;
    while (!query.empty())
    {
        int pos = query.find(" ");
        string temp = query.substr(0, pos);
        query.erase(0, pos+1);
        queries.push_back(temp);
    }
    bool leading = false;
    bool AND = false;
    bool OR = false;
    bool NOT = false;
    word docTracker("", "");
    for (int i = 0; i < queries.size(); i++)
    {
        if (!leading)
        {
            AND = false;
            OR = false;
            NOT = false;
        }

        bool twoWords = (queries[i].at(0) == '[');
        if (twoWords)
        {
            string firstWord = queries[i].substr(1, queries[i].length() -1);
            i++;
            string secondWord = queries[i].substr(0, queries[i].length() -1);

        }
        else
        {
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
                    i++;
                    if (AND)
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

    }

}
void QueryEngine::run(IndexerFace*& avS, IndexerFace*& haS, IndexerFace*& avD, IndexerFace*& haD, bool& type)
{
    bool searching = true;
    while (searching)
    {
        takeQuery(avS, haS, avD, haD, type);
    }

}
