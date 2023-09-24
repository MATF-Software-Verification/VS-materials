#include <stdio.h>
#include <string.h>

void grant_privilege() {
    char password[16];
    char ok[16] = "no";

    printf("\n Enter the password : \n");
    scanf("%s", password);

    if (strcmp(password, "MyPassword")) {
        printf("\n Wrong Password \n");
    } else {
        printf("\n Correct Password \n");
        strcpy(ok, "yes");
    }

    if (strcmp(ok, "yes") == 0) {
        /*
         * Give root or admin rights to user
         */
        printf("\n Root privileges given to the user \n\n");
    }
}

char *read_username() {
    char username[10];

    printf(" Enter username: \n");
    scanf("%s", username);
    return username;
}

int main(void) {
    // char *username = read_username();
    // printf("%s\n",username);

    grant_privilege();

    return 0;
}
