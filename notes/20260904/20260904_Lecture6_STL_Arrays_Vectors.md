# C++ STL Arrays & Vectors

## Topics Covered
 1. Arrays & Vectors in C++ vs Other Languages
 2. Sampling of Vector Member Function Comparisons
 3. One Dimensional

    a. Standard Library Arrays

    b. Standard Library Vectors

 4. Iteration Over Arrays & Vectors
 
    a. for-each loop

    b. index based iteration

 5. Two Dimensions and Beyond
 6. C++ Legacy Vector Print - Pass by Const Reference
 7. C++20 Print Elements Function using Span
 8. C++23 Print Vector with println


<br>
<br>

## 1. Arrays & Vectors in C++ vs Other Languages
| C++ Type | Python Equivalent | Java Equivalent | When to use it |
| :--- | :--- | :--- | :--- |
| **C-Style Array** | *None (Too unsafe)* | Primitive Array `int[]` | Interacting with legacy C code |
| **`std::array`** | Tuple (fixed size) | Primitive Array `int[]` | Size is known and fixed forever |
| **`std::vector`** | List `[]` | `ArrayList` | Size can grow/shrink |

<br>
<br>

## 2. Sampling of Vector Member Function Comparisons
| Operation | C++ `std::vector` | Python `list` | Java `ArrayList` | What It Does / Notes |
| :--- | :--- | :--- | :--- | :--- |
| **Add to end** | `.push_back(val)` | `.append(val)` | `.add(val)` | The primary way to add new elements and grow the array dynamically. |
| **Get length** | `.size()` | `len(lst)` | `.size()` | Returns the current number of elements. |
| **Safe Access** | `.at(index)` | `lst[index]` | `.get(index)` | **Bounds-checked.** Throws an exception if the index is out of bounds. |
| **Fast Access** | `[index]` | *(No equivalent)* | *(No equivalent)*| **Unchecked.** Blindly accesses memory. Faster, but risks crashing or logic bugs. |
| **Check if empty**| `.empty()` | `not lst` | `.isEmpty()` | Returns a boolean. Preferred over checking if `size() == 0` for readability. |
| **Remove all** | `.clear()` | `.clear()` | `.clear()` | Empties the container so `size()` becomes `0`. |
| **Get first item**| `.front()` | `lst[0]` | `.get(0)` | Quick access to the first element. |
| **Get last item** | `.back()` | `lst[-1]` | `.get(lst.size()-1)`| Quick access to the last element. |
| **Remove last** | `.pop_back()` | `.pop()` | `.remove(lst.size()-1)` | **Warning:** In C++, this only removes the item; it does *not* return the removed value like Python does. |

<br>
<br>

## 3. One Dimension
### STL Arrays
To use the standard library arrays we need include the array library alongside any of include statements in our program. 
```cpp
#include <array>
```

Size is fixed at compile time.
```cpp
array<double, 4> values = {3.5, 4.0, 3.8, 3.2};
```

### STL Vectors
To use the standard library vectors require us to include the vector library alongside any of include statements in our program. 
```cpp
#include <vector>
```

Size can change at runtime. 

This means we could prefill values and grow to add more, or we could start with an empty vector and grow it from size 0.

#### Empty to Start
```cpp
vector<double> values;
```

#### Prefilled with Values
```cpp
vector<double> values = {3.5, 4.0, 3.8, 3.2};
```

<br>
<br>

## 4. Iteration Over Arrays & Vectors
### for-each loop 
Cleanest methodology. Iterates over every item in the container. Akin to Python 'for x in list:'

### for-each with value-copy
In the standard for-each loop a copy of the element is created and stored in the looping variable.

In the following example we ouput every score in our vector container followed by a space.
```cpp
vector<int> scores = {90, 85, 100};
for (int score : scores) 
{
    cout << score << " ";
}
```
<br>

### for-each with reference
Using a reference variable allows us to modify the contents of the vector since we now have direct access to the vector element and are not make a copy of that element.

In this example we modify all scores that are odd (not evenly divisible by 2) to have one more point.

```cpp
vector<int> scores = {90, 85, 100};
for (int &score : scores) 
{
    if (score % 2 == 1)
    {
        score = score + 1;
    }
}
```
After executing the loop that modifies our vector, the scores vector now contains the values of `90`, `86`, and `100`.

