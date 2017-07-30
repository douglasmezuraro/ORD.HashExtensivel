#include "hash.h"

int hash(int key) {
    return key; // TODO: Se necessário fazer a função de espalhamento
}

int makeAddress(int key, int depth) {
    int retValue = 0,
        mask     = 1,
        value    = hash(key),
        lowBit   = 0;

    for(int i = 1; i <= depth; i++) {
        retValue = retValue<<1;
        lowBit   = value&mask;
        retValue = retValue|lowBit;
        value    = value>>1;
    }

    return retValue;
}
