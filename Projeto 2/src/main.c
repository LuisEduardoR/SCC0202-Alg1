#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "bb/bb.h"
#include "lo/listaord.h"
#include "los/listaord_sentinela.h"
#include "abb/abb.h"
#include "avl/avl.h"
#include "lfreq/lfreq.h"

// Número de potencias de 10 a partir de 100 com as quais as estuturas serão testadas.
#define UPPER_POW_BOUND 4

// Imprime uma tabela com os tempos das estruturas.
void imprimir_tabela (char texto_tabela[81], double tempos[6][4]) {

    printf("%s\n", texto_tabela);
    printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
    printf("BB\t%lf\t%lf\t%lf\t%lf\n", tempos[0][0], tempos[0][1], tempos[0][2], tempos[0][3]);
    printf("LO\t%lf\t%lf\t%lf\t%lf\n", tempos[1][0], tempos[1][1], tempos[1][2], tempos[1][3]);
    printf("LOS\t%lf\t%lf\t%lf\t%lf\n", tempos[2][0], tempos[2][1], tempos[2][2], tempos[2][3]);
    printf("ABB\t%lf\t%lf\t%lf\t%lf\n", tempos[3][0], tempos[3][1], tempos[3][2], tempos[3][3]);
    printf("AVL\t%lf\t%lf\t%lf\t%lf\n", tempos[4][0], tempos[4][1], tempos[4][2], tempos[4][3]);
    printf("LFRQ\t%lf\t%lf\t%lf\t%lf\n", tempos[5][0], tempos[5][1], tempos[5][2], tempos[5][3]);
    printf("-\n");

}

// Executa e mede os tempos das operações do vetor sequêncial com busca binária.
int executa_seq_bb (double t_insCres[4], double t_busCres[4], double t_remCres[4],
                    double t_insDecres[4], double t_busDecres[4], double t_remDecres[4],
                    double t_insRand[4], double t_busRand[4], double t_remRand[4]) {

    // Cria a estutura.
    ListaSeqBB bb;
    criaSeqBB(&bb);

    clock_t clk_ini, clk_fim; // Usados para medir o tempo.

    // Executa para diferentes valores.
    for(int s = 0; s < UPPER_POW_BOUND; s++) {         

        //Pega o número de elementos a serem usados.
        int n = 100;
        for(int j = 1; j <= s; j++) { n*=10; }


        // Faz a inserção crescente.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insereSeqBB(&bb, i); }
        clk_fim = clock();                    
        t_insCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC; 
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaSeqBB(&bb, rand() % (n * 2)); }
        clk_fim = clock();
        t_busCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;                      
        clk_ini = clock(); // Remove crescente.
        for(int i = 0; i < n*2; i+=2) { removerSeqBB(&bb, i); }
        clk_fim = clock();
        t_remCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ deletaSeqBB(&bb);


        // Faz a inserção crescente novamente.
        for(int i = 0; i < n; i++) { insereSeqBB(&bb, i); }                    
        clk_ini = clock(); // Remove, mas agora decrescente.
        for(int i = (n * 2) - 1; i >= 0; i-=2) { removerSeqBB(&bb, i); }
        clk_fim = clock();
        t_remDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ deletaSeqBB(&bb);


        // Insere decrescente.
        clk_ini = clock();
        for(int i = n - 1; i >= 0; i--) { insereSeqBB(&bb, i); }
        clk_fim = clock();                    
        t_insDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaSeqBB(&bb, rand() % (n * 2)); }
        clk_fim = clock();
        t_busDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        /* Reseta a estrutura.*/ deletaSeqBB(&bb);


        // Insere aleatório.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insereSeqBB(&bb, rand() % n); }
        clk_fim = clock();
        t_insRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaSeqBB(&bb, rand() % (n * 2)); }
        clk_fim = clock();
        t_busRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock();  // Remove aleatório.
        for(int i = 0; i < n; i++) { removerSeqBB(&bb, rand() % (n * 2)); }
        clk_fim = clock();
        t_remRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;

        //Deleta a estrutura.
        deletaSeqBB(&bb);
    }
}

