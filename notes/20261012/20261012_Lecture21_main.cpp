/// @file 20261012_Lecture21_main.cpp
/// @author Adam T Koehler, PhD
/// @date October 12, 2026
/// @brief Code and lecture notes from the live lecture.
///     Compile with g++ XXX_main.cpp

#include <iostream>

using namespace std;


/// @brief Concatenate the src C-string on to the dest C-string
/// @param dest The destination C-string to append the src on to.
/// @param src The src C-string value to copy into the destination.
/// @pre Destination C-String has enough space in it to first Source.
void cStrCat(char dest[], const char src[])
{
    // Find the spot to start the copy.
    uint start = 0; // start = strlen(dest);
    while (dest[start] != '\0')
    {
        start++;
    }

    // Copy over every character until null character.
    uint loc = 0;
    while(src[loc] != '\0')
    {
        dest[start+loc] = src[loc];
        loc++;
    }

    // Properly terminate our updated C-string.
    dest[start+loc] = '\0';
}

void Example1()
{
    // Using literal values to instantiate a C-String
    char one[] = "hello";
    char two[80] = "world";

    // Instantiate a character array based on a C-String
    char three[10];
    for(int i = 0; one[i] != '\0'; i++)
    {
        three[i] = one[i];
    }
    
    // After the loop array three has...
    // 'h' 'e' 'l' 'l' 'o' ... garbage/unknown
    cout << "Value in array three:" << endl;
    cout << three << endl;

    cout << endl;
    cout << "Notice any issues?" << endl << endl;

    three[2] = '\0';
    // After null assignment, array three has...
    // 'h' 'e' '\0' 'l' 'o' ... garbage/unknown
    cout << "Value after \\0 insertion at index 2:" << endl;
    cout << three << endl;

    cout << endl << endl;

    // Attempt to concatenate C-string one and C-string two
    // on to C-string two (in string terms this is two+one)
    cout << "Combining " << two << " and " << one << endl;
    cout << "Before: " << two << endl;
    cStrCat(two, one);
    cout << "After:  " << two << endl;
    cout << endl << endl;

    // Now also place C-string three on to C-string two
    // (in string terms this is two+three)
    cout << "Combining " << two << " and " << three << endl;
    cout << "Before: " << two << endl;
    cStrCat(two, three);
    cout << "After:  " << two << endl;
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
