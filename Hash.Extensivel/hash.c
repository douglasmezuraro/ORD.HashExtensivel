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
    int retVal  = 0,
        mask    = 1,
        hashVal = hash(key),
        lowBit  = 0;

    int i;
    for(i = 1; i <= depth; i++) {
        retVal  = retVal << 1;
        lowBit  = hashVal & mask;
        retVal  = retVal | lowBit;
        hashVal = hashVal >> 1;
    }

    return retVal;
}

bool op_find(int key, Bucket ** bucket) {
    int address = makeAddress(key, dir.depth);

    * bucket = dir.values[address].ref;

    if(* bucket != NULL) {
        int i;
        for(i = 0; i < (* bucket)->count; i++)
            if((* bucket)->keys[i] == key)
                return true;
    }

    return false;
}

bool op_add(int key) {
    Bucket * bucket = NULL;

    if(op_find(key, &bucket))
        return false;

    bk_add_key(key, bucket);
    return true;
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
    if(bucket->depth == dir.depth) // ta cheio, precisa aumentar o diretorio
        dir_double(); // método que dobra o tamanho do diretorio

    Bucket * newBucket;
    newBucket = (Bucket *)malloc(sizeof(Bucket));
    newBucket->count = 0;

    int newStart = 0,
          newEnd = 0;

    find_new_range(bucket, &newStart, &newEnd);
    dir_ins_bucket(newBucket, newStart, newEnd);

    bucket->depth++;

    newBucket->depth = bucket->depth;

    int buffer[TAM_MAX_BUCKET];
    int i, address;

    for(i = 0; i < TAM_MAX_BUCKET; i++){
        buffer[i] = bucket->keys[i];
        bucket->keys[i] = 0;
        bucket->count--;
    }

    for(i = 0; i < TAM_MAX_BUCKET; i++){
        address = makeAddress(buffer[i], dir.depth);

        if((address >= newStart) && (address <= newEnd))
            bk_add_key(buffer[i], newBucket);
        else
            bk_add_key(buffer[i], bucket);
    }
}

void find_new_range(Bucket * old, int * newStart, int * newEnd) {

    // NOTA: os parâmetros "newStart" e "newEnd" são parâmetros de saída,
    // por isso precisam ser ponteitos

    int mask,
        sharedAddress,
        newShared,
        bitsToFill;

    mask          = 1;
    sharedAddress = makeAddress(old->keys[1], old->depth);
    newShared     = sharedAddress << 1;
    newShared     = newShared | mask;
    bitsToFill    = dir.depth - (old->depth + 1);
    * newStart    = (* newEnd) = newShared;

    int i;
    for(i = 0; i < bitsToFill; i++) {
        * newStart = (* newStart) << 1;
        * newEnd   = (* newEnd) << 1;
        * newEnd   = (* newEnd) | mask;
    }
}

void dir_ins_bucket(Bucket * bucket, int start, int end) {
    int i;
    for(i = start; i <= end; i++)
        dir.values[i].ref = bucket;
}

void dir_double(void) {
    int currentSize = pow(2, dir.depth); // fórmula vista na pag. 24 da aula 11.1
    int newSize = currentSize * 2; // dobro do tamanho antigo

    Directory temp;

    temp.values = (DirCell *)malloc(newSize * sizeof(DirCell));

    int i;
    for(i = 0; i < currentSize - 1; i++) {
        temp.values[2 * i].ref = dir.values[i].ref;
        temp.values[2 * i + 1].ref = dir.values[i].ref;
    }

    free(dir.values);

    dir.values = temp.values;

    dir.depth++;
}
