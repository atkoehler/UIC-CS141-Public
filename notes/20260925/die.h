/// @file die.h
/// @brief Die class declaration the creates an N-sided colored die.
/// @author Adam T Koehler, PhD
/// @date September 21, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23

#pragma once

#include <compare>
#include <random>
#include <string>
#include <string_view>

using std::string;
using std::string_view;
using std::mt19937;
using std::uniform_int_distribution;

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
        explicit Die(int v, string c);
        Die(int v, int s, string c);

        // Accessors / Getters
        // Die property / data member value acquisition
        string_view getColor() const;
        int getSides() const;
        int getValue() const;


        // Die Interactions
        int roll();
        
        // Comparisons Overloaded
        // Legacy Method - Pre C++23

        // Exact Equality - As of C++20, this handles == and !=
        bool operator==(const Die& rhs) const;
        // bool operator!=(const Die& rhs) const;

        
        // Modern C++23 Methodology
        // Requires c++23 and gcc-14.1+
        // bool operator==(this const Die& self, const Die& rhs);


        // The Spaceship Operator - C++20
        // Relational Comparisons - Handles <, >, <=, >=
        std::strong_ordering operator<=>(const Die &other) const;

        // Prevention of Specific Creation Actions
        Die(const Die&) = delete;
        Die& operator=(const Die&) = delete;

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

