#ifndef ARVOREBIN_H
#define ARVOREBIN_H

#include "../include/item.h"


typedef struct registro{
    Item key;
    int dir;
    int esq;
}Registro;

//Função do tipo void que recebe o arquivo de entrada, a quantidade de itens do arquivo, a chave que vai ser pesquisada e a estrutura de analise.
void arvoreBinaria(FILE* ,long int* ,int* ,DadosPesquisa* );

//Função do tipo void que recebe o arquivo que vai ser colocado a arvore, o arqiuvo de entrada, a quantidade de itens e a struct de analise;
void criaArvoreBin(FILE* ,FILE* ,Analise* );

//Fenção do tipo bool que retorna se foi achado ou não a chave, recebe o arquivo da arvore, a chave a ser pesquisada e um ponteiro para a struct de analise e de registro como função auxliar.
bool pesquisaArvoreBin(FILE* ,int ,Analise* ,Registro* ,long int* );

#endif // arvorebin.h