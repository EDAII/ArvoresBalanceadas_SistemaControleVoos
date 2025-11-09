#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int altura(NoAVL *no) {
    return no ? no->altura : 0;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}

int fator_balanceamento(NoAVL *no) {
    return no ? altura(no->esq) - altura(no->dir) : 0;
}


NoAVL* criar_no(Voo *v) {
    NoAVL *no = (NoAVL*)malloc(sizeof(NoAVL));
    no->voo = v;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 1;
    return no;
}
NoAVL* rotacao_direita(NoAVL *y) {
    NoAVL *x = y->esq;
    NoAVL *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;

    return x;
}

NoAVL* rotacao_esquerda(NoAVL *x) {
    NoAVL *y = x->dir;
    NoAVL *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;

    return y;
}

NoAVL* inserir_avl(NoAVL *raiz, Voo *v) {
    if (!raiz) return criar_no(v);

    int cmp = strcmp(v->numero_voo, raiz->voo->numero_voo);

    if (cmp < 0)
        raiz->esq = inserir_avl(raiz->esq, v);
    else if (cmp > 0)
        raiz->dir = inserir_avl(raiz->dir, v);
    else
        return raiz;

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int fb = fator_balanceamento(raiz);

    if (fb > 1 && strcmp(v->numero_voo, raiz->esq->voo->numero_voo) < 0)
        return rotacao_direita(raiz);

    if (fb < -1 && strcmp(v->numero_voo, raiz->dir->voo->numero_voo) > 0)
        return rotacao_esquerda(raiz);

    if (fb > 1 && strcmp(v->numero_voo, raiz->esq->voo->numero_voo) > 0) {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

    if (fb < -1 && strcmp(v->numero_voo, raiz->dir->voo->numero_voo) < 0) {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

NoAVL* buscar_avl(NoAVL *raiz, char *numero_voo) {
    if (!raiz) return NULL;

    int cmp = strcmp(numero_voo, raiz->voo->numero_voo);

    if (cmp == 0) return raiz;
    if (cmp < 0) return buscar_avl(raiz->esq, numero_voo);
    return buscar_avl(raiz->dir, numero_voo);
}

NoAVL* no_min(NoAVL *no) {
    NoAVL *atual = no;
    while (atual->esq) atual = atual->esq;
    return atual;
}

NoAVL* remover_avl(NoAVL *raiz, char *numero_voo) {
    if (!raiz) return raiz;

    int cmp = strcmp(numero_voo, raiz->voo->numero_voo);

    if (cmp < 0)
        raiz->esq = remover_avl(raiz->esq, numero_voo);
    else if (cmp > 0)
        raiz->dir = remover_avl(raiz->dir, numero_voo);
    else {
        if (!raiz->esq || !raiz->dir) {
            NoAVL *temp = raiz->esq ? raiz->esq : raiz->dir;
            if (!temp) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            NoAVL *temp = no_min(raiz->dir);
            raiz->voo = temp->voo;
            raiz->dir = remover_avl(raiz->dir, temp->voo->numero_voo);
        }
    }

    if (!raiz) return raiz;

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int fb = fator_balanceamento(raiz);

    if (fb > 1 && fator_balanceamento(raiz->esq) >= 0)
        return rotacao_direita(raiz);

    if (fb > 1 && fator_balanceamento(raiz->esq) < 0) {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

    if (fb < -1 && fator_balanceamento(raiz->dir) <= 0)
        return rotacao_esquerda(raiz);

    if (fb < -1 && fator_balanceamento(raiz->dir) > 0) {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

void imprimir_avl_ordem(NoAVL *raiz) {
    if (!raiz) return;
    imprimir_avl_ordem(raiz->esq);
    imprimir_voo(raiz->voo);
    imprimir_avl_ordem(raiz->dir);
}


void buscar_por_destino(NoAVL *raiz, char *destino) {
    if (!raiz) return;
    buscar_por_destino(raiz->esq, destino);
    if (strcmp(raiz->voo->destino, destino) == 0) {
        imprimir_voo(raiz->voo);
    }
    buscar_por_destino(raiz->dir, destino);
}


void liberar_avl(NoAVL *raiz) {
    if (!raiz) return;
    liberar_avl(raiz->esq);
    liberar_avl(raiz->dir);
    free(raiz);
}
