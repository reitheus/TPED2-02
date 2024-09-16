#include "../include/ordenar.h"

// Função para realizar a troca de elementos
void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// Função de partição para o QuickSort
int partition(Item *arr, int esq, int dir, Analise *analise) {
    float pivot = arr[dir].notas;
    int i = esq - 1;

    for (int j = esq; j <= dir - 1; j++) {
        analise->numComp++; // Contabiliza as comparações
        if (arr[j].notas < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[dir]);
    return i + 1;
}

// Implementação do QuickSort
void quickSort(Item *arr, int esq, int dir, Analise *analise) {
    if (esq < dir) {
        int pi = partition(arr, esq, dir, analise);

        
        quickSort(arr, esq, pi - 1, analise);
        quickSort(arr, pi + 1, dir, analise);
    }
}

// aloca dinamicamente o vetor e chamar o QuickSort
void ordenarItens(Item *arr, int tamanho, Analise *analise) {
    

    quickSort(arr, 0, tamanho - 1, analise);

   
}
