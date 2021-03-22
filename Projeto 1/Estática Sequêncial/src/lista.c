#include "lista.h"
#include "brinquedo.h"
#include <stdlib.h>

struct lista {

    int tam;
    Brinquedo* item[MAX_LST_SIZE];

};

Lista* cria_lista() {

    Lista* lst = NULL;
    lst = (Lista*)malloc(sizeof(Lista));

    lst->tam = 0;

    return lst; 

}

// Insere no final.
int insere_na_lista(Lista* lst, Brinquedo* brinq) {

    if(lst == NULL || lst->tam + 1 > MAX_LST_SIZE)
        return 1;

    lst->tam++;
    lst->item[lst->tam - 1] = brinq;

    return 0;

}

Brinquedo* remove_da_lista(Lista* lst, int pos) {

    if(lst == NULL)
        return NULL;

    Brinquedo* brinq = NULL;

    if(lst->tam > 0) {
        
        // O % garante que caso o final da lista seja ultrapassado a insercao "de a volta"
        // e parta do começo de novo.
        brinq = lst->item[pos % lst->tam];

        // Faz shift da memoria necessaria.
        for(int i = (pos % lst->tam); i < lst->tam - 1; i++)
            lst->item[i] = lst->item[i+1];

        lst->tam--;
        return brinq;

    }

    return brinq;

}

int vazia_lista(Lista* lst) {

    if(lst == NULL)
        return -1;

    if(lst->tam == 0)
        return 1;
    
    return 0;

}

int cheia_lista(Lista* lst) {

    if(lst == NULL)
        return -1;

    if(lst->tam >= MAX_LST_SIZE)
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
