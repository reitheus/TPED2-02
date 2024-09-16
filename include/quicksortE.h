#ifndef QUICKSORTE_E
#define QUICKSORTE_E

#include "../include/item.h"
#include <limits.h>

typedef struct tipoa{
    Item itens[M];
    int NumCelOcupadas;
}TipoA;

typedef Item Registro;

void leSup(FILE** ,Registro* ,int* ,bool* );
void leInf(FILE** ,Registro* ,int* ,bool* );
void insArea(TipoA* ,Registro* ,int* );
void escreveMin(FILE** ,Registro ,int* );
void escreveMax(FILE** ,Registro ,int* );
void retiraMax(TipoA* ,Registro* ,int* );
void retiraMin(TipoA* ,Registro* ,int* );
void partitionE(FILE** ,FILE** ,FILE** ,TipoA ,int ,int ,int* ,int* ,Analise* );
void quicksortExterno(FILE** ,FILE** ,FILE** ,int ,int ,Analise* );
void quick(FILE* ,DadosPesquisa* );

#endif //quicksort Externo