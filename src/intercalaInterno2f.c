#include "../include/menu.h"
#include "../include/item.h"
#include "../include/intercalaInterno2f.h"
#include "../include/ordenar.h"
#include "../include/gerador.h"
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Procura o menor item dentro do vetor e retorna sua posição
int menorItem(Item *itens) {
    int pos, i;
    float menor = 9999999999999.9;
    for( i = 0; i < 20; i++){   
        if(itens[i].notas < menor && itens[i].notas >= 0.0){
            menor = itens[i].notas;
            pos = i;
        }
    }
    return pos;
}

//Abre os arquivos das fitas
int abreArquivos(FITAS *fitas, int familia){
    char nome[15];

    for(int k = 0; k < 20; k++){

        sprintf(nome, "fitas/f%i-%i", familia, k+1);
       
        fitas[k].quantItens = 0;
        fitas[k].ativa = 0;
        fitas[k].itensLido = 0;
        fitas[k].vazia = 1;
        fitas[k].file = fopen(nome, "w+b");
        if(fitas[k].file == NULL){
            printf("ERRO ao abrir arquivo F Fitas numero %i da familia %i", k+1, familia);
            exit(1);
        }
    }
    return 0;
}

//Fecha os arquivos das fitas e Exclui 
int fechaArquivos(FITAS *fitas, int familia){
    char nome[15];
    for(int k = 0; k < 20; k++){
        sprintf(nome, "fitas/f%i-%i", familia, k+1);
        fclose(fitas[k].file);
        remove(nome);
    }
    return 0;
}

//Coloca o ponteiro de todas as fitas no inicio
int setPonteiroFitas(FITAS *fitas){
    for(int i = 0; i < 20; i++){
        fseek(fitas[i].file, 0, SEEK_SET);
    }
    return 0;
}


//Etapa 1 do processo de intercalação balanceada
//Le o arquivo original e controi os blocos ordenados em cada fita
int etapa1(FILE *pFile, FITAS *fitas1, DadosPesquisa *entrada, Item *itens){
    int i = 0, k = 0;
    int quantLe = 20;
    
    while(i < entrada->quant){// Enquanto houver item executa
        
        if((entrada->quant - i) < 20 ){
            quantLe = (entrada->quant - i);
        }
        //LÊ os arquivos no arquivo original
        fread(itens, sizeof(Item), quantLe, pFile);
        entrada->analise.numTransLeitura++;
        i += quantLe;
        //Quicksort Interno para ordenar os itens
        ordenarItens(itens, quantLe, &entrada->analise);

        //Depois de ordenado escreve em uma das fitas indicada
        fwrite(itens, sizeof(Item), quantLe, fitas1[k].file);
        entrada->analise.numTransEscrita++;
        fitas1[k].ativa = 1;
        fitas1[k].vazia = 0;
        fitas1[k].quantItens += quantLe;
        
        //Se acabou as fitas inicia na primeira fita novamente para continuar escrevendo
        if(k == 19){
            k = 0;
        }else{
            k++;
        }
    }
    return 0;
}

//verifica quantas fitas ainda contem blocos e retorna a quantidade
int verificaSeOrdenacaoAcabou(FITAS *fitas){//retorna a quantidade de fitas com itens
    int cont = 0;
    for(int k = 0; k < 20; k++){
        if(fitas[k].vazia == 0){//se vazio é falsa quer dizer que ainda tem bloco na fita
            cont++;
        }
    }
    
    return cont;
}

//Verifica quantas fitas estão ativas e retorna a quantidade
int verificaSeAsFitasEstaoAtivas(FITAS *fitas){
    int cont = 0;
    for(int k = 0; k < 20; k++){
        if(fitas[k].ativa == 1){//se vazio é falsa quer dizer que ainda tem bloco na fita
            cont++;
        }
    }
    return cont;

}

//Reativa as ficas que contem itens
int reativaAsFitas(FITAS *fitas){
    
    for(int k = 0; k < 20; k++){
        
        fitas[k].itensLido = 0;
        if(fitas[k].quantItens > 0){
            fitas[k].ativa = 1;
            fitas[k].vazia = 0;
        }else if(fitas[k].quantItens <= 0){
            
            fitas[k].vazia = 1;
            fitas[k].ativa = 0;
        }
    }
    return 0;
}

