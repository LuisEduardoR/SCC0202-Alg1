#ifndef LISTA_H
#define LISTA_H
#include "brinquedo.h"
#define MAX_LST_SIZE 1000
// Lista circular
typedef struct lista Lista;
// Aloca memoria e inicializa a lista.
Lista* cria_lista();
// Adiciona um elemento no final da lista e retorna 0 caso haja suceso e 1 se ouver erro.
int insere_na_lista(Lista* lst, Brinquedo* brinq);
// Adiciona um elemento na lista, caso a posicao seja maior que o tamanho da lista recomeça
// a contar do comeco.
Brinquedo* remove_da_lista(Lista* lst, int pos);
// Verifica se a lista esta vazia.
int vazia_lista(Lista* lst);
// Verifica se o tamanho maximo da lista foi atingido.
int cheia_lista(Lista* lst);
// Retorna o tamanho da lista ou -1 se uma lista nula for passada.
int tamanho_lista(Lista* lst);
// Libera a memoria da lista.
void deleta_lista(Lista* lst);
#endif
