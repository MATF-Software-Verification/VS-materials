#include <cstdlib>
#include <iostream>

using namespace std;

void junk_data();
int main();

//****************************************************************************80

int main()
//****************************************************************************80
//
//  Purpose:
//
//    MAIN is the main program for TEST01.
//
//  Discussion:
//
//    TEST02 has some uninitialized data.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    19 May 2011
//
{
    cout << "\n";
    cout << "TEST02:\n";
    cout << "  C++ version\n";
    cout << "  A sample code for analysis by VALGRIND.\n";

    junk_data();
    //
    //  Terminate.
    //
    cout << "\n";
    cout << "TEST02\n";
    cout << "  Normal end of execution.\n";

    return 0;
}

//****************************************************************************80

void junk_data()
//****************************************************************************80
//
//  Purpose:
//
//    JUNK_DATA has some uninitialized variables.
//
//  Discussion:
//
//    VALGRIND's MEMCHECK program monitors uninitialized variables, but does
//    not complain unless such a variable is used in a way that means its
//    value affects the program's results, that is, the value is printed,
//    or computed with.  Simply copying the unitialized data to another
//    variable is of no concern.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    18 May 2011
//
{
    int i;
    int *x;

    x = new int[10];

    for (i = 0; i < 5; i++) {
        x[i] = i;
    }

    x[2] = x[7];
    x[5] = x[6];

    for (i = 0; i < 10; i++) {
        x[i] = 2 * x[i];
    }

    for (i = 0; i < 10; i++) {
        cout << "  " << i << "  " << x[i] << "\n";
    }

    delete[] x;

    return;
}
