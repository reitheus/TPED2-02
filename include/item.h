#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define M 10

typedef struct analise{
  int numTransLeitura;//numero de leitura da memória externa para memória interna
  int numTransEscrita;//numero de escrita da memória interna para memória externa
  int numComp;// número de comparações entre valores do campo de ordenação dos registros
  double time;//tempo e execução do método
}Analise;


typedef struct item{
  long int numInscricao;//Numero de insrição do aluno
  float notas;//Nota obtida pelo aluno, valor real entre 0.0 e 100.0
  char estado[3];// Estado do Aluno
  char cidade[50];// Cidade do Aluno
  char curso[30];//Curso do Aluno
}Item;

typedef struct dadospesquisa{
  int metodo;
  long int quant;
  int situacao;
  char op[3];
  Analise analise;
} DadosPesquisa;

void impreResultado(DadosPesquisa* );

void impremeDado(DadosPesquisa* );

#endif // ITEM_H
