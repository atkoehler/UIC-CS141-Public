/// @file 20260923_Lecture13_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 23, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23
///     Compile with g++ -std=c++23 die.cpp XXX_main.cpp

#include <iostream>
#include <vector>

using namespace std;

/// @brief Question: T/F - Class constructor overloading is a form of 
///                  compile-time polymorphism in which the compiler 
///                  selects the appropriate constructor at compile time.
void quizQuestion1()
{
    string a;
    string b("Hello World!");
    string c({'h', 'e', 'l', 'l', 'o'});
    string d(50, '=');

    cout << "Using 4 different constructors for 4 string creations:" << endl;
    cout << "string a;" << endl << "    a: " << a << endl << endl;
    cout << "string b(\"Hello World!\");" << endl 
        << "    b: " << b << endl << endl;
    cout << "string c({'h', 'e', 'l', 'l', 'o'});" << endl 
        << "    c: " << c << endl << endl;
    cout << "string d(50, '=');" << endl << "    d: " 
        << d << endl << endl;
}


/// @brief Question: What value is in s after the code?
void quizQuestion2()
{
    string s = "hello world!?";

    cout << "Before pop_back(): " << s << endl;
    
    s.pop_back();

    cout << "After pop_back():  " << s << endl;
}


/// @brief Question: T/F - The this keyword is always required when referring  
///                  to data members of a class.
void quizQuestion3()
{
    cout << "See examples in setValue and operator== within \"die.cpp\"" 
        << endl;
}


// Quiz Question 4
// Shouldn't this lead to a compiler error due to duplicate
// code definitions being included?
//
// Without the proper protections, that is exactly what will happen.
// See the top of "die.h" to see #pragma once in use.
#include "die.h"
#include "die.h"
#include "die.h"

/// @brief Question: Which of the following prevents headers from being 
///                  included multiple times during compilation?
void quizQuestion4()
{
    cout << "See top of \"die.h\"" << endl;
}


/// @brief Question: What is the output if we attempt to print the first 
///                  25,000 values of arr using square brackets, e.g. arr[44]?
void quizQuestion5()
{
    vector<int> arr(25);

    for (int i = 0; i < 25000; ++i)
    {
        // remember: accessing with square brackets does not check bounds
        cout << i << ": " << arr[i] << endl;
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
                quizQuestion1();
                break;
            case 2:
                quizQuestion2();
                break;
            case 3:
                quizQuestion3();
                break;
            case 4:
                quizQuestion4();
                break;
            case 5:
                quizQuestion5();
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