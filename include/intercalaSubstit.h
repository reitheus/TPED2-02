#ifndef _INTERCALACAO_SUBST_H_
#define _INTERCALACAO_SUBST_H_

#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "../include/intercala.h"

#define TAM_MAXIMO 20

typedef struct item_heap {
    Item registro;
    bool marcado;
} ItemHeap; // recebe o item e se ele foi marcado ou não 

typedef struct heap {
    ItemHeap itens[TAM_MAXIMO]; // vetor de itens do heap 
    unsigned short tamanho; // confere o tamanho do heap em tempo de execução
    unsigned short marcados;    // Responsavel por contar a quantidade de itens marcados no vetor.
} Heap;


//HEAP
void iniciaHeap(Heap *heap);
void heapRefaz(Heap *heap, short esq, short dir);
void heapConstroi(Heap *heap);
ItemHeap heapRetira(Heap *heap);
void heapInsere(Heap *heap, ItemHeap *item);
void desmarcarItensHeap(Heap *heap);

//INTERCALAÇÃO
void criacaoBlocosOrdenados(FILE *, long, FITAS*);
void iniciaHeap(Heap *);
#endif