//Preenche o vetor com um item de cada fita ativa
int preencheVetor(FITAS *fitas, Item *itens){
    
    for(int i = 0; i < 20;i++){
        if(fitas[i].ativa == 1 && fitas[i].vazia == 0){
            fread(&itens[i], sizeof(Item), 1, fitas[i].file);
            fitas[i].itensLido++;
            fitas[i].quantItens--;
        }else{
            itens[i].notas = -1;
        }
    }
    return 0;
}

FILE *intercala(FILE *pFile, FITAS *fitas1, FITAS *fitas2, DadosPesquisa *entrada, Item *itens){
    //Inicializa as variaveis contadoras
    int k = 0, i = 0, troca = 1, j;
    FITAS *fitasEntrada = fitas1;
    FITAS *fitasSaida = fitas2;
    int tamBloco = 20;//inicializa o tamanho do bloco
    int posMenor;
    
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
            
            preencheVetor(fitasEntrada, itens);//primeiro preenchimento do vetor
            entrada->analise.numTransLeitura += 20;
            
            while(verificaSeAsFitasEstaoAtivas(fitasEntrada)){//loop que controla a construção de cada bloco
            
                posMenor = menorItem(itens);
                entrada->analise.numComp += 20;
                
                fwrite(&itens[posMenor],sizeof(Item),1, fitasSaida[k].file);
                entrada->analise.numTransEscrita++;
                fitasSaida[k].quantItens++;
                fitasSaida[k].vazia = 0;
                
                i++;

                if(fitasEntrada[posMenor].itensLido >= tamBloco ){//se já tiver lido todos os itens do bloco desativa a fita
                    fitasEntrada[posMenor].ativa = 0;
                }
                if(fitasEntrada[posMenor].quantItens <= 0 || feof(fitasEntrada[posMenor].file) != 0){
                    fitasEntrada[posMenor].ativa = 0;
                    fitasEntrada[posMenor].vazia = 1;
                }

                if(fitasEntrada[posMenor].ativa == 1){//Verifica se a fita está ativa para poder ler
                    
                    fread(&itens[posMenor], sizeof(Item), 1, fitasEntrada[posMenor].file);//Le o novo valor da fita que vai para o vetor
                    entrada->analise.numTransLeitura++;
                    fitasEntrada[posMenor].itensLido++;
                    fitasEntrada[posMenor].quantItens--;
                }else{
                    itens[posMenor].notas = -1.0;//isso torna o item referente a esta posição e fita inativo
                }
            }
            if(k == 19){
                k = 0;
            }else{
                k++;
            }
            reativaAsFitas(fitasEntrada);
 
        }
        tamBloco = tamBloco*20;//multiplica a quantidade maxima do tamanho do proximo bloco que vai ser lido
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
int intercalaOrdenaInterno(FILE *pFile, FILE *pFile2, DadosPesquisa *entrada){
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
    mkdir("./fitas", 0755);//cria uma pasta para ficar as fitas
    
    //Incializa as fitas
    abreArquivos(fitas1, 1);
    abreArquivos(fitas2, 2);
    
    //ETAPA 1
    //1 é lido blocos de 20 registros e ordenados
    //2 cada bloco é colocado em uma fita seguindo a ordem até acabar as fitas

    etapa1(pFile, fitas1, entrada, itens);

    //ETAPA 2 É feito a intercalação dos itens na fitas até que reste somente uma fita com 1 unico bloco
    aux = intercala(pFile, fitas1, fitas2, entrada, itens);
    entrada->analise.time = (((double)clock()) - entrada->analise.time)/CLOCKS_PER_SEC;
    copiaFile(aux, pFile2, *entrada);//Copia o arquivo da fita que continha todo o bloco ordenado para o arquivo final
    fseek(pFile, 0, SEEK_SET);
    fseek(pFile2, 0, SEEK_SET);

    printf("\ntempo = %f", entrada->analise.time);
    printf("\nnumero de leituras %i", entrada->analise.numTransLeitura);
    printf("\nnumero de Escritas %i", entrada->analise.numTransEscrita);
    printf("\nnumero de Comparações %i\n", entrada->analise.numComp);

    //Fecha os arquivos fitas e apaga da memória
    fechaArquivos(fitas1, 1);
    fechaArquivos(fitas2, 2);
    //Apaga a pasta criada para ficar as fitas
    remove("./fitas");
    
    return 0;
}