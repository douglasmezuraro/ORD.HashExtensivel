#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bucket.h"
#include "constants.h"
#include "hash.h"

bool readFile(void) {
    FILE * file = fopen(FILE_NAME, "r");

    while(!feof(file)) {
        long key = getKey(file);

        printf("%i = %i\n", key, makeAddress(key, BUCKET_DEPTH));
    }
    return true;
}

void main(void) {
    readFile();
}
