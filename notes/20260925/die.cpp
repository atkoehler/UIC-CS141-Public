/// @file die.cpp
/// @brief Implementation of the various Die class functions.
/// @author Adam T Koehler, PhD
/// @date September 21, 2026
/// @brief Code and lecture notes from the live lecture.
///     Requires C++20 and some code my require C++23, use -std=c++23
///     Compile everything with g++ -std=23 die.cpp XXX_main.cpp

#include <compare>
#include <random>
#include <string>

#include "die.h"

using std::string;
using std::string_view;
using std::uniform_int_distribution;
using std::random_device;
using std::seed_seq;

//////////////////////////////////////////////////////////////////////
//
//  Die Class Implementations
//  Constructors - Used to create and instantiate a Die object.
//
//////////////////////////////////////////////////////////////////////

// Initialization lists can be used to set class member variables by
// specifying the variable name and then in parentheses the value to set.

// C++11 introduced constructor delegation which allows an overloaded 
// constructor to invoke another constructor and reduce repeated 
// initialization code.

/// @brief Create a die from a constructor that specifies 0 values.
Die::Die() : Die(6, -1, "white")
{ }


/// @brief Create a die with specific member values - partially parameterized
/// @param s the number of sides on the die
/// @param c the color of the die
Die::Die(int s, string c) : Die(s, -1, c)
{ }


/// @brief Create a die with specific member values - fully parameterized
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


// Legacy C++ Operator Overload of Equality Comparison (pre C++23)
/// @brief Compare whether two dice are equivalent
/// @param rhs The Die on the Right Hand Side of the equivalence check
/// @return true when the one die completely matches the other 
///         Die, otherwise false.
bool Die::operator==(const Die& rhs) const 
{
    // only want the value compared or all the parts?
    // return value == rhs.value;
    // return this->value == rhs.value;
    // return this->getValue() == rhs.getValue();

    return (value == rhs.value) &&
           (sides == rhs.sides) &&
           (color == rhs.color);
}


// C++23 Methodology of Explicitly Show the Self Pointer
// Requires C++23 and gcc-14.1+
// bool Die::operator==(this const Die& self, const Die& rhs)
// {
//     // Both the left-hand side (self) and right-hand side (rhs)
//     // are explicit references
//     return (self.value == rhs.value) &&
//            (self.sides == rhs.sides) &&
//            (self.color == rhs.color);
// }


// Legacy C++ Operator Overload of Equality Comparison 
// As of C++20 the compiler automatically will handle the comparison 
// conversion from != to ==.

/// @brief Compare whether two dice are not equivalent
/// @param rhs The Die on the Right Hand Side of the operator
/// @return true when the one die does not completely matches the other 
///         Die, otherwise false.
// bool Die::operator!=(const Die& rhs) const 
// { 
//     // return (self.value != rhs.value) ||
//     //    (self.sides != rhs.sides) ||
//     //    (self.color != rhs.color);
//
//     // We can rewrite this in one line using the defined == operator
//     // and negating the entire expression. This is the task that the
//     // compiler takes on as of C++20.
//     return !(*this == rhs);
// }



// The Spaceship Operator - C++20
// Relational Comparisons - Handles  <, >, <=, >=
// We define how dice "rank" against each other. For simplcity, and for many
// games, the magnitude of the die value is often the comparison.
std::strong_ordering Die::operator<=>(const Die& other) const 
{
    return value <=> other.value;
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
void Die::setValue(int value) 
{
    this->value = value;
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

