#ifndef ABB_H
#define ABB_H

typedef int elem;

typedef struct no_abb {
    elem info;
    struct no_abb *esq, *dir;
} No_abb;

typedef struct {
    No_abb *raiz;
} ABB;

void criaABB(ABB *a);
void destroiABB(ABB *a);
int vaziaABB(ABB a);
void imprimeABB(ABB a);
int alturaABB(ABB a);
void preOrdemABB(ABB a);
void emOrdemABB(ABB a);
void posOrdemABB(ABB a);
int buscaABB(ABB a, elem x);
int insercaoABB(ABB *a, elem x);
int remocaoABB(ABB *a, elem x);

#endif