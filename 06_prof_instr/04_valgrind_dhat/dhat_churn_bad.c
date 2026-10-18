#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { RECORDS = 5000, PASSES = 20, WIDTH = 64 };

static char *make_record(int id, int pass) {
    char buffer[WIDTH];
    int written =
        snprintf(buffer, sizeof(buffer), "student:%05d:pass:%02d:verification",
                 id, pass);
    if (written < 0) {
        exit(2);
    }

    char *record = malloc((size_t)written + 1);
    if (record == NULL) {
        exit(1);
    }

    memcpy(record, buffer, (size_t)written + 1);
    return record;
}

int main(void) {
    unsigned long checksum = 0;

    for (int pass = 0; pass < PASSES; pass++) {
        char **records = calloc(RECORDS, sizeof(*records));
        if (records == NULL) {
            return 1;
        }

        for (int i = 0; i < RECORDS; i++) {
            records[i] = make_record(i, pass);
            checksum += (unsigned char)records[i][0];
            checksum += (unsigned char)records[i][(i + pass) % 16];
        }

        for (int i = 0; i < RECORDS; i++) {
            free(records[i]);
        }
        free(records);
    }

    printf("checksum=%lu\n", checksum);
    return 0;
}
