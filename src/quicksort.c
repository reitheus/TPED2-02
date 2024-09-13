#include "../include/quicksort.h"

// Função para realizar a troca de elementos
void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// Função de partição
int partition(Item arr[], int esq, int dir, Analise *analise) {
    float pivot = arr[dir].notas;  // Define o pivô como a nota do último elemento
    int i = esq - 1;

    for (int j = esq; j <= dir - 1; j++) {
        analise->numComp++;  // Incrementa o número de comparações
        if (arr[j].notas < pivot) {
            i++;
            swap(&arr[i], &arr[j]); 
        }
    }
    swap(&arr[i + 1], &arr[dir]);  // Coloca o pivô na posição correta
    return (i + 1); 
}

// Função principal do QuickSort
void quickSort(Item arr[], int esq, int dir, Analise *analise) {
    if (esq < dir) {
        // Obtém o índice da partição
        int pi = partition(arr, esq, dir, analise);

        // Ordena os elementos antes e depois da partição
        quickSort(arr, esq, pi - 1, analise);
        quickSort(arr, pi + 1, dir, analise);
    }
}
