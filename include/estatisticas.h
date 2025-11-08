#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include "voo.h"

typedef struct {
    int total_voos_processados;
    int total_decolagens;
    int total_pousos;
    int total_cancelados;
    int total_atrasados;
    int total_passageiros;
    double tempo_medio_espera;
    int voos_por_companhia[10];
    char companhias[10][30];
    int num_companhias;
} Estatisticas;

Estatisticas* criar_estatisticas();
void atualizar_estatisticas(Estatisticas *est, Voo *v, int processado);
void imprimir_estatisticas(Estatisticas *est);
void registrar_companhia(Estatisticas *est, char *companhia);
void liberar_estatisticas(Estatisticas *est);

#endif
