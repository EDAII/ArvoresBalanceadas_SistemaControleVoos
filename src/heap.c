#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

Heap* criar_heap() {
    Heap *h = (Heap*)malloc(sizeof(Heap));
    h->tamanho = 0;
    return h;
}
void trocar(Voo **a, Voo **b) {
    Voo *temp = *a;
    *a = *b;
    *b = temp;
}
void heapify_cima(Heap *h, int idx) {
    if (idx == 0) return;

    int pai = (idx - 1) / 2;

    if (h->voos[idx]->prioridade < h->voos[pai]->prioridade) {
        trocar(&h->voos[idx], &h->voos[pai]);
        heapify_cima(h, pai);
    }
}
void heapify_baixo(Heap *h, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < h->tamanho && h->voos[esq]->prioridade < h->voos[menor]->prioridade)
        menor = esq;

    if (dir < h->tamanho && h->voos[dir]->prioridade < h->voos[menor]->prioridade)
        menor = dir;

    if (menor != idx) {
        trocar(&h->voos[idx], &h->voos[menor]);
        heapify_baixo(h, menor);
    }
}


void inserir_heap(Heap *h, Voo *v) {
    if (h->tamanho >= MAX_HEAP) {
        printf("Heap cheio!\n");
        return;
    }

    h->voos[h->tamanho] = v;
    heapify_cima(h, h->tamanho);
    h->tamanho++;
}

Voo* remover_heap(Heap *h) {
    if (h->tamanho == 0) return NULL;

    Voo *raiz = h->voos[0];
    h->voos[0] = h->voos[h->tamanho - 1];
    h->tamanho--;
    heapify_baixo(h, 0);

    return raiz;
}

Voo* topo_heap(Heap *h) {
    if (h->tamanho == 0) return NULL;
    return h->voos[0];
}

int heap_vazio(Heap *h) {
    return h->tamanho == 0;
}

void imprimir_heap(Heap *h) {
    printf("\n========== FILA DE PRIORIDADE ==========\n");
    printf("Total de voos na fila: %d\n", h->tamanho);

    for (int i = 0; i < h->tamanho; i++) {
        printf("\n[%d] ", i + 1);
        imprimir_voo(h->voos[i]);
    }
}


void liberar_heap(Heap *h) {
    free(h);
}
