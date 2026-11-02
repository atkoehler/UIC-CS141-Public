/// @file 20261030_Lecture30_main.cpp
/// @author Adam T Koehler, PhD
/// @date November 2, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some items require C++20, compile with g++ -std=c++23 XXX_main.cpp

#include <iostream>
#include <string>
#include <vector>

#include "card.h"

using namespace std;

void printReverse(string_view);
void printInReverse(string_view);
void printInReverse(string_view, size_t);
void releaseAll(vector<Card*> &);


/// @brief Executing activity area 1 which was a function to print provided 
///         strings in reverse from last character to first character.
///        We are using encapsulation to hide whether the printing process is 
///         using a recursive or iterative algorithm for printing.
void Activity1()
{
    vector<string> words = {"help", "me", "sample", "racecar", "howdy"};

    for(const auto &w : words)
    {
        cout << w << " in reverse is: " << endl;
        printReverse(w);
        cout << endl;
    }
}


/// @brief Create a container full of Cards that are dynamically allocated.
///         Note that these Card objects are allocated from the heap segment
///         of memory, not the stack segment we have been working with.
void Activity2()
{
    vector<Card*> hand;

    hand.push_back(new Card("One", "Hearts", true));
    hand.push_back(new Card("Two", "Diamonds", true));
    hand.push_back(new Card("Three", "Spades", false));
    hand.push_back(new Card("Ace", "Clubs", false));

    // Print each card
    // Example 1: Index-Based For Loop
    for (size_t index = 0; index < hand.size(); ++index)
    {
        // A null pointer (nullptr) means no valid memory address
        // is stored at this index, and therefore we cannot dereference
        // to utilize the Card object and its member functions.
        if (hand.at(index) == nullptr)
        {
            continue;
        }

        cout << hand.at(index)->to_string() << endl;
    }
    cout << endl << endl;

    // Example 2: For Each Loop
    for (const Card* c : hand)
    {
        if (c == nullptr)
        {
            continue;
        }

        cout << c->to_string() << endl;
    }
}


/// @brief Write a function that takes a container of Card pointers and releases
///         all the dynamically allocated cards from within the container.
void Activity3()
{
    vector<Card*> hand;

    hand.push_back(new Card("One", "Hearts", true));
    hand.push_back(new Card("Two", "Diamonds", true));
    hand.push_back(new Card("Three", "Spades", false));
    hand.push_back(new Card("Ace", "Clubs", false));

    cout << "Before Release: " << endl;
    for (const Card* c : hand)
    {
        if (c == nullptr)
        {
            continue;
        }

        cout << "   " << c->to_string() << endl;
    }

    releaseAll(hand);

    cout << "After Release: " << endl;
    for (const Card* c : hand)
    {
        // A null pointer (nullptr) means no valid memory address
        // is stored at this index, and therefore we cannot dereference
        // to utilize the Card object and its member functions.
        
        // Try: Comment this if statement and body out and see what happens.
        if (c == nullptr)
        {
            continue;
        }
        
        cout << "   " << c->to_string() << endl;
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


void printReverse(string_view s)
{
    if (s.size() % 2 == 0)
    {
        printInReverse(s, 0);
        cout << "    Used the recursive reverse print." << endl;
    }
    else
    {
        printInReverse(s);
        cout << "    Used the iterative reverse print." << endl;
    }
}

void printInReverse(string_view s)
{
    if (s.empty())
    {
        return;
    }

    // Why can't we use size_t for this loop's 
    // iteration variable type?
    for(int i = s.size() - 1; i >= 0; --i)
    {
        cout << s.at(i) << ' ';
    }
    cout << endl;
}

void printInReverse(string_view s, size_t index)
{
    if (s.empty())
    {
        return;
    }

    if (index >= s.size())
    {
        return;
    }

    printInReverse(s, index+1);

    cout << s.at(index) << ' ';

    if (index == 0)
    {
        cout << endl;
    }
}

/// @brief Given a container of Card pointers, release each dynamically 
///         allocated pointer and set to a "safe" value.
/// @param v The vector of Card pointers to release.
void releaseAll(vector<Card *> &v)
{
    for (size_t index = 0; index < v.size(); ++index)
    {
        // Release the pointer at this specific index.
        delete v.at(index);

        // No dangling pointer.
        // Having the address but it no longer being accessible.
        v.at(index) = nullptr;
    }
}