#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[8];
    int is_admin;
    int balance;
} Account;

static void copy_name(Account *account, const char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        account->name[i] = input[i];
    }
}

static void print_account(const Account *account) {
    printf("name=%s admin=%d balance=%d\n", account->name, account->is_admin,
           account->balance);
}

int main(int argc, char **argv) {
    const char *name = argc > 1 ? argv[1] : "petar";
    Account account = {.name = "", .is_admin = 0, .balance = 100};

    copy_name(&account, name);
    print_account(&account);

    if (account.is_admin) {
        puts("administrative path enabled");
    }

    return 0;
}
