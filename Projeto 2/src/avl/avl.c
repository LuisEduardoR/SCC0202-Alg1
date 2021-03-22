#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void criaAVL(AVL *a) {
    a->raiz = NULL; // cria uma arvore vazia
    return;
}

void destroiSubAVL(No_avl *p) {
    if (p == NULL)
        return;
    destroiSubAVL(p->esq); // destroi subarvore esquerda
    destroiSubAVL(p->dir); // destroi subarvore direita
    free(p); // apaga o raiz da subarvore
    return;
}

void destroiAVL(AVL *a) {
    destroiSubAVL(a->raiz); // inicia recursao
    a->raiz = NULL;
    return;
}

int vaziaAVL(AVL a) {
    return a.raiz == NULL;
}

void imprimeSubAVL(No_avl *p) {
    printf("{");
    if (p != NULL) {
        printf("%d:%d, ", p->info, p->fb);
        imprimeSubAVL(p->esq);
        printf(", ");
        imprimeSubAVL(p->dir);
    }
    printf("}");
    return;
}

void imprimeAVL(AVL a) {
    imprimeSubAVL(a.raiz);
    printf("\n");
    return;
}

int alturaSubAVL(No_avl *p) {
    int aesq, adir;
    if (p == NULL)
        return 0; // arvore nula
    aesq = alturaSubAVL(p->esq); // altura da subarvore esquerda
    adir = alturaSubAVL(p->dir); // altura da subarvore direita
    return (aesq > adir)? aesq + 1 : adir + 1;
}

int alturaAVL(AVL a) {
    return alturaSubAVL(a.raiz); // inicia recursao
}

void preOrdemSubAVL(No_avl *p) {
    if (p != NULL) {
        printf("%d ", p->info); // processa antes de varrer subarvores
        preOrdemSubAVL(p->esq); // varre lado esquerdo
        preOrdemSubAVL(p->dir); // varre lado direito
    }
    return;
}

void preOrdemAVL(AVL a) {
    preOrdemSubAVL(a.raiz); // inicia recursao
    printf("\n");
    return;
}

void emOrdemSubAVL(No_avl *p) {
    if (p != NULL) {
        emOrdemSubAVL(p->esq); // varre lado esquerdo
        printf("%d ", p->info); // processa entre uma subarvore e a outra
        emOrdemSubAVL(p->dir); // varre lado direito
    }
    return;
}

void emOrdemAVL(AVL a) {
    emOrdemSubAVL(a.raiz); // inicia recursao
    printf("\n");
    return;
}

void posOrdemSubAVL(No_avl *p) {
    if (p != NULL) {
        posOrdemSubAVL(p->esq); // varre lado esquerdo
        posOrdemSubAVL(p->dir); // varre lado direito
        printf("%d ", p->info); // processa apos subarvores
    }
    return;
}

void posOrdemAVL(AVL a) {
    posOrdemSubAVL(a.raiz); // inicia recursao
    printf("\n");
    return;
}

int buscaSubAVL(No_avl *p, elem x) {
    if (p == NULL)
        return 0; // nao achou
    if (p->info == x)
        return 1; // achou
    return (x < p->info) ? buscaSubAVL(p->esq, x) : buscaSubAVL(p->dir, x);
}

int buscaAVL(AVL a, elem x) {
    return buscaSubAVL(a.raiz, x); // inicia recursao
}


// rotacao simples a esquerda
void E(No_avl **p) {
    // p => No **; *p => No *; **p => No
    No_avl *novoRaiz, *realocar;
    novoRaiz = (*p)->dir;
    realocar = novoRaiz->esq;
    novoRaiz->esq = *p;
    (*p)->dir = realocar;
    *p = novoRaiz;
    return;
}

// rotacao simples a direita
void D(No_avl **p) {
    // p => No **; *p => No *; **p => No
    No_avl *novoRaiz, *realocar;
    novoRaiz = (*p)->esq;
    realocar = novoRaiz->dir;
    novoRaiz->dir = *p;
    (*p)->esq = realocar;
    *p = novoRaiz;
    return;
}

void ED(No_avl **p) {
    E(&((*p)->esq));
    D(p);
    return;
}

void DE(No_avl **p) {
    D(&((*p)->dir));
    E(p);
    return;
}

