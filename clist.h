/*
 * Arquivo: clist.h
 * Autor: Igor Peretta
 * Sobre: Lista duplamente ligada em C (cabeçalho)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __CLIST__
#define __CLIST__

typedef
    struct _CNode {
        int elem;
        struct _CNode * prev;
        struct _CNode * next;
    }
CNode;

typedef
    struct {
        CNode * head;
        size_t len;
    }
CList;

/* Cria lista vazia.
 * Em Python, equivale a: l = [] # ou l = list()
 */
CList CList_new(void);

/* Apaga '*clist' liberando memória (previne vazamentos).
 * IMPORTANTE! Não encerrar o programa sem apagar suas listas.
 * Em Python, realizado pelo coletor de lixo.
 */
void CList_destroy(CList * clist);

/* Verifica se 'clist' está vazia.
 * Em Python, equivale a: bool(l)
 */
bool CList_isEmpty(CList clist);

/* Imprime a lista 'clist'.
 * Em Python, equivale a: print(l)
 */
void CList_print(CList clist);

/* Retorna o endereço do último elemento de 'clist'; ou NULL, se 'clist' vazia.
 * Em Python, equivale a: id(l[-1]) # com ressalvas
 */
CNode * CList_last(CList clist);

/* Adiciona elemento como primeiro de '*clist'.
 * Retorno booleano: 'true' se conseguiu, senão 'false'.
 * Em Python, equivale a: l = [e] + l
 */
bool CList_push(CList * clist, int elem);

/* Adiciona elemento como último de '*clist'.
 * Retorno booleano: 'true' se conseguiu, senão 'false'.
 * Em Python, equivale a: l.append(e)
 */
bool CList_append(CList * clist, int elem);

/* Remove a primeira instância de 'elem' em '*clist', se encontrar.
 * Retorno booleano: 'true' se conseguiu, senão 'false'.
 * Em Python, equivale a: l.remove(e)
 */
bool CList_remove(CList * clist, int elem);

/* Insere 'elem' em '*clist' no 'index', se encontrar 'index'.
 * Retorno booleano: 'true' se conseguiu, senão 'false'.
 * Em Python, equivale a: l.insert(i, e)
 */
bool CList_insert(CList * clist, size_t index, int elem);

/* Verifica se 'elem' está contido em 'clist', retorno booleano ('true'/'false').
 * Em Python, equivale a: e in l
 */
bool CList_in(int elem, CList clist);

/* Conta quantas instâncias de 'elem' estão contidas em 'clist'.
 * Em Python, equivale a: l.count(e)
 */
size_t CList_count(CList clist, int elem);

/* Retorna endereço (memória) de 'index' na 'clist', 
 * ou imprime mensagem de erro e retorna NULL se não existir 'index'.
 * Em Python, equivale a: id(l[i]) # com ressalvas
 */
CNode * CList_addr(CList clist, size_t index);

/* Retorna elemento em 'index' na 'clist'.
 * Se não existir 'index', retorna maior int do sistema.
 * Em Python, equivale a: l[i]
 */
int CList_at(CList clist, size_t index);

/* Atribui 'elem' para 'index' na 'clist'.
 * Em Python, equivale a: l[i] = e
 */
bool CList_assign(CList clist, size_t index, int elem);

/* Troca elementos entre 'index1' e 'index2' na 'clist'.
 * Retorno booleano: 'true' se conseguiu, senão 'false'.
 * Em Python, equivale a: l[i1], l[i2] = l[i2], l[i1]
 */
bool CList_swap(CList * clist, size_t index1, size_t index2);

/* Gera uma lista com 'len' instâncias de 0 (zero).
 * Em Python, equivale a: l = [0]*n
 */
CList CList_zeros(size_t len);

/* Gera uma lista com 'len' instâncias de 1 (um).
 * Em Python, equivale a: l = [1]*n
 */
CList CList_ones(size_t len);

/* Gera uma lista com 'len' instâncias de 'elem'.
 * Em Python, equivale a: l = [e]*n
 */
CList CList_mult(int elem, size_t len);

/* Converte vetor de C ('array' de tamanho 'N') para CList.
 * Não existe equivalente em Python.
 */
CList CList_fromArray(int * array, size_t N);

/* Cria CList a partir de arquivo 'filename' gravado em binário a partir de vetor de 'int' (4 bytes por elemento).
 * Em Python, equivale a:
 * with open(filename, 'rb') as f: l = list(int.from_bytes(reversed(f.read(4))) for _ in range(os.stat(filename).st_size//4))
 */
CList CList_fromBinFile(char * filename);

/* Gera uma lista que é uma cópia independente de 'clist'.
 * Em Python, equivale a: l2 = l.copy()
 */
CList CList_copy(CList clist);

/* Gera uma lista que é uma cópia independente de uma sublista de 'clist', 
 * entre 'index1' (incluso) e 'index2' (excluso). Retorna lista vazia se falhar por qualquer motivo.
 * Em Python, equivale a: l2 = l[i:j] # com j > i
 */
CList CList_slice(CList clist, size_t index1, size_t index2);

/* Gera uma lista que possui a ordem reversa dos elementos da lista recebida em 'clist'.
 * Em Python, equivale a: l2 = reversed(l)
 */
CList CList_reversed(CList clist);

/* Retorna o índice na lista recebida em 'clist' da primeira instância de 'elem'.
 * Se 'elem' não for encontrado, retorna -1.
 * Em Python, equivale a: l.index(e)
 */
long long int CList_index(CList clist, int elem);

#endif