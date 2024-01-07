#include "SemanticDictionary.h"
#include <chrono>
#include <fstream>
//#include "../std_lib_facilities.h"
using namespace std::chrono;

void printMenu()
{
    cout << "1.  Read the semantic dictionary from storage" << endl;
    cout << "2.  Write the semantic dictionary to storage" << endl;
    cout << "3.  Read and process a text file (get smarter!)" << endl;
    cout << "4.  Solve a TOEFL question" << endl;
    cout << "5.  Quit" << endl;
    cout << "> ";
}

int main()
{
    //declare SemanticDictionary object
    //declare string for menu choice
    //declare and assign a string for the dictionary file name

    SemanticDictionary d;
    string menuChoice;
    string fileName = "SemanticDictionary.txt";


    //output some kind of welcome message
    //print the menu
    //input the menu choice

    cout << "Welcome to the similarity checker!" << endl;
    printMenu();
    cin >> menuChoice;

    //while not quit
    //if 1

    while(menuChoice != "5")
    {
        if(menuChoice == "1")
        {
            //output that you are reading the dictionary file
            //construct ifstream object and open the file

            cout << "Reading dictionary from " << fileName << endl;
            ifstream inFile(fileName);

            //if failed

            if(!inFile)
            {
                //error message
                cout <<"Cannot open the file " << fileName << endl;
            }
            else
            {
                //extract from ifstream object into your dictionary object
                ///output that you are done reading

                inFile >> d;
                inFile.close();
                cout << "Done." << endl;
            }
        }

        //else if 2
        //warn the user that this will overwrite the previous file, ask if they want to proceed

        else if(menuChoice == "2")
        {
            cout << "Warning:  this will overwrite the previous data.  Proceed? (y or n): ";
            cin.clear();
            cin >> menuChoice;

            //if proceed
            if(menuChoice == "y" || menuChoice == "Y")
            {
                //output that you are writing the dictionary to a file
                //declare and open ofstream object
                //insert from the dictionary object into the ofstream object
                //output that you are done writing

                cout << "Saving dictionary to SemanticDictionary.txt" << endl;
                ofstream outFile(fileName);
                outFile << d;
                outFile.close();
                cout << "Done." << endl;
            }
        }

        //else if 3
        //declare variable for file name
        //prompt and input file name
        //construct ifstream object and open the file

        else if(menuChoice == "3")
        {
            string FileName2;
            cout << "Enter file name: ";
            cin >> FileName2;
            ifstream outFile2(FileName2);

            //if failed
            //error message

            if(!outFile2)
            {
                cout << "Cannot open the file " << FileName2 <<  endl;
            }

            else
            {
                //output that you are processing the file

                cout << "Processing file..." << endl;
                auto start = high_resolution_clock::now(); //code to record time elapsed

                //declare a variable to hold all of the text
                //loop to read every word in the file.  Concatenate each word onto text, separated by " "
                
                string text;
                string tempWord;
                while(outFile2 >> tempWord)
                {
                    text += tempWord + " ";
                }

                //pass text into getSentenceLists.  (This is a copy paste from the last project)
                //Create a double for loop to loop through each word of each sentenceList in sentenceLists and
                //  process the target word.  (This is also a copy paste from the last project)

                vector<vector<string>> sentenceLists = getSentenceLists(text);

                for(vector<string> sentenceList : sentenceLists)
                {
                    for(string targetWord : sentenceList)
                    {
                        d.processTargetWord(targetWord, sentenceList);
                    }
                }

                auto stop = high_resolution_clock::now();  //code to record time elapsed
                auto duration = duration_cast<milliseconds>(stop - start);
                cout << "Done.  Time elapsed: " << duration.count() << " milliseconds" << endl;
            }
        }

        //else if 4
        else if(menuChoice == "4")
        {
            //this is a copy and paste of the logic from your old project, starting with "Enter a TOEFL question..."
            cout << "Enter a TOEFL question as <word> <answer> <choice1> <choice2> <choice3>:" << endl;
            string word, answer, choice1, choice2, choice3;
            cin >> word >> answer >> choice1 >> choice2 >> choice3;

            try
            {
                string s = d.mostSimilarWord(word, vector<string> {choice1, choice2, choice3});
                cout << "Most similar: " << s << endl;
                cout << "Index: " << d.getSimilarity(word, s) << endl;
                if(s == answer)
                    cout << "Correct answer." << endl;
                else
                    cout << "Incorrect answer." << endl;
            }
            catch(runtime_error& e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            cout << "Invalid menu choice" << endl;
        }

        //print the menu
        //input the menu choice
        printMenu();
        cin >> menuChoice;
    }

    return 0;
}




/*
#include "SemanticDictionary.h"
using namespace std;

int main()
{
    SemanticDictionary d;

    string text;
    cout << "Type a paragraph followed by a newline to build semantic descriptors:" << endl;
    getline(cin, text);

    vector<vector<string>> sentenceLists = getSentenceLists(text);

    cout << sentenceLists << endl;

    for(vector<string> sentenceList : sentenceLists)
        for(string targetWord : sentenceList) 
        d.processTargetWord(targetWord, sentenceList);

    cout << d << endl;

    cout << "Enter a TOEFL question as <word> <answer> <choice1> <choice2> <choice3>:" << endl;
    string word, answer, choice1, choice2, choice3;
    cin >> word >> answer >> choice1 >> choice2 >> choice3;

    try
    {
        string s = d.mostSimilarWord(word, vector<string>{choice1, choice2, choice3});
        cout << "Most similar: " << s << endl;
        cout << "Index: " << d.getSimilarity(word, s) << endl;
        if(s == answer) cout << "Correct answer." << endl;
        else cout << "Incorrect answer." << endl;
    }
    catch(runtime_error& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}

*/