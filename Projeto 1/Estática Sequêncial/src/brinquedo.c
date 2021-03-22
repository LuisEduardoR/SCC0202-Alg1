#include "brinquedo.h"

#include <stdlib.h>
#include <string.h>

struct brinquedo {

    int num;
    char nome[65];

};

Brinquedo* cria_brinquedo(int num, char* nome) {

    Brinquedo* brinq = NULL;

    brinq = (Brinquedo*)malloc(sizeof(Brinquedo));

    brinq->num = num;
    strcpy(brinq->nome, nome);

    return brinq;

}

int num_brinquedo (Brinquedo* brinq) {

    return brinq->num;
    
}

char* nome_brinquedo (Brinquedo* brinq) {

    return brinq->nome;

}

void deleta_brinquedo(Brinquedo* brinq) {

    free(brinq);

}