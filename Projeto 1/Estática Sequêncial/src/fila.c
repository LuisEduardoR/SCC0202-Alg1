#include "fila.h"
#include "brinquedo.h"
#include <stdlib.h>

struct fila {

    int tam;
    Pilha* item[MAX_FL_SIZE];

};

Fila* cria_fila() {

    Fila* fl = NULL;
    fl = (Fila*)malloc(sizeof(Fila));

    fl->tam = 0;

    return fl; 

}

int insere_na_fila(Fila* fl, Pilha* plh) {

    fl->tam++;
    fl->item[fl->tam - 1] = plh;

    return 0;

}

Pilha* remove_fila(Fila* fl) {

    Pilha* plh = NULL;

    if(fl->tam > 0 && fl->tam + 1 < MAX_FL_SIZE) {
        
        plh = fl->item[0];

        for(int i = 0; i < fl->tam - 1; i++)
            fl->item[i] = fl->item[i+1];

        fl->tam--;
        return plh;

    }

    return plh;

}

int vazia_fila(Fila* fl) {

    if(fl->tam == 0)
        return 1;
    
    return 0;

}

int cheia_fila(Fila* fl) {

    if(fl->tam == MAX_FL_SIZE)
        return 1;
    
    return 0;

}

void deleta_fila(Fila* fl) {

    free(fl);

}
