/// @file 20260831_Lecture4_main.cpp
/// @author Adam T Koehler, PhD
/// @date August 31, 2026
/// @brief Code and lecture notes from the live lecture. 
///     Some code may require -std=c++23


// Libraries to accomplish various tasks
#include <iostream> // Input-Output Streams
#include <string>   // For the C++ string datatype
#include <vector>   // For using vector containers for many counters


using namespace std;


//////////////////////////////////////////////////////////////////////////////
//
// Stepwise development of a Frequency Counter program a pratical exploration  
// of vectors, counting, strings, branches, and loops within C++.
//
// Pairs with Lecture 4 activities with string function development.
//
//////////////////////////////////////////////////////////////////////////////

using namespace std;


// Prototypes for all local functions
// Implemented in order listed here below main()
void Option1Examples();
void Option2Examples();

// Activity Area 1 Options
bool isVowel(char);

// Activity Area 2 Options
bool isLower(const string &);
void trimEnd(string &);

// // Activity Area 3 Options -- Did not get to these.
// int countNonVowels(const vector<string> &);
// int countVowels(const vector<string> &data);
// int countVowelStarters(const vector<string> &);


// Baseline Code
// Some example code to kick things off which may be useful for activities.
void baseline()
{
    string s = "hello world";

    // Iterate over and act on each character in a string.
    // No access to the individual indices of the string.
    for (char c : s)
    {
        cout << c << endl;
    }

    // Iterate over and act on each character in a string.
    // No access to the individual indices of the string.
    for (size_t i = 0; i < s.size(); i++)
    {
        cout << s.at(i) << endl;

        // array - style access
        // unsafe vector/string access - no bounds checking
        // cout << s[i] << endl;
    }
}


/// @brief main function for running our examples
/// @param argc the number of command line arguments
/// @param argv the array containing c-strings of command line args
int main(int argc, char *argv[])
{
    // no second command line argument, run all examples
    if (argc > 1 && isdigit(argv[1][0]))
    {       
        switch(atoi(argv[1]))
        {
            case 1:
                Option1Examples();   
                break;

            case 2:
                Option2Examples();
                break;
            
            default:
                break;
        }
    }
    return 0;
}

// Execution of various Activity Area 1 examples
void Option1Examples()
{
    string word;
    cout << "Enter a word: ";
    cin >> word;
    cout << endl;
    cout << endl;
    cout << "You entered: " << word << endl;

    cout << "The third character in the word " << word << " is ";
    if (isVowel(word.at(2)))
    {
        cout << "a vowel.";
    }
    else
    {
        cout << "NOT a vowel.";
    }

    cout << "The first character in the word " << word << " is ";
    if (isVowel(word.front()))
    {
        cout << "a vowel.";
    }
    else
    {
        cout << "NOT a vowel.";
    }
    cout << endl;

    cout << "The last character in the word " << word << " is ";
    if (isVowel(word.back()))
    {
        cout << "a vowel.";
    }
    else
    {
        cout << "NOT a vowel.";
    }
    cout << endl;
}

// Execution of various Activity Area 2 examples
void Option2Examples()
{
    string word;
    cout << "Enter a word: ";
    cin >> word;
    cout << endl;
    cout << endl;

    cout << "Before trimming, your word is: " << word << endl;
    trimEnd(word);
    cout << "After trimming, your word is:  " << word << endl;
}




/// @brief Return whether a character is a vowel or not.
/// @param c The character to check.
/// @pre character c is lowercase
/// @return true when the character is a vowel, otherwise false.
bool isVowel(char c)
{
    // potential implementation options
    // if statements
    // if (c == 'a')
    // {
    //     return true;
    // }
    // else if (c == 'e')
    // {
    //     return true;
    // }
    // else if (c == 'i')
    // {
    //     return true;
    // }
    // else if (c == 'o')
    // {
    //     return true;
    // }
    // else if (c == 'u')
    // {
    //     return true;
    // }

    // switch statements instead
    // switch(c)
    // {
    //     case 'a':
    //     case 'e':
    //     case 'i':
    //     case 'o':
    //     case 'u':
    //         return true;
    //     default:
    //         return false;
    // }

    // comound conditional in a single if statement
    // if ('a' == c || 'e' == c || 'i' == c || 'o' == c || 'u' == c)
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }

    // one line function, return the result of the compound conditional
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

    // Example 1
    // abc123 gets '3' becomes abc12
    // abc12  gets '2' becomes abc1
    // abc1   gets '1' becomes abc
    // abc    gets 'c' stops loops

    // Example 2 (shortened)
    // abc34qr95 ==> abc34qr

    // remove all non-alphabetic characters from the end of the string
    while(!isalpha(word.back()))
    {
        word.pop_back();
    }

    // Alternate Implementation without isalpha
    // Continue iterating as long as the character is 
    //      not a lowercase and not an uppercase character
    // while (!(word.back() >= 'a' && word.back() <= 'z') && 
    //        !(word.back() >= 'A' && word.back() <= 'Z'))
    // {
    //     word.pop_back();
    // }
}
