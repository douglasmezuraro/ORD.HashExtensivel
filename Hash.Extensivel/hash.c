#include "hash.h"

int hash(int key) {
    return key; // TODO: Se necessário fazer a função de espalhamento
}

int makeAddress(int key, int depth) {
    int retVal  = 0,
        mask    = 1,
        hashVal = hash(key),
        lowBit  = 0;

    for(int i = 1; i <= depth; i++) {
        retVal  = retVal<<1;
        lowBit  = hashVal&mask;
        retVal  = retVal|lowBit;
        hashVal = hashVal>>1;
    }

    return retVal;
}
