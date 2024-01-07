#ifndef SEMANTICDESCRIPTOR_H_INCLUDED
#define SEMANTICDESCRIPTOR_H_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

struct ContextWord
{
    string word;
    int count;
};

class SemanticDescriptor
{
    private:

        string targetWord;
        vector<ContextWord> contextWords;

    public:
        SemanticDescriptor(string _targetWord) : targetWord(_targetWord) {}
        string getTargetWord() {return targetWord;}
        void processContextWord(string s);
        int operator*(const SemanticDescriptor& desc);
        friend ostream& operator<<(ostream& os, const SemanticDescriptor& desc);

        //Add the extraction operator inside your public class declaration.  
        //The rest of the file is the same as the previous project:
        
        friend istream& operator>>(istream& is, SemanticDescriptor& desc);
};

#endif // SEMANTICDESCRIPTOR_H_INCLUDED