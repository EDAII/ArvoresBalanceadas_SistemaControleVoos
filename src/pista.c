#include "pista.h"
#include "cores.h"
#include <stdio.h>
#include <stdlib.h>

GerenciadorPistas* criar_gerenciador_pistas(int num_pistas) {
    GerenciadorPistas *gp = (GerenciadorPistas*)malloc(sizeof(GerenciadorPistas));
    gp->total_pistas = num_pistas > 5 ? 5 : num_pistas;

    for (int i = 0; i < gp->total_pistas; i++) {
        gp->pistas[i].numero = i + 1;
        gp->pistas[i].status = LIVRE;
        gp->pistas[i].voo_atual = NULL;
        gp->pistas[i].tempo_restante = 0;
    }

    return gp;
}

bool alocar_pista(GerenciadorPistas *gp, Voo *v, TipoVoo tipo) {
    for (int i = 0; i < gp->total_pistas; i++) {
        if (gp->pistas[i].status == LIVRE) {
            gp->pistas[i].status = OCUPADA;
            gp->pistas[i].voo_atual = v;
            gp->pistas[i].tempo_restante = (tipo == PARTIDA) ? 5 : 3;

            printf("\n%sPista %d alocada para voo %s%s\n",
                   COR_VERDE, gp->pistas[i].numero, v->numero_voo, COR_RESET);
            return true;
        }
    }

    printf("\n%sTodas as pistas estao ocupadas!%s\n", COR_VERMELHO, COR_RESET);
    return false;
}

void liberar_pista(GerenciadorPistas *gp, int numero) {
    if (numero < 1 || numero > gp->total_pistas) return;

    int idx = numero - 1;
    gp->pistas[idx].status = LIVRE;
    gp->pistas[idx].voo_atual = NULL;
    gp->pistas[idx].tempo_restante = 0;

    printf("%sPista %d liberada%s\n", COR_VERDE, numero, COR_RESET);
}

void atualizar_pistas(GerenciadorPistas *gp) {
    for (int i = 0; i < gp->total_pistas; i++) {
        if (gp->pistas[i].status == OCUPADA && gp->pistas[i].tempo_restante > 0) {
            gp->pistas[i].tempo_restante--;

            if (gp->pistas[i].tempo_restante == 0) {
                printf("\n%sVoo %s finalizou uso da pista %d%s\n",
                       COR_AMARELO,
                       gp->pistas[i].voo_atual->numero_voo,
                       gp->pistas[i].numero,
                       COR_RESET);
                liberar_pista(gp, gp->pistas[i].numero);
            }
        }
    }
}

int contar_pistas_livres(GerenciadorPistas *gp) {
    int livres = 0;
    for (int i = 0; i < gp->total_pistas; i++) {
        if (gp->pistas[i].status == LIVRE) livres++;
    }
    return livres;
}

void imprimir_status_pistas(GerenciadorPistas *gp) {
    printf("\n");
    printf("%s╔══════════════════════════════════════════════════╗%s\n", COR_AZUL, COR_RESET);
    printf("%s║            STATUS DAS PISTAS                     ║%s\n", COR_AZUL, COR_RESET);
    printf("%s╠══════════════════════════════════════════════════╣%s\n", COR_AZUL, COR_RESET);

    for (int i = 0; i < gp->total_pistas; i++) {
        Pista *p = &gp->pistas[i];
        char *cor_status;
        char *status_str;

        switch (p->status) {
            case LIVRE:
                cor_status = COR_VERDE;
                status_str = "LIVRE";
                break;
            case OCUPADA:
                cor_status = COR_VERMELHO;
                status_str = "OCUPADA";
                break;
            case MANUTENCAO:
                cor_status = COR_AMARELO;
                status_str = "MANUTENCAO";
                break;
            default:
                cor_status = COR_RESET;
                status_str = "DESCONHECIDO";
        }

        printf("%s║%s Pista %d: %s%-10s%s",
               COR_AZUL, COR_RESET, p->numero, cor_status, status_str, COR_RESET);

        if (p->status == OCUPADA && p->voo_atual) {
            printf(" | Voo: %-8s | Tempo: %d min", p->voo_atual->numero_voo, p->tempo_restante);
        } else {
            printf("                              ");
        }

        printf(" %s║%s\n", COR_AZUL, COR_RESET);
    }

    printf("%s╠══════════════════════════════════════════════════╣%s\n", COR_AZUL, COR_RESET);
    printf("%s║%s Pistas Livres: %s%d/%d%s                              %s║%s\n",
           COR_AZUL, COR_RESET, COR_VERDE, contar_pistas_livres(gp), gp->total_pistas,
           COR_RESET, COR_AZUL, COR_RESET);
    printf("%s╚══════════════════════════════════════════════════╝%s\n", COR_AZUL, COR_RESET);
}
