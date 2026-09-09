/// @file 20260909_Lecture7_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 4, 2026
/// @brief Code and lecture notes from the live lecture. 
///     Some code may require -std=c++23


// Libraries to accomplish various tasks
#include <iostream> // Input-Output Streams
#include <string>   // For the C++ string datatype

using namespace std;


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

void Option1Examples()
{

}

void Option2Examples()
{
    
}