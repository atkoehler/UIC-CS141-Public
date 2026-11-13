# From Composition to Inheritance in C++

## 1. Building Complexity: Composition First
Before diving into inheritance, it is important to understand how we traditionally build complex objects in C++ using **composition**. 

Composition is the practice of building a complex class by combining simpler objects as member variables. For instance, a `Car` object might contain an `Engine` object and four `Wheel` objects. 

```mermaid
classDiagram
    class Engine {
        +start()
    }
    class Car {
        -Engine myEngine
        +drive()
    }
    
    Car *-- Engine : HAS-A (Composition)
```

Here is what that **HAS-A** relationship looks like in actual C++ syntax. Notice how the `Car` class creates an instance of `Engine` as a private member variable to do its job:

```cpp
#include <iostream>
using namespace std;

class Engine 
{
    public:
        void start() 
        {
            cout << "Engine is running.\n";
        }
};

class Car 
{
    private:
        // Composition: A Car HAS-A Engine
        Engine myEngine; 

    public:
        void drive() 
        {
            myEngine.start(); // Using the composed object's functionality
            cout << "Car is driving forward.\n";
        }
};
```

Composition solves the problem of *assembly* (putting parts together to make a whole). But what happens when we do not want to just assemble parts, but instead need to create a *specialized version* of an existing concept? That is where we cross the bridge from composition to inheritance.

---

## 2. What is Inheritance? (And Why Do We Use It?)
In Object-Oriented Programming (OOP), **inheritance** is a mechanism that allows a new class to acquire the properties and behaviors of an existing class. 

### The Core Goals of Inheritance
*   **Code Reusability:** Write common attributes and methods once in a base class rather than copying and pasting boilerplate code into every new class.
*   **Extensibility:** Take a general concept and specialize it by adding new variables and functions without altering the original working code.
*   **Logical Hierarchy:** Organize code to mirror real-world classifications and relationships.

---

## 3. The IS-A vs. HAS-A Relationship
Building on our introduction to composition, we must always ask: *How do these objects relate to one another?* We categorize software design relationships into two main buckets: **IS-A** and **HAS-A**.

*   **IS-A (Inheritance):** Represents a relationship of specialization. If Class B **IS-A** Class A, it means Class B is a specific version of Class A. It automatically receives Class A's attributes and behaviors, and then adds its own.
*   **HAS-A (Composition):** Represents ownership or a part-whole relationship. If Class B **HAS-A** Class A, it means Class B contains an instance of Class A as a member variable to do its job.

### Applying IS-A to Vehicles
If we want our program to represent different types of vehicles, we do not want to write the same speed and weight variables for every single type. Instead, we can create a `Vehicle` base class. 

A `Car` **IS-A** `Vehicle`. A `Truck` **IS-A** `Vehicle`. Because of this inheritance, both `Car` and `Truck` logically contain the foundational data from `Vehicle`, and we only need to write code for their specialized features (like `trunkCapacity` for the car, and `towingCapacity` for the truck).

Conversely, a `Car` is not an engine. It uses an engine. Therefore, the `Car` **HAS-A** `Engine`, meaning we represent that by giving `Car` a member variable of type `Engine`.

```mermaid
classDiagram
    class Vehicle {
        -int topSpeed
        -int weight
    }
    class Car {
        -int trunkCapacity
    }
    class Truck {
        -int towingCapacity
    }
    class Engine {
        -int horsepower
    }
    
    Vehicle <|-- Car : IS-A (Inheritance)
    Vehicle <|-- Truck : IS-A (Inheritance)
    Car *-- Engine : HAS-A (Composition)
    Truck *-- Engine : HAS-A (Composition)
```

---

## 4. Core Terminology
Before mapping these concepts to C++ syntax, we need to establish a shared vocabulary:

*   **Base Class (Parent / Superclass):** The original, general class whose attributes and methods are being inherited (e.g., `Vehicle`).
*   **Derived Class (Child / Subclass):** The new, specialized class that inherits from the base class and adds its own unique features (e.g., `Truck`).
*   **Specialization:** The process of extending a general base class to create a more specific derived class.
*   **Generalization:** Extracting shared traits from multiple specialized classes and placing them into a common base class.
*   **Access Specifiers:** Keywords (`public`, `private`, `protected`) that control which parts of a program can see and modify class members.

