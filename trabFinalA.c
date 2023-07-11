/*
* Arquivo: trabfinalA.c
* Compilação: gcc -std=c99 clist.c trabfinalA.c -o trabfinalA
* Autor: Whebert Nascimento
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clist.h"

/*
Busca Linear
Retorna índice do alvo na lista; retorna lista.len se não encontrar 
*/
size_t buscaLinear(CList lista, int alvo) {
  size_t index = 0;
    for(CNode *it = lista.head; it; it = it->next, index++)
      if(it->elem == alvo)
          return index;
  return lista.len;
}

/* 
Busca Binária
Retorna índice do alvo na lista; retorna lista.len se não encontrar 
*/
size_t buscaBinaria(CList lista, int alvo) {
  long long int low = 0;
  long long int high = lista.len - 1;
    while (low <= high) {
      long long int mid = (low + high) / 2;
      int valorMeio = CList_at(lista, mid);

      if (valorMeio == alvo)
        return mid;
        else if (valorMeio < alvo)
          low = mid + 1;
        else
          high = mid - 1;
    }

// Se o elemento não foi encontrado, retorna o complemento do índice onde ele deveria ser inserido
  return -high - 1;
}

/*
int main(void) {
  #if defined(_WIN32) || defined(_WIN64)
      system("chcp 65001"); // troca para UTF-8
  #endif

  clock_t clkini, clkfim;
  double tempo_cpu;

// Carregando lista do arquivo
  CList lista = CList_fromBinFile("vecrnd_1000000.bin");

// Imprimindo a lista
//  CList_print(lista);
  
// Medindo desempenho do algoritmo
clkini = clock();
    size_t idx = buscaBinaria(lista, 913428);
clkfim = clock();

tempo_cpu = ((double) (clkfim - clkini)) / CLOCKS_PER_SEC;
  printf("Tempo utilizado: %lg ms\n", tempo_cpu*1000);
    
// Resposta do algoritmo de busca
  printf("Alvo localizado no índice %zu\n", idx);
  
  CList_destroy(&lista);
  
  return EXIT_SUCCESS;
  
}

*/