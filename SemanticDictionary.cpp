#include "SemanticDescriptor.h"
#include "SemanticDictionary.h"


/*

vector<vector<string>> getSentenceLists(string text)
{
    vector<vector<string>> sentenceLists;
    vector<string> sentenceList;
    string word = "";

    for(size_t i = 0; i < text.size(); i++)
    {
        ///if the ith char is alphabetical, concatenate it onto word

        //else
        ///  if the size of word > 0, push it back into sentenceList and make the word empty
        ///  if the ith char is '?', '.', or '!', AND the size of sentenceList > 0, 
        ///    then push back sentenceList into sentenceLists and clear sentenceList

        if (isalpha(text.at(i)))
        {
            word += text.at(i);
        }
        else
        {
            if (word.size() > 0)
            {
                sentenceList.push_back(word);
                word = "";
            }
        }
        if ((text.at(i) == '?' || text.at(i) == '.' || text.at(i) == '!') && (sentenceList.size() > 0))
        {
            sentenceLists.push_back(sentenceList);
            sentenceList.clear();
        }
    }
    ///if the size of word > 0, push it back into sentenceList
    if (word.size() > 0)
    {
        sentenceList.push_back(word);
        word = "";
    }
    ///if the size of sentenceList > 0, push it back into sentenceLists
    if (sentenceList.size() > 0)
    {
        sentenceLists.push_back(sentenceList);
    }
    return sentenceLists;
}

*/


vector<vector<string>> getSentenceLists(string text)
{
    vector<vector<string>> sentenceLists;
    vector<string> sentenceList;
    string word = "";

    for(size_t i = 0; i < text.size(); i++)
    {
        //if the ith char is alphabetical, concatenate it onto word

        //else
        //  if the size of word > 0, push it back into sentenceList and make the word empty
        //  if the ith char is '?', '.', or '!', AND the size of sentenceList > 0,
        //  then push back sentenceList into sentenceLists and clear sentenceList

        if (isalpha(text.at(i)))
        {
            word += tolower(text.at(i));
        }
        else
        {
            if (word.size() > 0 && !isStopWord(word))
            {
                sentenceList.push_back(word);
                word = "";
            }
            else
            {
                word = "";
            }
        }
        if ((text.at(i) == '?' || text.at(i) == '.' || text.at(i) == '!') && sentenceList.size() > 0 )
        {
            sentenceLists.push_back(sentenceList);
            sentenceList.clear();
        }
    }

    ///if the size of word > 0, push it back into sentenceList
    if (word.size() > 0 && !isStopWord(word))
    {
        sentenceList.push_back(word);
        word = "";
    }
    ///if the size of sentenceList > 0, push it back into sentenceLists
    if (sentenceList.size() > 0 && !isStopWord(word))
    {
        sentenceLists.push_back(sentenceList);
    }
    return sentenceLists;
}


int SemanticDictionary::searchTargetWord(string targetWord)
{
    for (long unsigned int i = 0; i < semanticDescriptors.size(); ++i)
    {
        if (semanticDescriptors.at(i).getTargetWord() == targetWord)
        {
            return i;
        }
    }
    return -1;
}

void SemanticDictionary::processTargetWord(string targetWord, vector<string> sentenceList)
{
    int index = searchTargetWord(targetWord);
    if (index == -1)
    {
        SemanticDescriptor current(targetWord);
        semanticDescriptors.push_back(current);
    }
    index = searchTargetWord(targetWord);
    
    for (long unsigned int i = 0; i < sentenceList.size(); ++i)
    {
        if (sentenceList.at(i) != targetWord)
        {
            semanticDescriptors.at(index).processContextWord(sentenceList.at(i));
        }
    }
}

double SemanticDictionary::getSimilarity(string targetWord1, string targetWord2)
{
    int firstIndex = searchTargetWord(targetWord1);
    int secondIndex = searchTargetWord(targetWord2);
    if (firstIndex == -1 || secondIndex == -1)
    {
        throw runtime_error("Target word(s) unknown");
    }

    SemanticDescriptor temp1 = semanticDescriptors.at(firstIndex);
    SemanticDescriptor temp2 = semanticDescriptors.at(secondIndex);
    double result = (double)(temp1 * temp2) / (sqrt(temp1 * temp1) * sqrt(temp2 * temp2));
    
    return result;
}

string SemanticDictionary::mostSimilarWord(string word, vector<string> choices)
{
    double max, d;
    string mostSimilar;
    for (long unsigned int i = 0; i < choices.size(); i++)
    {
        d = getSimilarity(word, choices.at(i));
        if (d > max)
        {
            max = d;
            mostSimilar = choices.at(i);
        }
    }
    return mostSimilar;
}

ostream& operator<<(ostream& os, const SemanticDictionary& d)
{
    os << "Semantic Descriptors:" << endl;
    os << "{" << endl;
    for (long unsigned int i = 0; i < d.semanticDescriptors.size(); ++i)
    {
        os << d.semanticDescriptors.at(i) << endl;
    }
    os << "}";
    return os;
}

ostream& operator<<(ostream& os, const vector<vector<string>>& sentenceLists)
{
    os << "Sentence Lists: " << endl;
    os << "[" << endl;
    for (long unsigned int i = 0; i < sentenceLists.size(); ++i)
    {
        os << "[ ";
        for (long unsigned int j = 0; j < sentenceLists.at(i).size(); ++j)
        {
            os << sentenceLists.at(i).at(j) << " ";
        }
        os << "]" << endl;
    }
    os << "]";
    return os;
}


bool isStopWord(string s)
{
    vector<string> stopWord = { "i", "a", "about", "an", "are", "as", "at",
                                "be", "by", "for", "from", "how", "in", "is",
                                "it", "of", "on", "or", "that", "the", "this",
                                "to", "was", "what", "when","where", "who", "will", "with" };
    for (size_t i = 0; i < stopWord.size(); i++)
    {
        if (s == stopWord.at(i))
        {
            return true;
        }
    }

    return false;
}


istream& operator>>(istream& is, SemanticDictionary& d)
{
    d.semanticDescriptors.clear();
    SemanticDescriptor temp{""};

    char symbol;

    while (symbol != '{')
    {
        is >> symbol;
    }

    while (is >> temp)
    {
        d.semanticDescriptors.push_back(temp);
    }

    is >> symbol;
    if (symbol != '}')
    {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    return is;
}
