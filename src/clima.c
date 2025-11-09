#include "clima.h"
#include "cores.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Clima* criar_clima() {
    Clima *c = (Clima*)malloc(sizeof(Clima));
    c->condicao = ENSOLARADO;
    c->visibilidade = 10;
    c->vento_kmh = 10;
    c->impacto_prioridade = 0;
    return c;
}

void atualizar_clima(Clima *c, CondicaoClima nova_condicao) {
    c->condicao = nova_condicao;

    switch (nova_condicao) {
        case ENSOLARADO:
            c->visibilidade = 10;
            c->vento_kmh = 5 + rand() % 15;
            c->impacto_prioridade = 0;
            break;
        case NUBLADO:
            c->visibilidade = 8;
            c->vento_kmh = 10 + rand() % 20;
            c->impacto_prioridade = 1;
            break;
        case CHUVOSO:
            c->visibilidade = 5;
            c->vento_kmh = 20 + rand() % 30;
            c->impacto_prioridade = 2;
            break;
        case TEMPESTADE:
            c->visibilidade = 2;
            c->vento_kmh = 40 + rand() % 40;
            c->impacto_prioridade = 5;
            break;
        case NEVOA:
            c->visibilidade = 3;
            c->vento_kmh = 5 + rand() % 10;
            c->impacto_prioridade = 3;
            break;
    }
}

void gerar_clima_aleatorio(Clima *c) {
    CondicaoClima condicoes[] = {ENSOLARADO, NUBLADO, CHUVOSO, TEMPESTADE, NEVOA};
    int idx = rand() % 5;
    atualizar_clima(c, condicoes[idx]);
}

int calcular_impacto_clima(Clima *c) {
    return c->impacto_prioridade;
}

void imprimir_clima(Clima *c) {
    char *condicao_str[] = {"ENSOLARADO", "NUBLADO", "CHUVOSO", "TEMPESTADE", "NEVOA"};
    char *cor_clima;

    switch (c->condicao) {
        case ENSOLARADO:
            cor_clima = COR_AMARELO;
            break;
        case NUBLADO:
            cor_clima = COR_BRANCO;
            break;
        case CHUVOSO:
            cor_clima = COR_AZUL;
            break;
        case TEMPESTADE:
            cor_clima = COR_VERMELHO;
            break;
        case NEVOA:
            cor_clima = COR_DIM;
            break;
        default:
            cor_clima = COR_RESET;
    }

    printf("\n");
    printf("%s╔════════════════════════════════════════════════╗%s\n", COR_MAGENTA, COR_RESET);
    printf("%s║           CONDIÇÕES METEOROLÓGICAS             ║%s\n", COR_MAGENTA, COR_RESET);
    printf("%s╠════════════════════════════════════════════════╣%s\n", COR_MAGENTA, COR_RESET);
    printf("%s║%s Condicao: %s%-33s%s%s║%s\n",
           COR_MAGENTA, COR_RESET, cor_clima, condicao_str[c->condicao],
           COR_RESET, COR_MAGENTA, COR_RESET);
    printf("%s║%s Visibilidade: %-27d km %s║%s\n",
           COR_MAGENTA, COR_RESET, c->visibilidade, COR_MAGENTA, COR_RESET);
    printf("%s║%s Vento: %-34d km/h %s║%s\n",
           COR_MAGENTA, COR_RESET, c->vento_kmh, COR_MAGENTA, COR_RESET);
    printf("%s║%s Impacto na Prioridade: %s+%-19d%s%s║%s\n",
           COR_MAGENTA, COR_RESET,
           c->impacto_prioridade > 2 ? COR_VERMELHO : COR_AMARELO,
           c->impacto_prioridade, COR_RESET, COR_MAGENTA, COR_RESET);
    printf("%s╚════════════════════════════════════════════════╝%s\n", COR_MAGENTA, COR_RESET);
}
