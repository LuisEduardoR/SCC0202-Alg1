#ifndef LFREQ_H
#define LFREQ_H

typedef int elem;

typedef struct no_lfreq {
    elem info;
    struct no_lfreq *ant, *prox;
} No_lfreq;

typedef struct {
    No_lfreq *ini;
} ListaFreq;

void criaLFreq(ListaFreq *l);
int insereLFreq(ListaFreq *l, elem x);
int removerLFreq(ListaFreq *l, elem x);
int buscaLFreq(ListaFreq l, elem x);
void imprimeLFreq(ListaFreq l);
int esta_vaziaLFreq(ListaFreq l);
int deletaLFreq(ListaFreq *l);

#endif