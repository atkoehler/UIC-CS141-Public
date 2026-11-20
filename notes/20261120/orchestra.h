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

    public:
        Orchestra();
        ~Orchestra(); // Custom destructor to prevent stack overflow
        
        void addFront(unique_ptr<Instrument> inst);
        void addBack(unique_ptr<Instrument> inst);
        void printChairs() const;
        void playConcert() const;
};