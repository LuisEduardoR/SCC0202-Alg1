#include <stdlib.h>
#include <stdio.h>
#include "lfreq.h"

void criaLFreq(ListaFreq *l) {
    l->ini = NULL;
    return;
}

int insereLFreq(ListaFreq *l, elem x) {

    No_lfreq *novo, *p;

    if (buscaLFreq(*l, x))
        return 1; // erro, elemento repetido
        
    novo = (No_lfreq *) malloc(sizeof(No_lfreq));
    if (novo == NULL)
        return 1; // erro, memoria insuficiente

    novo->info = x; // copia informacao
    
    // atualiza ponteiros
    if (l->ini == NULL) {
        l->ini = novo; // insere no inicio
        novo->ant = novo;
        novo->prox = novo;
    } else {
        l->ini->ant->prox = novo;
        novo->ant = l->ini->ant;

        l->ini->ant = novo;
        novo->prox = l->ini;
    } // insere no meio ou fim
    return 0; // sucesso
}

int removerLFreq(ListaFreq *l, elem x) {

    No_lfreq *p = l->ini;
    while(p != NULL && p->info != x && p->prox != l->ini)
        p = p->prox;

    if (p == NULL || p->info != x)
        return 1; // erro

    if (l->ini == p) {
        if(l->ini == p->prox) {
            l->ini = NULL;
            free(p); // remove o unico elemento
            return 0;
        } else
            l->ini = l->ini->prox; // remove do inicio
    }

    p->ant->prox = p->prox; // remove do meio ou do final
    p->prox->ant = p->ant;

    free(p);
    return 0; // sucesso
}

void imprimeLFreq(ListaFreq l) {

    if(l.ini == NULL) {
        printf("\n");
        return;
    }

    printf("%d ", l.ini->info);

    No_lfreq *no = l.ini->prox;
    while (no != l.ini) {
        printf("%d ", no->info);
        no = no->prox;
    }

    printf("\n");
    return;
}

int buscaLFreq(ListaFreq l, elem x) {

    No_lfreq *p = l.ini;
    while(p != NULL && p->info != x && p->prox != l.ini)
        p = p->prox;

    if (p == NULL || p->info != x)
        return 0; // nao achou

    // adianta o valor do elemento x em um no.
    if(p != l.ini) {
        int temp = p->info;
        p->info = p->ant->info;
        p->ant->info = temp;
    }


    return 1;
    
}

int esta_vaziaLFreq(ListaFreq l) {
    return (l.ini == NULL);
}

void deletaNoLFreq(No_lfreq* no) {

    if(no == NULL)
        return;

    deletaNoLFreq(no->prox);
    free(no);

}

int deletaLFreq(ListaFreq *l) {
    
    if(l == NULL)
        return 1;

    // Quebra a circularidade da lista.
    l->ini->ant->prox = NULL;

    // Deleta todos os nós recursivamente.
    deletaNoLFreq(l->ini);
    l->ini = NULL;

    return 0;    

}