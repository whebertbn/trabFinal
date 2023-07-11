/*
 * Arquivo: clist.c
 * Compilação: gcc -std=c99 clist.c example.c -o example
 * Autor: Igor Peretta
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clist.h"

/* Retorna índice do alvo na lista; retorna lista.len se não encontrar */
size_t buscaLinear(CList lista, int alvo) {
    size_t index = 0;
    for(CNode *it = lista.head; it; it = it->next, index++)
        if(it->elem == alvo)
            return index;
    return lista.len;
}

int main(void) {
    #if defined(_WIN32) || defined(_WIN64)
        system("chcp 65001"); // troca para UTF-8
    #endif

    clock_t clkini, clkfim;
 	double tempo_cpu;

    // Carregando lista do arquivo
    CList lista = CList_fromBinFile("vecrnd_100.bin");

    // Medindo desempenho do algoritmo
    clkini = clock();
    size_t idx = buscaLinear(lista, 42);
 	clkfim = clock();

 	tempo_cpu = ((double) (clkfim - clkini)) / CLOCKS_PER_SEC;
    printf("Tempo utilizado: %lg ms\n", tempo_cpu*1000);
    
    // Resposta do algoritmo de busca
    printf("Alvo localizado no índice %zu\n", idx); // 42 no índice 11

    CList_destroy(&lista);
    return EXIT_SUCCESS;
}
