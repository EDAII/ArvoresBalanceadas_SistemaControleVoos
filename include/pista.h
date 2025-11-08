#ifndef PISTA_H
#define PISTA_H

#include "voo.h"
#include <stdbool.h>

typedef enum {
    LIVRE,
    OCUPADA,
    MANUTENCAO
} StatusPista;

typedef struct {
    int numero;
    StatusPista status;
    Voo *voo_atual;
    int tempo_restante;
} Pista;

typedef struct {
    Pista pistas[5];
    int total_pistas;
} GerenciadorPistas;

GerenciadorPistas* criar_gerenciador_pistas(int num_pistas);
bool alocar_pista(GerenciadorPistas *gp, Voo *v, TipoVoo tipo);
void liberar_pista(GerenciadorPistas *gp, int numero);
void atualizar_pistas(GerenciadorPistas *gp);
void imprimir_status_pistas(GerenciadorPistas *gp);
int contar_pistas_livres(GerenciadorPistas *gp);

#endif
