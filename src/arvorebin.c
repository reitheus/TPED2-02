#include "../include/arvorebin.h"

// cria uma arvore em memoria externa
void criaArvoreBin(FILE *arvoreBin, FILE *arquivo,Analise *dado) {
    dado->timepre = (double)clock();
    if (arvoreBin == NULL || arquivo == NULL) {
        printf("Erro no arquivo\n");
        return;
    }
    Registro aux, aux1;
    Item info;
    int att, cont;
    dado->transpre += 1;
    while (fread(&info, sizeof(Item), 1, arquivo) == 1) {
        att = 0;
        aux.dir = -1;
        aux.esq = -1;
        aux.key = info;
        fseek(arvoreBin, 0, SEEK_END);
        dado->transpre += 1;
        fwrite(&aux, sizeof(Registro), 1, arvoreBin);
        cont = ftell(arvoreBin);
        fseek(arvoreBin, 0, SEEK_SET);
        dado->comppre += 3;
        while (att == 0) {
            dado->transpre += 1;
            if (fread(&aux1, sizeof(Registro), 1, arvoreBin) == 1) {
                if (aux.key.chave < aux1.key.chave) {
                    if (aux1.esq == -1) {
                        att = 1;
                        aux1.esq = cont;
                        dado->comppre += 1;
                    } else {
                        dado->comppre += 1;
                        fseek(arvoreBin, sizeof(Registro) * aux1.esq, 0);
                    }
                } else if (aux.key.chave > aux1.key.chave) {
                    if (aux1.dir == -1) {
                        att = 1;
                        aux1.dir = cont;
                        dado->comppre += 1;
                    } else {
                        dado->comppre += 1;
                        fseek(arvoreBin, sizeof(Registro) * aux1.dir, 0);
                    }
                }
            } else {
                att = 1;
            }

        }
    }
    dado->timepre = (double) ((clock() - dado->timepre)/CLOCKS_PER_SEC);
}

// Pesquisa da Arvore binaria de pesquisa em memoria externa
bool pesquisaArvoreBin(FILE *arvoreBin, int chaveP, Analise *dado, Registro *aux,long *quant) {
    int i = 0;
    dado->timepesquisa = (double)clock();
    dado->transpesquisa += 1;
    fseek(arvoreBin, 0, SEEK_SET);
    while (fread(aux, sizeof(Registro), 1, arvoreBin) == 1 && i < *quant) {
        dado->transpesquisa += 1;
        if (aux->key.chave != chaveP) {
            if (chaveP < aux->key.chave) {
                dado->comppesquisa += 1;
                fseek(arvoreBin,0 , sizeof(Registro) * aux->esq);
            }
            if (chaveP > aux->key.chave) {
                dado->comppesquisa += 1;
                fseek(arvoreBin,0 ,sizeof(Registro) * aux->dir);
            }
        }
        if (aux->key.chave == chaveP) {
            if (dado->comppesquisa == 0) {
                dado->comppesquisa += 1;
            }
            dado->timepesquisa = (double)((clock() - dado->timepesquisa)/CLOCKS_PER_SEC);
            return true;
        }
        i++;
    }
    dado->timepesquisa = (double)((clock() - dado->timepesquisa)/CLOCKS_PER_SEC);
    return false;
}

void arvoreBinaria(FILE *arquivo, long int *quantidade, int *chave,DadosPesquisa *dado) {
    FILE *arvoreBin = fopen("ArvoreBin.bin", "w+b");
    Registro entrada;
    criaArvoreBin(arvoreBin, arquivo, &dado->analise);
    bool pesquisa = pesquisaArvoreBin(arvoreBin, *chave, &dado->analise, &entrada,quantidade);
    fclose(arvoreBin);
    impreResultado(pesquisa,dado,&entrada.key);    
}
