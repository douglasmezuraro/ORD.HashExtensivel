#ifndef _HASH
#define _HASH

#include <stdbool.h>
#include "constants.h"

typedef struct {
    unsigned int id;
    unsigned int depth;
    unsigned int count;
    unsigned keys[TAM_MAX_BUCKET];
} Bucket;

typedef struct {
    Bucket * ref;
} DirCell;

typedef struct {
    DirCell * values;
    unsigned int depth;
    unsigned int count;
} Directory;

// Hash
int hash(int key);
int makeAddress(int key, int depth);
// Diretório
void dir_initialize(void);
void dir_finalize(void);
void dir_ins_bucket(Bucket * bucket, int start, int end);
void dir_double(void);
void dir_redistribute_keys(Bucket * oldBucket, Bucket * newBucket, int newStart, int newEnd);
// Buckets
void bk_add_key(int key, Bucket * bucket);
void bk_split(Bucket * bucket);
// Uteis
bool op_find(int key, Bucket ** foundBucket);
bool op_add(int key);
void find_new_range(Bucket * old, int * newStart, int * newEnd);
unsigned int gen_id(void);

#endif
