#ifndef SEQUENCIAL_H
#define SEQUENCIAL_H
#include "../include/item.h"
#include "../include/pesquisaBinariaInterna.h"

bool pesquisaSequencial(int*, int , Item* , FILE*, int , int , int , DadosPesquisa* );

//Parametros: arquivo, quantidade de itens no arquivo, situação, Item passado por poteiro,chave que vai ser pesquisada
void acessoSequencial(FILE *, int , int , Item *, int , DadosPesquisa *);

#endif // SEQUENCIAL_H