No_avl *criaNoAVL(elem info, No_avl *esq, No_avl *dir, int fb) {
    No_avl *nova = malloc(sizeof(No_avl));
    if (nova != NULL) {
        nova->info = info;
        nova->esq = esq;
        nova->dir = dir;
        nova->fb = fb;
    }
    return nova;
}

// atualiza fatores de balanceamento apos a rotacao dupla
void atualizaFB(No_avl *p) {
    switch (p->fb) {
        case 1:
            p->dir->fb = 0;
            p->esq->fb = -1;
            break;
        case -1:
            p->dir->fb = 1;
            p->esq->fb = 0;
            break;
        case 0:
            p->dir->fb = 0;
            p->esq->fb = 0;
            break;
    }
    p->fb = 0;
}

int insercaoSubAVL(No_avl **p, elem x, int *cresceu) {
    // p => No **; *p => No *; **p => No
    int retorno;
    if (*p == NULL) {
        *p = criaNoAVL(x, NULL, NULL, 0); // insere
        *cresceu = 1; // subarvore cresceu; era nula e agora tem o raiz
        return *p == NULL; // erro de memoria ou sucesso
    }
    if ((*p)->info == x)
        return 1; // erro, achou
    retorno = insercaoSubAVL((x < (*p)->info) ? &((*p)->esq) : &((*p)->dir), x, cresceu);
    if (!retorno && *cresceu) { // atualiza fator de balanceamento e rebalanceia se necessario
        (*p)->fb += (x < (*p)->info) ? -1 : 1; // atualiza fator de balanceamento
        if ((*p)->fb == 0 || (*p)->fb == 2 || (*p)->fb == -2) {
            *cresceu = 0; // arvore parou de crescer: 0 => melhorou o balanceamento; 2 ou -2 => sera feito o rebalanceamento
            switch ((*p)->fb) {
                case 2: // arvore muito alta a direita
                    if ((*p)->dir->fb == 1) { // mesmo sinal
                        E(p); // rotacao simples a esquerda
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->esq->fb = 0;
                    } else { // sinais opostos
                        DE(p); // rotacao dupla direita-esquerda
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
                case -2: // arvore muito alta a esquerda
                    if ((*p)->esq->fb == -1) { // mesmo sinal
                        D(p); // rotacao simples a direita
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->dir->fb = 0;
                    } else { // sinais opostos
                        ED(p); // rotacao dupla esquerda-direita
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
            }
        }
    }
    return retorno;
}

int insercaoAVL(AVL *a, elem x) {
    int cresceu;
    return insercaoSubAVL(&(a->raiz), x, &cresceu); // inicia recursao
}

int remocaoSubAVL(No_avl **p, elem x, int *diminuiu) {

    if (*p == NULL)
        return 1; // erro, nao achou

    if()

    // p => No **; *p => No *; **p => No
    int retorno;
    retorno = remocaoSubAVL((x < (*p)->info) ? &((*p)->esq) : &((*p)->dir), x, diminuiu);
    if (!retorno && *diminuiu) { // atualiza fator de balanceamento e rebalanceia se necessario
        (*p)->fb += (x < (*p)->info) ? -1 : 1; // atualiza fator de balanceamento
        if ((*p)->fb == 0 || (*p)->fb == 2 || (*p)->fb == -2) {
            *diminuiu = 0; // arvore parou de crescer: 0 => melhorou o balanceamento; 2 ou -2 => sera feito o rebalanceamento
            switch ((*p)->fb) {
                case 2: // arvore muito alta a direita
                    if ((*p)->dir->fb == 1) { // mesmo sinal
                        E(p); // rotacao simples a esquerda
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->esq->fb = 0;
                    } else { // sinais opostos
                        DE(p); // rotacao dupla direita-esquerda
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
                case -2: // arvore muito alta a esquerda
                    if ((*p)->esq->fb == -1) { // mesmo sinal
                        D(p); // rotacao simples a direita
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->dir->fb = 0;
                    } else { // sinais opostos
                        ED(p); // rotacao dupla esquerda-direita
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
            }
        }
    }
    return retorno;
}

int remocaoAVL(AVL *a, elem x) {
    int diminuiu;
    return remocaoSubAVL(&(a->raiz), x, &diminuiu); // inicia recursao
}