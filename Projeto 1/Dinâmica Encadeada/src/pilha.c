#include "pilha.h"
#include "brinquedo.h"
#include <stdlib.h>

typedef struct no No;
struct no {

    No* ant;

    Brinquedo* item;

};

struct pilha {

    int tam;
    No* topo;

};

Pilha* cria_pilha() {

    Pilha* plh = NULL;
    plh = (Pilha*)malloc(sizeof(Pilha));

    plh->tam = 0;
    plh->topo = NULL;

    return plh; 

}

int push(Pilha* plh, Brinquedo* brinq) {

    if(plh == NULL)
        return 1;
    
    // Cria um novo no.
    No* novo_no = NULL;
    novo_no = (No*)malloc(sizeof(No));

    if(novo_no == NULL)
        return 1;

    // Atuliza o proximo.
    if(plh->topo != NULL)
        novo_no->ant = plh->topo;
    else
        novo_no->ant = NULL;
    
    
    novo_no->item = brinq;

    // Atualiza o inico da fila.
    plh->topo = novo_no;

    plh->tam++;

    return 0;

}

Brinquedo* top(Pilha* plh) {

    if(plh == NULL || plh->tam == 0 || plh->topo == NULL)
        return NULL;

    No* t_no;
    Brinquedo* brinq = NULL;

    t_no = plh->topo;
    brinq = t_no->item;

    plh->topo = t_no->ant;

    free(t_no);

    plh->tam--;

    return brinq;

}

int vazia_pilha(Pilha* plh) {

    if(plh == NULL)
        return -1;

    if(plh->tam == 0)
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