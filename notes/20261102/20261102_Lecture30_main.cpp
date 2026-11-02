/// @file 20261030_Lecture30_main.cpp
/// @author Adam T Koehler, PhD
/// @date November 2, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some items require C++20, compile with g++ -std=c++23 XXX_main.cpp

#include <iostream>
#include <string>
#include <vector>

using namespace std;


/// @brief  
void Activity1()
{

}

 
/// @brief 
void Activity2()
{
    
}


/// @brief 
void Activity3()
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
                Activity1();
                break;

            case 2:
                Activity2();
                break;

            case 3:
                Activity3();
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

