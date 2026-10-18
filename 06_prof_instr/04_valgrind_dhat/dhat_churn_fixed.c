#include <stdio.h>
#include <stdlib.h>

enum { RECORDS = 5000, PASSES = 20, WIDTH = 64 };

int main(void) {
    unsigned long checksum = 0;
    char(*records)[WIDTH] = malloc(RECORDS * sizeof(*records));
    if (records == NULL) {
        return 1;
    }

    for (int pass = 0; pass < PASSES; pass++) {
        for (int i = 0; i < RECORDS; i++) {
            int written =
                snprintf(records[i], WIDTH,
                         "student:%05d:pass:%02d:verification", i, pass);
            if (written < 0 || written >= WIDTH) {
                free(records);
                return 2;
            }

            checksum += (unsigned char)records[i][0];
            checksum += (unsigned char)records[i][(i + pass) % 16];
        }
    }

    free(records);
    printf("checksum=%lu\n", checksum);
    return 0;
}
