#include "../include/arvoreb.h"
#include "../include/item.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void inicializa(Apontadores* Arvore) { // Cria apontador para a árvore
    *Arvore = NULL;
    printf("Arvore inicializada\n");
}

void liberaPagina(Apontadores Ap) { // Função recursiva para liberar cada nodo da árvore
    if (Ap != NULL) {
        for (int i = 0; i <= Ap->quant; i++) {
            liberaPagina(Ap->filhos[i]);
        }
        free(Ap);
    }
}

void liberaArvore(Apontadores *Arvore) {
    if (*Arvore != NULL) {
        liberaPagina(*Arvore); // Chamada para função recursiva
        *Arvore = NULL;
    }
}

// Insere os registros nas páginas
void inserenaPagina(Apontadores Arvore, Item dados, Apontadores ApDir, Analise* analise) {
    short Nhaposicao;
    int k;
    k = Arvore->quant;
    Nhaposicao = (k > 0);

    while (Nhaposicao) { // Loop até que a posição seja encontrada
        analise->comppre+=1; // Acrescenta a cada comparação

        // Se a chave a ser inserida for maior que 
        if (dados.chave >= Arvore->pai[k-1].chave) {
            Nhaposicao = 0;
            break;
        }

        Arvore->pai[k] = Arvore->pai[k-1];
        Arvore->filhos[k+1] = Arvore->filhos[k];
        k--;
        if (k < 1)
            Nhaposicao = 0;
    }

    Arvore->pai[k] = dados;
    Arvore->filhos[k+1] = ApDir;
    Arvore->quant++; // Os itens na página aumentam
}

void ins(Item registro, Apontadores Arvore, short *cresceu, Item* registroretorno, Apontadores* ApRetorno, Analise* analise) {
    long i = 1;
    long j;

    Apontadores ApTemp;

    if (Arvore == NULL) {
        *cresceu = 1;
        *registroretorno = registro;
        *ApRetorno = NULL;
        return;
    }

    // Enquanto o valor de `i` for menor que a quantidade de itens na árvore e a chave do item `x` for maior que a chave do item na posição `i-1` do vetor `pai` da árvore, incrementa `i` para continuar a busca na próxima posição.
   analise->comppre++;
   while (i < Arvore->quant && registro.chave > Arvore->pai[i-1].chave) {
        i++;
        analise->comppre++;
    }

    // Se o item já existir ele não é reinserido 
   analise->comppre+=1;
    if (registro.chave == Arvore->pai[i-1].chave) {
        printf("Registro existente");
        
        *cresceu = 0;
        return;
    }

   analise->comppre+=1;
    // Se a chave a ser inserida for menor que a chave da página
    if (registro.chave < Arvore->pai[i-1].chave) {
        i--;
    }
    ins(registro, Arvore->filhos[i], cresceu, registroretorno, ApRetorno, analise);
    if (!*cresceu) {
        return;
    }

    // Página tem espaço
    if (Arvore->quant < 2*M) {
        inserenaPagina(Arvore, *registroretorno, *ApRetorno, analise);
        *cresceu = 0;
        return;
    }

    // Dividir página: número de itens máximo atingido
    ApTemp = (Apontadores)malloc(sizeof(Pagina)); // Alocação de nova página
    ApTemp->quant = 0;
    ApTemp->filhos[0] = NULL;

    if (i < M + 1) {
        inserenaPagina(ApTemp, Arvore->pai[2 * M-1], Arvore->filhos[2 * M], analise);
        Arvore->quant--;
        inserenaPagina(Arvore, *registroretorno, *ApRetorno, analise);
    } else {
        inserenaPagina(ApTemp, *registroretorno, *ApRetorno, analise);
    }

    for (j = M+2; j <= 2 * M; j++) {
        inserenaPagina(ApTemp, Arvore->pai[j-1], Arvore->filhos[j], analise);
    }

    Arvore->quant = M;
    ApTemp->filhos[0] = Arvore->filhos[M+1];
    *registroretorno = Arvore->pai[M];
    *ApRetorno = ApTemp;
}

void insere(Item reg, Apontadores* Arvore, Analise* analise) {
    short cresceu;
    Item registroretorno;
    Pagina* ApRetorno, *ApTemp;
    ins(reg, *Arvore, &cresceu, &registroretorno, &ApRetorno, analise);

    if (cresceu) { // Crescimento na altura da raiz
        ApTemp = (Pagina*)malloc(sizeof(Pagina)); // Alocando memória
        ApTemp->quant = 1;
        ApTemp->pai[0] = registroretorno;
        ApTemp->filhos[1] = ApRetorno;
        ApTemp->filhos[0] = *Arvore;
        *Arvore = ApTemp;
    }
}

void pesquisar(Item *registro, Apontadores Arvore, Analise* analise, bool *achou) {
    long i = 1;

    // Se a árvore estiver vazia
    if (Arvore == NULL) {
        //analise->comppesquisa+=1;
        printf("Nenhum registro encontrado.\n");
        *achou = false;
        return;
    }

    analise->transpesquisa++; 
    analise->comppesquisa+=1;
    // Enquanto i for menor que a quantidade de Itens na árvore e a chave for  
    while (i < Arvore->quant && registro->chave > Arvore->pai[i-1].chave) {
        i++;
        analise->comppesquisa+=1;
    }

    // Se a chave for igual ao item da árvore
   analise->comppesquisa+=1;
    if (registro->chave == Arvore->pai[i-1].chave) {
        *registro = Arvore->pai[i-1];
        
        *achou = true;
        return;
    }

    analise->comppesquisa++;
    // Se a chave for menor que item da árvore retorna chamada recursiva pela esquerda 
    if (registro->chave < Arvore->pai[i-1].chave) {
        pesquisar(registro, Arvore->filhos[i-1], analise, achou);
    } else { // Se a chave for maior chamada recursiva para a direita
        pesquisar(registro, Arvore->filhos[i], analise, achou);
    }
}

void criaarvoreb(FILE *arquivo, Item *registro, DadosPesquisa *dados) {
    Apontadores Arvore;

    inicializa(&Arvore);

    int i = 0;

    dados->analise.timepre = (double)clock(); // Marcar o tempo de início do processamento
    
    // Lendo dados do arquivo e inserindo na árvore
    dados->analise.transpre += 1;
    while ((fread(registro, sizeof(Item), 1, arquivo) == 1) && i < dados->quant) {
        insere(*registro, &Arvore, &dados->analise);
        i++;
        dados->analise.transpre += 1;
    }

    dados->analise.timepre = (((double)clock() - dados->analise.timepre) / CLOCKS_PER_SEC); // Fim do processamento 
    // Número de comparações ao inserir dados
    dados->analise.timepesquisa = (double)clock();
    bool pesq;
    registro->chave = dados->chave;
    pesquisar(registro, Arvore, &dados->analise, &pesq);
    dados->analise.timepesquisa = (((double)clock() - dados->analise.timepesquisa) / CLOCKS_PER_SEC);
    impreResultado(pesq, dados, registro);
    liberaArvore(&Arvore); // Chamada da função para liberar árvore da memória principal
}
