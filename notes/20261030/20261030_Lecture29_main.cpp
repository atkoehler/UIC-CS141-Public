/// @file 20261030_Lecture29_main.cpp
/// @author Adam T Koehler, PhD
/// @date October 30, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some items require C++20, compile with g++ -std=c++23 XXX_main.cpp

#include <iostream>
#include <vector>

#include "card.h"

using namespace std;

// Builds off prior lecture that contained multiple binary search functions
// but all with separate function names for learning clarity. Now we have
// the same name and utilize compile-time polymorphism to know which function
// will be invoked. Additionally we encapsulate the search algorithms to hide
// the implementation details from the user. This allows us to change the 
// underlying algorithm and its details, as long as the way to invoke search
// does not change then the user's end use-case will not be impacted.
bool binarySearch(const auto &v, const Card &value, int &loc);
bool binarySearch(const auto &v, const Card &value, int &loc, 
        int low, int high);
bool linearSearch(const auto &v, const Card &value, int &loc);
bool linearSearch(const auto &v, const Card &value, int &loc, int index);


// The use of auto as a function parameter was introduced in C++20 and 
// is known as abbreviated function templates. The compiler will convert the
// following const auto function header to a templated function automatically.
// So what we have coded will turn into:
//      template <typename T>
//      bool isSorted(const T &container);
//
// This is a powerful development tool. Although we designed are function for 
// vectors, the iteration strategies and member functions we use exist in 
// strings and lists too. This one function will now accept any of those.
bool isSorted(const auto &container);

/// @brief Search the container for the specified value and update the variable loc.
/// @param v The container to search.
/// @param value The value to search for.
/// @param loc The variable to update to the index of the discovered value.
/// @return true when the value is found, otherwise false
bool search(const auto &v, const Card &value, int &loc)
{
    if (isSorted(v))
    {
        if(v.size() % 2 == 0)
        {
            cout << "Executing binary search." << endl;
            return binarySearch(v, value, loc);
        }

        cout << "Executing binary search recursively." << endl;
        return binarySearch(v, value, loc, 0, v.size()-1);
    }


    if(v.size() % 2 == 0)
    {
        cout << "Executing linear search." << endl;
        return linearSearch(v, value, loc);
    }
    cout << "Executing linear search recursively." << endl;
    //return linearSearch(v, value, loc, 0);
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
    cout << "Attempting to find: " << endl << searchFor.to_string() << endl;
    discovered = search(pile, searchFor, location);    
    if(discovered)
    {
        cout << "  Found at index value " << location << endl;  
    }
    else
    {
        cout << "  Did not find " << searchFor.to_string() << endl;
    }
    cout << endl << endl;


    // Search Attempt #2 - Same as #1 but iterative
    pile.push_back(Card("Ace", "Spades", false));
    searchFor = Card("King", "Clubs", false);  
    cout << "Attempting to find: " << endl << searchFor.to_string() << endl;
    discovered = search(pile, searchFor, location);    
    if(discovered)
    {
        cout << "  Found at index value " << location << endl;  
    }
    else
    {
        cout << "  Did not find " << searchFor.to_string() << endl;
    }
    cout << endl << endl;


    // Search Attempt #3
    pile.push_back(Card("One", "Clubs", false));
    searchFor = Card("Queen", "Hearts", true);  
    cout << "Attempting to find: " << endl << searchFor.to_string() << endl;
    discovered = search(pile, searchFor, location);    
    if(discovered)
    {
        cout << "  Found at index value " << location << endl;  
    }
    else
    {
        cout << "  Did not find " << searchFor.to_string() << endl;
    }
    cout << endl << endl;


    // Search Attempt #4 - Same as #3 but iterative
    pile.push_back(Card("Five", "Clubs", false));
    searchFor = Card("Queen", "Hearts", true);  
    cout << "Attempting to find: " << endl << searchFor.to_string() << endl;
    discovered = search(pile, searchFor, location);    
    if(discovered)
    {
        cout << "  Found at index value " << location << endl;  
    }
    else
    {
        cout << "  Did not find " << searchFor.to_string() << endl;
    }
}


void Example2()
{
    string unsorted = "hello";
    string sorted = "aim";

    // Demonstrating the power of auto as a function parameter.
    // We designed our function around vectors, but the member functions we 
    // use and iteration strategies all exist in the string data type too!
    if (!isSorted(unsorted))
    {
        cout << "This string's characters are not in ascending order: "
            << endl << unsorted << endl;
    }

    cout << endl << endl;

    if (isSorted(sorted))
    {
        cout << "This string's characters are in ascending order: "
            << endl << sorted << endl;
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

            case 2:
                Example2();
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


/// @brief Determine if the container is sorted in ascending order.
/// @param container The container to check the sorted state of.
/// @return true when the container is in ascending order, otherwise false
bool isSorted(const auto &container)
{
    // Compare the current element to the previous one in the container
    for (size_t i = 1; i < container.size(); ++i)
    {
        if (container.at(i - 1) > container.at(i))
        {
            return false;
        }
    }

    return true;
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


/// @brief Utilize recursive binary search to look for a provided value 
///     and provide its index back through reference parameter.
///     Compile-time polymorphism will be utilized to determine which
///     binary search function to invoke based on parameters.
/// @param v the directly accessible (at(i)) container, often a vector
/// @param value the value to look for within the container
/// @param loc the variable to update to the discovery location when found
/// @param low the lowest index in the range to search
/// @param high the highest index in the range to search
/// @return true when the value is found, otherwise false
/// @pre The container v is sorted in ascending order.
bool binarySearch(const auto &v, const Card &value, 
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
        return binarySearch(v, value, loc, mid+1, high);
    }
    else
    {
        return binarySearch(v, value, loc, low, mid-1);
    }   
}


/// @brief Utilize linear search to look for the value in the container.
/// @param v The container to search through.
/// @param value The value to look for in the container.
/// @param loc The variable to update to the index of the discovered value.
/// @return true when the value is found, otherwise false
bool linearSearch(const auto &v, const Card &value, int &loc)
{
    for(size_t index = 0; index < v.size(); ++index)
    {
        if (v.at(index) == value)
        {
            loc = index;
            return true;
        }
    }
    return false;
}
