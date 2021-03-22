#include <stdlib.h>
#include <stdio.h>
#include "listaord_sentinela.h"

int criaLOS(ListaOrdSen *l) {
    l->sentinela = malloc(sizeof(No_los));
    if (l->sentinela == NULL)
        return 1; // erro
    l->sentinela->prox = NULL;
    l->ini = l->sentinela;
    return 0; // sucesso
}

void destroiLOS(ListaOrdSen *l) {
    No_los *aux;
    while (l->ini != NULL) {
        aux = l->ini;
        l->ini = l->ini->prox;
        free(aux);
    }
    l->sentinela = NULL;
    return;
}

void busca_internaLOS(ListaOrdSen *l, elem x, No_los **ant, No_los **p) {
    // ant, p => No **
    // *ant, *p => No *
    // **ant, **p => No
    l->sentinela->info = x;
    *ant = NULL;
    *p = l->ini;
    while ((*p)->info < x) {
        *ant = *p;
        *p = (*p)->prox;
    }
    return;
}

int insereLOS(ListaOrdSen *l, elem x) {
    No_los *novo, *ant, *p;
    busca_internaLOS(l, x, &ant, &p); // busca primeiro maior ou igual a x
    if (p != l->sentinela && p->info == x)
        return 1; // erro, elemento repetido
    novo = (No_los *) malloc(sizeof(No_los));
    if (novo == NULL)
        return 1; // erro, memoria insuficiente
    novo->info = x; // copia informacao
    // atualiza ponteiros
    novo->prox = p;
    if (ant == NULL)
        l->ini = novo; // insere no inicio
    else
        ant->prox = novo; // insere no meio ou fim
    return 0; // sucesso
}

int removerLOS(ListaOrdSen *l, elem x) {
    No_los *ant, *p;
    busca_internaLOS(l, x, &ant, &p);
    if (p == l->sentinela || p->info != x)
        return 1; // erro
    if (l->ini == p)
        l->ini = l->ini->prox; // remove do inicio
    else
        ant->prox = p->prox; // remove do meio ou do final
    free(p);
    return 0; // sucesso
}

void imprimeLOS(ListaOrdSen l) {
    while (l.ini != l.sentinela) {
        printf("%d", l.ini->info);
        l.ini = l.ini->prox;
    }
    printf("\n");
    return;
}

int buscaLOS(ListaOrdSen l, elem x) {
    l.sentinela->info = x;
    while(l.ini->info < x)
        l.ini = l.ini->prox;
    return (l.ini != l.sentinela && l.ini->info == x);
}

int esta_vaziaLOS(ListaOrdSen l) {
    return (l.ini == l.sentinela);
}

void deletaNoLOS(No_los* no) {

    if(no == NULL)
        return;

    deletaNoLOS(no->prox);
    free(no);

}

int deletaLOS(ListaOrdSen *l) {
    
    if(l == NULL)
        return 1;

    deletaNoLOS(l->ini);
    l->ini = NULL;
    l->sentinela = NULL;

    return 0;    

}