/// @file card.h
/// @author Adam T Koehler, PhD
/// @date October 19, 2026
/// @brief Definition for the Card class. Implementations exist in the
///         the card.cpp file. Continually developed. New implementations are
///         often timestamped with the leture date within the .cpp file.

#pragma once

#include <string>

using namespace std;

/// @brief a Card class to mimic a playing card
class Card
{
    private:
        string faceValue;
        string suit;
        bool coloredRed;

        
    ////////////////////////////////////////////////////////////
    // private or protected functions
    // facilitate functionality only to be used internally by
    // the Card class or any derived class from the Card class
    ////////////////////////////////////////////////////////////
    private:
        void makeRed(bool);
        void setSuit(const string &s);


    ////////////////////////////////////////////////////////////
    // publicly (user) accessible data members and functionality
    // facilitating an API for users of the Card class
    ////////////////////////////////////////////////////////////
    public:
        ////////////////////////////////////////////////////////////
        // constructors
        // facilitate object creation
        ////////////////////////////////////////////////////////////
        Card();
        Card(const string&, const string&, bool);


        ////////////////////////////////////////////////////////////
        // accessors/getters
        // provide public ability to acquire a data member's value
        ////////////////////////////////////////////////////////////
        string getFaceValue() const;
        string getSuit() const;
        bool isRed() const;


        ////////////////////////////////////////////////////////////
        // setters/mutators
        // provide public ability to change a data member's value
        //
        // generally good design would make this private unless we 
        // want users to be able to change the values of the card
        ////////////////////////////////////////////////////////////
        void setFaceValue(const string &v);

        ////////////////////////////////////////////////////////////
        // object funtionality implementations or usage functions
        // provide public ability to acquire a data member's value
        ////////////////////////////////////////////////////////////
        string to_string() const;

        ////////////////////////////////////////////////////////////
        // object operator overloads to allow card comparisons
        ////////////////////////////////////////////////////////////
        bool operator==(const Card &) const;
        bool operator!=(const Card &) const;
        bool operator<=(const Card &) const;
        bool operator>=(const Card &) const;
        bool operator<(const Card &) const;
        bool operator>(const Card &) const;


        private:

        // Helper function for relational comparisons
        bool convertToRank(int &number) const;
        string makeLowerCase(const string &con) const;
};