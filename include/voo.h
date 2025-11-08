#ifndef VOO_H
#define VOO_H

#include <time.h>

typedef enum {
    PARTIDA,
    CHEGADA
} TipoVoo;

typedef enum {
    PROGRAMADO,
    EMBARCANDO,
    ATRASADO,
    CANCELADO,
    FINALIZADO
} StatusVoo;

typedef struct {
    char numero_voo[10];
    char destino[50];
    char origem[50];
    TipoVoo tipo;
    StatusVoo status;
    int prioridade;
    time_t horario_programado;
    int passageiros;
    char companhia[30];
} Voo;

void imprimir_voo(Voo *v);
void imprimir_horario(time_t t);

#endif
