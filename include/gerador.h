 #include <ctype.h>
#include <string.h>
#include <math.h>
#include "../include/item.h"

#ifndef GERADOR_H
#define GERADOR_H

//converte um arquivo binario para TXT e o nomeia como ordenado.txt
//parametros: arquivo binario, dados de entrada
int conversorBinToTxt(FILE *pFile, DadosPesquisa entrada);

//arquivo que vai ser gerado por stream, Os dados de entrada
int converte(FILE *, DadosPesquisa );




#endif // GERADOR_H