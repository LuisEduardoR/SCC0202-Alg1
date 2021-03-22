#ifndef BRINQUEDO_H
#define BRINQUEDO_H
typedef struct brinquedo Brinquedo;
Brinquedo* cria_brinquedo(int num, char* nome);
int num_brinquedo (Brinquedo* brinq);
char* nome_brinquedo (Brinquedo* brinq);
void deleta_brinquedo(Brinquedo* brinq);
#endif