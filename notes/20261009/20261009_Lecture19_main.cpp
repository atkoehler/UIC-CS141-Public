/// @file 20261009_Lecture19_main.cpp
/// @author Adam T Koehler, PhD
/// @date October 9, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23
///     Compile with g++ -std=c++23 XXX_main.cpp

#include <iostream>

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
