#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "item.h"

// Função para trocar dois elementos
void swap(Item *a, Item *b);

// Função de partição 
int partition(Item arr[], int esq, int dir, Analise *analise);

// implementaçao algoritmo QuickSort
vounçid quickSort(Item arr[], int esq, int dir, Analise *analise);

#endif // QUICKSORT_H