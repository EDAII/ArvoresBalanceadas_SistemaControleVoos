#ifndef RUBRO_NEGRA_H
#define RUBRO_NEGRA_H

#include "voo.h"

typedef enum { VERMELHO, PRETO } Cor;

typedef struct NoRN {
    Voo *voo;
    Cor cor;
    struct NoRN *esq, *dir, *pai;
} NoRN;

typedef struct {
    NoRN *raiz;
    NoRN *nulo;
} ArvoreRN;

ArvoreRN* criar_arvore_rn();
void inserir_rn(ArvoreRN *t, Voo *v);
void imprimir_rn_ordem(ArvoreRN *t, NoRN *no);
void imprimir_cronograma(ArvoreRN *t);
void liberar_rn(ArvoreRN *t, NoRN *no);
void buscar_por_horario(ArvoreRN *t, NoRN *no, time_t inicio, time_t fim);

#endif
