#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "file.utils.h"
#include "constants.h"

bool isEOF(FILE * file) {
    char aux;
    if((aux = fgetc(file)) == EOF)
        return true;
    else {
        fseek(file, -1l, SEEK_CUR);
        return false;
    }
}

int getKeyFromFile(FILE * file) {
    char buffer[KEY_LENGTH] = EMPTY_STRING;

    if(!isEOF(file)) {
        char aux;
        int i = 0;
        do {
            buffer[i] = fgetc(file);
            aux = buffer[i];
            i++;
        } while((aux != LINE_BREAK_CHAR) && (aux != EOF));
    }

    // finaliza a string para evitar lixo no final
    buffer[strlen(buffer)] = END_OF_STRING;

    // converte a string para int
    return atoi(buffer);
}
