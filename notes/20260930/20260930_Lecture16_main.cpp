/// @file 20260930_Lecture16_main.cpp
/// @author Adam T Koehler, PhD
/// @date September 30, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some code may require -std=c++23
///     Compile with g++ -std=c++23 die.cpp XXX_main.cpp

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

void QuizQuestion_LinearSearch()
{
    // Initialize the random number engine
    // Using the Mersenne Twister engine, default seed 19937
    mt19937 gen; 

    // Define the distribution
    uniform_int_distribution<> dist(-32, 31);

    // Create a vector of integers
    vector<int> nums;

    // Populate the vector with random numbers
    cout << "Creating vector with the following integers: " << endl;
    for (int i = 0; i < 52; ++i) 
    {
        nums.push_back(dist(gen));
        cout << nums.back() << " ";
    }
    cout << endl;

    // define the target
    int target = nums.at(0);

    // Count comparisons needed to find the target
    int counter = 0;
    for (int n : nums) 
    {
        counter++;
        if (n == target)
        {
            break;
        }
    }
    cout << endl;
    cout << "Searched For: " << target << endl;
    cout << "Comparisons: " << counter << endl;


    // Count comparisons needed to find the target
    target = -18;
    counter = 0;
    for (int n : nums) 
    {
        counter++;
        if (n == target)
        {
            break;
        }
    }
    cout << endl;
    cout << "Searched For: " << target << endl;
    cout << "Comparisons: " << counter << endl;
    
    // Count comparisons needed to find the target
    target = dist(gen);
    target = dist(gen);
    target = dist(gen);

    counter = 0;
    for (int n : nums) 
    {
        counter++;
        if (n == target)
        {
            break;
        }
    }
    cout << endl;
    cout << "Searched For: " << target << endl;
    cout << "Comparisons: " << counter << endl;


    // Count comparisons needed to find the target
    target = -50;
    counter = 0;
    for (int n : nums) 
    {
        counter++;
        if (n == target)
        {
            break;
        }
    }
    cout << endl;
    cout << "Searched For: " << target << endl;
    cout << "Comparisons:  " << counter << endl;
}



int main(int argc, char *argv[])
{
    // no second command line argument, run all examples
    if (argc > 1 && isdigit(argv[1][0]))
    {
        switch (atoi(argv[1]))
        {
            case 1:
                QuizQuestion_LinearSearch();
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
