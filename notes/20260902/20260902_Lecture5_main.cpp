/// @file 20260902_Lecture5_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 2, 2026
/// @brief Code and lecture notes from the live lecture. 
///     Some code may require -std=c++23


// Libraries to accomplish various tasks
#include <iostream> // Input-Output Streams
#include <string>   // For the C++ string datatype
#include <vector>   // For using vector containers for many counters

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


void Option1Examples(); 
void Option2Examples(); 

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
    else
    {
        cout << "Specify a case to execute, e.g. ./exeName 1" << endl;
        cout << "If a.out is the executable we would use: ./a.out 1" << endl;
    }
    return 0;
}

/// @brief Quiz Based Examples
void Option1Examples()
{
    // Replacing characters in a string
    string x;

    // Goal: change 'h' to 'j' where 'h' is the first letter in the string
    // Method 1: use the at() member function
    x = "hello";
    cout << "Changing the first letter of a string." << endl;
    cout << "======================================" << endl;
    cout << "Using at(0)" << endl;
    cout << "Before: " << x << endl;
    x.at(0) = 'j';
    cout << "After:  " << x << endl;

    // Method 2: use the front() member function
    x = "hello";
    cout << endl;
    cout << "Using front()" << endl;
    cout << "Before: " << x << endl;
    x.front() = 'j';
    cout << "After:  " << x << endl;

    // Method 3: use the replace member function to replace 
    //           a substring of size 1 starting at 0
    x = "hello";
    cout << endl;
    cout << "Using replace(0, 1, \"j\")" << endl;
    cout << "Before: " << x << endl;
    x.replace(0, 1, "j");
    cout << "After:  " << x << endl;
}
 

void Option2Examples()
{
    // Chained at() Calls - How many to get to the character data type?
    cout << "Chaining at() calls in a multi-dimensional vector." << endl;
    cout << "==================================================" << endl;
    cout << "Create empty vector and push each row on to it." << endl;
    // Create an empty 2D vector of strings
    vector<vector<string>> v;

    // Initialize a single row and place it into the 2D vector
    // We could also acquire these values one by one and push them into
    // the row vector one at a time. For simplicity we initialize.
    cout << "Pushing row with values {\"howdy\", \"hi\"} " << endl << endl;
    vector<string> greeting = {"howdy", "hi"};
    v.push_back(greeting);

    // acquire the third character of first word in the first row
    char c = v.at(0).at(0).at(2);
    cout << "First row, First string, Third character: " << c << endl;

    // We could also do on at() call at a time
    vector<string> row = v.at(0);
    string word = row.at(0);
    char letter = word.at(1);
    cout << "First row, First string, Second character: " << letter << endl;

    // We could also instantiate the 2D vector of strings immediately
    cout << endl;
    cout << "Immediately instantiate our 2D vector of strings." << endl;
    cout << "Vector will initialize with: " << endl 
        << "   { {\"wellness\", \"goals\"}" << endl
        << "     {\"pizza\", \"ice cream\", \"salad\"} }" << endl << endl;

    vector<vector<string>> z = {{"wellness", "goals"}, 
                                {"pizza", "ice cream", "salad"}};
    
    // acquire the third character of first word in the first row
    char d = z.at(1).at(2).at(3);
    cout << "Second row, Third string, Fourth character: " << d << endl;

    // We could also do on at() call at a time
    vector<string> r = z.at(0);
    string w = r.at(1);
    char ltr = w.at(1);
    cout << "First row, Second string, Second character: " << d << endl;
}