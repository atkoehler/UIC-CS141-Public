/// @file 20261026_Lecture27_main.cpp
/// @author Adam T Koehler, PhD
/// @date October 26, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some items require C++20, compile with g++ -std=c++23 XXX_main.cpp

#include <iostream>
#include <vector>

using namespace std;

/// @brief Utilize binary search to determine the 
///         location of a value within a vector.
/// @param v the directly accessible (at(i)) container, often a vector
/// @param value the value to look for within the container
/// @param loc the variable to update to the discovery location when found
/// @return true when the value is found, otherwise false
/// @pre The container v is sorted in ascending order.
bool binarySearch(const auto &v, int value, int &loc)
{
    // Binary search utilizes three values and updates them
    // during the search pattern.
    int low, mid, high;

    if (v.empty())
    {
        return false;
    }

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
    vector<int> pile = {1, 2, 2, 3, 5, 5, 7};
    int location = -1;
    int searchFor = -1;
    bool discovered = false;
    
    cout << "Search through the pile of values containing: " << endl;
    for(const auto &val : pile)
    {
        cout << val << " ";
    }
    cout << endl << endl;

    searchFor = 8;  
    cout << "Attempting to find " << searchFor << " in pile." << endl;
    discovered = binarySearch(pile, searchFor, location);    
    if(discovered)
    {
        cout << "  Found at index value " << location << endl;  
    }
    else
    {
        cout << "  Did not find " << searchFor << endl;
    }

    searchFor = 5;
    cout << "Attempting to find " << searchFor << " in pile." << endl;
    discovered = binarySearch(pile, searchFor, location);    
    if(discovered)
    {
        cout << "  Found at index value " << location << endl;  
    }
    else
    {
        cout << "  Did not find " << searchFor << endl;
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
