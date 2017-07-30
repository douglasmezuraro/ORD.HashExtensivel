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

int getKey(FILE * file) {
    char text[100] = "";
    char aux;
    int i = 0;

    if(!endOfFile(file)) {
        do {
            text[i] = fgetc(file);
            aux = text[i];
            i++;
        } while((aux != '\n') && (aux != EOF));
    }

    text[i] = '\0';

    return atoi(text);
}
