/// @file 20261028_Lecture28_main.cpp
/// @author Adam T Koehler, PhD
/// @date October 28, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some items require C++20, compile with g++ -std=c++23 XXX_main.cpp

#include <iostream>
#include <vector>

#include "card.h"

using namespace std;

// Activity Pairing - Solution code shown but not live coded.
// binarySearchRecursive pairs with the code conversion activity of 
// converting the iterative search to a recursive implementation.
// 1) Identify the stopping points for the iterative algorithm and
// convert them to base cases. 2) Identify when the iterative algorithm
// continues and what the values for the next iteration get updated,
// and convert to a recursive function call.

/// @brief Utilize recursive binary search to look for a provided value 
///     and provide its index back through reference parameter.
/// @param v the directly accessible (at(i)) container, often a vector
/// @param value the value to look for within the container
/// @param loc the variable to update to the discovery location when found
/// @param low the lowest index in the range to search
/// @param high the highest index in the range to search
/// @return true when the value is found, otherwise false
/// @pre The container v is sorted in ascending order.
bool binarySearchRecursive(const auto &v, const Card &value, 
        int &loc, int low, int high)
{
    // Is our search space exhausted such that there are no more items in it?
    // Could be written as high-low < 0
    if (low > high)
    {
        return false;
    }

    int mid = (high + low) / 2;

    // Did we discover the thing we are looking for?
    if (v.at(mid) == value)
    {
        loc = mid;
        return true;
    }

    // Determine which half of the container to search
    if (v.at(mid) < value)
    {
        return binarySearchRecursive(v, value, loc, mid+1, high);
    }
    else
    {
        return binarySearchRecursive(v, value, loc, low, mid-1);
    }   
}

/// @brief Utilize binary search to determine the location of a value 
///         within a container.
/// @param v the directly accessible (at(i)) container, often a vector
/// @param value the value to look for within the container
/// @param loc the variable to update to the discovery location when found
/// @return true when the value is found, otherwise false
/// @pre The container v is sorted in ascending order.
bool binarySearch(const auto &v, const Card &value, int &loc)
{
    // Binary search utilizes three values and updates them
    // during the search pattern.
    int low, mid, high;

    low = 0;
    high = v.size() - 1;
    // Keep searching until the search space is empty
    // while (high - low > 0)
    while (low < high)
    {
        // determine the middle index of the search space
        mid = (low+high) / 2;

        // did we discover the value?
        if (v.at(mid) == value)
        {
            loc = mid;
            return true;
        }

        // We did not discover the value, which half will have 
        // the value we are looking for? Update the low or high
        // value accordingly.
        if (v.at(mid) < value)
        {
            low = mid+1;
        }
        else
        {
            high = mid-1;
        }
    }

    return false;
}

/// @brief Binary search examples using a vector of integers.
void Example1()
{
    vector<Card> pile;
    pile.push_back(Card("Jack", "Clubs", false));
    pile.push_back(Card("Queen", "Diamonds", true));
    pile.push_back(Card("Jack", "Hearts", true));
    pile.push_back(Card("Queen", "Hearts", true));
    pile.push_back(Card("King", "Hearts", true));

    int location = -1;
    Card searchFor;
    bool discovered = false;
    
    cout << "Search through the pile of values containing: " << endl;
    for(const auto &val : pile)
    {
        cout << "   " << val.to_string() << "\n";
    }
    cout << endl << endl;


    // Search Attempt #1
    searchFor = Card("King", "Clubs", false);  
    cout << "Search Attempt #1 - Iterative" << endl;
    cout << "Attempting to find: " << endl << searchFor.to_string() << endl;
    discovered = binarySearch(pile, searchFor, location);    
    if(discovered)
    {
        cout << "  Found at index value " << location << endl;  
    }
    else
    {
        cout << "  Did not find " << searchFor.to_string() << endl;
    }
    cout << endl << endl;


    // Search Attempt #2
    searchFor = Card("Queen", "Hearts", true); 
    cout << "Search Attempt #2 - Iterative" << endl; 
    cout << "Attempting to find: " << endl << searchFor.to_string() << endl;
    discovered = binarySearch(pile, searchFor, location);    
    if(discovered)
    {
        cout << "  Found at index value " << location << endl;  
    }
    else
    {
        cout << "  Did not find " << searchFor.to_string() << endl;
    }
    cout << endl << endl;

    // Search Attempt #3 - Same as #1 but recursive
    searchFor = Card("King", "Clubs", false);  
    cout << "Search Attempt #3 - Recursive (same as #1)" << endl;
    cout << "Attempting to find: " << endl << searchFor.to_string() << endl;
    discovered =  binarySearchRecursive(pile, searchFor, location, 0, pile.size()-1);
    if(discovered)
    {
        cout << "  Found at index value " << location << endl;  
    }
    else
    {
        cout << "  Did not find " << searchFor.to_string() << endl;
    }
    cout << endl << endl;


    // Search Attempt #4 - Same as #2 but recursive
    searchFor = Card("Queen", "Hearts", true);  
    cout << "Search Attempt #4 - Recursive (same as #2)" << endl;
    cout << "Attempting to find: " << endl << searchFor.to_string() << endl;
    discovered =  binarySearchRecursive(pile, searchFor, location, 0, pile.size()-1);
    if(discovered)
    {
        cout << "  Found at index value " << location << endl;  
    }
    else
    {
        cout << "  Did not find " << searchFor.to_string() << endl;
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
                Example1();
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
