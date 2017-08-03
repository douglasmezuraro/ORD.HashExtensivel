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
int dir_get_current_size(void);
unsigned int gen_id(void);
// Uteis para printar
void printDirectory(void);
void printBuckets(void);
void initializeArray(int * array, int size);
bool isPrinted(int id, int * array, int max);

#endif
