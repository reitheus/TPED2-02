#include "../include/menu.h"
#include "../include/item.h"
#include "../include/quicksortE.h"
#include "../include/intercalaInterno2f.h"
#include <ctype.h>
#include <string.h>

#define NITENS 150

int erros() {
  printf("Formato incorreto!\n");
  printf("Formatos:\n");
  printf("ordena <método> <quantidade> <situacao> [-P]\n");
  printf("  <método> Método de Pesquisa Externa\n");
  printf("  <quantidade> quantidade de registros a serem gerados\n");
  printf("  <situacao> 1 (arquivo ordenado ascendentemente)\n");
  printf("             2 (arquivo ordenado descendentemente)\n");
  printf("             3 (arquivo desordenado aleatoriamente)\n");
  printf("\n\n");
  printf("[-p] Para mostrar os do arquivo\n");
  return 0;
}

int printArquivo(int tam, FILE *pFile){
  int quant = 50;
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
      printf("\nItem notas %.1f estado %s curso %s ", vetor[i].notas, vetor[i].estado, vetor[i].curso);
      //printf("\nItem notas %.1f curso %s ", vetor[i].notas, vetor[i].curso);

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

  FILE *pFile, *pFile2 = NULL;
  //Item x;
  DadosPesquisa entrada;
  entrada.metodo = atoi(argv[1]);
  entrada.quant = atoi(argv[2]);
  entrada.situacao = atoi(argv[3]);
  //Zera as variaveis que contam e analisam o desempenho
  
  entrada.analise.numTransLeitura = 0;
  entrada.analise.numTransEscrita = 0;
  entrada.analise.numComp = 0;
  entrada.analise.time = 0.0;

  if(argc == 5){
    strcpy(entrada.op, argv[4]);
  }

  if(argc < 4 || argc > 5 || entrada.metodo < 1 || entrada.metodo > 4 || entrada.quant < 1){// Verifica se a quantidade de parametros está correta
    printf("\nErro 1\n");
   
    erros();
    return 0;
  }else if(entrada.situacao < 1 || entrada.situacao > 3){
    printf("Erro 2");
    erros();
    return 0;
  }else if( (strcmp(entrada.op, "-P") != 0 && strcmp(entrada.op, "-p") != 0) && argc == 5){
    printf("Erro 3");
    erros();
    return 0;
  }
  
  if(entrada.metodo != 4){
    switch(entrada.situacao){
      case 1:
        pFile = fopen("ascendente.bin", "rb");
        if(pFile == NULL){
          printf("Arquivo não encontrado, primeiro gere o arquivo ascendente.bin\n");
          printf("Para gerar o arquivo utilize  opção 4, Gere o arquivo aleatorio depois gere o arquivo Ascendente");

        }
      break;
      case 2:
        pFile = fopen("descendente.bin", "rb");
        if(pFile == NULL){
          printf("Arquivo não encontrado, primeiro gere o arquivo ascendente.bin\n");
          printf("Para gerar o arquivo utilize  opção 4, Gere o arquivo aleatorio,\n depois gere o arquivo Ascendente,\n depois Gere o arquivo descendente");

        }
      break;
      case 3:
        pFile = fopen("aleatorio.bin", "rb");
        if(pFile == NULL){
          printf("Arquivo não encontrado, primeiro gere o arquivo ascendente.bin\n");
          printf("Para gerar o arquivo utilize  opção 4, Gere o arquivo aleatorio");

        }
      break;
      default:
        printf("\nOpção incorreta\n");
    
    }
  }
  


  switch(entrada.metodo){
    case 1:
      pFile2 = fopen("ordenado.bin","w+b");
      intercalaOrdenaInterno(pFile, pFile2, &entrada);
      
    break;
    case 2:
      //intercalaSelecao();
    break;
    case 3:
      pFile2 = fopen("ordenado.bin","r+b");
      copiaFile(pFile, pFile2, entrada);
      fseek(pFile, 0, SEEK_SET);
      fseek(pFile2, 0, SEEK_SET);
      quick(pFile2, &entrada);
      //quicksort();
    break;
    case 4:
      
      converte(pFile, entrada);
    break;

    default:
      printf("\nOpção invalida\n");

  }
  if(entrada.metodo != 4){
    conversorBinToTxt(pFile2, entrada);
  }

  if((strcmp(entrada.op, "-P") == 0 || strcmp(entrada.op, "-p") == 0) && entrada.metodo != 5){
    printf("\nArquivo Original");
    printArquivo(entrada.quant, pFile);
    printf("\n-----------------------------------------\n");
    printf("\nArquivo Ordenado");
    printArquivo(entrada.quant, pFile2);
  }

  if(entrada.metodo != 4){
    fclose(pFile);
    fclose(pFile2);
  }

  return 0;
}
