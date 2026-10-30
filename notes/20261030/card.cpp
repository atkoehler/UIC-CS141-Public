/// @file card.cpp
/// @author Adam T Koehler, PhD
/// @date October 21, 2026
/// @brief Card class that is continually under development.
///     New functionality that is added in a lecture will exist at end
///     after comment about lecture date that featured the live additions.

#include <array>
#include <string>
#include "card.h"

using namespace std;

////////////////////////////////////////////////////////////
//
// Notes from introduction to separate class files.
// scope resolution operator (::)
// Since we are opting to define the class functions and 
// declare the class functions in separate files. We use 
// the scope resolution operator to note where the 
// declaration of this function exists.  
//
// RETURN_TYPE CLASS_NAME::FUNCTION_NAME(FUNCTION PARAMS)
// e.g. bool Card::isRed() const
//
////////////////////////////////////////////////////////////



/// @brief Converts the provide string to a all lowercase version of string
/// @param con the string to convert
/// @return a new string with all the alphabetic characters converted to 
///     lowercase versions
string Card::makeLowerCase(const string &con) const
{
    string converted = con;

    // convert every alphabetic character in the converted
    // string to a lowercase character
    for (auto &ch : converted)
    {
        if (isalpha(ch))
        {
            ch = tolower(ch);
        }
    }

    return converted;
}


/// @brief Attempt to convert the Card's face value to a playing card rank
/// @param number pass by reference integer to update with conversion value
/// @return true when successfully converted, false otherwise
bool Card::convertToRank(int &number) const
{
    // Use a static array allocation as ranks array does not grow or shrink
    array<string, 14> ranks = {"joker", "ace", "2", "3", "4", "5", 
            "6", "7", "8", "9", "10", "jack", "queen", "king"};

    // check every rank and see if this card's face value matches
    for (size_t i = 0; i < ranks.size(); ++i)
    {
        if (ranks.at(i) == makeLowerCase(getFaceValue()))
        {
            number = i;
            return true;
        }
    }

    return false;
}


/// @brief Compare the cards to determine which is less than the other.
///     Uses suit strings for first comparison.
///     Then attempt to convert to numerical rank from 0 to 13.
///     When playing card conversion fails use string comparison of 
///     face values where black cards of matching face values come first.
/// @param rightSide the card to compare to the implicit object
/// @return true when the implict object is less than, otherwise false
bool Card::operator<(const Card &rightSide) const
{
    // Suits do not match, simply compare them with greater than
    // operator to compare the strings
    if (this->getSuit() != rightSide.getSuit())
    {
        return this->getSuit() < rightSide.getSuit();
    }

    // Suits match, attempt to convert to numerical rank
    int leftSideAsNumber = -1;
    int rightSideAsNumber = -1;
    if (convertToRank(leftSideAsNumber) && 
        rightSide.convertToRank(rightSideAsNumber))
    {
        // Suits match and ranks match, return whether the card
        // is red as red will come after black (using alphabetical sort)
        if (leftSideAsNumber == rightSideAsNumber)
        {
            // all properties match, not less than
            if (isRed() == rightSide.isRed())
            {
                return false;
            }
            
            // Colors do not match, we define !red < red
            return !isRed();
        }
        
        // unmatching ranks, return comparison result
        return leftSideAsNumber < rightSideAsNumber;
    }

    // Rank conversion failed for at least one of the cards fallback to
    // string comparison of face values.

    // Suits match and face values match, return whether the card
    // is red as red will come after black (using alphabetical sort)
    if (getFaceValue() == rightSide.getFaceValue())
    {
        // all properties match, not greater
        if (isRed() == rightSide.isRed())
        {
            return false;
        }
        
        // Colors do not match, we define !red < red
        return !isRed();
    }

    // Unmatched face values, just return the alphabetic string comparison
    return getFaceValue() < rightSide.getFaceValue();
}



// Because all the logic is contained in < operator implementation, 
// we defined the rest of the relational comparisons in terms of <

/// @brief Relational less than than operator overlaod for the Card class.
/// @param rhs The right hand side object of the relational comparison.
/// @return true when the implicit object is defined as greater than the parameter object
bool Card::operator>(const Card &rhs) const
{
    // We can define > with a combination of multiple relational expressions
    // we create this compound using && or ||
    // We break down > to two parts
    // first we know we want to use < but the opposite of > is <= not 
    // strictly < so we use != to avoid the equality case and the
    // remaining cases are all strictly <
    return !(*this == rhs) && !(*this < rhs);
}


