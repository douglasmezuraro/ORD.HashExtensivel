#include "hash.h"
#include <math.h>
#include <stdlib.h>

Directory dir;        // Diretório global
unsigned last_id;     // Gerador de ids global

void dir_initialize(void) {
    // Inicializa o gerador de ids
    last_id = 0;

    // Inicializa o diretório
    dir.depth = 0;
    dir.values = (DirCell *)malloc(sizeof(Bucket));

    // Inicializa o primeiro bucket
    // TODO: Criar método que aloca função e inicializa os valores
    dir.values[last_id].ref        = (Bucket *)malloc(sizeof(Bucket));
    dir.values[last_id].ref->count = 0;
    dir.values[last_id].ref->depth = 0;
    dir.values[last_id].ref->id    = gen_id();

    // Inicializa as chaves do primeiro bucket
    int i = 0;
    for(i; i < TAM_MAX_BUCKET; i++)
        dir.values[last_id - 1].ref->keys[i] = 0;
}

void dir_finalize(void) {
    printDirectory();
    printBuckets();
}

int hash(int key) {
    return key; // TODO : Se necessário fazer a função de espalhamento
}

int make_address(int key, int depth) {
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
    int address = make_address(key, dir.depth);

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

    Bucket * newBucket = (Bucket *)malloc(sizeof(Bucket));
    newBucket->count = 0;
    newBucket->id = gen_id();

    int newStart = 0, newEnd = 0;

    find_new_range(bucket, &newStart, &newEnd);
    dir_ins_bucket(newBucket, newStart, newEnd);

    bucket->depth++;
    newBucket->depth = bucket->depth;

    dir_redistribute_keys(bucket, newBucket, newStart, newEnd);
}

void find_new_range(Bucket * old, int * newStart, int * newEnd) {

    // NOTA: os parâmetros "newStart" e "newEnd" são parâmetros de saída,
    // por isso precisam ser ponteitos

    int mask          = 1,
        sharedAddress = 0,
        newShared     = 0,
        bitsToFill    = 0;

    sharedAddress = make_address(old->keys[1], old->depth);
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
    // pega o tamanho atual do diretorio igual na pagina 24 da aula 11.1
    int currentSize = dir_get_current_size();
    // dobra o tamanho do diretorio atual
    int newSize = 2 * currentSize;

    Directory temp;

    temp.values = (DirCell *)malloc(newSize * sizeof(DirCell));

    int i;
    for(i = 0; i <= currentSize - 1; i++) {
        temp.values[2 * i].ref = dir.values[i].ref;
        temp.values[2 * i + 1].ref = dir.values[i].ref;
    }

    // libera os values do diretório
    free(dir.values);

    // atribui do diretório temp ao diretório
    dir.values = temp.values;

    // aumenta a profundidade
    dir.depth++;
}

void dir_redistribute_keys(Bucket * oldBucket, Bucket * newBucket, int newStart, int newEnd) {
    int keys[TAM_MAX_BUCKET];
    int i;

    for(i = 0; i < TAM_MAX_BUCKET; i++){
        keys[i] = oldBucket->keys[i];
        oldBucket->keys[i] = 0;
    }

    oldBucket->count = 0;

    for(i = 0; i < TAM_MAX_BUCKET; i++){
        int address = make_address(keys[i], dir.depth);

        if((address >= newStart) && (address <= newEnd))
            bk_add_key(keys[i], newBucket);
        else
            bk_add_key(keys[i], oldBucket);
    }
}

unsigned int gen_id(void) {
    unsigned int result = last_id;
    last_id++;
    return result;
}

int dir_get_current_size(void) {
    return pow(2, dir.depth);
}

void printBuckets(void) {
    int currentSize = dir_get_current_size();

    int * array = (int *)malloc(currentSize * sizeof(int));
    initializeArray(array, currentSize);

    int i;
    for(i = 0; i < currentSize; i++) {
        if(!isPrinted(dir.values[i].ref->id, array, currentSize)) {
            printf("\n== Bucket %i ==\n", dir.values[i].ref->id);
            printf("#depth = %i\n", dir.values[i].ref->depth);
            printf("key[0] = %i\n", dir.values[i].ref->keys[0]);
            printf("key[1] = %i\n", dir.values[i].ref->keys[1]);

            array[i] = dir.values[i].ref->id;
        }
    }
}

void printDirectory(void) {
    int currentSize = dir_get_current_size();

    int i;
    for(i = 0; i < currentSize; i++)
        printf("dir[%i] = bucket #%i\n", i, dir.values[i].ref->id);

    printf("\nDirectory current size = %i", currentSize);
    printf("\nNumber of buckets = %i\n", last_id);
}

void initializeArray(int * array, int size) {
    int i;
    for(i = 0; i < size; i++)
        array[i] = -1;
}

bool isPrinted(int id, int * array, int max) {
    int i;

    for(i = 0; i < max; i++)
        if(array[i] == id)
            return true;

    return false;
}
