#include "../include/item.h"
#include "../include/graficos.h"

void impPesq(DadosPesquisa *dados);

void impPesq(DadosPesquisa *dados){

  printf(TAB_VER);
  for(int i = 0;i <= 43;i++)printf(" ");
  printf(BLUE(BOLD("Ordenção: ")));
  for(int i = 0;i < 46;i++)printf(" ");
  printf(TAB_VER"\n");

  //quantidade
  printf(TAB_VER);
  for(int i = 0;i < 25;i++)printf(" ");
  printf("Quantidade de comparações na ordenação = %-10d", dados->analise.numComp);
  for(int i = 0;i < 24;i++)printf(" ");
  printf(TAB_VER"\n");
  //transferencias
  printf(TAB_VER);
  for(int i = 0;i < 25;i++)printf(" ");
  printf("Quantidade de transferencias na leitura = %-10d", dados->analise.numTransLeitura);
  for(int i = 0;i < 23;i++)printf(" ");
  printf(TAB_VER"\n");
  //transferencias
  printf(TAB_VER);
  for(int i = 0;i < 25;i++)printf(" ");
  printf("Quantidade de transferencias na escrita = %-10d", dados->analise.numTransEscrita);
  for(int i = 0;i < 23;i++)printf(" ");
  printf(TAB_VER"\n");
  //tempo
  printf(TAB_VER);
  for(int i = 0;i < 25;i++)printf(" ");
  printf("Tempo de execução na pesquisa = %-lf segundos", dados->analise.time);
  for(int i = 0;i < 26;i++)printf(" ");
  printf(TAB_VER"\n");
  //linha debaixo
  printf(TAB_BL);
  for (int i = 0; i < 100; i++)printf(TAB_HOR);
  printf(TAB_BR"\n");
}

void impreResultado(DadosPesquisa *dado){
  
  printf("\n");
  printf(TAB_TL);
  for (int i = 0; i < 100; i++){
    printf(TAB_HOR);
  }
  printf(TAB_TR"\n");

  switch(dado->metodo){
    case 1:
      //escrita
      printf(TAB_VER);
      for (int i = 0; i < 100; i++)printf(" ");
      printf(TAB_VER"\n");
      printf(TAB_VER);
      for (int i = 0; i < 34; i++)printf(" ");//34
      printf(YELLOW(BOLD("Ordenação Intercação interna")));
      for (int i = 0; i < 38; i++)printf(" ");//38
      printf(TAB_VER"\n");
      printf(TAB_VER);
      for (int i = 0; i < 100; i++)printf(" ");
      printf(TAB_VER"\n");
      //linha debaixo
      printf(TAB_ML);
      for (int i = 0; i < 100; i++)printf(TAB_HOR);
      printf(TAB_MR"\n");
      impPesq(dado);
      printf("\n");
    break;
    case 2:
      //escrita
      printf(TAB_VER);
      for (int i = 0; i < 100; i++)printf(" ");
      printf(TAB_VER"\n");
      printf(TAB_VER);
      for (int i = 0; i < 34; i++)printf(" ");
      printf(CYAN(BOLD("Ordenação Intercação por seleção")));
      for (int i = 0; i < 34; i++)printf(" ");
      printf(TAB_VER"\n");
      printf(TAB_VER);
      for (int i = 0; i < 100; i++)printf(" ");
      printf(TAB_VER"\n");
      //linha debaixo
      printf(TAB_ML);
      for (int i = 0; i < 100; i++)printf(TAB_HOR);
      printf(TAB_MR"\n");
      impPesq(dado);
      printf("\n");
    break;
    case 3:
      //escrita
      printf(TAB_VER);
      for (int i = 0; i < 100; i++)printf(" ");
      printf(TAB_VER"\n");
      printf(TAB_VER);
      for (int i = 0; i < 34; i++)printf(" ");
      printf(GREEN(BOLD(" Ordenação Quicksort Externo")));
      for (int i = 0; i < 38; i++)printf(" ");
      printf(TAB_VER"\n");
      printf(TAB_VER);
      for (int i = 0; i < 100; i++)printf(" ");
      printf(TAB_VER"\n");
      //linha debaixo
      printf(TAB_ML);
      for (int i = 0; i < 100; i++)printf(TAB_HOR);
      printf(TAB_MR"\n");
      impPesq(dado);
      printf("\n");
    break;
    default:
    break;    
    
  }
}