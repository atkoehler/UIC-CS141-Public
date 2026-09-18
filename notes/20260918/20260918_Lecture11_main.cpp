/// @file 20260918_Lecture10_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 18, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23

// Libraries to accomplish various tasks
#include <array>
#include <iostream> // Input-Output Streams
#include <random>   // For random_device and pseudorandom number generator
#include <string>   // For the C++ string datatype
#include <utility>  // std::move()

using namespace std;

void Option1Examples();

/// @brief Example class implementation based on volunteered properties
///        and actions from the Die class design activity.
class Die
{
    private:
        string color;
        int sides;
        int value;

        // Modern C++ Pseudo-Random Number Generator
        mt19937 rng;
        uniform_int_distribution<int> dist;

    public:
        // Constructors - Creation & Instantiation of an Object
        Die();
        Die(int v, string c);
        Die(int v, int s, string c);

        // Accessors / Getters
        // Die property / data member value acquisition
        string_view getColor() const;
        int getSides() const;
        int getValue() const;

        // Die Interactions
        int roll();

        // Prevention of Specific Creation Actions with delete
        Die(const Die&) = delete;               // No Copy-Constructor
        Die& operator=(const Die&) = delete;    // No Assignment Operator

    private:
        // Mutators / Setters
        // Die property / data member value modification
        void setValue(int);
        void setSides(int);
        void setColor(string);

        // Private seed functions for the random number generator
        void seedRNG();
        void seedRNG(int);
};






//////////////////////////////////////////////////////////////////////
//
//  Die Class Implementations
//  Constructors - Used to create and instantiate a Die object.
//
//////////////////////////////////////////////////////////////////////

// Initialization lists can be used to set class member variables by
// specifying the variable name and then in parentheses the value to set.

/// @brief Create a die from a constructor that specifies no values.
Die::Die() : color("white")
{
    setSides(6);
    seedRNG();
    roll(); // Initialize with a valid starting value
}

/// @brief Create a die with specific member values - partially parametized
/// @param s the number of sides on the die
/// @param c the color of the die
Die::Die(int s, string c) 
{
    setSides(s);
    setColor(std::move(c));
    seedRNG();
    roll(); 
}

/// @brief Create a die with specific member values - fully parametized
/// @param s the number of sides on the die
/// @param seed seed value to use with the pseduorandom number generator
/// @param c the color of the die
Die::Die(int s, int seed, string c) 
{
    setSides(s);
    setColor(std::move(c));
    seedRNG(seed);
    roll(); 
}





//////////////////////////////////////////////////////////////////////
//
//  Die Class Implementations
//  Public Functions - User Accessible via dot operator invocation.
//
//////////////////////////////////////////////////////////////////////

/// @brief Acquire the value of the private data member value that represents
///        the face of the die that is upwards and its current value.
/// @return the current value of the die
int Die::getValue() const 
{
    return value;
}

/// @brief Acquire the value of the private data member sides that represents
///        the number of sides that this die has. The number of sides is also
///        the maximum value this die can roll/generate.
/// @return the number of sides this die has
int Die::getSides() const 
{
    return sides;
}

/// @brief Acquire the value of the private data member color that is the
///        color of the die represented as a string.
/// @return a read-only viewer of the color property of the die
string_view Die::getColor() const 
{
    return color;
}


/// @brief Roll the die. Sets value to a random number bewteen 1 and 
///         the number of sides of the die.
/// @return The new value of the die set by using the random number generator.
int Die::roll() 
{
    value = dist(rng);  
    return value;
}






////////////////////////////////////////////////////////////////////////////
//
//  Die Class Implementations
//  Private Functions - Helpers, Setters, etc.
//  Only accessible to other functions in the class, not accessible via the 
//  dot operator to users.
//
////////////////////////////////////////////////////////////////////////////

/// @brief Set the private class data member color. Utilizes the move()
///         semantics established in C++11 to transfer the underlying
///         aspects of the string without a character by character copy.
/// @param c the string to update the internal color value to
void Die::setColor(string c) 
{
    color = std::move(c);
}


/// @brief Set the private class data member value
/// @param v the integer to update the value of value to
void Die::setValue(int v) 
{
    value = v;
}

/// @brief Set the private class data member sides
/// @param s the integer to update the value of sides to
void Die::setSides(int s) 
{
    // Basic validation to prevent invalid side counts
    if (sides >= 1)
    {
        sides = s;
    }
    else
    {
        sides = 6;
    }
    
    // Update the distribution boundaries to match the side count
    dist = uniform_int_distribution<int>(1, sides);
}

/// @brief a simple no argument seeding function that causes true randomness
///         to be utilized to create the seed value sequence
void Die::seedRNG() 
{
    // Invoke parameterized version with 0 to trigger true randomness
    seedRNG(-1); 
}

/// @brief Seed the pseduorandom number generator associated
///         with this object's instantiation.
/// @param seedValue Integer value to use as a seed or 0 for true randomness
void Die::seedRNG(int seedValue) 
{
    if (seedValue == -1) 
    {
        random_device rd;

        // Seed with multiple values using a simple initializer
        // and a seed sequence object. Using 8 32-bit numbers to help
        // increase the entropy of the pseudorandom number generator.
        seed_seq seq{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
        rng.seed(seq);
    } 
    else 
    {
        // Use the provided integer for a predictable, deterministic sequence
        rng.seed(seedValue);
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


// Prior Activity - Compare Two Dice
// Pass by Value - Should not do this, creates a copy of the dice.
// bool compare(Die a, Die b)
// {
//     return a.getValue() == b.getValue();
// }

/// @brief A comparison function that determines if two dice are equivalent.
///        Design Choice: What determines equivalence?
/// @param a the first die to compare
/// @param b the second die to compare
/// @return true when the values of the dice are the same
bool compare(const Die &a, const Die &b)
{
    return a.getValue() == b.getValue();
}


// Main program with simple example using a collection of dice and rolling them
void Option1Examples()
{
    Die a;
    Die b(6, "blue");
    Die c(6, 0, "green");


    // Create with the Copy Constructor
    // Die d = b;

    // Overwrite old Die with the Assignment Operator
    // c = a;


    // roll the dice
    cout << "Values Rolled" << endl <<  "=============" << endl;
    cout << "a: " << a.roll() << endl;
    cout << "b: " << b.roll() << endl;
    cout << "c: " << c.roll() << endl;

    // Cannot have d print out when declaration is commented out
    // cout << "d: " << d.roll() << endl;

    cout << endl << endl;
    cout << "Use the Compare Function" << endl;
    cout << "========================" << endl;
    cout << "a and b variables" << endl;
    if (compare(a, b))
    {
        cout << "   matching value!" << endl;  
    }
    else
    {
        cout << "   no match" << endl;
    }

    cout << endl;
    cout << "a and c variables" << endl;
    if (compare(a, c))
    {
        cout << "   matching value!" << endl;  
    }
    else
    {
        cout << "   no match" << endl;
    }
}