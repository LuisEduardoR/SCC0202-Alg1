#ifndef AVL_H
#define AVL_H

typedef int elem;

typedef struct no_avl {
    elem info;
    struct no_avl *esq, *dir;
    int fb;
} No_avl;

typedef struct {
    No_avl *raiz;
} AVL;

void criaAVL(AVL *a);
void destroiAVL(AVL *a);
int vaziaAVL(AVL a);
void imprimeAVL(AVL a);
int alturaAVL(AVL a);
void preOrdemAVL(AVL a);
void emOrdemAVL(AVL a);
void posOrdemAVL(AVL a);
int buscaAVL(AVL a, elem x);
int insercaoAVL(AVL *a, elem x);

#endif