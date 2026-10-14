/// @file 20261014_Lecture22_main.cpp
/// @author Adam T Koehler, PhD
/// @date October 14, 2026
/// @brief Code and lecture notes from the live lecture.
///     Compile with g++ XXX_main.cpp

#include <iostream>

using namespace std;


/// @brief Count the quantity of characters that exist in provided C-string
/// @param cArr C-string to start counting from
/// @return the quantity of characters counted
int countC(const char str[])
{
    int sum = 0;
    int index = 0;

    sum = 0;
    while(str[index] != '\0')
    {
        sum++;
        index++;
    }

    return sum;

    // alternate implementations
    // sum = 0;
    // for(index=0; str[index] != '\0'; index++)
    // { 
    //     sum++;
    // }

    // index = 0;
    // while(str[index] != '\0')
    // {
    //     index++;
    // }
    // return index;

    // index = 0;
    // while(str[index++] != '\0');
    // return index;

    return sum;
}



/// @brief Count the quantity of characters that exist in provided C-string
///     Use pointer parameter for this version but still square brackets.
/// @param cPtr pointer to address in a C-string to start counting from
/// @return the quantity of characters counted
int countC_PtrParam0(const char *str)
{
    int sum = 0;
    int index = 0;

    sum = 0;
    while(str[index] != '\0')
    {
        sum++;
        index++;
    }

    return sum;
}

/// @brief Count the quantity of characters that exist in provided C-string
///     Use pointer dereferencing and pointer parameter for this version
/// @param cPtr pointer to address in a C-string to start counting from
/// @return the quantity of characters counted
int countC_PtrParam1(const char *str)
{
    int sum = 0;
    int index = 0;

    sum = 0;
    while(*(str + index) != '\0')
    {
        sum++;
        index++;
    }

    return sum;
}

/// @brief Count the quantity of characters that exist in provided C-string
///     Use pointer dereferencing and pointer parameter for this version.
///     Still use a counter to track the quantity of characters.
/// @param cPtr pointer to address in a C-string to start counting from
/// @return the quantity of characters counted
int countC_PtrParam2(const char *str)
{
    const char *current = str;
    int sum = 0;
    for(; *current != '\0'; ++sum, ++current);

    // The above code can be expanded and written into a while
    // loop that looks like:
    // while(*current != '\0')
    // {
    //     sum++;
    //     current++;
    // }

    return sum;
}


/// @brief Count the quantity of characters that exist in provided C-string
///     Use pointer dereferencing and pointer parameter for this version
///     Also use pointer math, not a counter, to calculate the difference
///     in memory addresses to calculate the quantity of characters.
/// @param cPtr pointer to address in a C-string to start counting from
/// @return the quantity of characters counted
int countC_PtrParam3(const char *start)
{
    const char *stop = start;

    // *loopVar - we get the character at that memory address
    while(*stop != '\0')
    {
        stop++; 
        // move 1 sizeof() type of pointer further in memory    
    }


    // int length = (stop - start) / sizeof(char);
    // length = (stop - start) / 1

    return stop - start;
}


void Example1()
{
    char a[6] = "hello";
    char b[81] = "hello world";
    char c[81] = "hello my name is";
    char d[81] = "hello\nworld";

    // Note the counts are the quantity of characters NOT the array sizes
    cout << "Array Version" << endl;
    cout << "=============" << endl;
    cout << countC(a) << " characters exist in: " << endl << a << endl;
    cout << endl;
    cout << countC(b) << " characters exist in: " << endl << b << endl;
    cout << endl;

    cout << "Pointer Version 0" << endl;
    cout << "=================" << endl;
    cout << countC_PtrParam0(c) << " characters exist in: " << endl << c << endl;
    cout << endl;

    cout << "Pointer Version 1" << endl;
    cout << "=================" << endl;
    cout << countC_PtrParam1(c) << " characters exist in: " << endl << c << endl;
    cout << endl;

    cout << "Pointer Version 2" << endl;
    cout << "=================" << endl;
    cout << countC_PtrParam2(c) << " characters exist in: " << endl << c << endl;
    cout << endl;

    cout << "Pointer Version 3" << endl;
    cout << "=================" << endl;
    cout << countC_PtrParam3(c) << " characters exist in: " << endl << c << endl;
    cout << endl;
    cout << countC_PtrParam3(d) << " characters exist in: " << endl << d << endl;
}




int main(int argc, char *argv[])
{
    // no second command line argument, run all examples
    if (argc > 1 && isdigit(argv[1][0]))
    {
        switch (atoi(argv[1]))
        {
            case 1:
                Example1();
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
