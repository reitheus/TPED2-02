#include <stdio.h>
#include "../include/pesquisaBinariaInterna.h"

void dicionarioInicio(Dicionario *dicio, int maximo, Item *x){
    dicio->n = 0;
    dicio->max = maximo;
    dicio->v = x;

}


int DicionarioBinariaCrescente( Dicionario *dicio , int esq , int dir , int chave) {
    int meio = ( esq + dir )/2;

    if( dicio->v[meio].chave != chave && esq == dir )
        return -1;
    else if( chave > dicio->v[ meio ].chave )
        return DicionarioBinariaCrescente( dicio , meio + 1 , dir , chave);
    else if( chave < dicio->v[ meio ].chave )
        return DicionarioBinariaCrescente( dicio , esq , meio - 1 , chave);
    else
        return meio ;
}
int DicionarioBinariaDecrescente( Dicionario *dicio , int esq , int dir , int chave) {
    int meio = ( esq + dir )/2;

    if( dicio->v[meio].chave != chave && esq == dir )
        return -1;
    else if( chave < dicio->v[ meio ].chave )
        return DicionarioBinariaDecrescente( dicio , meio + 1 , dir , chave);
    else if( chave > dicio->v[ meio ].chave )
        return DicionarioBinariaDecrescente( dicio , esq , meio - 1 , chave);
    else
        return meio ;
}

int pesquisaSequencialInterna(Dicionario *dicio , int chave){

    for (int i=0; i < dicio->max; i++){
        if(dicio->v[i].chave == chave) {
            return i; 
        }
    }
    return -1;

}

int dicionarioFind( Dicionario *dicio , int situation, int chave) {
    if(situation == 1){
        return DicionarioBinariaCrescente(  dicio , 0 , dicio->max - 1 , chave); // dicio->max é o tamanho
        
    }else if(situation == 2){
        return DicionarioBinariaCrescente( dicio , 0 , dicio->max - 1 , chave);
    }else{
        return pesquisaSequencialInterna(dicio ,chave);
    }
}
