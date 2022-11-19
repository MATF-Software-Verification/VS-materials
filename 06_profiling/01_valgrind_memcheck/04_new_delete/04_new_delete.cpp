#include <cstdlib>
#include <string>

using namespace std;

int main() {
    string *s = new string[5];

    free(s);
    return 0;
}
