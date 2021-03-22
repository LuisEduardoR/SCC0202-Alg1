#include <stdio.h>

#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include "brinquedo.h"

int main (void) {

    // Recebe o numero de brinquedos, o valor do intervalo, e a capacidade de cada caixa
    int n, k, p;
    scanf(" %d %d %d", &n, &k, &p);

    // Caso o usuario insira que nao existem brinquedos o programa acabou.
    if(n == 0)
        return 0;

    // Cria uma lista que representa esteira
    Lista* esteira = NULL;
    esteira = cria_lista();
    if(esteira == NULL) {
        fprintf(stderr, "Erro ao criar lista de brinquedos!\n");
        return 1;
    }

    // Recebe os brinquedos e os adiciona na esteira.
    int t_num;
    char t_nome[65];
    for(int i = 0; i < n; i++) {

        scanf(" %d %s", &t_num, t_nome);
        
        Brinquedo* brinq = cria_brinquedo(t_num, t_nome);

        insere_na_lista(esteira, brinq);

    }

    /*
    while(!vazia_lista(esteira)) {

        Brinquedo* b = remove_da_lista(esteira, 0);
        printf("%d<--\n", num_brinquedo(b));

    }*/

    
    // Cria uma fila de caixas.
    Fila* caixas = NULL;
    caixas = cria_fila();
    if(caixas == NULL) {
        fprintf(stderr, "Erro ao criar fila de caixas!\n");
        return 1;
    }

    // Cria uma caixa.
    Pilha* caixa_atual = cria_pilha();
    if(caixa_atual == NULL) {
        fprintf(stderr, "Erro ao criar caixa de brinquedos!\n");
        return 1;
    }

    // Posicao da onde retirar.
    int pos = 0;
    // Brinquedo retirado.
    Brinquedo* brinq;
    while(!vazia_lista(esteira)) {

        // Retira um brinquedo da esteira.
        brinq = remove_da_lista(esteira, pos);

        pos--; // Compensa na posicao o fato de um brinquedo ter sido retirado.

        // Verifica se a caixa atual esta cheia e se necessario a coloca na fila e cria uma nova.
        if(tamanho_pilha(caixa_atual) == p) {

            insere_na_fila(caixas, caixa_atual);

            caixa_atual = cria_pilha();
            if(caixa_atual == NULL) {
                fprintf(stderr, "Erro ao criar caixa de brinquedos!\n");
                return 1;
            }

        }

        // Coloca o brinquedo retirado na caixa.
        push(caixa_atual, brinq);

        // Encontra a proxima posicao de onde retirar.
        pos += k;
        if(pos >= tamanho_lista(esteira)) {
            pos = 0;
            k--;
        }
    }

    // Insere a ultima caixa na fila.
    insere_na_fila(caixas, caixa_atual);

    // Deleta a esteira que ja nao eh mais necessaria.
    deleta_lista(esteira);

    // Guarda o numero da caixa atual.
    int caixa_num = 1;
    // Guarda a quantidade de brinquedos em uma caixa.
    int quant_brinq;
    // Printa o numero da caixa, o brinquedo no topo dela e a quantidade dentro dela.
    while(!vazia_fila(caixas)) {

        // Pega uma caixa da fila.
        caixa_atual = remove_fila(caixas);

        // Printa as informacoes necessarias.
        quant_brinq = tamanho_pilha(caixa_atual);
        brinq = top(caixa_atual);
        printf("caixa %d: brinquedo <%d,%s> - quantidade %d\n", caixa_num, num_brinquedo(brinq), nome_brinquedo(brinq), quant_brinq);

        // Aumenta o numero da caixa.
        caixa_num++;
        
        // Libera a memoria da caixa e dos brinquedos dentro dela, que ja nao eh mais necessaria.
        deleta_brinquedo(brinq);
        while(tamanho_pilha(caixa_atual) > 0) {
            deleta_brinquedo(top(caixa_atual));
        }
        deleta_pilha(caixa_atual);
        
    }

    // Deleta a fila.
    deleta_fila(caixas);
    
}