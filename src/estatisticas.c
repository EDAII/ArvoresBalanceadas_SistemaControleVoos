#include "estatisticas.h"
#include "cores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Estatisticas* criar_estatisticas() {
    Estatisticas *est = (Estatisticas*)malloc(sizeof(Estatisticas));
    est->total_voos_processados = 0;
    est->total_decolagens = 0;
    est->total_pousos = 0;
    est->total_cancelados = 0;
    est->total_atrasados = 0;
    est->total_passageiros = 0;
    est->tempo_medio_espera = 0.0;
    est->num_companhias = 0;

    for (int i = 0; i < 10; i++) {
        est->voos_por_companhia[i] = 0;
        memset(est->companhias[i], 0, 30);
    }

    return est;
}

void registrar_companhia(Estatisticas *est, char *companhia) {
    for (int i = 0; i < est->num_companhias; i++) {
        if (strcmp(est->companhias[i], companhia) == 0) {
            est->voos_por_companhia[i]++;
            return;
        }
    }

    if (est->num_companhias < 10) {
        strcpy(est->companhias[est->num_companhias], companhia);
        est->voos_por_companhia[est->num_companhias] = 1;
        est->num_companhias++;
    }
}

void atualizar_estatisticas(Estatisticas *est, Voo *v, int processado) {
    if (processado) {
        est->total_voos_processados++;

        if (v->tipo == PARTIDA) {
            est->total_decolagens++;
        } else {
            est->total_pousos++;
        }
    }

    if (v->status == CANCELADO) {
        est->total_cancelados++;
    } else if (v->status == ATRASADO) {
        est->total_atrasados++;
    }

    est->total_passageiros += v->passageiros;
    registrar_companhia(est, v->companhia);
}

void imprimir_estatisticas(Estatisticas *est) {
    printf("\n");
    printf("%s╔════════════════════════════════════════════════════╗%s\n", COR_CIANO, COR_RESET);
    printf("%s║           ESTATÍSTICAS DO AEROPORTO                ║%s\n", COR_CIANO, COR_RESET);
    printf("%s╠════════════════════════════════════════════════════╣%s\n", COR_CIANO, COR_RESET);

    printf("%s║%s Voos Processados: %s%-28d%s%s║%s\n",
           COR_CIANO, COR_RESET, COR_VERDE, est->total_voos_processados, COR_RESET, COR_CIANO, COR_RESET);
    printf("%s║%s   - Decolagens: %-33d%s║%s\n",
           COR_CIANO, COR_RESET, est->total_decolagens, COR_CIANO, COR_RESET);
    printf("%s║%s   - Pousos: %-37d%s║%s\n",
           COR_CIANO, COR_RESET, est->total_pousos, COR_CIANO, COR_RESET);

    printf("%s║%s Voos Atrasados: %s%-32d%s%s║%s\n",
           COR_CIANO, COR_RESET, COR_AMARELO, est->total_atrasados, COR_RESET, COR_CIANO, COR_RESET);
    printf("%s║%s Voos Cancelados: %s%-31d%s%s║%s\n",
           COR_CIANO, COR_RESET, COR_VERMELHO, est->total_cancelados, COR_RESET, COR_CIANO, COR_RESET);
    printf("%s║%s Total de Passageiros: %-27d%s║%s\n",
           COR_CIANO, COR_RESET, est->total_passageiros, COR_CIANO, COR_RESET);

    printf("%s╠════════════════════════════════════════════════════╣%s\n", COR_CIANO, COR_RESET);
    printf("%s║              VOOS POR COMPANHIA                    ║%s\n", COR_CIANO, COR_RESET);
    printf("%s╠════════════════════════════════════════════════════╣%s\n", COR_CIANO, COR_RESET);

    for (int i = 0; i < est->num_companhias; i++) {
        printf("%s║%s %-30s: %-16d%s║%s\n",
               COR_CIANO, COR_RESET, est->companhias[i], est->voos_por_companhia[i], COR_CIANO, COR_RESET);
    }

    printf("%s╚════════════════════════════════════════════════════╝%s\n", COR_CIANO, COR_RESET);
}

void liberar_estatisticas(Estatisticas *est) {
    free(est);
}