// Executa e mede os tempos das operações da lista ordenada.
int executa_listaord (double t_insCres[4], double t_busCres[4], double t_remCres[4],
                      double t_insDecres[4], double t_busDecres[4], double t_remDecres[4],
                      double t_insRand[4], double t_busRand[4], double t_remRand[4]) {

    // Cria a estutura.
    ListaOrd lo;
    criaLO(&lo);

    clock_t clk_ini, clk_fim; // Usados para medir o tempo.

    // Executa para diferentes valores.
    for(int s = 0; s < UPPER_POW_BOUND; s++) {         

        //Pega o número de elementos a serem usados.
        int n = 100;
        for(int j = 1; j <= s; j++) { n*=10; }

        // Faz a inserção crescente.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insereLO(&lo, i); }
        clk_fim = clock();                    
        t_insCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC; 
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaLO(lo, rand() % (n * 2)); }
        clk_fim = clock();
        t_busCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;                      
        clk_ini = clock(); // Remove crescente.
        for(int i = 0; i < n*2; i+=2) { removerLO(&lo, i); }
        clk_fim = clock();
        t_remCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ deletaLO(&lo);

        // Faz a inserção crescente novamente.
        for(int i = 0; i < n; i++) { insereLO(&lo, i); }                    
        clk_ini = clock(); // Remove, mas agora decrescente.
        for(int i = (n * 2) - 1; i >= 0; i-=2) { removerLO(&lo, i); }
        clk_fim = clock();
        t_remDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ deletaLO(&lo);


        // Insere decrescente.
        clk_ini = clock();
        for(int i = n - 1; i >= 0; i--) { insereLO(&lo, i); }
        clk_fim = clock();                    
        t_insDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaLO(lo, rand() % (n * 2)); }
        clk_fim = clock();
        t_busDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        /* Reseta a estrutura.*/ deletaLO(&lo);

        // Insere aleatório.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insereLO(&lo, rand() % n); }
        clk_fim = clock();                    
        t_insRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaLO(lo, rand() % (n * 2)); }
        clk_fim = clock();
        t_busRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock();  // Remove aleatório.
        for(int i = 0; i < n; i++) { removerLO(&lo, rand() % (n * 2)); }
        clk_fim = clock();
        t_remRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;

        //Deleta a estrutura.
        deletaLO(&lo);
    }
}

// Executa e mede os tempos das operações da lista ordenada com sentinela.
int executa_listaord_sen (double t_insCres[4], double t_busCres[4], double t_remCres[4],
                          double t_insDecres[4], double t_busDecres[4], double t_remDecres[4],
                          double t_insRand[4], double t_busRand[4], double t_remRand[4]) {

    // Cria a estutura.
    ListaOrdSen los;
    criaLOS(&los);

    clock_t clk_ini, clk_fim; // Usados para medir o tempo.

    // Executa para diferentes valores.
    for(int s = 0; s < UPPER_POW_BOUND; s++) {         

        //Pega o número de elementos a serem usados.
        int n = 100;
        for(int j = 1; j <= s; j++) { n*=10; }

        // Faz a inserção crescente.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insereLOS(&los, i); }
        clk_fim = clock();                    
        t_insCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC; 
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaLOS(los, rand() % (n * 2)); }
        clk_fim = clock();
        t_busCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;                      
        clk_ini = clock(); // Remove crescente.
        for(int i = 0; i < n*2; i+=2) { removerLOS(&los, i); }
        clk_fim = clock();
        t_remCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ deletaLOS(&los);

        // Faz a inserção crescente novamente.
        for(int i = 0; i < n; i++) { insereLOS(&los, i); }                    
        clk_ini = clock(); // Remove, mas agora decrescente.
        for(int i = (n * 2) - 1; i >= 0; i-=2) { removerLOS(&los, i); }
        clk_fim = clock();
        t_remDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ deletaLOS(&los);


        // Insere decrescente.
        clk_ini = clock();
        for(int i = n - 1; i >= 0; i--) { insereLOS(&los, i); }
        clk_fim = clock();                    
        t_insDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaLOS(los, rand() % (n * 2)); }
        clk_fim = clock();
        t_busDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        /* Reseta a estrutura.*/ deletaLOS(&los);

        // Insere aleatório.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insereLOS(&los, rand() % n); }
        clk_fim = clock();                    
        t_insRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaLOS(los, rand() % (n * 2)); }
        clk_fim = clock();
        t_busRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock();  // Remove aleatório.
        for(int i = 0; i < n; i++) { removerLOS(&los, rand() % (n * 2)); }
        clk_fim = clock();
        t_remRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;

        //Deleta a estrutura.
        deletaLOS(&los);
    }
}

