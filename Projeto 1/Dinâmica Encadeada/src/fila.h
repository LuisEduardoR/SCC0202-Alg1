#ifndef FILA_H
#define FILA_H
#include "pilha.h"
// FIla (FIFO)
typedef struct fila Fila;
// Aloca memoria e inicializa a pilha.
Fila* cria_fila();
// Insere elemento no inicio da fila, retorna 0 no suceso e 1 caso o 
// tamanho maximo tenha sido atingido.
int insere_na_fila(Fila* fl, Pilha* caixa);
// Remove o primeiro elemento da fila.
Pilha* remove_fila(Fila* fl);
// Verfica se a fila esta vazia.
int vazia_fila(Fila* fl);
// Libera a memoria da fila.
void deleta_fila(Fila* fl);
#endif