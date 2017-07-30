#include <stdio.h>
#include <stdbool.h>
#include "file.utils.h"

bool endOfFile(FILE * file) {
    char aux;
    if((aux = fgetc(file)) == EOF)
        return true;
    else {
        fseek(file, -1l, SEEK_CUR);
        return false;
    }
}

long getKey(FILE * file) {
    char text[100] = "";
    int i = 0;

    if(!endOfFile(file)) {
        do {
            text[i] = fgetc(file);
            i++;
        } while(text[i - 1] != '\n');
    }

    text[i] = '\0';

    return atol(text);
}
