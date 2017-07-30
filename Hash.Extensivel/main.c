#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "bucket.h"
#include "constants.h"
#include "hash.h"

Directory dir;

bool readFile(void) {
    FILE * file = fopen(FILE_NAME, "r");

    while(!feof(file)) {
        int key = getKey(file);
        inicialization(key);
        op_add(key, &dir);
    }
    return true;
}

void inicialization(int key) {
    if(dir.values == NULL) {
        dir.deepth = 0;
        dir.count = 0;
    }
    else dir.deepth = (int)log2(dir.count);

    int address = makeAddress(key, BUCKET_DEPTH);

    DirCell d = (Bucket *)malloc(sizeof(Bucket));
    *d = newBucket();

    //dir.values[address] = (DirCell *)malloc(sizeof(DirCell));
    dir.values[address] = d;
    dir.count++;
}

void finalization(void) {

}

int main(void) {
    readFile();
    exit(EXIT_SUCCESS);
}