// Executa e mede os tempos das operações da árvore binária de busca.
int executa_abb (double t_insCres[4], double t_busCres[4], double t_remCres[4],
                 double t_insDecres[4], double t_busDecres[4], double t_remDecres[4],
                 double t_insRand[4], double t_busRand[4], double t_remRand[4]) {

    // Cria a estutura.
    ABB abb;
    criaABB(&abb);

    clock_t clk_ini, clk_fim; // Usados para medir o tempo.

    // Executa para diferentes valores.
    for(int s = 0; s < UPPER_POW_BOUND; s++) {         

        //Pega o número de elementos a serem usados.
        int n = 100;
        for(int j = 1; j <= s; j++) { n*=10; }

        // Faz a inserção crescente.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insercaoABB(&abb, i); }
        clk_fim = clock();                    
        t_insCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC; 
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaABB(abb, rand() % (n * 2)); }
        clk_fim = clock();
        t_busCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;                      
        clk_ini = clock(); // Remove crescente.
        for(int i = 0; i < n*2; i+=2) { remocaoABB(&abb, i); }
        clk_fim = clock();
        t_remCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ destroiABB(&abb);

        // Faz a inserção crescente novamente.
        for(int i = 0; i < n; i++) { insercaoABB(&abb, i); }                    
        clk_ini = clock(); // Remove, mas agora decrescente.
        for(int i = (n * 2) - 1; i >= 0; i-=2) { remocaoABB(&abb, i); }
        clk_fim = clock();
        t_remDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ destroiABB(&abb);


        // Insere decrescente.
        clk_ini = clock();
        for(int i = n - 1; i >= 0; i--) { insercaoABB(&abb, i); }
        clk_fim = clock();                    
        t_insDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaABB(abb, rand() % (n * 2)); }
        clk_fim = clock();
        t_busDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        /* Reseta a estrutura.*/ destroiABB(&abb);

        // Insere aleatório.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insercaoABB(&abb, rand() % n); }
        clk_fim = clock();                    
        t_insRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaABB(abb, rand() % (n * 2)); }
        clk_fim = clock();
        t_busRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock();  // Remove aleatório.
        for(int i = 0; i < n; i++) { remocaoABB(&abb, rand() % (n * 2)); }
        clk_fim = clock();
        t_remRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;

        //Deleta a estrutura.
        destroiABB(&abb);
    }
}

// Executa e mede os tempos das operações da árvore AVL.
int executa_avl (double t_insCres[4], double t_busCres[4], double t_remCres[4],
                 double t_insDecres[4], double t_busDecres[4], double t_remDecres[4],
                 double t_insRand[4], double t_busRand[4], double t_remRand[4]) {

    // Cria a estutura.
    AVL avl;
    criaAVL(&avl);

    clock_t clk_ini, clk_fim; // Usados para medir o tempo.

    // Executa para diferentes valores.
    for(int s = 0; s < UPPER_POW_BOUND; s++) {         

        //Pega o número de elementos a serem usados.
        int n = 100;
        for(int j = 1; j <= s; j++) { n*=10; }

        // Faz a inserção crescente.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insercaoAVL(&avl, i); }
        clk_fim = clock();                    
        t_insCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC; 
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaAVL(avl, rand() % (n * 2)); }
        clk_fim = clock();
        t_busCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;                      
        //clk_ini = clock(); // Remove crescente.
        //for(int i = 0; i < n*2; i+=2) { remocaoAVL(&avl, i); }
        //clk_fim = clock();
        //t_remCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ //destroiAVL(&avl);
        
        // Faz a inserção crescente novamente.
        //for(int i = 0; i < n; i++) { insercaoAVL(&avl, i); }                    
        //clk_ini = clock(); // Remove, mas agora decrescente.
        //for(int i = (n * 2) - 1; i >= 0; i-=2) { remocaoAVL(&avl, i); }
        //clk_fim = clock();
        //t_remDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ destroiAVL(&avl);
        

        // Insere decrescente.
        clk_ini = clock();
        for(int i = n - 1; i >= 0; i--) { insercaoAVL(&avl, i); }
        clk_fim = clock();                    
        t_insDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaAVL(avl, rand() % (n * 2)); }
        clk_fim = clock();
        t_busDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        /* Reseta a estrutura.*/ destroiAVL(&avl);

        // Insere aleatório.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insercaoAVL(&avl, rand() % n); }
        clk_fim = clock();                    
        t_insRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaAVL(avl, rand() % (n * 2)); }
        clk_fim = clock();
        t_busRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        //clk_ini = clock();  // Remove aleatório.
        //for(int i = 0; i < n; i++) { remocaoAVL(&avl, rand() % (n * 2)); }
        //clk_fim = clock();
        //t_remRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;

        //Deleta a estrutura.
        destroiAVL(&avl);
    }
}

