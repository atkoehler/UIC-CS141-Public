#include <string>
#include <compare> 

using namespace std; 

class Instrument {
    private:
        // ==========================================================
        // Private Member Variables
        // ==========================================================
        string name = "";
        string manufacturer = "";
        int yearBuilt = 1970;
        int cost = 0;

    public:
        // ==========================================================
        // Constructors & Destructors
        // ==========================================================
        // Explicitly defaulting this constructor tells the compiler to 
        // automatically generate it. This allows us to create an Instrument 
        // with no arguments while safely utilizing the default values (like "")
        // assigned to the member variables above.
        Instrument() = default;

        Instrument(string name, string manufacturer, int yearBuilt, int cost);

        // Making the destructor 'virtual' is a critical rule for base classes.
        // It ensures that if a derived object (like a StringInstrument) is 
        // deleted through a base class pointer, the derived class's destructor 
        // is properly called first, preventing memory leaks.
        virtual ~Instrument() = default;

        // ==========================================================
        // Mutators (Setters)
        // ==========================================================
        // Note: Strings are passed by value here in the header so the 
        // .cpp implementation can efficiently use std::move() to transfer ownership.
        void setName(string name);
        void setManufacturer(string manufacturer);
        
        void setYearBuilt(int yearBuilt);
        void setCost(int cost);

        // ==========================================================
        // Accessors (Getters)
        // ==========================================================
        // Returning 'const string&' avoids a bulky copy while keeping the 
        // internal string safe from modification. 
        const string& getName() const;
        const string& getManufacturer() const;
        
        // Primitives are returned by value because they are tiny and fast to copy.
        int getYearBuilt() const;
        int getCost() const;

        // ==========================================================
        // Utility Methods
        // ==========================================================
        virtual void printInfo() const;
        
        // Returns a formatted string representation of the object.
        // Matches the C++ standard library naming convention.
        string to_string() const;

        // ==========================================================
        // Operator Overloads (Pass-by-Const-Reference)
        // ==========================================================
        bool operator==(const Instrument& other) const;
        auto operator<=>(const Instrument& other) const;

    private:
        // ==========================================================
        // Private Helper Methods
        // ==========================================================
        // Placed at the bottom so the public interface remains the focus.
        // These functions can only be called from inside the class itself.
        bool isValidYear(int year) const;
};