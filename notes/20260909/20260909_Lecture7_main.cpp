/// @file 20260909_Lecture7_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 9, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23

// Libraries to accomplish various tasks
#include <iostream> // Input-Output Streams
#include <string>   // For the C++ string datatype

using namespace std;

class Die
{
    private:
        string color;
        int sides;
        int value;

    public:
        int roll();
        int getValue();

    private:
        void setValue(int);
};

void Option1Examples();
void Option2Examples();

int main(int argc, char *argv[])
{
    // no second command line argument, run all examples
    if (argc > 1 && isdigit(argv[1][0]))
    {
        switch (atoi(argv[1]))
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
    // Instantiating a object from our class definition
    // Without anything specified the default constructor will be used.
    Die sixSidedDie;

    // Calling a member function on our Die instance
    // sixSidedDie.roll();
}

void Option2Examples()
{

}