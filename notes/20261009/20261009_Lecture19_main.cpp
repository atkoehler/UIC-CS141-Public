/// @file 20261009_Lecture19_main.cpp
/// @author Adam T Koehler, PhD
/// @date October 9, 2026
/// @brief Code and lecture notes from the live lecture.
///     Compile with g++ XXX_main.cpp

#include <iostream>

using namespace std;



// Alternate funtion header options and related design choices
// string faroShuffle(string s)         // pass by value - invokes copy constructor
// string faroShuffle(string &s)        // pass by reference - allows modification of external string
// string faroShuffle(const string &s)  // pass by const reference - appropriate legacy methodology

/// @brief Perform an interleaving shuffling of two halves of the whole. 
///         Thus fitting one letter ("card") from the second half in
///         between each letter of the first half.
///         Corresponds to prior lecture activity where we didn't get to
///         write the actual code and see it running.
/// @param s string to generate a shuffled string from
/// @return the shuffled string
string faroShuffle(string_view s)
{
    string shuffled;   

    // determine the split point for the provided string
    const size_t halfway = s.size() / 2;

    // iterate over the first half 
    // calculate the index for the second half
    for (size_t i = 0; i < halfway; ++i)
    {
        shuffled.push_back(s.at(i));
        shuffled.push_back(s.at(i + halfway));
    }

    // determine if the string has an odd size.
    // (we do not need to check for size > 0 first)
    if (s.size() % 2 != 0)
    {
        shuffled.push_back(s.back());
    }

    return shuffled;
}


void Example1()
{
    cout << "Even Length Strings" << endl;
    cout << "===================" << endl;
    cout << "Provided: \"123456\"" << endl;
    cout << "Expected: \"142536\"" << endl;
    cout << "Shuffled: \"" << faroShuffle("123456") << "\"" << endl;
    cout << endl;

    cout << "Provided: \"abcdefgh\"" << endl;
    cout << "Expected: \"aebfcgdh\"" << endl;
    cout << "Shuffled: \"" << faroShuffle("abcdefgh") << "\"" << endl;
    cout << endl << endl;

    cout << "Odd Length Strings" << endl;
    cout << "==================" << endl;
    cout << "Provided: \"12345\"" << endl;
    cout << "Expected: \"13245\"" << endl;
    cout << "Shuffled: \"" << faroShuffle("12345") << "\"" << endl;
    cout << endl;
    cout << "Provided: \"A1234567890JQK?\"" << endl;
    cout << "Expected: \"A71829304J5Q6K?\"" << endl;
    cout << "Shuffled: \"" << faroShuffle("A1234567890JQK?") << "\"" << endl;
    cout << endl << endl;

    cout << "Edge Cases" << endl;
    cout << "==========" << endl;
    cout << "Provided: \"A\"" << endl;
    cout << "Expected: \"A\"" << endl;
    cout << "Shuffled: \"" << faroShuffle("A") << "\"" << endl;
    cout << endl;
    cout << "Provided: \"\"" << endl;
    cout << "Expected: \"\"" << endl;
    cout << "Shuffled: \"" << faroShuffle("") << "\"" << endl;
}


// Activity - Code Traversal
// Given our knowledge of Faro Shuffle. How many shuffles occur before
// the original string is the result of the shuffle?
void Example2()
{
    int counter = 0;
    string original = "123456";
    string result = faroShuffle(original);
    counter++;

    // When does the shuffling result become the original string?
    while (result != original) 
    { 
        result = faroShuffle(result);
        counter++;
    }

    // Algorithm walkthrough for "123456"
    // 1: "142536"
    // 2: "154326"
    // 3: "135246"
    // 4: "123456"

    cout << "Faro Shuffle took " << counter << " times, "
         << "to get back to the original." << endl;

    // This algorithmic style of shuffling is mathematically predictable.
    // That is great for checking correctness, but not so great if we want 
    // to produce unpredictable orderings / shuffles.
}


/// @brief Linear search through a C-string for a specific character
/// @param word the C-string (null terminated character array) to search
/// @param lookFor the character to search for
/// @pre The C-string is properly terminated with a null character.
/// @return The index of the discovered character or -1 when not found.
int cStrSearch(char word[], char lookFor)
{
    // iterate through the C-string until a null character is discovered
    for(uint i = 0; word[i] != '\0'; ++i)
    {
        // When we find the character, we can return immediately
        if (word[i] == lookFor)
        {
            return i;
        }
    }
    
    // When we do not find the character, we return a value that is an invalid
    // index into the C-string so the caller knows it was not found.
    return -1;
}

void Example3()
{
    char c = 'j';
    char word1[80] = "hello";
    char word2[80] = "jello";
    int index = -1;

    cout << "Searching for " << c << " in " << word1 << endl;
    index = cStrSearch(word1, c);
    if (index >= 0)
    {
        cout << "Found " << c << " at index " << index << endl;
    }
    else
    {
        cout << "Did not find " << c << endl;
    }

    cout << endl;
    
    cout << "Searching for " << c << " in " << word2 << endl;
    index = cStrSearch(word2, c);
    if (index >= 0)
    {
        cout << "Found " << c << " at index " << index << endl;
    }
    else
    {
        cout << "Did not find " << c << endl;
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
            case 3:
                Example3();
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
