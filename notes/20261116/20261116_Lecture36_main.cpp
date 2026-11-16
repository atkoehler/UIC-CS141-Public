/// @file 20261116_Lecture36_main.cpp
/// @author Adam T Koehler, PhD
/// @date November 16, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some items require C++23, compile with g++ -std=c++23 XXX_main.cpp

#include <iostream>
#include <memory>
#include <string>

// Includes the abstract base class Instrument
#include "instrument.h" 

using namespace std;

// ==========================================================
// Derived Class: Cello
// ==========================================================
class Cello : public Instrument 
{
    private:
        string bowType; 

    public:
        // Constructor Chaining (4 base parameters + 1 derived parameter)
        Cello(string name, string manufacturer, int yearBuilt, int cost, string bowType)
            : Instrument(name, manufacturer, yearBuilt, cost), bowType(bowType) {}

        // Fulfilling the pure virtual contract
        void play() const override {
            // 'name' is accessible because it was made protected in instrument.h
            cout << name << " (Cello): Drawing the " << bowType << " bow across the strings...\n";
        }
};

// ==========================================================
// Derived Class: Trumpet
// ==========================================================
class Trumpet : public Instrument 
{
    private:
        string finish; 

    public:
        Trumpet(string name, string manufacturer, int yearBuilt, int cost, string finish)
            : Instrument(name, manufacturer, yearBuilt, cost), finish(finish) {}

        void play() const override {
            cout << name << " (Trumpet): Buzzing the mouthpiece of the " << finish << " trumpet...\n";
        }
};

// ==========================================================
// The ChairNode (Linked List Node)
// ==========================================================
struct ChairNode 
{
    std::unique_ptr<Instrument> instrument; // Universal pointer to the base class
    std::unique_ptr<ChairNode> next;        // Pointer to the next chair

    // Constructor using std::move to transfer ownership
    ChairNode(std::unique_ptr<Instrument> inst) 
        : instrument(std::move(inst)), next(nullptr) {}
};

// ==========================================================
// Primary Function: Manual Stage Setup
// ==========================================================
void Activity() 
{
    // 1. Setup the first chair and sit a Cello in it
    // Explicit type declaration for clarity
    std::unique_ptr<ChairNode> chair1 = std::make_unique<ChairNode>(
        std::make_unique<Cello>("Stradivarius", "Antonio Stradivari", 1711, 2500000, "French")
    );

    // 2. Setup the second chair and sit a Trumpet in it
    // Using auto here for cleaner syntax (translates to std::unique_ptr<ChairNode>)
    auto chair2 = std::make_unique<ChairNode>(
        std::make_unique<Trumpet>("Model 37", "Vincent Bach", 2015, 3000, "Silver")
    );

    // 3. Link them together: Chair 1 now owns Chair 2
    // We must use std::move because unique_ptr cannot be copied
    chair1->next = std::move(chair2);

    // 4. Play them manually to prove the polymorphic dispatch works
    cout << "=== Manual Concert ===" << endl;

    // Play first instrument
    chair1->instrument->play();

    // Play second instrument
    chair1->next->instrument->play();
    
    // Both chairs and instruments are automatically destroyed at the return!
}

int main(int argc, char *argv[])
{
    // no second command line argument, run all examples
    if (argc > 1 && isdigit(argv[1][0]))
    {
        switch (atoi(argv[1]))
        {
            case 1:
                Activity();
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