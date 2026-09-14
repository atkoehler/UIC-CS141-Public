/// @file 20260911_Lecture8_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 11, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23

// Libraries to accomplish various tasks
#include <iostream> // Input-Output Streams
#include <string>   // For the C++ string datatype

#include <random>

using namespace std;

/// @brief Example class implementation based on volunteered properties
///        and actions from the Die class design activity.
class Die
{
    // items in the private area are only accessible within the class
    // and not by objects that are created by users of the class.
    private:
        string color;
        int sides;
        int value;

        // Modern C++ Pseudo-Random Number Generator
        mt19937 rng;
        uniform_int_distribution<int> dist;

    // items in the public area can be accessed via the dot operator
    public:
        int roll();

        // We utilize const here to prevent changes to our internal 
        // member variables as these are simple accessors and should not
        // be modifying the values of the object's members.
        int getValue() const;
        int getSides() const;
        string getColor() const;

    private:
        void setValue(int);
        void setSides(int);

        // We pass the string by value so we can use move() (std::move())
        // and its semantics to transfer ownership of the string's underlying 
        // memory directly to our class' member variable.
        void setColor(string);
        
        void seedRNG();
};

void Option1Examples()
{
    // Instantiating a object from our user created Die class
    Die sixSidedDie;

    // Calling a member function on our Die instance
    // sixSidedDie.roll();
}


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
