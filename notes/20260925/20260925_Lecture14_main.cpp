/// @file 20260925_Lecture14_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 25, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23
///     Compile with g++ -std=c++23 die.cpp XXX_main.cpp

#include <iostream>
#include <vector>
#include "die.h"

using namespace std;


void Example1()
{
    Die a(6, 0, "white");
    Die b(6, 0, "white");
    Die c(6, "white");
    Die d(6, "blue");

    cout << "Rolls" << endl;
    cout << "=====" << endl;
    cout << "a: " << a.getValue() << endl;
    cout << "b: " << b.getValue() << endl;
    cout << "c: " << c.getValue() << endl;
    cout << "d: " << d.getValue() << endl;
    
    cout << endl << "Die equality (==) comparison a == b"
        << endl << "===============================" << endl;
    if (a == b)
    {
        cout << "Die a and Die b are the same" << endl;
    }
    else
    {
        cout << "Die a and Die b are not the same" << endl;
    }

    cout << endl << "Die inequality (!=) comparison b != c"
         << endl << "===============================" << endl;
    if (b != c)
    {
        cout << "Die b and Die c are not the same" << endl;
    }
    else
    {
        cout << "Die b and Die c are the same" << endl;
    }

    cout << endl << "Die relational comparison c < d"
         << endl << "===============================" << endl;
    if (c < d)
    {
        cout << "Die c is less than Die d" << endl;
    }
    else
    {
        cout << "Die c is not less than Die d" << endl;
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