#include "hash.h"

int hash(int key) {
    return key; // TODO: Se necessário fazer a função de espalhamento
}

int makeAddress(int key, int depth) {
    int i,
        retVal  = 0,
        mask    = 1,
        hashVal = hash(key),
        lowBit  = 0;

    for(i = 1; i <= depth; i++) {
        retVal  = retVal<<1;
        lowBit  = hashVal&mask;
        retVal  = retVal|lowBit;
        hashVal = hashVal>>1;
    }

    return retVal;
}

bool op_find(int key, Bucket * foundBucket, Directory * directory) {
    int i, address = makeAddress(key, BUCKET_DEPTH);

    * foundBucket = directory->values[address];

    for(i = 0; i < foundBucket->count; i++)
        if(foundBucket->keys[i] == key)
            return true;

    return false;
}

bool op_add(int key, Directory * directory) {
    Bucket * bucket = (Bucket *)malloc(sizeof(Bucket));

    if(op_find(key, bucket, directory))
        return false;
    else {
        bk_add_key(key, bucket, directory);
        return true;
    }
}

void bk_add_key(int key, Bucket * bucket, Directory * directory) {
    if(bucket->count < TAM_MAX_BUCKET) {
        bucket->keys[bucket->count] = key;
        bucket->count++;
    }
    else {
        bk_split(bucket, directory);
        op_add(key, directory);
    }
}

void bk_split(Bucket * bucket, Directory * directory) {
    if(bucket->depth == directory->globalDeepth) {
        Bucket newBucket;
        int newStart, newEnd;

        find_new_range(bucket, newStart, newEnd, directory);
        dir_ins_bucket(&newBucket, newStart, newEnd, directory);

        bucket->depth++;
        newBucket.depth = bucket->depth;
    }
}

void find_new_range(Bucket * oldBucket, int newStart, int newEnd, Directory * directory) {
    int i,
        mask,
        sharedAddress,
        newShared,
        bitsToFill;

    mask          = 1;
    sharedAddress = makeAddress(oldBucket->keys[0], oldBucket->depth);
    newShared     = sharedAddress<1;
    newShared     = newShared|mask;
    bitsToFill    = directory->globalDeepth - (oldBucket->depth + 1);
    newStart      = newEnd = newShared;

    for(i = 1; i <= bitsToFill; i++) {
        newStart = newStart<1;
        newEnd   = newEnd<1;
        newEnd   = newEnd|mask;
    }
}

void dir_ins_bucket(Bucket * bucket, int start, int end, Directory * directory) {
    int i;
    for(i = start; i <= end; i++)
        directory->values[i] = * bucket;
}

Bucket newBucket(void) {
    int i;
    Bucket b;

    b.count = 0;
    b.depth = 0;

    for(i = 0; i < TAM_MAX_BUCKET; i++)
        b.keys[i] = 0;
}
