# C++ Smart Pointers: Cyclic Dependencies and `weak_ptr`

While `shared_ptr` provides a robust way to manage shared ownership of dynamically allocated memory, it comes with a significant pitfall: **cyclic dependencies**. This section explains how cycles cause memory leaks and how to resolve them using `weak_ptr`.

## The Problem: Cyclic Dependencies

A cyclic dependency occurs when two or more objects managed by `shared_ptr` hold `shared_ptr` references to each other. 

Because a `shared_ptr` destroys its managed object only when its reference count drops to zero, a cycle creates a situation where the reference counts will never reach zero, even when the objects go out of scope. This results in a **memory leak**.

### Example: A Memory Leak

Consider a data structure with `Node` objects that point to each other:

```cpp
#include <iostream>
#include <memory>

class Node 
{
    public:
        shared_ptr<Node> neighbor;
        
        Node() { cout << "Node created\n"; }
        ~Node() { cout << "Node destroyed\n"; } // This won't get called!
};

int main() 
{
    {
        auto nodeA = make_shared<Node>();
        auto nodeB = make_shared<Node>();
        
        // Creating the cycle
        nodeA->neighbor = nodeB;
        nodeB->neighbor = nodeA;
        
        cout << "nodeA use count: " << nodeA.use_count() << "\n"; // Outputs 2
        cout << "nodeB use count: " << nodeB.use_count() << "\n"; // Outputs 2
    } // nodeA and nodeB go out of scope, but reference counts only drop to 1.
    
    cout << "End of scope.\n"; 
    // "Node destroyed" is never printed. Memory is leaked.
    return 0;
}
```

## The Solution: `weak_ptr`

To break a reference cycle, C++ provides `weak_ptr`. 

A `weak_ptr` is a smart pointer that holds a non-owning ("weak") reference to an object that is managed by `shared_ptr`. Crucially, **assigning a `shared_ptr` to a `weak_ptr` does not increment the reference count** of the managed object.

### Breaking the Cycle

If we change one of our pointers to a `weak_ptr`, the cycle is broken. The `shared_ptr` reference count will correctly drop to zero when the objects go out of scope.

```cpp
#include <iostream>
#include <memory>

class Node 
{
    public:
        // One strong reference, one weak reference prevents the cycle
        weak_ptr<Node> neighbor; 
        
        Node() { cout << "Node created\n"; }
        ~Node() { cout << "Node destroyed\n"; } // This WILL get called now!
};

int main() 
{
    {
        auto nodeA = make_shared<Node>();
        auto nodeB = make_shared<Node>();
        
        nodeA->neighbor = nodeB; // nodeB's use_count is still 1
        nodeB->neighbor = nodeA; // nodeA's use_count is still 1
        
        cout << "nodeB use count: " << nodeB.use_count() << "\n"; // Outputs 1
    } // Both nodes go out of scope. Reference counts hit 0. 
    
    cout << "End of scope.\n";
    // "Node destroyed" prints twice.
    return 0;
}
```

### Accessing a Weak Pointer with `lock()`

Because a `weak_ptr` does not own the object, the object might be destroyed while the `weak_ptr` is still pointing to it; creating a dangling pointer. This means we cannot directly access the memory address stored by a `weak_ptr`.

To safely access the object, you cannot dereference a `weak_ptr` directly. You must first convert it into a `shared_ptr` using the `lock()` method. 

*   If the object still exists, `lock()` returns a valid `shared_ptr` (temporarily increasing the reference count).
*   If the object has been destroyed, `lock()` returns an empty `shared_ptr`.

```cpp
#include <iostream>
#include <memory>

using namespace std;

struct Node 
{
    int value;
    ~Node() { cout << "Node destroyed!\n"; }
};


int main() 
{
    weak_ptr<Node> weakNode;

    // Using curly braces here to create a forced scope where the shared
    // pointer is automatically destroyed.
    {
        shared_ptr<Node> sharedNode = make_shared<Node>();
        sharedNode->value = 42;
        weakNode = sharedNode; // weak_ptr observes, but does not own

        // 1. Call lock() to attempt to get a strong shared_ptr
        shared_ptr<Node> tempShared = weakNode.lock();

        // 2. Explicitly check if the returned pointer is valid
        if (tempShared != nullptr) 
        {
            cout << "Node is alive. Value: " << tempShared->value << "\n";
        } 
        else 
        {
            cout << "Node has been destroyed.\n";
        }
    
        // Same as above with condense C++ that causes the pointer to 
        //  immediately go out of scope after branch
        // if (shared_ptr<Node> sharedNeighbor = nodeA->neighbor.lock())
        // {
        //     cout << "Alive. Value: " << sharedNeighbor->value << "\n";
        // } 


    } // sharedNode goes out of scope here. The Node is destroyed.

    cout << "Trying to access Node after it goes out of scope...\n";

    // 1. Call lock() again
    shared_ptr<Node> anotherTemp = weakNode.lock();

    // 2. Check validity again
    if (anotherTemp != nullptr) 
    {
        cout << "Node is alive.\n";
    } 
    else 
    {
        cout << "Node has been destroyed.\n";
    }

    return 0;
}
```