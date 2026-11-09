/// @file 20261109_Lecture32_main.cpp
/// @author Adam T Koehler, PhD
/// @date November 9, 2026
/// @brief Code and lecture notes from the live lecture.
///     Some items require C++23, compile with g++ -std=c++23 XXX_main.cpp

#include <iostream>

using namespace std;

void hanoi(int n, char src, char dest, char aux) 
{
    cout << "hanoi( " << n << ", '" << src << "', '" << dest << "', '" << aux 
        << "' )" << endl;

    if (n == 1) 
    {
        cout << "Move disk 1 : " << src << " -> " << dest << "\n";
        return;
    }

    hanoi(n - 1, src, aux, dest);

    cout << "Move disk " << n << " : " << src << " -> " << dest << "\n";

    hanoi(n - 1, aux, dest, src);
}

void Activity()
{
    hanoi(3, 'A', 'C', 'B');
}

int main(int argc, char *argv[])
{
    // no second command line argument, run all examples
    if (argc > 1 && isdigit(argv[1][0]))
    {
        switch (atoi(argv[1]))
        {
            case 1:
                Activity();
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