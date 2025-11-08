#ifndef CLIMA_H
#define CLIMA_H

typedef enum {
    ENSOLARADO,
    NUBLADO,
    CHUVOSO,
    TEMPESTADE,
    NEVOA
} CondicaoClima;

typedef struct {
    CondicaoClima condicao;
    int visibilidade;
    int vento_kmh;
    int impacto_prioridade;
} Clima;

Clima* criar_clima();
void atualizar_clima(Clima *c, CondicaoClima nova_condicao);
void gerar_clima_aleatorio(Clima *c);
void imprimir_clima(Clima *c);
int calcular_impacto_clima(Clima *c);

#endif