// Executa e mede os tempos das operações da lista com frequências.
int executa_lfreq (double t_insCres[4], double t_busCres[4], double t_remCres[4],
                 double t_insDecres[4], double t_busDecres[4], double t_remDecres[4],
                 double t_insRand[4], double t_busRand[4], double t_remRand[4]) {

    // Cria a estutura.
    ListaFreq lfreq;
    criaLFreq(&lfreq);

    clock_t clk_ini, clk_fim; // Usados para medir o tempo.

    // Executa para diferentes valores.
    for(int s = 0; s < UPPER_POW_BOUND; s++) {         

        //Pega o número de elementos a serem usados.
        int n = 100;
        for(int j = 1; j <= s; j++) { n*=10; }

        // Faz a inserção crescente.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insereLFreq(&lfreq, i); }
        clk_fim = clock();                    
        t_insCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC; 
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaLFreq(lfreq, rand() % (n * 2)); }
        clk_fim = clock();
        t_busCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;                      
        clk_ini = clock(); // Remove crescente.
        for(int i = 0; i < n*2; i+=2) { removerLFreq(&lfreq, i); }
        clk_fim = clock();
        t_remCres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ deletaLFreq(&lfreq);

        // Faz a inserção crescente novamente.
        for(int i = 0; i < n; i++) { insereLFreq(&lfreq, i); }                    
        clk_ini = clock(); // Remove, mas agora decrescente.
        for(int i = (n * 2) - 1; i >= 0; i-=2) { removerLFreq(&lfreq, i); }
        clk_fim = clock();
        t_remDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;  
        /* Reseta a estrutura.*/ deletaLFreq(&lfreq);


        // Insere decrescente.
        clk_ini = clock();
        for(int i = n - 1; i >= 0; i--) { insereLFreq(&lfreq, i); }
        clk_fim = clock();                    
        t_insDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaLFreq(lfreq, rand() % (n * 2)); }
        clk_fim = clock();
        t_busDecres[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        /* Reseta a estrutura.*/ deletaLFreq(&lfreq);

        // Insere aleatório.
        clk_ini = clock();
        for(int i = 0; i < n; i++) { insereLFreq(&lfreq, rand() % n); }
        clk_fim = clock();                    
        t_insRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock(); // Faz a busca.
        for(int i = 0; i < n; i++) { buscaLFreq(lfreq, rand() % (n * 2)); }
        clk_fim = clock();
        t_busRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;
        clk_ini = clock();  // Remove aleatório.
        for(int i = 0; i < n; i++) { removerLFreq(&lfreq, rand() % (n * 2)); }
        clk_fim = clock();
        t_remRand[s] = (double)(clk_fim - clk_ini) / CLOCKS_PER_SEC;

        //Deleta a estrutura.
        deletaLFreq(&lfreq);
    }
}

int main(int argc, char const *argv[])
{

    // Gera uma seed para os números aleatórios.
    srand(time(NULL));

    // Guarda os tempos das estruturas.
    double t_insCres[6][4], t_busCres[6][4], t_remCres[6][4];
    double t_insDecres[6][4], t_busDecres[6][4], t_remDecres[6][4];
    double t_insRand[6][4], t_busRand[6][4], t_remRand[6][4];    

    // Executa e mede os tempos para cada estrutura.
    executa_seq_bb (t_insCres[0], t_busCres[0], t_remCres[0],
                            t_insDecres[0], t_busDecres[0], t_remDecres[0],
                            t_insRand[0], t_busRand[0], t_remRand[0]);

    executa_listaord (t_insCres[1], t_busCres[1], t_remCres[1],
                      t_insDecres[1], t_busDecres[1], t_remDecres[1],
                      t_insRand[1], t_busRand[1], t_remRand[1]);

    executa_listaord_sen (t_insCres[2], t_busCres[2], t_remCres[2],
                          t_insDecres[2], t_busDecres[2], t_remDecres[2],
                          t_insRand[2], t_busRand[2], t_remRand[2]);

    executa_abb (t_insCres[3], t_busCres[3], t_remCres[3],
                 t_insDecres[3], t_busDecres[3], t_remDecres[3],
                 t_insRand[3], t_busRand[3], t_remRand[3]);

    executa_avl (t_insCres[4], t_busCres[4], t_remCres[4],
                 t_insDecres[4], t_busDecres[4], t_remDecres[4],
                 t_insRand[4], t_busRand[4], t_remRand[4]);

    executa_lfreq (t_insCres[5], t_busCres[5], t_remCres[5],
                   t_insDecres[5], t_busDecres[5], t_remDecres[5],
                   t_insRand[5], t_busRand[5], t_remRand[5]);

    // Imprime os resultados.    
    imprimir_tabela("Tabela 1: Tempo de insercao crescente", t_insCres);
    imprimir_tabela("Tabela 2: Tempo de insercao decrescente", t_insDecres);
    imprimir_tabela("Tabela 2: Tempo de insercao aleatoria", t_insRand);
    imprimir_tabela("Tabela 4: Tempo de remocao crescente (apos insercao crescente)", t_remCres);
    imprimir_tabela("Tabela 5: Tempo de remocao decrescente (apos insercao crescente)", t_remDecres);
    imprimir_tabela("Tabela 6: Tempo de remocao aleatoria (apos insercao aleatoria)", t_remRand);
    imprimir_tabela("Tabela 7: Tempo de busca (apos insercao crescente)", t_busCres);
    imprimir_tabela("Tabela 8: Tempo de busca (apos insercao decrescente)", t_busDecres);
    imprimir_tabela("Tabela 9: Tempo de busca (apos insercao aleatoria)", t_busRand);

    return 0;
}
