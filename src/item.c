#include "../include/item.h"

void imprimeDado(DadosPesquisa *dado, Item *entrada) {
    printf("|  Pré - Processamento: \n");
    printf("|  Quantidade de comparações no pré processamento = %d\n", dado->analise.comppre);
    printf("|  Quantidade de transferencias no Pré processamento = %d\n", dado->analise.transpre);
    printf("|  Tempo de execução do pré processamento = %lf segundos\n", dado->analise.timepre);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|  Pesquisa: \n");
    printf("|  Quantidade de comparações na pesquisa = %d\n", dado->analise.comppesquisa);
    printf("|  Quantidade de transferencias na pesquisa = %d\n", dado->analise.transpesquisa);
    printf("|  Tempo de execução na pesquisa = %lf segundos\n", dado->analise.timepesquisa);
    printf("-----------------------------------------------------------------------------------------\n");
}

void impreResultado(bool pesq,DadosPesquisa *dado,Item* entrada){

  if (pesq) {
    printf("\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|  Encontrou a Chave!  \n");
    printf("-----------------------------------------------------------------------------------------\n");
    imprimeDado(dado, entrada);
    printf("\n");
  } else {
    printf("\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|  Não encontrou a Chave!  \n");
    printf("-----------------------------------------------------------------------------------------\n");
    imprimeDado(dado, entrada);
    printf("\n");
  }
}
