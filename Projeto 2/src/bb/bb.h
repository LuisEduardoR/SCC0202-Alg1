typedef int elem;

typedef struct no {
    elem info;
    struct no *prox;
} No;

typedef struct {
    elem* vet;
    int tam;
} ListaSeqBB;

void criaSeqBB(ListaSeqBB *l);
int insereSeqBB(ListaSeqBB *l, elem x);
int removerSeqBB(ListaSeqBB *l, elem x);
int buscaSeqBB(ListaSeqBB *l, elem x);
void imprimeSeqBB(ListaSeqBB *l);
int esta_vaziaSeqBB(ListaSeqBB *l);
void deletaSeqBB (ListaSeqBB *l);