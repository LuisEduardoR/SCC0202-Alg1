#ifndef PILHA_H
#define PILHA_H
#include "brinquedo.h"
#define MAX_PLH_SIZE 1000
// Pilha (LIFO)
typedef struct pilha Pilha;
// Aloca memoria e inicializa a pilha.
Pilha* cria_pilha();
// Coloca um elemento no topo da pilha, retorna 0 no sucesso e 1 caso a pilha ja esteja no
// tamanho maximo.
int push(Pilha* plh, Brinquedo* brinq);
// Retira e retorna o topo da pilha.
Brinquedo* top(Pilha* plh);
// Verifica se a pilha esta cheia.
int cheia_pilha(Pilha* plh);
// Retorna o tamanho da pilha.
int tamanho_pilha(Pilha* plh);
// Libera a memoria da pilha.
void deleta_pilha(Pilha* plh);
#endif
