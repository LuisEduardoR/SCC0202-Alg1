#include "fila.h"
#include "brinquedo.h"
#include <stdlib.h>

typedef struct no No;
struct no {

    No* prox;

    Pilha* item;

};

struct fila {

    int tam;
    No* ini;
    No* fim;

};

Fila* cria_fila() {

    Fila* fl = NULL;
    fl = (Fila*)malloc(sizeof(Fila));

    fl->tam = 0;
    fl->ini = NULL;
    fl->fim = NULL;

    return fl; 

}

int insere_na_fila(Fila* fl, Pilha* plh) {

    if(fl == NULL)
        return 1;
    
    // Cria um novo no.
    No* novo_no = NULL;
    novo_no = (No*)malloc(sizeof(No));

    if(novo_no == NULL)
        return 1;

    novo_no->prox = NULL;

    // Atuliza o proximo.
    if(fl->fim != NULL) {

        fl->fim->prox = novo_no;
        fl->fim = novo_no;
        
    } else {

        fl->ini = novo_no;
        fl->fim = novo_no;
    }
    
    novo_no->item = plh;

    fl->tam++;

    return 0;

}

Pilha* remove_fila(Fila* fl) {

    if(fl == NULL || fl->tam == 0 || fl->ini == NULL)
        return NULL;

    No* t_no;
    Pilha* plh = NULL;

    t_no = fl->ini;
    plh = t_no->item;

    fl->ini = t_no->prox;

    free(t_no);

    fl->tam--;

    return plh;

}

int vazia_fila(Fila* fl) {

    if(fl->tam == 0)
        return 1;
    
    return 0;

}

void deleta_fila(Fila* fl) {

    free(fl);

}