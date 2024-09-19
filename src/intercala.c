#include "../include/intercala.h"
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

        sprintf(nome, "fitas2/f%i-%i", familia, k+1);
       
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
        sprintf(nome, "fitas2/f%i-%i", familia, k+1);
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
int preencheVetor(FITAS *fitas, Item *itens, DadosPesquisa *entrada){
    
    for(int i = 0; i < 20;i++){
        if(fitas[i].ativa == 1 && fitas[i].vazia == 0){
            fread(&itens[i], sizeof(Item), 1, fitas[i].file);
            entrada->analise.numTransLeitura++;
            fitas[i].itensLido++;
            fitas[i].quantItens--;
        }else{
            itens[i].notas = -1;
        }
    }
    return 0;
}