/// @brief Compare the cards to determine which is greater than or equal than 
///     the other. Where the parameter is the right hand side of the operator.
//      Uses suit strings for first comparison.
///     Then attempt to convert to numerical rank from 0 to 13.
///     When playing card conversion fails use string comparison of 
///     face values where black cards of matching face values come first.
/// @param rhs the card to compare to the implicit object
/// @return true when the implict object is less than or equal, otherwise false
bool Card::operator>=(const Card &rhs) const
{
    return (*this > rhs) && (*this == rhs);
}

/// @brief Compare the cards to determine which is less than or equal than the
///     other. Where the parameter is the right hand side of the operator.
//      Uses suit strings for first comparison.
///     Then attempt to convert to numerical rank from 0 to 13.
///     When playing card conversion fails use string comparison of 
///     face values where black cards of matching face values come first.
/// @param rhs the card to compare to the implicit object
/// @return true when the implict object is less than or equal, otherwise false
bool Card::operator<=(const Card &rhs) const
{
    return !(*this > rhs);
}


////////////////////////////////////////////////////////////
// constructors
// facilitate object creation
// Recall constructors are unlike our other function 
// definitions because they do not have a return type in
// the function header.
////////////////////////////////////////////////////////////

/// @brief default constructor for the Card object
Card::Card() : faceValue(""), suit(""), coloredRed(false)
{}

/// @brief fully parameterized constructor for the Card object
/// @param fv the value to set to the private data member faceValue
/// @param st the value to set to the private data member suit
/// @param isRed the value to set to the private data member coloredRed
Card::Card(const string& fv, const string& st, bool isRed) : 
    faceValue(fv), suit(st), coloredRed(isRed)
{}






////////////////////////////////////////////////////////////
// private or protected functions
////////////////////////////////////////////////////////////

/// @brief is the card a red card?
/// @return true when the card is a red card, false otherwise
bool Card::isRed() const
{
    return coloredRed;
}


////////////////////////////////////////////////////////////
// setters/mutators
// provide public ability to change a data member's value
////////////////////////////////////////////////////////////

/// @brief set the private data member for face value
/// @param faceValue the string to set the face value to 
void Card::setFaceValue(const string &faceValue)
{
    this->faceValue = faceValue;
}


////////////////////////////////////////////////////////////
// accessors/getters
// provide public ability to acquire a data member's value
////////////////////////////////////////////////////////////

/// @brief acquire the face value of the card
/// @return the value of the private data member for the card's face value
string Card::getFaceValue() const
{
    return faceValue;
}

/// @brief acquire the suit value of the card
/// @return the value of the private data member for the card's suit
string Card::getSuit() const
{
    return suit;
}






////////////////////////////////////////////////////////////
// object funtionality implementations or usage functions
// provide public ability to acquire a data member's value
////////////////////////////////////////////////////////////

/// @brief Generates a human readable string with all the values
///     of the private data members of the Card.
///     e.g. Card is a 2 of Clubs which is black
/// @return the generated string which is not newline terminated
string Card::to_string() const
{
    string color = "black";
    if(isRed())
    {
        color = "red";
    }

    // We can access class data members diretly because we'ree inside class
    if ("Joker" == faceValue)
    {
        return "Card is a " + faceValue + " which is " + color;
    }
    return "Card is a " + faceValue + " of " + suit + " which is " + color;
}






////////////////////////////////////////////////////////////////////
// operator overloading allows users to use well-defined operators
// with objects of this specific class type.
////////////////////////////////////////////////////////////////////

/// @brief Overload the equality operator to allow use with cards
/// @param rhs the right hand side of the equality check (lhs == rhs)
/// @return true when two cards have the same internal values, otherwise false
bool Card::operator==(const Card &rhs) const
{
    return this->getFaceValue() == rhs.faceValue
            && this->suit == rhs.getSuit()
            && this->isRed() == rhs.isRed();
}

/// @brief Overload the not equals operator to allow use with cards
/// @param rhs the right hand side of the not equals check (lhs != rhs)
/// @return true when two cards are not the same, otherwise false
bool Card::operator!=(const Card &rhs) const
{
    return !(*this == rhs);
}