#include "hash.h"
#include <stdlib.h>

Directory dir;

void inicialization(void) {
    dir.count = 0;
    dir.depth = 0;
    dir.values = (DirCell *)malloc(sizeof(Bucket));

    // TODO: Criar método que aloca função e inicializa os valores
    dir.values[0].ref = (Bucket *)malloc(sizeof(Bucket));
    dir.values[0].ref->count = 0;
    dir.values[0].ref->depth = 0;

    int i = 0;
    for(i; i < TAM_MAX_BUCKET; i++)
        dir.values[0].ref->keys[i] = 0;
}

void finalization(void) {
    // TODO : Implementar
}

int hash(int key) {
    return key; // TODO : Se necessário fazer a função de espalhamento
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

bool op_find(int key, Bucket ** bucket) {
    int address = makeAddress(key, dir.depth);

    (* bucket) = dir.values[address].ref;

    if(bucket != NULL) {
        int i;
        for(i = 0; i < (* bucket)->count; i++)
            if((* bucket)->keys[i] == key)
                return true;
    }

    return false;
}

bool op_add(int key) {
    Bucket * bucket;

    if(op_find(key, &bucket))
        return false;
    else {
      bk_add_key(key, bucket);
      return true;
    }
}

void bk_add_key(int key, Bucket * bucket) {
    if(bucket->count < TAM_MAX_BUCKET) {
        bucket->keys[bucket->count] = key;
        bucket->count++;
    }
    else {
        bk_split(bucket);
        op_add(key);
    }
}

void bk_split(Bucket * bucket) {
    if(bucket->depth == dir.depth) {
        Bucket * newBucket;
        int newStart, newEnd;

        find_new_range(bucket, newStart, newEnd);
        dir_ins_bucket(&newBucket, newStart, newEnd);

        bucket->depth++;
        newBucket->depth = bucket->depth;
    }
}

void find_new_range(Bucket * oldBucket, int newStart, int newEnd) {
    int i,
        mask,
        sharedAddress,
        newShared,
        bitsToFill;

    mask          = 1;
    sharedAddress = makeAddress(oldBucket->keys[0], oldBucket->depth);
    newShared     = sharedAddress<1;
    newShared     = newShared|mask;
    bitsToFill    = dir.depth - (oldBucket->depth + 1);
    newStart      = newEnd = newShared;

    for(i = 1; i <= bitsToFill; i++) {
        newStart = newStart<1;
        newEnd   = newEnd<1;
        newEnd   = newEnd|mask;
    }
}

void dir_ins_bucket(Bucket * bucket, int start, int end) {
    int i;
    for(i = start; i <= end; i++)
        dir.values[i].ref = bucket;
}

void dir_double(void) {

}
