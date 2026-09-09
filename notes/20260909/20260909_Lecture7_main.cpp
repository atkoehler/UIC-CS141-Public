/// @file 20260909_Lecture7_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 9, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23

// Libraries to accomplish various tasks
#include <iostream> // Input-Output Streams
#include <string>   // For the C++ string datatype

using namespace std;

/// @brief Example class implementation based on volunteered properties
///        and actions from the Die class design activity.
class Die
{
    // Three potential access modifiers: private, public, and protected.
    // Classess are private by default, so if nothing is specifed then
    // all declarations (data members and functions) will be private.
    // This makes the initial private modifier often seen before data members
    // a repeat as the access is already private. However, stating it provides
    // increased human readability of our code.

    // private indicates that only functions inside the Die class can 
    // directly access (acquire or set) the functions or data members
    private:
        string color;
        int sides;
        int value;

    // public indicates that all internal and external user can access these
    // items through the dot operator (e.g. x.roll())
    //
    // Most often these are functions that interact with the private data 
    // members in addition to function that perform some action related to 
    // the object's design and purpose.
    public:
        int roll();
        int getValue();

    // We can switch back to a prior modifier by simply stating it again.
    // If there are actions/functions that should only be used internally
    // within the class, such as helper functions, then they should 
    // exist within a private section.
    private:
        void setValue(int);
};

void Option1Examples();

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

    // This code is commented out because we have not implemented the
    // function, and therefore the code will not compile with just 
    // the declaration.
    // Calling a member function on our Die instance
    // sixSidedDie.roll();
}
