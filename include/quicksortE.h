#ifndef QUICKSORTE_E
#define QUICKSORTE_E

#include "../include/item.h"
#include <limits.h>

typedef int Apontador;

typedef struct cell{
    Item chave;
    Apontador Prox, Ant;
}Celula;

typedef struct tipoa{
    Celula itens[M];
    Apontador CelulasDisp, Primeiro, Ultimo;
    int NumCelOcupadas;
}TipoA;

typedef Item Registro;

void FAVazia(TipoA* );
int ObterNumCelOcupadas(TipoA* );
void InsereItem(Item ,TipoA* );
void RetiraPrimeiro(TipoA* ,Item* );
void RetiraUltimo(TipoA* , Item* );
void leSup(FILE** ,Registro* ,int* ,short* );
void leInf(FILE** ,Registro* ,int* ,short* );
void insArea(TipoA* ,Registro* ,int* );
void escreveMin(FILE** ,Registro ,int* );
void escreveMax(FILE** ,Registro ,int* );
void retiraMax(TipoA* ,Registro* ,int* );
void retiraMin(TipoA* ,Registro* ,int* );
void partitionE(FILE** ,FILE** ,FILE** ,TipoA ,int ,int ,int* ,int* );
void quicksortExterno(FILE** ,FILE** ,FILE** ,int ,int );

#endif //quicksort Externo