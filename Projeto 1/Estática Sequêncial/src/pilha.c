#include "pilha.h"
#include "brinquedo.h"
#include <stdlib.h>

struct pilha {

    int tam;
    Brinquedo* item[MAX_PLH_SIZE];

};

Pilha* cria_pilha() {

    Pilha* plh = NULL;
    plh = (Pilha*)malloc(sizeof(Pilha));

    plh->tam = 0;

    return plh; 

}

int push(Pilha* plh, Brinquedo* brinq) {

    if(plh == NULL || plh->tam + 1 > MAX_PLH_SIZE)
        return -1;

    plh->tam++;
    plh->item[plh->tam - 1] = brinq;

    return 0;

}

Brinquedo* top(Pilha* plh) {

    if(plh == NULL)
        return NULL;

    Brinquedo* brinq = NULL;

    if(plh->tam > 0) {
        
        brinq = plh->item[plh->tam - 1];

        plh->tam--;
        return brinq;

    }

    return brinq;

}

int vazia_pilha(Pilha* plh) {

    if(plh == NULL)
        return -1;

    if(plh->tam == 0)
        return 1;
    
    return 0;

}

int cheia_pilha(Pilha* plh) {

    if(plh == NULL)
        return -1;

    if(plh->tam == MAX_PLH_SIZE)
        return 1;
    
    return 0;

}

int tamanho_pilha(Pilha* plh) {

    if(plh == NULL)
        return -1;

    return plh->tam;

}

void deleta_pilha(Pilha* plh) {

    free(plh);

}
