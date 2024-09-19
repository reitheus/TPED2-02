#include "../include/intercalaSubstit.h"
#include "../include/intercala.h"
// inicializando o heap com valores vázios
void iniciaHeap(Heap *heap)
{
    heap->tamanho = 0;
    heap->marcados = 0;
}

void heapRefaz(Heap *heap, short esq, short dir)
{
    short i;
    short j;
    ItemHeap aux;

    i = esq;
    j = i * 2 + 1;

    aux = heap->itens[i];

    while (j <= dir)
    {
        if (j < dir)
        {
            if (!(heap->itens[j].marcado == false && heap->itens[j + 1].marcado == true))
            {
                if ((heap->itens[j].marcado == true && heap->itens[j + 1].marcado == false) ||
                    heap->itens[j].registro.notas > heap->itens[j + 1].registro.notas)
                    j++;
            }
        }

        if (!(aux.marcado == true && heap->itens[j].marcado == false))
        {
            if ((aux.marcado == false && heap->itens[j].marcado == true) ||
                (aux.registro.notas <= heap->itens[j].registro.notas))
                break;
        }
        heap->itens[i] = heap->itens[j];
        i = j;
        j = i * 2 + 1;
    }
    heap->itens[i] = aux;
}

void heapConstroi(Heap *heap)
{
    short esq;

    esq = (heap->tamanho / 2) - 1;

    while (esq >= 0)
    {
        heapRefaz(heap, esq, heap->tamanho - 1);
        esq--;
    }
}

ItemHeap heapRetira(Heap *heap)
{
    ItemHeap aux;

    aux = heap->itens[0];
    heap->itens[0] = heap->itens[heap->tamanho - 1];
    heap->tamanho--;

    return aux;
}

void desmarcarItensHeap(Heap *heap)
{
    for (unsigned short i = 0; i < 20; i++)
        heap->itens[i].marcado = false;

    heap->marcados = 0;
}
void criacaoBlocosOrdenados(FILE *arquivo, long quantidade, FITAS *fitas_entrada)
{
    // criando o heap, inicializando ele e preenchendo como os primeiros 20 registros do vetor
    Heap heap;
    iniciaHeap(&heap);

    for (int i = 0; i < TAM_MAXIMO; i++)
    {
        // faz a leitura de um item no arquivo por vez e o adiciona ao heap
        if (fread(&heap.itens[i].registro, sizeof(Item), 1, arquivo) == 0)
            exit(1);
        // faz todos os itens do heap receber false para a marca
        heap.itens[i].marcado = false;
        // soma o tamanho do heap
        heap.tamanho++;
    }

    heapConstroi(&heap);

    int fitasId;
    fitasId = 0;
    ItemHeap auxiliar;
    auxiliar.registro.notas = -1;
    ItemHeap ultimoR; // ultimo item retirado
    ItemHeap novoRegistro;
    int cont = 0;
    while (cont < quantidade)
    {
        if (heap.marcados == heap.tamanho )
        {
            
            fwrite(&auxiliar.registro, sizeof(Item), 1, fitas_entrada[fitasId].file);
            desmarcarItensHeap(&heap);
            
            if (fitasId == TAM_MAXIMO - 1){
                fitasId = 0;
            }else{
                fitasId++;
            }

        }
        heapConstroi(&heap);
        
        fwrite(&heap.itens[0].registro, sizeof(Item), 1, fitas_entrada[fitasId].file);
        fitas_entrada[fitasId].ativa = 1;
        fitas_entrada[fitasId].vazia = 0;
        fitas_entrada[fitasId].quantItens++;
        heap.tamanho--;
        ultimoR = heap.itens[0];

        if (fread(&novoRegistro.registro, sizeof(Item), 1, arquivo) == 0){
            
             
        }
            
        if (novoRegistro.registro.notas < ultimoR.registro.notas)
        {
            novoRegistro.marcado = true;
            heap.marcados++;
        }
        else
        {
            novoRegistro.marcado = false;
        }
        heap.itens[0] = novoRegistro;
        heap.tamanho++;
        cont++;
    }

   
    int cont2 = 0;
    while (heap.tamanho > 0)
    {   
        
        if (heap.marcados == heap.tamanho)
        {

            desmarcarItensHeap(&heap);
            fitasId++;

            if (fitasId == TAM_MAXIMO)
                fitasId = 0;
            
        }

        ultimoR = heapRetira(&heap);

        fwrite(&ultimoR.registro, sizeof(Item), 1, fitas_entrada[fitasId].file);
        fitas_entrada[fitasId].ativa = 1;
        fitas_entrada[fitasId].vazia = 0;
        fitas_entrada[fitasId].quantItens++;
        
        heapRefaz(&heap, 0, heap.tamanho - 1);
        cont2++;
        
    }
    
}
