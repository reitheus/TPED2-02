#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define M 10

typedef struct analise{
  double timepre;//tempo no pré processamento
  double timepesquisa;//tempo na pesquisa
  int transpre;//transferencia no pré processamento
  int transpesquisa;//transferencia na pesquisa
  int comppre;//comparações no pré processamento
  int comppesquisa;//comparações na pesquisa
}Analise;


typedef struct item{
  int chave;
  long int dado1;
  char dado2[1001];
  char dado3[5001];
} Item;

typedef struct dadospesquisa{
  int metodo;
  long int quant;
  int situacao;
  int chave;
  char op[3];
  Analise analise;
} DadosPesquisa;

void impreResultado(bool ,DadosPesquisa* ,Item* );

void impremeDado(DadosPesquisa* ,Item* );

#endif // ITEM_H
