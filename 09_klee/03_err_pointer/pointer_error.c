#include <stdio.h>

int main(int argc, char **argv) {
    char s[] = "PozdravStudenti!";
    int p1, p2, p3;
    char *p;

    scanf("%d %d %d", &p1, &p2, &p3);

    p = s;

    if (p1) {
        p += 1;
    } else {
        p += 2;
    }
    if (p2) {
        p += 6;
    } else {
        p += 7;
    }
    if (p3) {
        p += 8;
    } else {
        p += 9;
    }

    printf("%c ", *p);
}
