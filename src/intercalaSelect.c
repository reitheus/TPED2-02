#include "../include/menu.h"
#include "../include/item.h"
#include "../include/intercalaInterno2f.h"
#include "../include/ordenar.h"
#include "../include/gerador.h"
#include "../include/intercala.h"
#include "../include/intercalaSubstit.h"
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE *intercala2(FILE *pFile, FITAS *fitas1, FITAS *fitas2, DadosPesquisa *entrada, Item *itens){
    //Inicializa as variaveis contadoras
    int k = 0, i = 0, troca = 1, j;
    FITAS *fitasEntrada = fitas1;
    FITAS *fitasSaida = fitas2;
    int posMenor;
    Item auxiliar;
    auxiliar.notas = -1;
    
    //coloca os ponteiros das fitas no inicio
    setPonteiroFitas(fitas1);
    setPonteiroFitas(fitas2);

    while(!(verificaSeOrdenacaoAcabou(fitasSaida) == 1)){//Verifica a quantidade de fitas com blocos se for igual a 1 termina o loop
        
        //seleiona qual cojunto de fitas vai ser as fitas de entrada no momento
        if( troca == 1){//se troca = 1 fitas 1 vai ser as fitas de entrada
            fitasEntrada = fitas1;
            fitasSaida = fitas2;
            troca = troca*(-1);
        }else if(troca == -1){//se troca = -1 fitas 2 vai ser as fitas de entrada
            fitasEntrada = fitas2;
            fitasSaida = fitas1;
            troca = troca*(-1);
        }
        reativaAsFitas(fitasEntrada);//Reativa as fitas que contem itens para uso
        setPonteiroFitas(fitasEntrada);
        setPonteiroFitas(fitasSaida);
        k = 0;
        i = 0;
        while(i < entrada->quant - 1){//Enquanto houver itens para ser intercalos vão gerar novos blocos nas itas de saida
            
            preencheVetor(fitasEntrada, itens, entrada);//primeiro preenchimento do vetor
            
            while(verificaSeAsFitasEstaoAtivas(fitasEntrada)){//loop que controla a construção de cada bloco
                
                posMenor = menorItem(itens);
                entrada->analise.numComp += 20;
                
                fwrite(&itens[posMenor],sizeof(Item),1, fitasSaida[k].file);
                entrada->analise.numTransEscrita++;
                fitasSaida[k].quantItens++;
                fitasSaida[k].vazia = 0;
                
                i++;

                if(feof(fitasEntrada[posMenor].file) != 0){
                    fitasEntrada[posMenor].ativa = 0;
                    fitasEntrada[posMenor].vazia = 1;
                 }

                if(fitasEntrada[posMenor].ativa == 1){//Verifica se a fita está ativa para poder ler
                    
                    fread(&itens[posMenor], sizeof(Item), 1, fitasEntrada[posMenor].file);//Le o novo valor da fita que vai para o vetor
                    entrada->analise.numTransLeitura++;
                    fitasEntrada[posMenor].quantItens--;
                    if(itens[posMenor].notas == -1){
                        
                        fitasEntrada[posMenor].ativa = 0;
                    }

                }else{
                    itens[posMenor].notas = -1.0;//isso torna o item referente a esta posição e fita inativo
                }
                
            }
            fwrite(&auxiliar,sizeof(Item),1, fitasSaida[k].file);
            if(k == 19){
                k = 0;
            }else{
                k++;
            }
            reativaAsFitas(fitasEntrada);
            
 
        }
        reativaAsFitas(fitasSaida);
        
    }
    
    setPonteiroFitas(fitasSaida);
   
    //Encontra em qual fita está o Bloco final ordenado
    for( j = 0; j < 20; j++){
        
        if(fitasSaida[j].vazia == 0){
            break;
        }
    }
  return fitasSaida[j].file;// Retorna a Fita ordenada

}

//Parametros: Arquivo original que vai ser ordenado, arquivo que foi ordenado, Dados de entrada
int intercalaSubstituicao(FILE *pFile, FILE *pFile2, DadosPesquisa *entrada){
    //inicializa as variaveis de analise
    entrada->analise.numTransEscrita = 0;
    entrada->analise.numTransLeitura = 0;
    entrada->analise.numComp = 0;
    entrada->analise.time = (double)clock();
    Item itens[20];//cria um vetor que contem 20 itens
    //cria os vetores de fitas
    FITAS fitas1[20];
    FITAS fitas2[20];
    FILE *aux;

    //abre os 40 arquivos
    mkdir("./fitas2", 0755);//cria uma pasta para ficar as fitas
    
    //Incializa as fitas
    abreArquivos(fitas1, 1);
    abreArquivos(fitas2, 2);
    
    //ETAPA 1
    //Cria os blocos pelo étodo de seleção por sustituição

    criacaoBlocosOrdenados(pFile, entrada->quant, fitas1);
    printf("saiu");
    //ETAPA 2 É feito a intercalação dos itens na fitas até que reste somente uma fita com 1 unico bloco
    aux = intercala2(pFile, fitas1, fitas2, entrada, itens);
    entrada->analise.time = (((double)clock()) - entrada->analise.time)/CLOCKS_PER_SEC;
    copiaFile(aux, pFile2, *entrada);//Copia o arquivo da fita que continha todo o bloco ordenado para o arquivo final
    fseek(pFile, 0, SEEK_SET);
    fseek(pFile2, 0, SEEK_SET);

    //Fecha os arquivos fitas e apaga da memória
    fechaArquivos(fitas1, 1);
    fechaArquivos(fitas2, 2);
    //Apaga a pasta criada para ficar as fitas
    remove("./fitas2");
    
    return 0;
}