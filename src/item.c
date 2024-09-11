#include "../include/item.h"

void imprimeDado(DadosPesquisa *dado, Item *entrada) {
    printf("|  Pré - Processamento: \n");
    printf("|  Quantidade de transferencias Leitura = %d\n", dado->analise.numTransLeitura);
    printf("|  Quantidade de transferencias Escrita = %d\n", dado->analise.numTransEscrita);
    printf("|  Quantidade de Comparações = %d \n", dado->analise.numComp);
    printf("|  Tempo de execução = %lf \n", dado->analise.time);
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
  }else {
    printf("\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("|  Não encontrou a Chave!  \n");
    printf("-----------------------------------------------------------------------------------------\n");
    imprimeDado(dado, entrada);
    printf("\n");
  }
}
