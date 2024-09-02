#ifndef PESQUISABINARIAINTERNA_H
#define PESQUISABINARIAINTERNA_H
#include "../include/item.h"
#include "../include/sequencial.h"

typedef struct {
    Item *v;
    int n , max ;
 } Dicionario;

//Inicialização do dicionario para pesquisa
//ponteiro do dicionario, tamanho do vetor, vetor
void dicionarioInicio(Dicionario*, int , Item*);

int dicionarioFind( Dicionario* , int , int ); 


#endif // PESQUISABINARIAINTERNA_H


