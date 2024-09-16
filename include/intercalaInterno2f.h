#ifndef INTERCALAINTERNO2F_H
#define INTERCALAINTERNO2F_H
#include "../include/item.h"
#include "../include/gerador.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

//estrutura de dados fita cada fita tem um arquio e um inteiro contendo a quantidade de itens na fita
typedef struct fitas{
    FILE *file;//arquivo que vai ser usado como fita
    int quantItens;//quantidade de itens na fita
    int itensLido;
    int ativa;//verifica se a fita está ativa para ler
    int vazia;//verifica se a fita está vazia
}FITAS;


int intercalaOrdenaInterno(FILE *, FILE *, DadosPesquisa );


#endif // INTERCALAINTERNO2F_H
