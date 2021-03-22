#ifndef LISTAORD_SENTINELA_H
#define LISTAORD_SENTINELA_H

typedef int elem;

typedef struct no_los {
    elem info;
    struct no_los *prox;
} No_los;

typedef struct {
    No_los *ini, *sentinela;
} ListaOrdSen;

int criaLOS(ListaOrdSen *l);
void destroiLOS(ListaOrdSen *l);
int insereLOS(ListaOrdSen *l, elem x);
int removerLOS(ListaOrdSen *l, elem x);
int buscaLOS(ListaOrdSen l, elem x);
void imprimeLOS(ListaOrdSen l);
int esta_vaziaLOS(ListaOrdSen l);
int deletaLOS(ListaOrdSen *los);

#endif
