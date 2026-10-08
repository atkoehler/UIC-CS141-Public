/// @file 20261007_Lecture18_main.cpp
/// @author Adam T Koehler, PhD
/// @date October 7, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23
///     Compile with g++ -std=c++23 die.cpp XXX_main.cpp

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "die.h"

using namespace std;

// Using the to_string function from 10-05 activities
// That we implemented in codebase for 10-07
void Example1()
{
    Die a;
    Die b(14, "green");

    cout << a.to_string() << endl;
    cout << b.to_string() << endl;
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
