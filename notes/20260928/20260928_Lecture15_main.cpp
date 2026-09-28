/// @file 20260928_Lecture15_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 28, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23
///     Compile with g++ -std=c++23 die.cpp XXX_main.cpp

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "die.h"

using namespace std;


/// @brief Concatenate the two provided strings into a third string.
/// @param first The string to occur first in the concatenation.
/// @param second The string to occur second in the concatenation.
/// @return The concatenated string.
string combineStrings(string_view first, string_view second) 
{
    // Create a standard string using the first view
    string result(first); 

    // Iterate over the second string and append the characters
    for (char c : second) 
    {
        result.push_back(c); 
    }

    return result;
}

void Example1()
{
    string a;
    string b;

    a = "hello";
    b = "world";
    cout << combineStrings(a, b) << endl;

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "combo: " << a+b << endl;
    if (a+b == combineStrings(a, b))
    {
        cout << "SUCCESS" << endl;
    }
    else
    {
        cout << "Failed to combine a + b as strings with combineStrings." 
            << endl;
    }


    cout << endl << endl;
    a = "howdy";
    b = " partner";
    cout << combineStrings(a, b) << endl;
    
    cout << endl << endl;
    a = "";
    b = "first is empty";
    cout << combineStrings(a, b) << endl;

    cout << endl << endl;
    a = "second is empty";
    b = "";
    cout << combineStrings(a, b) << endl;
}



void Example2()
{
    Die a(6, "blue");
    Die b;
    Die c(14, "yellow");

    cout << "Dice Initial Values" << endl
         << "===================" << endl;
    
    cout << "A is " << a.getValue() << ", " 
        << a.getSides() << ", " 
        << a.getColor() << endl;
    cout << "B is " << b.getValue() << ", " 
        << b.getSides() << ", " 
        << b.getColor() << endl;
    cout << "C is " << c.getValue() << ", " 
        << c.getSides() << ", " 
        << c.getColor() << endl;

    cout << endl << endl;
    cout << "Combined Dice Values" << endl
         << "====================" << endl;
    cout << "A+B is " << (a+b).getValue() << ", " 
        << (a+b).getSides() << ", " 
        << (a+b).getColor() << endl;

    cout << "B-C is " << (b-c).getValue() << ", " 
        << (b-c).getSides() << ", " 
        << (b-c).getColor() << endl;
}



/// @brief determine whether the provided character is an uppercase
///     or lowercase vowel.
/// @param c the character to check
/// @return true when the character is a vowel, otherwise false.
bool isVowel(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

/// @brief 
/// @param word 
/// @return 
bool areVowelsAlphabetical(string_view word) 
{
    // initialize our "last vowel" to to first potential option
    char lastVowel = 'a'; 

    // iterate through every character in the string
    for (char c : word) 
    {
        // make sure all comparisons are the same case
        char currentChar = tolower(c);

        // act on the current character when it is a vowel
        if (isVowel(currentChar)) 
        {
            // compare against the previously seen vowel
            // to see if they are in the correct alphabetical order
            if (currentChar < lastVowel) 
            {
                return false; 
            }

            // update our tracker for future comparisons
            lastVowel = currentChar; 
        }
    }

    // the entire word was checked and we did not discover any
    // vowels that were not in alphabetic order.
    return true;
}

void Example3()
{
    string a;

    // Test Case: Word with sorted vowels.
    a = "hello";
    if(areVowelsAlphabetical(a))
    {
        cout << "The word \"" << a << "\" has sorted vowels." 
            << endl;
    }
    else
    {
        cout << "The word \"" << a << "\" does not have sorted vowels." 
            << endl;       
    }

    // Test Case: Word with repeated vowels.
    a = "hollow";
    if(areVowelsAlphabetical(a))
    {
        cout << "The word \"" << a << "\" has sorted vowels." 
            << endl;
    }
    else
    {
        cout << "The word \"" << a << "\" does not have sorted vowels." 
            << endl;       
    }

    // Test Case: Word with unsorted vowels.
    a = "piper";
    if(areVowelsAlphabetical(a))
    {
        cout << "The word \"" << a << "\" has sorted vowels." 
            << endl;
    }
    else
    {
        cout << "The word \"" << a << "\" does not have sorted vowels." 
            << endl;       
    }
}

int main(int argc, char *argv[])
{
    // no second command line argument, run all examples
    if (argc > 1 && isdigit(argv[1][0]))
    {
        switch (atoi(argv[1]))
        {
            case 1:
                Example1();
                break;
            case 2:
                Example2();
                break;
            case 3:
                Example3();
                break;

            default:
                break;
        }
    }
    else
    {
        cout << "Specify a case to execute, e.g. ./exeName 1" << endl;
        cout << "If a.out is the executable we would use: ./a.out 1" << endl;
    }
    return 0;
}