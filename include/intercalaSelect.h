#ifndef _INTERCALA_SELEC_H_
#define _INTERCALA_SELEC_H_

#include "item.h"
#include "intercala.h"

    FILE *intercala2(FILE *pFile, FITAS *fitas1, FITAS *fitas2, DadosPesquisa *entrada, Item *itens);
    int intercalaSubstituicao(FILE *pFile, FILE *pFile2, DadosPesquisa *entrada);
#endif