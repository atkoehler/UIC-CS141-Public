#include "instrument.h"
#include <iostream>
#include <tuple> // Required for std::tie

using namespace std;

// ==========================================================
// Constructors
// ==========================================================
// Uses a member initialization list. Note the use of std::move() 
// for the strings to efficiently transfer ownership without copying.
Instrument::Instrument(string name, string manufacturer, int year, int cost)
    : name(std::move(name)), manufacturer(std::move(manufacturer)), cost(cost)
{
    if (isValidYear(year)) 
    {
        this->yearBuilt = year;
    } 
    else 
    {
        this->yearBuilt = 1970; // Fallback to default if invalid
    }
}

// ==========================================================
// Mutators (Setters)
// ==========================================================
void Instrument::setName(string name) 
{
    this->name = std::move(name);
}

void Instrument::setManufacturer(string manufacturer) 
{
    this->manufacturer = std::move(manufacturer);
}

void Instrument::setYearBuilt(int yearBuilt) 
{
    if (isValidYear(yearBuilt)) {
        this->yearBuilt = yearBuilt;
    }
}

void Instrument::setCost(int cost) 
{
    if (cost >= 0) { // Simple validation to prevent negative costs
        this->cost = cost;
    }
}

// ==========================================================
// Accessors (Getters)
// ==========================================================
const string& Instrument::getName() const 
{
    return name;
}

const string& Instrument::getManufacturer() const 
{
    return manufacturer;
}

int Instrument::getYearBuilt() const 
{
    return yearBuilt;
}

int Instrument::getCost() const 
{
    return cost;
}

// ==========================================================
// Utility Methods
// ==========================================================
void Instrument::printInfo() const 
{
    cout << to_string() << endl;
}

string Instrument::to_string() const 
{
    // std::to_string is used to convert primitive integers to strings
    return name + " made by " + manufacturer + 
           " (Built: " + std::to_string(yearBuilt) + 
           ", Cost: $" + std::to_string(cost) + ")";
}



// ==========================================================
// Operator Overloads
// ==========================================================
bool Instrument::operator==(const Instrument& other) const 
{
    return name == other.name &&
           manufacturer == other.manufacturer &&
           yearBuilt == other.yearBuilt &&
           cost == other.cost;
}

auto Instrument::operator<=>(const Instrument& other) const 
{
    // std::tie groups the members into a tuple and compares 
    //  them lexicographically. It checks name first; if they tie, 
    //  it checks manufacturer, and so on.
    return std::tie(name, manufacturer, yearBuilt, cost) <=> 
        std::tie(other.name, other.manufacturer, other.yearBuilt, other.cost);
}

// ==========================================================
// Private Helper Methods
// ==========================================================
bool Instrument::isValidYear(int year) const 
{
    // Simple validation rule: Assuming instruments in our system 
    // shouldn't pre-date 1500 and shouldn't be from the future.
    return year >= 1500 && year <= 2026; 
}