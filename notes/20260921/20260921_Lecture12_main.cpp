/// @file 20260921_Lecture12_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 21, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23
///     Compile with g++ -std=c++23 die.cpp XXX_main.cpp

// Libraries to accomplish various tasks
#include <array>
#include <iostream> // Input-Output Streams
#include <random>   // For random_device and pseudorandom number generator
#include <string>   // For the C++ string datatype
#include <utility>  // std::move()

#include "die.h"

using namespace std;

// accepted for partial credit
// bool matches(vector<string> &one, vector<string> &two)
// bool matches(vector<string> one, vector<string> two)

/// @brief Activity Prompt: Write a function that compares two vectors of 
///         strings to determine if every similar index between the two 
///         vectors has the same size.
/// @param one first vector of strings to compare
/// @param two second vector of strings to compare
/// @return true when the strings at all the individual indices have the
///         same size, otherwise false
bool matches(const vector<string> &one, const vector<string> &two )
{
    // Bounds checking can happen before or within the loop.
    // Bounds checking ensures that the at(i) accesses within
    // the loop will work for both vectors.
    if (one.size() != two.size())
    {
        return false;
    }

    // Iterate over the vector element by element
    // Since we need to compare the same index across multiple
    // vectors we will need access to the index and must use
    // an index-based loop (not a for-each loop).

    // acceptable for hand-written code
    // for (int i = 0; i < one.size(); ++i)
    // for (unsigned int i = 0; i < one.size(); ++i)
    // for (uint i = 0; i < one.size(); ++i)
    for (size_t i = 0; i < one.size(); ++i)
    {
        if(one.at(i).size() != two.at(i).size())
        {
            return false;
        }

        // Bounds checking within the loop to ensure 
        // the i index is a valid value for the second vector.
        // However using this methodology will presume vector one
        // is larger than vector two. And would require cleanup
        // after the loop because the sizes not matching should
        // yield a false outcome of for the function.
        // if(i < two.size())
        // {
        //     // Compare the two sizes of the string elements
        //     // at the current index value. When they don't match
        //     // we can be done early and return false.
        //     if(one.at(i).size() != two.at(i).size())
        //     {
        //         return false;
        //     }
        // }
        // else
        // {
        //     // When i would be out of bounds for the second vector
        //     // but is still in bounds for the first vector (because we
        //     // are in the loop body) then the sizes are mismatched.
        //     // No element to compare to means we can return false early.
        //     return false;
        // }
    }

    // We made it through all the comparisons of the similar indices
    // and never exited early with a "return false" so everything matched.
    return true;
}

void Option1Examples()
{
    vector<string> x;
    vector<string> y;
    string a = "hello";
    string b = "abcde";
    string c = "acb";

    x.push_back(a);
    if(matches(x, y))
    {
        cout << "Vectors have strings with matching sizes for all indices."
            << endl;
    }
    else
    {
        cout << "Vectors have strings with mismatched sizes across indices."
            << endl;
    }

    y.push_back(b);
    if(matches(x, y))
    {
        cout << "Vectors have strings with matching sizes for all indices."
            << endl;
    }
    else
    {
        cout << "Vectors have strings with mismatched sizes across indices."
            << endl;
    }

    y.push_back(c);
    if(matches(x, y))
    {
        cout << "Vectors have strings with matching sizes for all indices."
            << endl;
    }
    else
    {
        cout << "Vectors have strings with mismatched sizes across indices."
            << endl;
    }
    


}




// const & is good too
// accepted for partial credit
// bool isSorted(string s)
// bool isSorted(string &s)

// accepted for full credit but not best design choice
// bool isSorted(const string &s)

/// @brief Activity Prompt: Write a function that takes a string and 
///         determines if the elements are sorted.
/// Design Choice: What is sorted order? Ascending Alphabetical?
/// @param s a viewer of the string to be checked for sorted order
/// @return true when the string is in sorted character by character
bool isSorted(string_view s) 
{
    // Initial Implementation - A lot of people go this route.
    for(int i = 0; i+1 < s.size(); ++i)
    {
        // Using the transitive property of inequality 
        // e.g. a < b and b < c means a < c
        
        // When we find a character that is out of place we can return 
        // immediately because the string is not in sorted order and 
        // we do not have to check any other characters.
        if (s.at(i) > s.at(i+1))
        {
            return false;
        }
    }

    return true;
}

void Option2Examples()
{
    string a = "hello world";
    string ordered = "abcdefg";
    string unordered = "acb";
    string reverse = "gfedcba";

    if(isSorted(a))
    {
        cout << "The string \"" << a << "\" is sorted!" << endl;
    }
    else
    {
        cout << "The string \"" << a << "\" is not sorted." << endl;
    }

    if(isSorted(ordered))
    {
        cout << "The string \"" << ordered << "\" is sorted!" << endl;
    }
    else
    {
        cout << "The string \"" << ordered << "\" is not sorted." << endl;
    }

    if(isSorted(unordered))
    {
        cout << "The string \"" << unordered << "\" is sorted!" << endl;
    }
    else
    {
        cout << "The string \"" << unordered << "\" is not sorted." << endl;
    }

    if(isSorted(reverse))
    {
        cout << "The string \"" << reverse << "\" is sorted!" << endl;
    }
    else
    {
        cout << "The string \"" << reverse << "\" is not sorted." << endl;
    }

}




/// @brief compare all the Die objects in the container to determine 
///         if they have the same value
/// @param container the C++ array of 5 Die objects
/// @return true when all the Die objects have the same value, otherwise false
bool allTheSame(const array<Die, 5> &container)
{
    if (container.empty())
    {
        return true;
    }

    for(size_t i = 1; i < container.size(); ++i)
    {
        // compare every Die in the array to the first
        if (container.at(0).getValue() != container.at(i).getValue())
        {
            return false;
        }
    }

    return true;
}

// Main program with simple example using a collection of dice and rolling 
// the collection some number of times.
void Option3Examples()
{
    // A container full objects that are from our user created Die Class
    array<Die, 5> cup;

    // Could also use a vector, but since we know it is always 5 Die objects
    // an array would be the better design choice.
    // vector<Die> cup(5);
    
    ulong simulations = 1000000;
    ulong i = 0;
    while(i < simulations)
    {
        // Roll the cup of dice
        for (Die &d : cup)
        {
            d.roll();
        }

        // Display the cup contents
        string output = "[";
        for (const Die &d : cup)
        {
            output += to_string(d.getValue()) + ',';
        }
        output.pop_back();
        output += "]";

        cout << "Shake " << i << ": " << output << endl;

        // Are all the rolled dice the same?
        if(allTheSame(cup))
        {
            cout << "    They all match!" << endl;
            break;
        }
        else
        {
            cout << "    Not all the same :(" << endl;
        }

        i++;
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
            case 2:
                Option2Examples();
                break;
            case 3:
                Option3Examples();
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



