#ifndef _BUCKET
#define _BUCKET

#include "constants.h"

typedef struct {
    int depth;
    int count;
    int keys[TAM_MAX_BUCKET];
} Bucket;

#endif