<br>

### Index-Based Iteration 
Use when you need the index number or do not want to iterate over every item.

In this example we ouput multiple lines, and on each line is the student number (index within the vector) and the student's score.
```cpp
vector<int> scores = {90, 85, 100};
for (size_t i = 0; i < scores.size(); ++i) 
{
    cout << "Student " << i << ": " << scores.at(i) << "\n"; 
}
```

We can also modify the contents of a vector using index-based iteration. 

In the following example we use an update step of `i+=2` to increase `i` by `2` every iteration and skip every other vector element. Then, in the loop body we set the current score's value to zero.

```cpp
vector<int> scores = {90, 85, 100};
for (size_t i = 0; i < scores.size(); i+=2) 
{
    scores.at(i) = 0; 
}
```

After executing the loop that modifies our vector, the scores vector now contains the values of `0`, `85`, and `0`.

<br>
<br>

## 5. Two Dimensions and Beyond
A vector of vectors is similar to a list of lists in Python. We can create a multi dimensional vector and then access using multiple chained `.at()` function calls.

In the following example we declare and initialize a multidimensional vector. The external vector's element data type is `vector<int>` so every element is its own vector. The internal vectors have elements that are integers. Based on our initialization, we will have 4 rows and 3 columns in a two-dimensional layout.

```cpp
vector<vector<int>> grid = 
{
    { 1,  2,  3},   // row 0
    { 4,  5,  6},   // row 1
    { 7,  8,  9},   // row 2
    {10, 11, 12}    // row 3
};
```

After our declaration and initialization, we can access the specific row-column combination with chained `at()` calls. Here we access row 1, col 2 and output the element value (6) using safe bounds-checking provided by the `at()` function.

```cpp
cout << grid.at(1).at(2) << "\n";
```

<br>
<br>

## 6. C++ Legacy Vector Print - Pass by Const Reference
In legacy C++, the common idiom was to define parameters as pass by constant reference. This methodology allows the memory address of the container to be passed instead of creating an entire duplicate of the container when passing the container by value. We provide this const reference (`const &`) example as a reference to common code you will encounter because C++ was first released in 1985.

```cpp
#include <iostream>
#include <vector>

using namespace std;

void printVector(const vector<int> &vals)
{
    for (int num : vals)
    {
        cout << num << " ";
    }
    cout << "\n";
}

int main()
{
    vector<int> values = {7, 8, 9};
    
    printVector(values);

    return 0;
}
```


<br>
<br>

## 7. C++20 Print Elements Function using Span
In modern C++ we use the span object as a parameter, and this will accept multiple a vector, an array, or a C-style raw array as an argument. Let's explore an example with the three types of one-dimensional containers we have seen.

To utilize the span obect, we include the span library alongside our other library includes.
```cpp
#include <span>
```

The span object has constant and non-constant options. In our printElements example below we create a constant integer element type that will force the function to be a read-only or user of the container and disallow manipulation of the container.

```cpp
#include <iostream>
#include <array> 
#include <span>
#include <vector>

using namespace std;

void printElements(span<const int> view)
{
    for (int num : view)
    {
        cout << num << " ";
    }
    cout << "\n";
}

int main()
{
    // C++ STL Containers
    vector<int> values = {6, 7, 8, 9, 10, 11, 12};
    array<int, 5> vals = {5, 4, 3, 2, 1};

    // C-Style Array
    int arr[3] = {21, 22, 23};

    printElements(values);
    printElements(vals);
    printElements(arr);
    
    return 0;
}
```


<br>
<br>

## 8. C++23 Print Vector with println
In the C++23 version support for direct range printing was added. This allows printing of vectors directly without having to create a separate function.

To use the print and println functions added with C++23 we include the print library alongside the other libraries included within our program.

```cpp
#include <print>
```

Lets explore a full progam that is similar to the last one that utilized span to print out our vectors, but in this C++23 version we are using the builtin println function instead of the character output buffer (`cout`);

```cpp
#include <vector>
#include <print>

using namespace std;

int main()
{
    // C++ STL Containers
    vector<int> data = {6, 7, 8, 9};

    println("Data: {}", data);
    return 0
}
```

Using println the entire vector will be output in a comma separated list surrounded by square brackets. In the example above our program will output `[6, 7, 8, 9]`.