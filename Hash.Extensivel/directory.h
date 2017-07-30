#ifndef _DIRECTORY
#define _DIRECTORY

#include <stdbool.h>
#include "bucket.h"

typedef struct {
    int depth;
    int count;
    int keys[TAM_MAX_BUCKET];
} Bucket;

typedef Bucket * DirCell;

typedef struct {
    DirCell values[100];
    int deepth;
    int count;
} Directory;

// directory
bool op_find(int key, Bucket * foundBucket, Directory * directory);
bool op_add(int key, Directory * directory);
// bucket
void bk_add_key(int key, Bucket * bucket, Directory * directory);
void bk_split(Bucket * bucket, Directory * directory);
void find_new_range(Bucket * oldBucket, int newStart, int newEnd, Directory * directory);
void dir_ins_bucket(Bucket * bucket, int start, int end, Directory * directory);
Bucket newBucket(void);

#endif
