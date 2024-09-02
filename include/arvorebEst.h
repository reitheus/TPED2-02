#ifndef ARVOREBEST_H
#define ARVOREBEST_H

#include "../include/item.h"

typedef int TipoChave;
typedef enum {Interna, Externa} TipoIntExt;

typedef struct tipopagina{
    TipoIntExt Pt;//ponteiro de controle de no
    union folha{
        struct interno{//interno
            int quant;//ni
            TipoChave pai[2 * M];//ri
            struct tipopagina *filho[2 * M + 1];//pi
        }U0;//indice
        struct externo{//externo
            int ne;//quantida externo
            Item re[2 * M];//Vetor de itens
            struct tipopagina *prox;
            
        }U1;//folha
    }UU;//união
    
} TipoPagina;//arvore

void iniciaArvoreBE(TipoPagina** );
void liberaArvoreBE(TipoPagina** );
void pesquisaArvorebEst(Item* ,TipoPagina* ,Analise* ,bool *);
void inserenaPaginaBI(TipoPagina* ,TipoChave ,TipoPagina* ,Analise*);
void inserenaPaginaBE(TipoPagina* ,Item* ,Analise* );
void insBE(Item* ,TipoPagina* ,short* ,TipoChave* ,TipoPagina** ,Analise* );
void insereBE(Item* ,TipoPagina** ,Analise* );
void criaarvoreBE(FILE *, Item *, DadosPesquisa *);

#endif// arvorebEst.h