---

## 5. Visualizing the `Instrument` Family Tree
Now let's bring these concepts back to the codebase we are working on. When we expand our `Instrument` base class into multiple specialized families, we create an inheritance hierarchy. Each derived class inherits the core members from `Instrument` while maintaining its own distinct member variables.

```mermaid
classDiagram
    class Instrument {
        -string name
        -string manufacturer
        -int yearBuilt
        -int cost
    }
    class StringInstrument {
        -int numStrings
        -bool isBowed
    }
    class BrassInstrument {
        -string mouthpieceType
        -bool hasValves
    }
    class PercussionInstrument {
        -bool isPitched
        -bool usesMallets
    }
    Instrument <|-- StringInstrument : inherits
    Instrument <|-- BrassInstrument : inherits
    Instrument <|-- PercussionInstrument : inherits
```

---

## 6. The Private Data Barrier
In C++, inheriting from a class means the derived class object contains the base class's data in memory. However, **inheriting data does not mean having direct access to it.**

In `instrument.h`, the member variables (`name`, `manufacturer`, `yearBuilt`, and `cost`) are marked `private`. Because they are `private`, **only** methods inside the `Instrument` class itself can read or modify them directly. Even a child class like `StringInstrument` is locked out.

### How Derived Classes Interact with Private Base Data
```cpp
// Inside a StringInstrument method:
void StringInstrument::updateDetails() 
{
    // COMPILER ERROR! 'name' and 'cost' are private in Instrument.
    // name = "Stradivarius"; 
    // cost = 1000000;

    // CORRECT: Use the public mutators (setters) inherited from Instrument.
    setName("Stradivarius");
    setCost(1000000);
}
```
To read or change base class data, derived classes must go through the `public` interface—using getters like `getName()` and setters like `setName()`. This preserves **encapsulation** and ensures any validation logic (like `isValidYear()` inside `Instrument`) cannot be bypassed by child classes.

---

## 7. The `protected` Access Modifier (The VIP Pass)
What if a base class designer *wants* child classes to have direct access to certain variables or helper methods, while still hiding them from the outside world (like `main.cpp`)? C++ provides a middle-ground access specifier: **`protected`**.

Think of `protected` as a **VIP Pass** for family members:
*   **`private`:** Locked in a safe. Accessible *only* within the class itself. Neither `main.cpp` nor derived classes can touch it directly.
*   **`protected`:** A VIP pass for derived classes. Accessible within the class itself **AND** within any derived classes, while remaining completely hidden from outside code like `main.cpp`.
*   **`public`:** Open to the general public. Accessible from anywhere.

### Comparing `private` vs. `protected` in Action
If we hypothetically changed `name` in `Instrument` from `private` to `protected`, direct access would behave differently depending on where the code lives:

```cpp
class Instrument 
{
    protected:
        string name; // Now has a VIP pass for child classes
    private:
        int cost;    // Still strictly locked to Instrument only
};

// 1. Inside a Derived Class (StringInstrument.cpp)
void StringInstrument::setup() 
{
    name = "Cello"; // ALLOWED! Derived classes can access 'protected' members.
    // cost = 500;  // COMPILER ERROR! 'cost' is still 'private'.
}

// 2. Inside Outside Code (main.cpp)
int main() 
{
    StringInstrument myCello;
    // myCello.name = "Cello"; // COMPILER ERROR! 'protected' is still hidden from main().
    // myCello.cost = 500;     // COMPILER ERROR! 'private' is hidden from main().
}
```

### Architectural Design Choices & Modern C++ Commentary
Choosing between `private`, `protected`, and `public` is an intentional architectural decision that balances convenience against safety:

*   **When `protected` is useful:** It is great for internal helper methods (like a `calculateBaseDepreciation()` function) that child classes need to use to build their own behavior, but that outside users in `main()` should never call directly.
*   **Modern C++ Guidance on Data Members:** While `protected` member variables are completely valid C++, modern C++ Core Guidelines generally advise keeping **data members** `private` and exposing `protected` getters/setters if derived classes need special access. 
*   **Why?** If a base class makes data `protected`, any derived class (even one written years later by another developer) can mutate that data directly, potentially bypassing validation rules (like `isValidYear()`) or breaking invariants the base class relies on. Keeping data `private` forces everyone—even child classes—to respect the class's data integrity rules.

