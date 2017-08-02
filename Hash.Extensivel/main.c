#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "constants.h"
#include "hash.h"

Directory dir;

void readFile(void) {
    FILE * file = fopen(FILE_NAME, "r");

    inicialization();
    while(!feof(file)) {
        int key = getKey(file);
        op_add(key, &dir);
    }

    fclose(file);
}

void inicialization() {
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
