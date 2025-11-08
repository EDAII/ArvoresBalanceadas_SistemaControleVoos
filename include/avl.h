#ifndef AVL_H
#define AVL_H

#include "voo.h"

typedef struct NoAVL {
    Voo *voo;
    struct NoAVL *esq;
    struct NoAVL *dir;
    int altura;
} NoAVL;

NoAVL* inserir_avl(NoAVL *raiz, Voo *v);
NoAVL* buscar_avl(NoAVL *raiz, char *numero_voo);
NoAVL* remover_avl(NoAVL *raiz, char *numero_voo);
void imprimir_avl_ordem(NoAVL *raiz);
void liberar_avl(NoAVL *raiz);
void buscar_por_destino(NoAVL *raiz, char *destino);

#endif
