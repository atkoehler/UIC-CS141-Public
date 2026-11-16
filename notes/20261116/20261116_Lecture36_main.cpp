/// @file 20261116_Lecture36_main.cpp
/// @author Adam T Koehler, PhD
/// @date November 16, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some items require C++23, compile with g++ -std=c++23 XXX_main.cpp

#include <iostream>

using namespace std;

void Activity()
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
                Activity();
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