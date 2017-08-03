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
    Bucket * ref;
} DirCell;

typedef struct {
    DirCell * values;
    int depth;
    int count;
} Directory;

// Hash
int hash(int key);
int makeAddress(int key, int depth);
// Diretório
void inicialization(void);
void finalization(void);
// Buckets
bool op_find(int key, Bucket ** foundBucket);
bool op_add(int key);
void bk_add_key(int key, Bucket * bucket);
void bk_split(Bucket * bucket);
void find_new_range(Bucket * old, int * newStart, int * newEnd);
void dir_ins_bucket(Bucket * bucket, int start, int end);
void dir_double(void);

#endif
