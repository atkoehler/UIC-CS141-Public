#include <iostream>

#include "instrument.h"
#include "orchestra.h"

using namespace std;

// Constructor
Orchestra::Orchestra() : head(nullptr), tail(nullptr) {}

// Destructor
Orchestra::~Orchestra() 
{
    // Iteratively destroy the list to prevent 
    // recursive destructor stack overflows
    while (head != nullptr) 
    {
        // Move the next node into head, 
        // automatically destroying the old head
        head = std::move(head->next);
    }
}

void Orchestra::addFront(unique_ptr<Instrument> inst) 
{
    auto newNode = make_unique<ChairNode>(std::move(inst));
    
    if (!head) 
    {
        // List is empty, head and tail point to the same new node
        head = std::move(newNode);
        tail = head.get();
    } 
    else 
    {
        // Link new node to current head, then update head
        newNode->next = std::move(head);
        head = std::move(newNode);

        // Note: tail does not change when adding to front of non-empty list
    }
}

void Orchestra::addBack(unique_ptr<Instrument> inst) 
{
    auto newNode = make_unique<ChairNode>(std::move(inst));
    
    if (!head) 
    {
        // List is empty, head and tail point to the same new node
        head = std::move(newNode);
        tail = head.get();
    } 
    else 
    {
        // Link current tail to new node, then update tail
        tail->next = std::move(newNode);
        tail = tail->next.get(); 
    }
}

// void Orchestra::addBackWithoutTail(std::unique_ptr<Instrument> inst) 
// {
//     auto newNode = std::make_unique<ChairNode>(std::move(inst));
    
//     // Is the list is empty?
//     if (!head) 
//     {
//         head = std::move(newNode);
//     } 
//     else 
//     {
//         // We must start at the beginning to find the end
//         ChairNode* current = head.get();
        
//         // Walk through the list until we find the node whose 'next' is nullptr
//         while (current->next != nullptr) 
//         {
//             current = current->next.get();
//         }
        
//         // We found the last node, now link the new node to it
//         current->next = std::move(newNode);
//     }
// }

void Orchestra::playConcert() const 
{
    cout << "=== Orchestra Concert Begins ===" << endl;
    
    ChairNode* current = head.get();
    while (current != nullptr) 
    {
        if (current->instrument) 
        {
            current->instrument->play();
        }
        current = current->next.get();
    }
    
    cout << "=== Orchestra Concert Concludes ===" << endl;
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