#ifndef ARVOREB_H
#define ARVOREB_H
#include "../include/item.h"

//criando variável ponteiro do tipo página
typedef struct Pagina* Apontadores;

typedef struct Pagina {
    short quant;// quantidades de itens nos vetores 
    Item pai[(2*M)];// vetor de itens na página
    Apontadores filhos[(2*M) + 1]; // vetor de apontadores 
} Pagina; 

void inicializa(Apontadores* Arvore);
void pesquisar(Item* x, Apontadores Arvore, Analise*,bool*);
void insere(Item x, Apontadores* Arvore, Analise*); 
void ins(Item x,Apontadores Arvore, short *cresceu, Item* registroretorno, Apontadores* ApRetorno, Analise*);
void criaarvoreb(FILE *arquivo, Item *registro,DadosPesquisa* );
void inserenaPagina(Apontadores Arvore, Item dados, Apontadores ApDir, Analise*);
void imprimir(Item x); // impressão das informações da chave encontrada. 

#endif
