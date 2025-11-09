#include "voo.h"
#include "cores.h"
#include <stdio.h>

void imprimir_horario(time_t t) {
    struct tm *tm_info = localtime(&t);
    printf("%02d/%02d/%04d %02d:%02d",
           tm_info->tm_mday,
           tm_info->tm_mon + 1,
           tm_info->tm_year + 1900,
           tm_info->tm_hour,
           tm_info->tm_min);
}

void imprimir_voo(Voo *v) {
    char *tipo_str[] = {"PARTIDA", "CHEGADA"};
    char *status_str[] = {"PROGRAMADO", "EMBARCANDO", "ATRASADO", "CANCELADO", "FINALIZADO"};
    char *cor_status;

    switch (v->status) {
        case PROGRAMADO:
            cor_status = COR_VERDE;
            break;
        case EMBARCANDO:
            cor_status = COR_CIANO;
            break;
        case ATRASADO:
            cor_status = COR_AMARELO;
            break;
        case CANCELADO:
            cor_status = COR_VERMELHO;
            break;
        case FINALIZADO:
            cor_status = COR_AZUL;
            break;
        default:
            cor_status = COR_RESET;
    }

    printf("\n%s┌───────────────────────────────────────────────┐%s\n", COR_BOLD, COR_RESET);
    printf("%s│%s Voo: %s%-8s%s | Companhia: %-18s%s│%s\n",
           COR_BOLD, COR_RESET, COR_CIANO, v->numero_voo, COR_RESET, v->companhia, COR_BOLD, COR_RESET);
    printf("%s│%s Tipo: %-8s | Status: %s%-18s%s%s│%s\n",
           COR_BOLD, COR_RESET, tipo_str[v->tipo], cor_status, status_str[v->status], COR_RESET, COR_BOLD, COR_RESET);
    printf("%s│%s %-8s -> %-32s%s│%s\n",
           COR_BOLD, COR_RESET, v->origem, v->destino, COR_BOLD, COR_RESET);
    printf("%s│%s Horario: ", COR_BOLD, COR_RESET);
    imprimir_horario(v->horario_programado);
    printf("                        %s│%s\n", COR_BOLD, COR_RESET);
    printf("%s│%s Passageiros: %-4d | Prioridade: %-13d%s│%s\n",
           COR_BOLD, COR_RESET, v->passageiros, v->prioridade, COR_BOLD, COR_RESET);
    printf("%s└───────────────────────────────────────────────┘%s\n", COR_BOLD, COR_RESET);
}
