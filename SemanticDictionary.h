#ifndef SEMANTICDICTIONARY_H_INCLUDED
#define SEMANTICDICTIONARY_H_INCLUDED

#include "SemanticDescriptor.h"
#include <sstream>
using namespace std;

vector<vector<string>> getSentenceLists(string text);

class SemanticDictionary
{
    private:
        vector<SemanticDescriptor> semanticDescriptors;
        int searchTargetWord(string targetWord);

    public:
        void processTargetWord(string targetWord, vector<string> sentenceList);
        double getSimilarity(string targetWord1, string targetWord2);
        string mostSimilarWord(string word, vector<string> choices);
        friend ostream& operator<<(ostream& os, const SemanticDictionary& d);

        friend istream& operator>>(istream& is, SemanticDictionary& d);
};

ostream& operator<<(ostream& os, const vector<vector<string>>& sentenceLists);

bool isStopWord(string s);

#endif // SEMANTICDICTIONARY_H_INCLUDED