#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User {
    int id;
    char name[32];
    struct User *next;
} User;

static User *make_user(int id, const char *name, User *next) {
    User *user = malloc(sizeof(*user));
    if (user == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    user->id = id;
    snprintf(user->name, sizeof(user->name), "%s", name);
    user->next = next;
    return user;
}

static User *find_user(User *head, int id) {
    for (User *it = head; it != NULL; it = it->next) {
        if (it->id == id) {
            return it;
        }
    }

    return NULL;
}

static void print_badge(User *user) {
    printf("user #%d: %s\n", user->id, user->name);
}

int main(int argc, char **argv) {
    int wanted = 2;
    if (argc > 1) {
        wanted = atoi(argv[1]);
    }

    User *users = make_user(1, "ana", make_user(2, "marko", NULL));
    User *selected = find_user(users, wanted);

    print_badge(selected);

    free(users->next);
    free(users);
    return 0;
}
