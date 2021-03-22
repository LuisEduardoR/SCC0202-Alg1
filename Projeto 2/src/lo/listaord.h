#ifndef LISTAORD_H
#define LISTAORD_H

typedef int elem;

typedef struct no_lo {
    elem info;
    struct no_lo *prox;
} No_lo;

typedef struct {
    No_lo *ini;
} ListaOrd;

void criaLO(ListaOrd *l);
int insereLO(ListaOrd *l, elem x);
int removerLO(ListaOrd *l, elem x);
int buscaLO(ListaOrd l, elem x);
void imprimeLO(ListaOrd l);
int esta_vaziaLO(ListaOrd l);
int deletaLO(ListaOrd *l);

#endif