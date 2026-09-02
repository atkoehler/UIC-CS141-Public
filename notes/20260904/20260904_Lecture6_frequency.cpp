/// @file 20260904_Lecture6_frequency.cpp
/// @author Adam T Koehler, PhD
/// @date September 4, 2026
/// @brief Code and lecture notes from the live lecture. 
///     Some code may require -std=c++23


// Libraries to accomplish various tasks
#include <iostream> // Input-Output Streams
#include <string>   // For the C++ string datatype
#include <vector>   // For using vector containers for many counters


using namespace std;


///////////////////////////////////////////////////////////////////////////////
//
// Incremental development of a Frequency Counter program a pratical   
// exploration of vectors, counting, strings, branches, and loops within C++.
//
// Pairs with Week 2 activities that have develop functions which use strings.
//
///////////////////////////////////////////////////////////////////////////////

using namespace std;


// Prototypes for all local functions
// Implemented in order listed here below main()
// 8/31 Activity Area 1 Options
bool isVowel(char);

// 8/31 Activity Area 2 Options
bool isLower(const string &);
void trimEnd(string &);

// 9/4 Activity Options
bool exists(const vector<string> &, const string &);
int countNonVowels(const vector<string> &);
int countVowels(const vector<string> &);

// Additional Function Prototypes (Pre-Coded)
int countVowelStarters(const vector<string> &);
void printMenu();
int readData(vector<string> &);
bool validSize(const string &);


/// @brief main function for running our examples
/// @param argc the number of command line arguments
/// @param argv the array containing c-strings of command line args
int main(int argc, char *argv[])
{    
    // When testing we can hardcode values into our valid data vector
    // so that we can test our functions with specific data.
    vector<string> data = {"my", "name", "bob", "and"};

    // When not testing we want to start with an empty data container.
    // vector<string> data;

    int option = -1, reads = -1;
    const int DONE = 6;

    cout << "Frequency Calculator" << endl;
    cout << "====================" << endl;
    cout << endl;

    do
    {   
        printMenu();

        // Acquire a user option based on the menu
        cout << "Choose an option: ";
        cin >> option;
        cout << endl;

        // Act on the option entered by the user
        switch(option)
        {
            case 1:
                // Future: readData - so we don't hardcode data
                break;

            case 2:
                data.clear();
                cout << "Data cleared." << endl;
                break;

            case 3:
                cout << "Found " << countVowels(data) << " vowels." 
                    << endl;
                break;
            case 4:
                cout << "Found " << countNonVowels(data) << " non-vowels." 
                    << endl;
                break;

            case 5:
                cout << "Found " << countVowelStarters(data) 
                    << " words that start with vowels." << endl;
                break;

            case DONE:
                break;

            default:
                cout << "Invalid Option: " << option << endl;
                break;
        }

        cout << endl;
    } while (option != DONE);


    cout << "Enjoy your day!" << endl;

    return 0;
}



////////////////////////////////////
//
// August 31, 2026 Activity Areas
//
////////////////////////////////////


/// @brief Return whether a character is a vowel or not.
/// @param c The character to check.
/// @pre character c is lowercase
/// @return true when the character is a vowel, otherwise false.
bool isVowel(char c)
{
    return 'a' == c || 'e' == c || 'i' == c || 'o' == c || 'u' == c;
}


/// @brief determine whether a string is all lowercase alphabetic characters
/// @param word the string to check
/// @return true when all lowercase alphabetic characters, otherwise false
bool isLower(const string &word)
{
    // iterate over every character in word
    for(const auto &letter : word)
    {
        // return false immediately when not between 'a' and 'z' (inclusive)
        if (!('a' <= letter && letter <= 'z'))
        {
            return false;
        }
    }
    return true;
}


/// @brief Removes all non-alphabetic characters from the end 
///        of the provided string.
/// @param word The string to trim.
void trimEnd(string &word)
{
    // An empty string causes certain fucntions to have undefined behavior.
    // Therefore we must handle the empty string as an edge case, and for 
    // our function return immediately because there is nothing to trim.
    if (word.empty())
    {
        return;
    }

    // remove all non-alphabetic characters from the end of the string
    while(!isalpha(word.back()))
    {
        word.pop_back();
    }
}




////////////////////////////////////
//
// September 2, 2026 Activity Areas
//
////////////////////////////////////

/// @brief determine whether the supplied word already exists in the data
/// @param data the container of data to check
/// @param word the string to look for in the data
/// @return true when the word exists in the data, false otherwise
// TODO - exists
bool exists(const vector<string> &data, const string &word)
{
    return false;
}


/// @brief Count the quantity of non-vowel characters in the data.
/// @param data the vector containing all the strings of data
/// @return the quantity of non-vowel characters in the data
// TODO - countNonVowels
int countNonVowels(const vector<string> &data)
{
    return 0;
}


/// @brief Count the quantity of vowel characters in the data.
/// @param data the vector containing all the strings of data
/// @return the quantity of vowel characters in the data
// TODO - countVowels
int countVowels(const vector<string> &data)
{
    return 0;
}




//////////////////////////////////////
//
// Given Implementations (pre-coded)
//
//////////////////////////////////////

/// @brief Count the quantity of words in the data that start with a vowel.
/// @param data the vector containing all the strings of data
/// @return the quantity of words counted that start with a vowel
int countVowelStarters(const vector<string> &data)
{
    int counter = 0;

    // every element in the data
    for(const auto &e : data)
    {
        if (e.size() > 0 && isVowel(e.at(0)))
        {
            counter++;
        }
    }
    
    return counter; 
}


/// @brief output the menu containing all the program options
void printMenu()
{
    cout << "Menu Options" << endl;
    cout << "1. Read Data" << endl;
    cout << "2. Clear Data" << endl;
    cout << "3. Count Vowels" << endl;
    cout << "4. Count Non-Vowels" << endl;
    cout << "5. Count words that start with vowels" << endl;
    cout << "6. Exit" << endl << endl;
}

/// @brief Determines that a supplied string is a valid size
/// @param s the string to validate the size of
/// @return true when the string size if valid, otherwise false
bool validSize(const string &s)
{
    // 5 is the only valid string size    
    return s.size() == 5;
}
