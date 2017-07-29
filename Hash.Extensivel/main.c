#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bucket.h"
#include "constants.h"

bool readFile(void) {
    FILE * file = fopen(FILE_NAME, "r");


    return true;
}

void main(void) {
    if(readFile())
        exit(EXIT_SUCCESS);
    else
        exit(EXIT_FAILURE);
}
