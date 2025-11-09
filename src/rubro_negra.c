#include "rubro_negra.h"
#include <stdio.h>
#include <stdlib.h>

ArvoreRN* criar_arvore_rn() {
    ArvoreRN *t = (ArvoreRN*)malloc(sizeof(ArvoreRN));
    t->nulo = (NoRN*)malloc(sizeof(NoRN));
    t->nulo->cor = PRETO;
    t->nulo->esq = t->nulo->dir = t->nulo->pai = NULL;
    t->raiz = t->nulo;
    return t;
}


NoRN* criar_no_rn(ArvoreRN *t, Voo *v) {
    NoRN *no = (NoRN*)malloc(sizeof(NoRN));
    no->voo = v;
    no->cor = VERMELHO;
    no->esq = t->nulo;
    no->dir = t->nulo;
    no->pai = NULL;
    return no;
}


void rotacao_esquerda_rn(ArvoreRN *t, NoRN *x) {
    NoRN *y = x->dir;
    x->dir = y->esq;

    if (y->esq != t->nulo)
        y->esq->pai = x;

    y->pai = x->pai;

    if (x->pai == NULL)
        t->raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;
}
void rotacao_direita_rn(ArvoreRN *t, NoRN *y) {
    NoRN *x = y->esq;
    y->esq = x->dir;

    if (x->dir != t->nulo)
        x->dir->pai = y;

    x->pai = y->pai;

    if (y->pai == NULL)
        t->raiz = x;
    else if (y == y->pai->dir)
        y->pai->dir = x;
    else
        y->pai->esq = x;

    x->dir = y;
    y->pai = x;
}

void corrigir_insercao_rn(ArvoreRN *t, NoRN *k) {
    while (k->pai && k->pai->cor == VERMELHO) {
        if (k->pai == k->pai->pai->esq) {
            NoRN *tio = k->pai->pai->dir;
            if (tio->cor == VERMELHO) {
                k->pai->cor = PRETO;
                tio->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                k = k->pai->pai;
            } else {
                if (k == k->pai->dir) {
                    k = k->pai;
                    rotacao_esquerda_rn(t, k);
                }
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                rotacao_direita_rn(t, k->pai->pai);
            }
        } else {
            NoRN *tio = k->pai->pai->esq;
            if (tio->cor == VERMELHO) {
                k->pai->cor = PRETO;
                tio->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                k = k->pai->pai;
            } else {
                if (k == k->pai->esq) {
                    k = k->pai;
                    rotacao_direita_rn(t, k);
                }
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                rotacao_esquerda_rn(t, k->pai->pai);
            }
        }
        if (k == t->raiz) break;
    }
    t->raiz->cor = PRETO;
}

void inserir_rn(ArvoreRN *t, Voo *v) {
    NoRN *novo = criar_no_rn(t, v);
    NoRN *y = NULL;
    NoRN *x = t->raiz;

    while (x != t->nulo) {
        y = x;
        if (novo->voo->horario_programado < x->voo->horario_programado)
            x = x->esq;
        else
            x = x->dir;
    }

    novo->pai = y;

    if (y == NULL)
        t->raiz = novo;
    else if (novo->voo->horario_programado < y->voo->horario_programado)
        y->esq = novo;
    else
        y->dir = novo;

    if (novo->pai == NULL) {
        novo->cor = PRETO;
        return;
    }

    if (novo->pai->pai == NULL)
        return;

    corrigir_insercao_rn(t, novo);
}

void imprimir_rn_ordem(ArvoreRN *t, NoRN *no) {
    if (no == t->nulo) return;
    imprimir_rn_ordem(t, no->esq);
    imprimir_voo(no->voo);
    imprimir_rn_ordem(t, no->dir);
}

void imprimir_cronograma(ArvoreRN *t) {
    printf("\n========== CRONOGRAMA DE VOOS ==========\n");
    imprimir_rn_ordem(t, t->raiz);
}

void buscar_por_horario(ArvoreRN *t, NoRN *no, time_t inicio, time_t fim) {
    if (no == t->nulo) return;
    buscar_por_horario(t, no->esq, inicio, fim);
    if (no->voo->horario_programado >= inicio && no->voo->horario_programado <= fim) {
        imprimir_voo(no->voo);
    }
    buscar_por_horario(t, no->dir, inicio, fim);
}

void liberar_rn(ArvoreRN *t, NoRN *no) {
    if (no == t->nulo) return;
    liberar_rn(t, no->esq);
    liberar_rn(t, no->dir);
    free(no);
}
