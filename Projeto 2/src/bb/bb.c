#include "bb.h"
#include <stdlib.h>
#include <stdio.h>

void criaSeqBB(ListaSeqBB *l) {

    l->vet = NULL;
    l->tam = 0;

}

int insereSeqBB(ListaSeqBB *l, elem x){

    if(l == NULL)
        return 1;

    // Aumenta o tamanho da lista.
    l->tam ++;
    if(l->tam > 1)
        l->vet = realloc(l->vet ,l->tam * sizeof(elem));
    else
        l->vet = malloc(sizeof(elem));

    if(l->vet == NULL) {
        l->tam --;
        return 1;
    }

    // Encontra a posição correta.
    int pos = 0;
    while(l->vet[pos] <= x && pos < l->tam - 1){

        // Se o elemento já estiver na lista, retorna.
        if(l->vet[pos] == x) {
            l->tam --;
            return 0;
        }

        pos++;
    }

    // Shifta os elementos necessários.
    for(int i = l->tam - 1; i > pos; i--)
        l->vet[i] = l->vet[i-1];
    
    // Insere.
    l->vet[pos] = x;

    return 0;

}

int removerSeqBB(ListaSeqBB *l, elem x){

    if(l == NULL)
        return 1;


    int ini, fim, pos;
    ini = 0;
    fim = l->tam - 1;
    pos = (fim + ini) / 2;

    //Encontra o elemento.
    while(ini != fim && l->vet[pos] != x)
    {
        if(x > l->vet[pos])
            ini = pos + 1;
        else
            fim = pos -1;

        pos = (fim + ini) / 2;

    }

    // Retorna se o elemento não foi encontrado.
    if(l->vet[pos] != x)
        return 0;

    // Remove e shifta os elementos necessários.
    for(int i = pos; i < l->tam - 1; i++)
        l->vet[i] = l->vet[i+1];
    
    // Reduz o tamanho da lista.
    l->tam --;
    if(l->tam > 0)
        l->vet = realloc(l->vet ,l->tam * sizeof(elem));
    else
        free(l->vet);

    if(l->vet == NULL)
        return 1;

    return 0;

}

int buscaSeqBB(ListaSeqBB* l, elem x){

    int ini, fim, pos;
    ini = 0;
    fim = l->tam - 1;
    pos = (fim + ini) / 2;

    //Encontra o elemento.
    while(ini < fim && l->vet[pos] != x)
    {

        if(x > l->vet[pos])
            ini = pos + 1;
        else
            fim = pos -1;

        pos = (fim + ini) / 2;

    }

    return (l->vet[pos] == x);

}

void imprimeSeqBB(ListaSeqBB* l){

    for(int i = 0; i < l->tam; i++)
        printf("%d ", l->vet[i]);
    printf("\n");

}

int esta_vaziaSeqBB(ListaSeqBB* l){

    return (l->tam == 0);

}

void deletaSeqBB (ListaSeqBB *l) {

    free(l->vet);
    l->tam = 0;

}