#include "../include/item.h"
#include "../include/graficos.h"
void impPre(DadosPesquisa *dados);
void impPesq(DadosPesquisa *dados);

void impPre(DadosPesquisa *dados){
  //titulo 1
  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_VER);
  for(int i = 0;i <= 41;i++)printf(" ");
  printf(BOLD(YELLOW("Pré - Processamento:")));
  for(int i = 0;i < 45;i++)printf(" ");
  printf(TAB_VER"\n");

  //quantidade
  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_VER);
  for(int i = 0;i < 21;i++)printf(" ");
  printf("Quantidade de comparações no pré processamento = %-10d",dados->analise.comppre);
  for(int i = 0;i < 27;i++)printf(" ");
  printf(TAB_VER"\n");
  //transferencias
  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_VER);
  for(int i = 0;i < 21;i++)printf(" ");
  printf("Quantidade de transferencias no Pré-processamento = %-10d", dados->analise.transpre);
  for(int i = 0;i < 24;i++)printf(" ");
  printf(TAB_VER"\n");
  //tempo
  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_VER);
  for(int i = 0;i < 21;i++)printf(" ");
  printf("Tempo de execução do pré processamento = %-lf segundos", dados->analise.timepre);
  for(int i = 0;i < 28;i++)printf(" ");
  printf(TAB_VER"\n");
  //linha debaixo
  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_ML);
  for (int i = 0; i < 107; i++)printf(TAB_HOR);
  printf(TAB_MR"\n");

}

void impPesq(DadosPesquisa *dados){

  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_VER);
  for(int i = 0;i <= 46;i++)printf(" ");
  printf(BLUE(BOLD("Pesquisa: ")));
  for(int i = 0;i < 50;i++)printf(" ");
  printf(TAB_VER"\n");

  //quantidade
  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_VER);
  for(int i = 0;i < 21;i++)printf(" ");
  printf("Quantidade de comparações na pesquisa = %-10d", dados->analise.comppesquisa);
  for(int i = 0;i < 36;i++)printf(" ");
  printf(TAB_VER"\n");
  //transferencias
  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_VER);
  for(int i = 0;i < 21;i++)printf(" ");
  printf("Quantidade de transferencias na pesquisa = %-10d", dados->analise.transpesquisa);
  for(int i = 0;i < 33;i++)printf(" ");
  printf(TAB_VER"\n");
  //tempo
  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_VER);
  for(int i = 0;i < 21;i++)printf(" ");
  printf("Tempo de execução na pesquisa = %-lf segundos", dados->analise.timepesquisa);
  for(int i = 0;i < 37;i++)printf(" ");
  printf(TAB_VER"\n");
  //linha debaixo
  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_BL);
  for (int i = 0; i < 107; i++)printf(TAB_HOR);
  printf(TAB_BR"\n");
}
void imprimeDado(DadosPesquisa *dado, Item *entrada) {

  impPre(dado);
  impPesq(dado);
  
}

void impreResultado(bool pesq,DadosPesquisa *dado,Item* entrada){
  
  printf("\n");
  for(int i = 0;i<=54;i++)printf(" ");
  printf(TAB_TL);
  for (int i = 0; i < 107; i++){
    printf(TAB_HOR);
  }
  printf(TAB_TR"\n");

  if (pesq) {
    //escrita
    for(int i = 0;i<=54;i++)printf(" ");
    printf(TAB_VER);
    for (int i = 0; i < 107; i++)printf(" ");
    printf(TAB_VER"\n");
    for(int i = 0;i<=54;i++)printf(" ");
    printf(TAB_VER);
    for (int i = 0; i < 42; i++)printf(" ");
    printf(GREEN(BOLD(" Encontrou a Chave!")));
    for (int i = 0; i < 46; i++)printf(" ");
    printf(TAB_VER"\n");
    for(int i = 0;i<=54;i++)printf(" ");
    printf(TAB_VER);
    for (int i = 0; i < 107; i++)printf(" ");
    printf(TAB_VER"\n");
    //linha debaixo
    for(int i = 0;i<=54;i++)printf(" ");
    printf(TAB_ML);
    for (int i = 0; i < 107; i++)printf(TAB_HOR);
    printf(TAB_MR"\n");
    imprimeDado(dado, entrada);
    printf("\n");
  } else {
    for(int i = 0;i<=54;i++)printf(" ");
    printf(TAB_VER);
    for (int i = 0; i < 107; i++)printf(" ");
    printf(TAB_VER"\n");
    for(int i = 0;i<=54;i++)printf(" ");
    printf(TAB_VER);
    for (int i = 0; i < 40; i++)printf(" ");
    printf(RED(BOLD("Não encontrou a Chave!")));
    for (int i = 0; i <= 44; i++)printf(" ");
    printf(TAB_VER"\n");
    for(int i = 0;i<=54;i++)printf(" ");
    printf(TAB_VER);
    for (int i = 0; i < 107; i++)printf(" ");
    printf(TAB_VER"\n");
    //linha debaixo
    for(int i = 0;i<=54;i++)printf(" ");
    printf(TAB_ML);
    for (int i = 0; i < 107; i++)printf(TAB_HOR);
    printf(TAB_MR"\n");
    imprimeDado(dado, entrada);
    printf("\n");
  }
}