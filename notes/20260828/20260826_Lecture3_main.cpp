/// @file 20260828_Lecture3_main.cpp
/// @author Adam T Koehler, PhD
/// @date August 28, 2026
/// @brief Code and lecture notes from the live lecture. 
///     Some code may require -std=c++23


// Libraries to accomplish various tasks
#include <iostream> // Input-Output Streams
#include <random>   // For prodcing random numbers
#include <vector>   // For using vector containers for many counters


// Specifying a namespace allows us to presume we are working in a 
// specific namespace and not have to use the scope resolution operator
// and namespace name (e.g. std::) with everything we need from that 
// namespace. However, it does make the code development less 
// "portable" as we are restricting the namespace.
using namespace std;



//////////////////////////////////////////////////////////////////////////////
//
// Stepwise development of a Monte Carlo simulation as a pratical exploration  
// of vectors, counting, accumulating, randomness, and loops within C++.
//
// Pairs with Lecture 2 Monte Carlo simulation of dice rolls activity.
//
//////////////////////////////////////////////////////////////////////////////



/// @brief main function for running our examples
/// @param argc the number of command line arguments
/// @param argv the array containing c-strings of command line args
int main(int argc, char *argv[])
{
    // Both of these declare unsigned integers
    unsigned int x;
    uint y;

    // These are signed integers
    int a, b, c;

    // We also have other numeric types: short, long, long long

    // srand allows us to seed the pseudorandom number generator
    // Using the same seed across different program runs will produce
    // the same random value sequence. This predictably is good for
    // testing but bad if randomness is being used to secure information
    // such as during encryption.
    srand(2026);

    // acquire a number from the random number generator
    cout << "Using old C-style rand()" << endl;
    cout << "========================" << endl;
    x = rand();
    cout << "Acquired random number: " << x << endl;
    x = rand();
    cout << "Acquired random number: " << x << endl;

    // If we invoke srand again, it restarts the sequence with the given seed.
    // This is why we generally only seed once per program execution.
    srand(2026);


    // Modern, high-quality pseudeorandom number generator
    // rand() is a pseudorandom number generator that is 
    // no longer commonplace in modern C++.
    // The mt19937 pseudeorandom number generator is used in modern C++
    // and stands for Mersenne Twister (mt) and the 19937 is the 
    // length of the repeating cycle.
    mt19937 modernRNG(2026);

    cout << endl << endl;
    cout << "Using modern C++ mt19937" << endl;
    cout << "========================" << endl;
    x = modernRNG();
    cout << "Acquired random number: " << x << endl;
    x = modernRNG();
    cout << "Acquired random number: " << x << endl;


    // Real randomness utilizes hardward (such as CPU) information/garbage to 
    // get random numbers. However, this is system dependent and can slow
    // down dramatically when compared to a mathematical pseudorandom 
    // number generator.
    random_device rd;

    cout << endl << endl;
    cout << "Using true randomness through hardware" << endl;
    cout << "======================================" << endl;
    x = rd();
    cout << "Acquired random number: " << x << endl;
    x = rd();
    cout << "Acquired random number: " << x << endl;


    // Usually we do not want such large numbers, so we must
    // constrain our random numbers in some way.
    
    // Our first methodology to do this is with the mod operator.
    // We mod by the range of potential numbers and then add the minimum value.
    x = rand();
    y = modernRNG();
    x = 1 + x % 6;  
    y = 1 + y % 6;
    cout << endl << endl;
    cout << "Limiting random numbers to a range" << endl;
    cout << "==================================" << endl;
    cout << "Constrained random number: " << x << endl;
    cout << "Constrained random number: " << y << endl;

    // Our second methodology utilizes the modern C++ uniform distribution 
    // object to enforce a random distribution on our random numbers.
    // This distribution takes the modern RNG object as an argument, so it 
    // does not work with C-style rand().
    uniform_int_distribution<int> dist(1, 6);
    x = dist(modernRNG);
    cout << endl << endl;
    cout << "Limiting random numbers to a range" << endl;
    cout << "==================================" << endl;
    cout << "Uniformly distrubted random number: " << x << endl;


    // Now let's count when we see a specific number
    int counter = 0;
    cout << endl << endl;
    cout << "Counting observations for rolling a 5" << endl;
    cout << "=====================================" << endl;
    cout << "Number of 5's observed: " << counter << endl;

    // repeated counting in branches and random number generation
    x = 1 + rand() % 6;
    if (x == 5)
    {
        counter++;
    }
    cout << "Number of 5's observed: " << counter << endl;

    x = 1 + rand() % 6;
    if (x == 5)
    {
        counter++;
    }
    cout << "Number of 5's observed: " << counter << endl;

    x = 1 + rand() % 6;
    if (x == 5)
    {
        counter++;
    }
    cout << "Number of 5's observed: " << counter << endl;


    // this process is redundant code and belongs in a loop
    // Let's place it in a loop and also use the modern C++
    // with the uniform distribution.
    counter = 0;
    uint simulation = 0;
    cout << endl << endl;
    cout << "Counting 5 observations in a loop" << endl;
    cout << "=================================" << endl;
    cout << "Number of 5's observed: " << counter << endl;
    while (simulation < 10)
    {
        // x = 1 + rand() % 6;
        x = dist(modernRNG);
        if (x == 5)
        {
            counter++;
        }      
        simulation++;
        cout << "Number of 5's observed: " << counter << endl;
    }


    // This process is great for one value, but how to about all
    // possible values that could be rolled with 3 6-sided die?
    
    // Create a container of counters for all potential rolled values.
    // The max value is 18 (6, 6, 6). If we want the value to be the index 
    // into the container, we waste some space on 0, 1, and 2 which are not
    // possible to roll with 3 dice. However, this reduces the cognitive 
    // load of designing algorithm and can be improved upon later.
    vector<int> counters(19);
    
    uint dieValue, roll;
    simulation = 0;
    uint maxSimulations = 0;

    cout << endl << endl << endl;
    cout << "Monte Carlo Simulation Activity" << endl;
    cout << "Estimating Probabilities of a Roll of 3 6-sided Dice" << endl;
    cout << "====================================================" << endl;
    cout << "How many simulations? ";
    cin >> maxSimulations;
    while (simulation < maxSimulations)
    {
        roll = 0;

        // Old style of using rand()
        // dieValue = 1 + rand() % 6;
        dieValue = dist(modernRNG);
        roll += dieValue;

        // dieValue = 1 + rand() % 6;
        dieValue = dist(modernRNG);
        roll += dieValue;

        // dieValue = 1 + rand() % 6;
        dieValue = dist(modernRNG);
        roll += dieValue;

        // could condense the above to:
        // roll = dist(modernRNG) + dist(modernRNG) + dist(modernRNG);

        counters.at(roll)++;
        simulation++;
    }

    // We could quickly output the values of every counter,
    // but that wouldn't have identifying information so 
    // that makes the output hard to read and decipher.
    // for(int val : counters)
    // {
    //     cout << val << endl;
    // }

    cout << endl << endl;
    cout << "Counting Observations" << endl;
    cout << "=====================" << endl;
    for(size_t i=0; i < counters.size(); ++i)
    {
        // Previously we matched the index value 
        // of the vector with or roll value
        cout << i << ": " << counters.at(i) << endl;
    }


    cout << endl << endl;
    cout << "Estimated Probabilities as Percentages" << endl;
    cout << "======================================" << endl;
    for(size_t i=0; i < counters.size(); ++i)
    {
        // Previously we matched the index value 
        // of the vector with or roll value
        cout << i << ": " 
            << static_cast<double>(counters.at(i)) / maxSimulations * 100
            << "%" << endl;
    }
    
    return 0;
}