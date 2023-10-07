#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 0;
const int PWD_SIZE = 16;

#define dbg(fmt, args)                                                         \
    if (debug) {                                                               \
        printf("DEBUG: ");                                                     \
        printf(fmt, args);                                                     \
    }

int main() {
    char pwd[PWD_SIZE];
    int privileged = 0;
    char *sensitive_data = "xxxxxxxxxxxxxxx";

    char *secret = getenv("SECRET");
    if (secret == NULL) {
        secret = "ThisIsASecretPassword";
    }

    if (getenv("DEBUG") != NULL) {
        debug = 1;
    }

    dbg("Address of user input array:'\t%p\n", pwd);
    dbg("Address of password check var:\t%p\n", &privileged);
    dbg("Address of stored secret array:\t%p\n", secret);
    dbg("Current secret: %s\n", secret);

    printf("Input password:\n");
    scanf("%s", pwd);

    dbg("User entered: %s\n", pwd);
    dbg("Password check var value: %d\n", privileged);

    if (strcmp(pwd, secret) == 0) {
        printf("Correct password.\n");
        privileged = 1;
    } else {
        printf("Wrong password.\n");
    }

    if (privileged) {
        printf("Password check verification passed!\n");
        printf("Sensitive data: %s\n", sensitive_data);
        system("cat /etc/shadow");
    }

    return 0;
}
