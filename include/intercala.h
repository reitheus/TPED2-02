#ifndef _INTERCALA_H_
#define _INTERCALA_H_

#include "item.h"

typedef struct fitas{
    FILE *file;//arquivo que vai ser usado como fita
    int quantItens;//quantidade de itens na fita
    int itensLido;
    int ativa;//verifica se a fita está ativa para ler
    int vazia;//verifica se a fita está vazia
}FITAS;


int menorItem(Item *itens);
int abreArquivos(FITAS *fitas, int familia);
int fechaArquivos(FITAS *fitas, int familia);
int setPonteiroFitas(FITAS *fitas);
int verificaSeOrdenacaoAcabou(FITAS *fitas);
int verificaSeAsFitasEstaoAtivas(FITAS *fitas);
int reativaAsFitas(FITAS *fitas);
int preencheVetor(FITAS *fitas, Item *itens, DadosPesquisa *entrada);

#endif