---

## 8. C++ Inheritance Syntax: The `Animal` Example

Before applying inheritance to our `Instrument` hierarchy, let's look at the exact C++ syntax using a classic `Animal` base class and two derived classes: `Dog` and `Cat`.

To declare that a class inherits from another, we place a single colon (`:`) after the derived class name, followed by the **inheritance access specifier** (`public`) and the name of the base class.

```cpp
#include <string>
#include <iostream>
using namespace std;

// ==========================================================
// Base Class (Parent)
// ==========================================================
class Animal 
{
    private:
        string name;
        int age;

    public:
        Animal(string name, int age) : name(name), age(age) 
        {
        }

        string getName() const 
        { 
            return name; 
        }
        
        int getAge() const 
        { 
            return age; 
        }

        void eat() const 
        {
            cout << name << " is eating." << endl;
        }
};

// ==========================================================
// Derived Class 1 (Child)
// ==========================================================
// Syntax: class DerivedClass : public BaseClass
class Dog : public Animal 
{
    private:
        string breed; // Specialized attribute only Dogs have

    public:
        // The derived constructor passes 'name' and 'age' up to the Animal constructor
        Dog(string name, int age, string breed)
            : Animal(name, age), breed(breed) 
        {
        }

        void bark() const 
        {
            // Must use getName() because 'name' is private in Animal
            cout << getName() << " says: Woof!" << endl;
        }
};

// ==========================================================
// Derived Class 2 (Child)
// ==========================================================
class Cat : public Animal 
{
    private:
        bool isIndoor; // Specialized attribute only Cats have

    public:
        Cat(string name, int age, bool isIndoor)
            : Animal(name, age), isIndoor(isIndoor) 
        {
        }

        void purr() const 
        {
            cout << getName() << " is purring..." << endl;
        }
};
```

### Key Syntax Takeaways
*   **`class Dog : public Animal`**: This establishes **public inheritance**. It tells the compiler that a `Dog` IS-A `Animal`, preserving the base class's `public` interface so outside code can still call `myDog.eat()` or `myDog.getName()`.
*   **Constructor Chaining (`: Animal(name, age)`)**: Because `Dog` and `Cat` do not own `name` or `age`, their constructors must invoke the `Animal` constructor in their **member initialization list** to initialize the base portion of the object before initializing their own specialized variables.
*   **Inherited Behavior**: Both `Dog` and `Cat` automatically gain `eat()`, `getName()`, and `getAge()` without rewriting a single line of that logic, while adding their own specialized behaviors (`bark()` and `purr()`).

---

## 9. Activity: Building Your Derived `Instrument` Class

Now it is your turn to apply C++ inheritance syntax to our `Instrument` base class. 

```mermaid
classDiagram
    class Instrument {
        -string name
        -string manufacturer
        -int yearBuilt
        -int cost
    }
    class StringInstrument {
        -int numStrings
        -bool isBowed
    }
    class BrassInstrument {
        -string mouthpieceType
        -bool hasValves
    }
    class PercussionInstrument {
        -bool isPitched
        -bool usesMallets
    }
    Instrument <|-- StringInstrument : inherits
    Instrument <|-- BrassInstrument : inherits
    Instrument <|-- PercussionInstrument : inherits
```

### Your Task
Choose **one** of the three derived instrument families shown in the diagram above (`StringInstrument`, `BrassInstrument`, or `PercussionInstrument`) and write a basic C++ class declaration in a new header file (e.g., `StringInstrument.h`).

**Requirements:**
1. **Include the Base Header:** Make sure to `#include "instrument.h"` at the top of your file.
2. **Inherit Publicly:** Declare your class so that it inherits `publicly` from `Instrument`.
3. **Add Specialized Data Members:** Declare `private` member variables unique to your chosen instrument type (use the diagram above for inspiration, or add your own).
4. **Keep it Focused:** For this step, focus solely on the class structure, inheritance syntax, and member variables—we will tackle constructors, getters/setters, and `.cpp` implementations next.