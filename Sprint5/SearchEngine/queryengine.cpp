#include "queryengine.h"

QueryEngine::QueryEngine()
{
    avS = new AVLIndex();
    avD = new AVLIndex();
    haS = new HashIndex();
    haD = new HashIndex();
    type = false;

}
QueryEngine::QueryEngine(IndexerFace*& avSx, IndexerFace*& haSx, IndexerFace*& avDx, IndexerFace*& haDx, bool& typex)
{
    avS = avSx;
    avD = avDx;
    haS = haSx;
    haD = haDx;
    type = typex;
}
void QueryEngine::takeQuery()
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
    word docTracker();
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
            string firstWord = queries[i].substr(1, queries[i++].length() -1);
            string secondWord = queries[i].substr(0, queries[i].length() -1);

        }
        else
        {
            if (queries[i].compare("AND") == 0)
            {
                if (i = 0)
                {
                    leading = true;
                    AND = true;
                }

                else
                {
                    word temp(queries[++i]);
                    if (type)
                        docTracker & avS->findWord(temp);
                    else
                        docTracker & haS->findWord(temp);
                }
            }
            else if (queries[i].compare("OR") == 0)
            {
                if (i = 0)
                {
                    leading = true;
                    OR = true;
                }
                else
                {   word temp(queries[++i]);
                    if (type)
                        docTracker | avS->findWord(temp);
                    else
                        docTracker | haS->findWord(temp);
                }
            }
            else if (queries[i].compare("NOT") == 0)
            {
                if (i = 0)
                {
                    leading = true;
                    NOT = true;
                }
                else
                {
                    word temp(queries[++i]);
                    if (type)
                        docTracker.logicalNot(avS->findWord(temp));
                    else
                        docTracker.logicalNot(haS->findWord(temp));
                }
            }
            else
            {
                if (leading)
                {
                    word temp(queries[++i]);
                    if (AND)
                    {
                        if (type)
                            docTracker & avS->findWord(temp);
                        else
                            docTracker & haS->findWord(temp);
                    }
                    else if (OR)
                    {
                        if (type)
                            docTracker | avS->findWord(temp);
                        else
                            docTracker | haS->findWord(temp);
                    }
                    else if(NOT)
                    {
                        if (type)
                            docTracker.logicalNot(avS->findWord(temp));
                        else
                            docTracker.logicalNot(haS->findWord(temp));
                    }
                }
                else
                {
                    word temp(queries[i]);
                    if (type)
                        docTracker= avS->findWord(temp);
                    else
                        docTracker = haS->findWord(temp);
                }
            }
        }

    }

}
void QueryEngine::run()
{
    bool searching = true;
    while (searching)
    {
        takeQuery();
    }

}
