#include <cstdlib>
#include <iostream>

using namespace std;

void junk_data();
int main();

int main()
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

void junk_data()
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
