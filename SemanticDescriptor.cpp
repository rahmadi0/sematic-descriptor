#include "SemanticDescriptor.h"

void SemanticDescriptor::processContextWord(string s)
{
    bool flag = false;
    for (long unsigned int i = 0; i < contextWords.size(); ++i)
    {
    
        if (contextWords.at(i).word == s)
        {
            flag = true;
            (contextWords.at(i).count)++;
        }
    }
    if (!flag)
    {
        ContextWord newObj;
        newObj.word = s;
        newObj.count = 1;
        contextWords.push_back(newObj);   
    }
}

int SemanticDescriptor::operator*(const SemanticDescriptor& desc)
{
    int sum = 0;
    for (long unsigned int i = 0; i < this->contextWords.size(); ++i)
    {
        for (long unsigned int j = 0; j < desc.contextWords.size(); ++j)
        {
            if (this->contextWords.at(i).word == desc.contextWords.at(j).word)
            {
                sum += (this->contextWords.at(i).count * desc.contextWords.at(j).count);
            }
        }
    }
    return sum;
}

ostream& operator<<(ostream& os, const SemanticDescriptor& desc)
{
    os << desc.targetWord << " { ";
    for (long unsigned int i = 0; i < desc.contextWords.size(); ++i)
    {
        os << desc.contextWords.at(i).word << " " << desc.contextWords.at(i).count << " ";
    }
    os << " } ";
    return os;
}


istream& operator>>(istream& is, SemanticDescriptor& desc)
{
    //Clear the contents of desc to ensure there is no old data in it
    
    desc.targetWord = "";
    desc.contextWords.clear();

    ContextWord tempText;
    char symbol;

    is >> desc.targetWord;

    is >> symbol;
    if (symbol != '{')
    {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    while (!is.fail())
    {
        is >> symbol;
        if (symbol == '}')
        {
            return is;
        }
        else
        {
            is.unget();
        }

        is >> tempText.word >> tempText.count;
        desc.contextWords.push_back(tempText);

    }
    return is;
}