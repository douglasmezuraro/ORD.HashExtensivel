#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "constants.h"
#include "hash.h"

Directory dir;

void readFile(void) {
    FILE * file = fopen(FILE_NAME, "r");

    while(!feof(file)) {
        int key = getKey(file);
        inicialization(key);
        op_add(key, &dir);
    }

    fclose(file);
}

void inicialization(int key) {
    int address = makeAddress(key, BUCKET_DEPTH);
    pBucket d = (pBucket)malloc(sizeof(pBucket));
    *d = newBucket();
    if(dir.values == NULL) {
        dir.depth = 0;
        dir.values = (pBucket)malloc(sizeof(Bucket));
    }
    else {
        dir.depth = (int)log2(dir.count);
        dir.values = (pBucket)realloc(dir.values, dir.depth * (sizeof(pBucket)));
    }
    dir.values[address] = d;
    dir.count++;


   // dir.values[address] = * newBucket();
}

void finalization(void) {

}

void printHeader(void) {
    puts("************************************************* ");
    puts("* Projeto    : Hash Extensivel                    ");
    puts("* Data       : 03/08/2017                         ");
    puts("* Autores    : Douglas Mezuraro RA95676           ");
    puts("*              Gustavo Leite Scalabrini RA89869   ");
    puts("* Disciplina : Organizacao e Recuperacao de Dados ");
    puts("* Professora : Valeria D. Feltrim                 ");
    puts("************************************************* ");
}

int main(void) {
    printHeader();
    readFile();
    exit(EXIT_SUCCESS);
}
