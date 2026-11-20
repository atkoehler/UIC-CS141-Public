#include <iostream>

#include "instrument.h"
#include "orchestra.h"

using namespace std;

// Constructor
Orchestra::Orchestra() : head(nullptr), tail(nullptr) {}

// Destructor
Orchestra::~Orchestra() 
{
}

void Orchestra::addFront(unique_ptr<Instrument> inst) 
{
}

void Orchestra::addBack(unique_ptr<Instrument> inst) 
{
}


void Orchestra::playConcert() const 
{
}


void Orchestra::printChairs() const 
{
    cout << "=== Orchestra Chairs ===" << endl;
    
    // Start at the head of the list using a raw observing pointer
    ChairNode* current = head.get();
    
    // Traverse until we fall off the end of the list
    while (current != nullptr) 
    {
        // Ensure the chair actually has an instrument before calling printInfo
        if (current->instrument) 
        {
            current->instrument->printInfo();
        }
        
        // Move to the next node
        current = current->next.get();
    }
}