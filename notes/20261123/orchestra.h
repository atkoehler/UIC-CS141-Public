#pragma once

#include <memory>
#include "instrument.h"

// ==========================================================
// The ChairNode (Linked List Node)
// ==========================================================
struct ChairNode 
{
    unique_ptr<Instrument> instrument;
    unique_ptr<ChairNode> next;

    ChairNode(unique_ptr<Instrument> inst) 
        : instrument(std::move(inst)), next(nullptr) {}
};

// ==========================================================
// Orchestra Class (Singly Linked List)
// ==========================================================
class Orchestra 
{
    private:
        // Owning pointer to the start of the list
        unique_ptr<ChairNode> head; 

        // Raw observing pointer to the end of the list
        ChairNode* tail;     
        
        size_t chairs;

    public:
        Orchestra();
        ~Orchestra(); // Custom destructor to prevent stack overflow
        
        // Acquire the size of the Linked List
        size_t size() const;

        // Interact with each item in the Linked List
        void playConcert() const;
        void printChairs() const;

        // Insertion
        void addBack(unique_ptr<Instrument> inst);
        void addFront(unique_ptr<Instrument> inst);
        void addAfter(unique_ptr<Instrument> inst, size_t location);

    // Helper Functions
    private:
        // Selection Sort Helper
        unique_ptr<ChairNode> extractMinimum();
};