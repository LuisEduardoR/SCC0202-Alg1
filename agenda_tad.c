#include <string.h>
#include <stdlib.h>

typedef struct _contato {

    char* nome;
    char* endereco;

} Contato;

typedef struct _agenda {

    Contato* contatos;
    unsigned tamanho;

} Agenda;

Agenda criarAgenda () {

    Agenda nova;
    nova.contatos = NULL;
    nova.tamanho = 0; 

    return nova;

}

int inserirContato(Agenda* agenda, Contato novo_contato) {

    for(int i = 0; i < (*agenda).tamanho; i++) {

        if(strcmp((*agenda).contatos[i].nome, novo_contato.nome) == 0)
            return 0; // O contato já existe.

    }

    (*agenda).tamanho++;
    (*agenda).contatos = (Contato*) realloc((*agenda).contatos, sizeof(Contato) * ((*agenda).tamanho));
    
    if((*agenda).contatos == NULL)
        return -1; // Ocorreu algo errado ao realocar.

    (*agenda).contatos[(*agenda).tamanho - 1] = novo_contato;

    return 1; // Sucesso.

}

int removerContato(Agenda* agenda, char* nome_alvo) {

    for(int i = 0; i < (*agenda).tamanho; i++) {
        if(strcmp((*agenda).contatos[i].nome, nome_alvo) == 0) {
            
            free((*agenda).contatos[i].nome);
            free((*agenda).contatos[i].endereco);

            for(int j = i; j < (*agenda).tamanho - 1; j++) {
                (*agenda).contatos[j] = (*agenda).contatos[j + 1];
            }

            (*agenda).tamanho--;
            (*agenda).contatos = (Contato*) realloc((*agenda).contatos, sizeof(Contato) * (*agenda).tamanho);

            if((*agenda).contatos == NULL)
                return -1; // Ocorreu algo errado ao realocar.

            return 1; // Sucesso.

        }
    }

    return 0; // O contato não existe.

}

int modificarEndereco(Agenda* agenda, char* nome_alvo, char* novo_endereco, unsigned tamanho) {

    for(int i = 0; i < (*agenda).tamanho; i++) {
        if(strcmp((*agenda).contatos[i].nome, nome_alvo) == 0) {
            
            (*agenda).contatos[i].endereco = (char*) realloc((*agenda).contatos[i].endereco, sizeof(char) * tamanho);
            strcpy((*agenda).contatos[i].endereco, novo_endereco);
            return 1; // Sucesso.

        }
    }

    return 0; // O contato não existe.

}

char* buscarEndereco(Agenda* agenda, char* nome_alvo) {

    for(int i = 0; i < (*agenda).tamanho; i++) {
        if(strcmp((*agenda).contatos[i].nome, nome_alvo) == 0) {
            
            return (char*) (*agenda).contatos[i].endereco; // Sucesso.

        }
    }

    return NULL; // O contato não existe.

}

int deletarAgenda(Agenda* agenda) {

    for(int i = 0; i < (*agenda).tamanho; i++) {
        if((*agenda).tamanho > 0) {
            free((*agenda).contatos[i].nome);
            free((*agenda).contatos[i].endereco);
        }
    }

    if((*agenda).contatos != NULL)
        free((*agenda).contatos);
    (*agenda).contatos = NULL;
    (*agenda).tamanho = 0;

}