#ifndef HEAP_H
#define HEAP_H

#include "voo.h"

#define MAX_HEAP 1000

typedef struct {
    Voo *voos[MAX_HEAP];
    int tamanho;
} Heap;

Heap* criar_heap();
void inserir_heap(Heap *h, Voo *v);
Voo* remover_heap(Heap *h);
Voo* topo_heap(Heap *h);
int heap_vazio(Heap *h);
void imprimir_heap(Heap *h);
void liberar_heap(Heap *h);

#endif
