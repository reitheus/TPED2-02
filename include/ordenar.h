#ifndef ORDENAR_H
#define ORDENAR_H

#include "../include/item.h"
#include <stdlib.h>

// Função para realizar a troca de  elementos
void swap(Item *a, Item *b);

// Função de partição para o QuickSort
int partition(Item *arr, int esq, int dir, Analise *analise);

// Implementação do QuickSort
void quickSort(Item *arr, int esq, int dir, Analise *analise);

// aloca dinamicamente o vetor e chama o QuickSort
void ordenarItens(Item *arr, int tamanho, Analise *analise);

#endif // ORDENAR_H
