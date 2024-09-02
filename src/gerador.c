#include "../include/menu.h"
#include "../include/item.h"
#include "../include/sequencial.h"


//função cria arquivo crescente (arquivo por ponteiro, struct entrada com dados do arquivo)
int geradorAscendente(FILE *pFile, DadosPesquisa entrada){

    Item v;

    for(int i = 0; i < entrada.quant; i++){
        
        v.chave = i;
        v.dado1 = rand();

        fwrite(&v, sizeof(Item), 1, pFile);
        
    }

    return 0;
}
//função cria arquivo descrescente (arquivo por ponteiro, struct entrada com dados do arquivo)

int geradorDescendente(FILE *pFile, DadosPesquisa entrada){

    Item v;

    for(int i = entrada.quant; i > 0; i--){
        
        v.chave = i;
        v.dado1 = rand();
     
        fwrite(&v, sizeof(Item), 1, pFile);
        
    }

    return 0;
}
//função cria arquivo aleatorio (arquivo por ponteiro, struct entrada com dados do arquivo)

int geradorAleatoriamente(FILE *pFile, DadosPesquisa entrada){
    srand(time(0));
    Item *v;
    int tamV;
    int j = 0;
    int x = 0;
    int i = 0;
    int randon;
    int quantTemp = entrada.quant;
    int escreveQuant;

    if(entrada.quant <= 10){
        tamV = entrada.quant;
    }else if(entrada.quant > 10 && entrada.quant <= 100){
        tamV = 10;
    }else if(entrada.quant > 100 ){
        tamV = 100;
    }

    v = malloc(tamV * sizeof(Item));
    
    escreveQuant = tamV;
    randon = rand() % tamV;
    while( i < entrada.quant ){
        if(quantTemp < tamV){//se a quantidade de itens for menor do que a o maximo do vetor o 
            tamV = quantTemp;

        }
        for(j = 0; j < tamV; j++){//zera o vetor
            v[j].chave = 0;
        }
        escreveQuant = tamV;
        x += tamV;
        quantTemp -= tamV;

        
        
        while(i < x){//enquanto não colocar todos os nḿeros no vetor repete o vetor

            while(v[randon].chave != 0){//escolhe um lugar aeatorio no vetor para colocar o numero
                randon = rand() % tamV;
                
            }
            
            v[randon].chave = i;
            randon = rand() % tamV;

            i++;
        }

       
        fwrite(v, sizeof(Item), escreveQuant, pFile);
        
    }

   
    free(v);
    return 0;
}


//arquivo que vai ser gerado por stream, Os dados de entrada
int gerar(FILE *pFile, DadosPesquisa entrada){

    switch(entrada.situacao){
        case 1:
            pFile = fopen("ascendente.bin", "wb");
            geradorAscendente(pFile,  entrada);
            fclose(pFile);
        break;
        case 2:
            pFile = fopen("descendente.bin", "wb");
            geradorDescendente(pFile,  entrada);
            fclose(pFile);
        break;
        case 3:
            pFile = fopen("aleatorio.bin", "wb");
            geradorAleatoriamente(pFile,  entrada);

            fclose(pFile);
        break;
        default:
        printf("\nOpção incorreta\n");

    }


    return 0;

}



