#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "bucket.h"
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
    if(dir.values == NULL) {
        dir.globalDeepth = 0;
        dir.count  = 0;
    }
    else dir.globalDeepth = (int)log2(dir.count);

    int address = makeAddress(key, BUCKET_DEPTH);

    dir.values = (DirCell *)malloc(sizeof(DirCell));
    DirCell * cell = (DirCell *)malloc(sizeof(DirCell));
    * cell = newBucket();
    dir.values[address] = * cell;
    dir.count++;
}

void finalization(void) {

}

void printHeader(void) {
    puts("************************************************* ");
    puts("* Projeto    : Hash Extensivel                    ");
    puts("* Data       : 01/08/2017                         ");
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
