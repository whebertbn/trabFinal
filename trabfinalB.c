/*
* Arquivo: trabfinalB.c
* Compilação: gcc -std=c99 clist.c trabfinalB.c -o trabfinalB
* Autor: Whebert Nascimento
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clist.h"

// Selection Sort
void selectionSort(CList *lista) {
  size_t n = lista->len;
  for (size_t i = 0; i < n - 1; i++) {
    size_t pos_menor = i;
    int valor_menor = CList_at(*lista, i);

    for (size_t j = i + 1; j < n; j++) {
      int valor_atual = CList_at(*lista, j);
      
      if (valor_atual < valor_menor) {
        pos_menor = j;
        valor_menor = valor_atual;
      }
    }
    
    if (pos_menor != i) {
      CList_swap(*lista, i, pos_menor);
    }
  }
}


// Inserion Sort
void insertionSort(CList *clist) {
  CNode *atual = clist->head;
  while (atual != NULL) {
    int valorAtual = atual->elem;
    CNode *anterior = atual->prev;
    while (anterior != NULL && anterior->elem > valorAtual) {
      anterior->next->elem = anterior->elem;
      anterior = anterior->prev;
    }
    if (anterior == NULL)
      clist->head->elem = valorAtual;
    else
      anterior->next->elem = valorAtual;
      atual = atual->next;
    }
}

// Quick Sort


int main(void) {
#if defined(_WIN32) || defined(_WIN64)
        system("chcp 65001"); // troca para UTF-8
#endif

clock_t clkini, clkfim;
double tempo_cpu;

// Carregando lista do arquivo
CList lista = CList_fromBinFile("vecrnd_1000000.bin");

// Imprimindo a lista antes da ordenação
//printf("Lista antes da ordenação:\n");
//CList_print(lista);

// Medindo desempenho do algoritmo
clkini = clock();
insertionSort(&lista);
clkfim = clock();
  
tempo_cpu = ((double) (clkfim - clkini)) / CLOCKS_PER_SEC;
printf("Tempo utilizado: %lg ms\n", tempo_cpu*1000);

// Imprimindo a lista após a ordenação
//printf("Lista após a ordenação:\n");
//CList_print(lista);

CList_destroy(&lista);
return EXIT_SUCCESS;
  
}

