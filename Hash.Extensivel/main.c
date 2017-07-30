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
        op_add(key, dir);
    }
    return true;
}

void inicialization(int key) {
    if(dir.values == NULL) {
        dir.deepth = 0;
        dir.count = 0;
    }
    else
        dir.deepth = pow(2, dir.count);

    dir.values = (DirCell)malloc(sizeof(DirCell));
    DirCell dirCell = (Bucket *)malloc(sizeof(Bucket));
    dir.values[dir.count] = dirCell;
    dir.count++;
}

void finalization(void) {

}

int main(void) {
    readFile();
    exit(EXIT_SUCCESS);
}
