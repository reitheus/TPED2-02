#include "../include/menu.h"
#include "../include/item.h"
#include "../include/sequencial.h"
#include "../include/arvorebin.h"
#include "../include/arvoreb.h"
#include "../include/arvorebEst.h"
#include <ctype.h>
#include <string.h>

#define NITENS 150

int erros() {
  printf("Formato incorreto!\n");
  printf("Formatos:\n");
  printf("pesquisar <método> <quantidade> <situacao> <chave> [-P]\n");
  printf("  <método> Método de Pesquisa Externa\n");
  printf("  <quantidade> quantidade de registros a serem gerados\n");
  printf("  <situacao> 1 (arquivo ordenado ascendentemente)\n");
  printf("             2 (arquivo ordenado descendentemente)\n");
  printf("             3 (arquivo ordenado aleatoriamente)\n");
  printf("\n\n");
  printf("<chave> Item a ser pesquisdo\n");
  printf("[-p] Para mostrar os itens pesquisados\n");
  return 0;
}

int printArquivo(int tam, FILE * pFile){
  int quant = NITENS;
  Item vetor[NITENS];
  fseek(pFile, 0, SEEK_SET);//coloca o ponteiro no inicio do aquivo

  while(tam > 0){
    
    if(tam < NITENS){
      quant = tam;
    }
    tam -= quant;

    fread(vetor,sizeof(Item), quant, pFile);
    //fseek(pFile, NITENS, SEEK_CUR);
    for(int i = 0; i < quant; i++){
      printf("Item %i\n", vetor[i].chave);
    }
  }
    

  return 0;
}


int menu(int argc, char **argv) {
  /*
    argv[0] nome do executavel - pesquisa
    argv[1] método de pesquisa externa - 1 a 4
    argv[2] Representa a quantidade de arquivos a ser considerado -  1 a 1000000
    argv[3] Representa a situação da ordem do arquivo - 1 a 3
    argv[4] A chave que vai ser pesquisada - 1 a descohecido
    argv[5] Opcional se vai aparecer as chaves e pesquisa - p
  */

  FILE *pFile;
  Item x;
  DadosPesquisa entrada;
  entrada.metodo = atoi(argv[1]);
  entrada.quant = atoi(argv[2]);
  entrada.situacao = atoi(argv[3]);
  entrada.chave = atoi(argv[4]);
  //Zera as variaveis que contam e analisam o desempenho
  
  entrada.analise.comppesquisa = 0;
  entrada.analise.transpre = 0;
  entrada.analise.transpesquisa = 0;
  entrada.analise.comppre = 0;



  if(argc == 6){
    strcpy(entrada.op, argv[5]);
  }

  if(argc < 5 || argc > 6 || entrada.metodo < 1 || entrada.metodo > 5 || entrada.quant < 1){// Verifica se a quantidade de parametros está correta
    printf("\nErro 1\n");
   
    erros();
    return 0;
  }else if(entrada.situacao < 1 || entrada.situacao > 3 || entrada.chave < 0 ){
    printf("Erro 2");
    erros();
    return 0;
  }else if( (strcmp(entrada.op, "-P") != 0 && strcmp(entrada.op, "-p") != 0) && argc == 6){
    printf("Erro 3");
    erros();
    return 0;
  }
  if(entrada.metodo != 5){
    switch(entrada.situacao){
      case 1:
        pFile = fopen("ascendente.bin", "rb");
      break;
      case 2:
        pFile = fopen("descendente.bin", "rb");
      break;
      case 3:
        pFile = fopen("aleatorio.bin", "rb");
      break;
      default:
        printf("\nOpção incorreta\n");
    
    }
  }
  
  switch(entrada.metodo){
    case 1:
      acessoSequencial(pFile, entrada.quant, entrada.situacao, &x, entrada.chave, &entrada);
     
    break;
    case 2:
      arvoreBinaria(pFile,&entrada.quant,&entrada.chave,&entrada);
    break;
    case 3:
      criaarvoreb(pFile,&x,&entrada);
    break;
    case 4:
      criaarvoreBE(pFile,&x,&entrada);
    break;
    case 5:
      gerar(pFile, entrada);
    break;

    default:
      printf("\nOpção invalida\n");

  }

if((strcmp(entrada.op, "-P") == 0 || strcmp(entrada.op, "-p") == 0) && entrada.metodo != 5){
  printArquivo(entrada.quant, pFile);
}

  if(entrada.metodo != 5){
    fclose(pFile);
  }

  return 0;
}
