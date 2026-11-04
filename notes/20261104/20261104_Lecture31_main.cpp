/// @file 20261104_Lecture31_main.cpp
/// @author Adam T Koehler, PhD
/// @date November 4, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some items require C++20, compile with g++ -std=c++23 XXX_main.cpp

#include <iostream>
#include <memory>
#include <vector>


using namespace std;

void Example1()
{
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
