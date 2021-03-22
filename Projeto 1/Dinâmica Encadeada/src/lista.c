#include "lista.h"
#include "brinquedo.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct no No;
struct no {

    No* prox;
    No* ant;

    Brinquedo* item;

};

struct lista {

    int tam;
    No* ini;

};

Lista* cria_lista() {

    Lista* lst = NULL;
    lst = (Lista*)malloc(sizeof(Lista));

    lst->tam = 0;
    lst->ini = NULL;

    return lst; 

}

// Insere no final.
int insere_na_lista(Lista* lst, Brinquedo* brinq) {

    if(lst == NULL)
        return 1;

    // Cria um novo no.
    No* novo_no = NULL;
    novo_no = (No*)malloc(sizeof(No));

    if(novo_no == NULL)
        return 1;

    if(lst->ini == NULL) {

        // Atualiza o anterior.
        novo_no->ant = novo_no;
        // Atualzia o proximo.
        novo_no->prox = novo_no;

        lst->ini = novo_no;

    } else {

        // Atualiza o anterior.
        novo_no->ant = lst->ini->ant;
        // Atualzia o proximo.
        novo_no->prox = lst->ini;

        // Atualiza os nos que ficaram adjacentes ao novo no.
        lst->ini->ant = novo_no;
        novo_no->ant->prox = novo_no;

    }
    
    novo_no->item = brinq;

    lst->tam++;

    return 0;

}

Brinquedo* remove_da_lista(Lista* lst, int pos) {

    if(lst == NULL || lst->tam < 1 || lst->ini == NULL)
        return NULL;

    No* t_no = lst->ini;
    Brinquedo* brinq = NULL;

    int t = 0;
    while(t < pos) {

        if(t_no == NULL)
            return NULL;

        t_no = t_no->prox;

        t++;

    }

    brinq = t_no->item;

    if(t_no == lst->ini)
        lst->ini = t_no->prox;

    // Atualiza os nos adjacentes.
    t_no->ant->prox = t_no->prox;
    t_no->prox->ant = t_no->ant;

    free(t_no);

    lst->tam--;
    
    return brinq;

}

int vazia_lista(Lista* lst) {

    if(lst == NULL)
        return -1;

    if(lst->tam == 0)
        return 1;
    
    return 0;

}

int tamanho_lista(Lista* lst) {

    if(lst == NULL)
        return -1;

    return lst->tam;

}

void deleta_lista(Lista* lst) {

    free(lst);

}