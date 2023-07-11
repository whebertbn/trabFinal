/*
 * Arquivo: clist.c
 * Autor: Igor Peretta
 * Sobre: Lista duplamente ligada em C (definições)
 */

#include "clist.h"

CList CList_new(void) {
    CList empty = {NULL, 0};
    return empty;
}

void CList_destroy(CList * clist) {
    if(clist->head) {
        CNode * it = clist->head;
        CNode * prev = NULL;
        while(it->next)
            it = it->next;
        do {
            prev = it->prev;
            free(it);
            it = prev;
        } while(prev);
    }
    clist->head = NULL;
    clist->len = 0;
}


bool CList_isEmpty(CList clist) {
    return clist.len == 0 || clist.head == NULL;
}

void CList_print(CList clist) {
    CNode * it = clist.head;
    printf("[ ");
    for(; it; it = it->next) {
        printf("%d", it->elem);
        if(it->next != NULL)
            printf("%d, ", it->elem);
    }
    printf("%s\n", clist.len? " ]" : "]");
}

CNode * CList_last(CList clist) {
    if(clist.head) {
        CNode * it = clist.head;
        while(it->next)
            it = it->next;
        return it;
    }
    return NULL;
}

bool CList_push(CList * clist, int elem) {
    CNode * new = (CNode *) malloc(sizeof(CNode));
    if(new == NULL)
        return false;
    new->elem = elem;
    new->prev = NULL;
    if(clist->head) {
        clist->head->prev = new;
        new->next = clist->head;
    } else
        new->next = NULL;
    clist->head = new;
    clist->len++;
    return true;
}

bool CList_append(CList * clist, int elem) {
    CNode * new = (CNode *) malloc(sizeof(CNode));
    if(new == NULL)
        return false;
    new->elem = elem;
    new->next = NULL;
    if(clist->head) {
        CNode * last = CList_last(*clist);
        new->prev = last;
        last->next = new;
    } else {
        new->prev = NULL;
        clist->head = new;
    }
    clist->len++;
    return true;
}

bool CList_remove(CList * clist, int elem) {
    for(CNode * it = clist->head; it; it = it->next)
        if(it->elem == elem){
            if(it->prev)
                it->prev->next = it->next;
            else // cabeça da lista
                clist->head = it->next;
            if(it->next)
                it->next->prev = it->prev;
            free(it);
            clist->len--;
            return true;
        }
    return false;
}

bool CList_insert(CList * clist, size_t index, int elem) {
    if(index == 0)
        return CList_push(clist, elem);
    if(index == clist->len)
        return CList_append(clist, elem);
    CNode * old = CList_addr(*clist, index);
    if(old) {
        CNode * new = (CNode *) malloc(sizeof(CNode));
        if(new == NULL)
            return false;
        new->elem = elem;
        new->prev = old->prev;
        new->next = old;
        old->prev->next = new;
        old->prev = new;
        clist->len++;
        return true;
    }
    return false;
}

bool CList_in(int elem, CList clist) {
    for(CNode * it = clist.head; it; it = it->next)
        if(it->elem == elem)
            return true;
    return false;
}

size_t CList_count(CList clist, int elem) {
    size_t count = 0;
    for(CNode * it = clist.head; it; it = it->next)
        if(it->elem == elem)
            count++;
    return count;
}

CNode * CList_addr(CList clist, size_t index) {
    size_t count = 0;
    for(CNode * it = clist.head; it; it = it->next, count++)
        if(count == index)
            return it;
    fprintf(stderr, "ERRO: Índice %zu não encontrado, "
        "lista com %zu elementos.\n", index, clist.len);
    return NULL;
}

int CList_at(CList clist, size_t index) {
    CNode * a = CList_addr(clist, index);
    if(a)
        return a->elem;
    return ~(1 << 31); // erro
}

bool CList_assign(CList clist, size_t index, int elem) {
    CNode * a = CList_addr(clist, index);
    if(a) {
        a->elem = elem;
        return true;
    }
    return false;
}

bool CList_swap(CList * clist, size_t index1, size_t index2) {
    if(index1 == index2)
        return true;
    CNode * a = CList_addr(*clist, index1);
    CNode * b = CList_addr(*clist, index2);
    CNode * prev, * next;
    if(a != NULL && b != NULL) { // se a e b são vizinhos
        if(a->next == b || a->prev == b) {
            prev = (a->next == b)? a->prev : b->prev;
            next = (a->next == b)? b->next : a->next;
            if(a->next == b){
                // se a antecede b
                a->next = next;
                a->prev = b;
                b->next = a;
                b->prev = prev;
                if(next)
                    next->prev = a;
                if(prev)
                    prev->next = b;
                else
                    clist->head = b;
                return true;
            }
            // se b antecede a
            b->next = next;
            b->prev = a;
            a->next = b;
            a->prev = prev;
            if(next)
                next->prev = b;
            if(prev)
                prev->next = a;
            else
                clist->head = a;
            return true;
        }
        prev = b->prev; next = b->next;
        // insere b em index1
        if(a->prev)
            a->prev->next = b;
        else
            clist->head = b;
        b->prev = a->prev;
        if(a->next)
            a->next->prev = b;
        b->next = a->next;
        // insere a em index2
        if(prev)
            prev->next = a;
        else
            clist->head = a;
        a->prev = prev;
        if(next)
            next->prev = a;
        a->next = next;
        return true;
    }
    return false;
}


CList CList_zeros(size_t len) {
    CList new = CList_new();
    for(size_t i = 0; i < len; i++)
        CList_push(&new, 0);
    return new;
}

CList CList_ones(size_t len) {
    CList new = CList_new();
    for(size_t i = 0; i < len; i++)
        CList_push(&new, 0);
    return new;
}

CList CList_mult(int elem, size_t len) {
    CList new = CList_new();
    for(size_t i = 0; i < len; i++)
        CList_push(&new, elem);
    return new;
}

CList CList_fromArray(int * array, size_t N) {
    CList new = CList_new();
    for(int i = N; i > 0; i--) // i: 1 to N
        CList_push(&new, array[i-1]); // i-1: 0 to N-1
    return new;
}

CList CList_fromBinFile(char * filename) {
    CList new = CList_new();
    int * array = NULL;
    size_t N = 0;
    FILE * file = fopen(filename, "rb");
    if(file) {
        fseek(file, 0, SEEK_END);
        N = ftell(file)/sizeof(int);
        array = (int *) malloc(sizeof(int)*N);
        rewind(file);
        fread(array, sizeof(int), N, file);
        fclose(file);
        new = CList_fromArray(array, N);
        free(array);
    }
    return new;
}

CList CList_copy(CList clist) {
    CList new = CList_new();
    for(CNode * it = CList_last(clist); it; it = it->prev)
        CList_push(&new, it->elem);
    return new;
}

CList CList_slice(CList clist, size_t index1, size_t index2) {
    CList new = CList_new();
    CNode * i = CList_addr(clist, index1);
    CNode * j = CList_addr(clist, index2);
    if(index1 < index2 && i != NULL && j != NULL) {
        for(CNode * it = j->prev; it != i->prev; it = it->prev)
            CList_push(&new, it->elem);
    }
    return new;
}

CList CList_reversed(CList clist) {
    CList new = CList_new();
    for(CNode * it = clist.head; it; it = it->next)
        CList_push(&new, it->elem);
    return new;
}

long long int CList_index(CList clist, int elem) {
    long long int count = 0;
    for(CNode * it = clist.head; it; it = it->next) {
        if(it->elem == elem)
            return count;
        count++;
    }
    return -1LL;
}
