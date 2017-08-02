#ifndef _HASH
#define _HASH

#include <stdbool.h>
#include "constants.h"

typedef struct {
    int depth;
    int count;
    int keys[TAM_MAX_BUCKET];
} Bucket;

typedef struct {
    Bucket * values;
    int depth;
    int count;
} Directory;

bool op_find(int key, Bucket * foundBucket, Directory * directory);
bool op_add(int key, Directory * directory);
void bk_add_key(int key, Bucket * bucket, Directory * directory);
void bk_split(Bucket * bucket, Directory * directory);
void find_new_range(Bucket * oldBucket, int newStart, int newEnd, Directory * directory);
void dir_ins_bucket(Bucket * bucket, int start, int end, Directory * directory);
Bucket newBucket(void);
int hash(int key);
int makeAddress(int key, int depth);

#endif
