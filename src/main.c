#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "voo.h"
#include "heap.h"
#include "avl.h"
#include "rubro_negra.h"
#include "cores.h"
#include "estatisticas.h"
#include "pista.h"
#include "clima.h"

typedef struct {
    Heap *fila_prioridade;
    NoAVL *arvore_busca;
    ArvoreRN *cronograma;
    Estatisticas *stats;
    GerenciadorPistas *pistas;
    Clima *clima;
    Voo **voos;
    int total_voos;
    int capacidade;
} SistemaAeroporto;

SistemaAeroporto* criar_sistema() {
    SistemaAeroporto *s = (SistemaAeroporto*)malloc(sizeof(SistemaAeroporto));
    s->fila_prioridade = criar_heap();
    s->arvore_busca = NULL;
    s->cronograma = criar_arvore_rn();
    s->stats = criar_estatisticas();
    s->pistas = criar_gerenciador_pistas(3);
    s->clima = criar_clima();
    s->capacidade = 100;
    s->voos = (Voo**)malloc(s->capacidade * sizeof(Voo*));
    s->total_voos = 0;

    srand(time(NULL));
    gerar_clima_aleatorio(s->clima);

    return s;
}

Voo* criar_voo(Clima *clima) {
    Voo *v = (Voo*)malloc(sizeof(Voo));

    printf("\n%s╔═══════════════════════════════════════╗%s\n", COR_VERDE, COR_RESET);
    printf("%s║       CADASTRO DE NOVO VOO            ║%s\n", COR_VERDE, COR_RESET);
    printf("%s╚═══════════════════════════════════════╝%s\n", COR_VERDE, COR_RESET);

    printf("\nNumero do voo: ");
    scanf("%s", v->numero_voo);

    printf("Companhia aerea: ");
    scanf(" %[^\n]", v->companhia);

    printf("Origem: ");
    scanf(" %[^\n]", v->origem);

    printf("Destino: ");
    scanf(" %[^\n]", v->destino);

    printf("Tipo (0-PARTIDA, 1-CHEGADA): ");
    int tipo;
    scanf("%d", &tipo);
    v->tipo = (TipoVoo)tipo;

    printf("Status (0-PROGRAMADO, 1-EMBARCANDO, 2-ATRASADO, 3-CANCELADO): ");
    int status;
    scanf("%d", &status);
    v->status = (StatusVoo)status;

    printf("Prioridade base (1-Emergencia, 5-Normal, 10-Baixa): ");
    scanf("%d", &v->prioridade);

    int impacto = calcular_impacto_clima(clima);
    if (impacto > 0) {
        v->prioridade += impacto;
        printf("%s  Clima afetou prioridade: +%d%s\n", COR_AMARELO, impacto, COR_RESET);
    }

    printf("Numero de passageiros: ");
    scanf("%d", &v->passageiros);

    printf("Horario (DD MM AAAA HH MM): ");
    struct tm tm_info = {0};
    scanf("%d %d %d %d %d", &tm_info.tm_mday, &tm_info.tm_mon, &tm_info.tm_year,
          &tm_info.tm_hour, &tm_info.tm_min);
    tm_info.tm_mon--;
    tm_info.tm_year -= 1900;
    v->horario_programado = mktime(&tm_info);

    return v;
}

void adicionar_voo(SistemaAeroporto *s, Voo *v) {
    if (s->total_voos >= s->capacidade) {
        s->capacidade *= 2;
        s->voos = (Voo**)realloc(s->voos, s->capacidade * sizeof(Voo*));
    }

    s->voos[s->total_voos++] = v;
    inserir_heap(s->fila_prioridade, v);
    s->arvore_busca = inserir_avl(s->arvore_busca, v);
    inserir_rn(s->cronograma, v);
    atualizar_estatisticas(s->stats, v, 0);

    SUCESSO("Voo cadastrado com sucesso!");
}

void processar_proximo_voo(SistemaAeroporto *s) {
    if (heap_vazio(s->fila_prioridade)) {
        AVISO("Nenhum voo na fila de prioridade!");
        return;
    }

    if (contar_pistas_livres(s->pistas) == 0) {
        ERRO("Todas as pistas estao ocupadas! Aguarde liberacao.");
        return;
    }

    Voo *v = remover_heap(s->fila_prioridade);

    printf("\n%s╔════════════════════════════════════════════════╗%s\n", COR_AMARELO, COR_RESET);
    printf("%s║          PROCESSANDO PRÓXIMO VOO               ║%s\n", COR_AMARELO, COR_RESET);
    printf("%s╚════════════════════════════════════════════════╝%s\n", COR_AMARELO, COR_RESET);

    imprimir_voo(v);

    if (alocar_pista(s->pistas, v, v->tipo)) {
        if (v->tipo == PARTIDA) {
            printf("\n%s✈ Autorizando decolagem...%s\n", COR_VERDE, COR_RESET);
        } else {
            printf("\n%s✈ Autorizando pouso...%s\n", COR_VERDE, COR_RESET);
        }

        v->status = FINALIZADO;
        atualizar_estatisticas(s->stats, v, 1);
        SUCESSO("Voo processado com sucesso!");
    }
}

void buscar_voo_numero(SistemaAeroporto *s) {
    char numero[10];
    printf("\nNumero do voo: ");
    scanf("%s", numero);

    NoAVL *resultado = buscar_avl(s->arvore_busca, numero);

    if (resultado) {
        printf("\n%s[ENCONTRADO - Busca AVL O(log n)]%s\n", COR_VERDE, COR_RESET);
        imprimir_voo(resultado->voo);
    } else {
        ERRO("Voo nao encontrado no sistema.");
    }
}

void buscar_voos_destino(SistemaAeroporto *s) {
    char destino[50];
    printf("\nDestino: ");
    scanf(" %[^\n]", destino);

    printf("\n%s╔════════════════════════════════════════════════╗%s\n", COR_CIANO, COR_RESET);
    printf("%s║         VOOS PARA %-29s║%s\n", COR_CIANO, destino, COR_RESET);
    printf("%s╚════════════════════════════════════════════════╝%s\n", COR_CIANO, COR_RESET);
    buscar_por_destino(s->arvore_busca, destino);
}

void listar_todos_voos(SistemaAeroporto *s) {
    printf("\n%s╔════════════════════════════════════════════════╗%s\n", COR_MAGENTA, COR_RESET);
    printf("%s║    TODOS OS VOOS (AVL - Em Ordem)              ║%s\n", COR_MAGENTA, COR_RESET);
    printf("%s╚════════════════════════════════════════════════╝%s\n", COR_MAGENTA, COR_RESET);
    imprimir_avl_ordem(s->arvore_busca);
}

void mostrar_cronograma(SistemaAeroporto *s) {
    imprimir_cronograma(s->cronograma);
}

void mostrar_fila_prioridade(SistemaAeroporto *s) {
    imprimir_heap(s->fila_prioridade);
}

void buscar_por_intervalo_horario(SistemaAeroporto *s) {
    struct tm tm_inicio = {0}, tm_fim = {0};

    printf("\nHorario inicial (DD MM AAAA HH MM): ");
    scanf("%d %d %d %d %d", &tm_inicio.tm_mday, &tm_inicio.tm_mon, &tm_inicio.tm_year,
          &tm_inicio.tm_hour, &tm_inicio.tm_min);
    tm_inicio.tm_mon--;
    tm_inicio.tm_year -= 1900;

    printf("Horario final (DD MM AAAA HH MM): ");
    scanf("%d %d %d %d %d", &tm_fim.tm_mday, &tm_fim.tm_mon, &tm_fim.tm_year,
          &tm_fim.tm_hour, &tm_fim.tm_min);
    tm_fim.tm_mon--;
    tm_fim.tm_year -= 1900;

    time_t inicio = mktime(&tm_inicio);
    time_t fim = mktime(&tm_fim);

    printf("\n%s╔════════════════════════════════════════════════╗%s\n", COR_VERDE, COR_RESET);
    printf("%s║    VOOS NO INTERVALO (Rubro-Negra)             ║%s\n", COR_VERDE, COR_RESET);
    printf("%s╚════════════════════════════════════════════════╝%s\n", COR_VERDE, COR_RESET);
    buscar_por_horario(s->cronograma, s->cronograma->raiz, inicio, fim);
}

void atualizar_clima_manual(SistemaAeroporto *s) {
    printf("\n%sCONDIÇÕES METEOROLÓGICAS:%s\n", COR_BOLD, COR_RESET);
    printf("0 - Ensolarado\n");
    printf("1 - Nublado\n");
    printf("2 - Chuvoso\n");
    printf("3 - Tempestade\n");
    printf("4 - Nevoa\n");
    printf("\nEscolha a nova condicao: ");

    int escolha;
    scanf("%d", &escolha);

    if (escolha >= 0 && escolha <= 4) {
        atualizar_clima(s->clima, (CondicaoClima)escolha);
        SUCESSO("Clima atualizado!");
        imprimir_clima(s->clima);
    } else {
        ERRO("Opcao invalida!");
    }
}

void menu_principal() {
    printf("\n");
    printf("%s╔════════════════════════════════════════════════════╗%s\n", COR_BOLD, COR_RESET);
    printf("%s║     SISTEMA DE CONTROLE DE VOOS - AEROPORTO        ║%s\n", COR_BOLD, COR_RESET);
    printf("%s╠════════════════════════════════════════════════════╣%s\n", COR_BOLD, COR_RESET);
    printf("%s║%s  %s1.%s  Cadastrar novo voo                            %s║%s\n",
           COR_BOLD, COR_RESET, COR_VERDE, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s2.%s  Processar proximo voo (Heap)                  %s║%s\n",
           COR_BOLD, COR_RESET, COR_VERDE, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s3.%s  Buscar voo por numero (AVL)                   %s║%s\n",
           COR_BOLD, COR_RESET, COR_AZUL, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s4.%s  Buscar voos por destino (AVL)                 %s║%s\n",
           COR_BOLD, COR_RESET, COR_AZUL, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s5.%s  Listar todos os voos (AVL)                    %s║%s\n",
           COR_BOLD, COR_RESET, COR_AZUL, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s6.%s  Mostrar cronograma (Rubro-Negra)              %s║%s\n",
           COR_BOLD, COR_RESET, COR_MAGENTA, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s7.%s  Mostrar fila de prioridade (Heap)             %s║%s\n",
           COR_BOLD, COR_RESET, COR_VERDE, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s8.%s  Buscar voos por horario (Rubro-Negra)         %s║%s\n",
           COR_BOLD, COR_RESET, COR_MAGENTA, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s╠════════════════════════════════════════════════════╣%s\n", COR_BOLD, COR_RESET);
    printf("%s║%s  %s9.%s  Ver estatisticas do aeroporto                 %s║%s\n",
           COR_BOLD, COR_RESET, COR_CIANO, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s10.%s Status das pistas                             %s║%s\n",
           COR_BOLD, COR_RESET, COR_CIANO, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s11.%s Condicoes meteorologicas                      %s║%s\n",
           COR_BOLD, COR_RESET, COR_CIANO, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s12.%s Alterar clima                                 %s║%s\n",
           COR_BOLD, COR_RESET, COR_AMARELO, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s║%s  %s13.%s Atualizar pistas                              %s║%s\n",
           COR_BOLD, COR_RESET, COR_AMARELO, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s╠════════════════════════════════════════════════════╣%s\n", COR_BOLD, COR_RESET);
    printf("%s║%s  %s0.%s  Sair                                          %s║%s\n",
           COR_BOLD, COR_RESET, COR_VERMELHO, COR_RESET, COR_BOLD, COR_RESET);
    printf("%s╚════════════════════════════════════════════════════╝%s\n", COR_BOLD, COR_RESET);
    printf("\n%sOpcao:%s ", COR_AMARELO, COR_RESET);
}

void liberar_sistema(SistemaAeroporto *s) {
    for (int i = 0; i < s->total_voos; i++) {
        free(s->voos[i]);
    }
    free(s->voos);
    liberar_heap(s->fila_prioridade);
    liberar_avl(s->arvore_busca);
    liberar_rn(s->cronograma, s->cronograma->raiz);
    free(s->cronograma->nulo);
    free(s->cronograma);
    liberar_estatisticas(s->stats);
    free(s->pistas);
    free(s->clima);
    free(s);
}

void banner_inicial() {
    printf("\n");
    printf("%s", COR_CIANO);
    printf("████████████████████████████████████████████████████████\n");
    printf("█                                                      █\n");
    printf("█      SISTEMA DE CONTROLE DE VOOS - AEROPORTO         █\n");
    printf("█                                                      █\n");
    printf("█         Trabalho 3 de EDA2 - Arvores Balanceadas     █\n");
    printf("█                                                      █\n");
    printf("█     # Heap | AVL | Rubro-Negra                       █\n");
    printf("█                                                      █\n");
    printf("████████████████████████████████████████████████████████\n");
    printf("%s\n", COR_RESET);
}

int main() {
    SistemaAeroporto *sistema = criar_sistema();
    int opcao;

    banner_inicial();

    do {
        menu_principal();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                Voo *novo_voo = criar_voo(sistema->clima);
                adicionar_voo(sistema, novo_voo);
                break;
            }
            case 2:
                processar_proximo_voo(sistema);
                break;
            case 3:
                buscar_voo_numero(sistema);
                break;
            case 4:
                buscar_voos_destino(sistema);
                break;
            case 5:
                listar_todos_voos(sistema);
                break;
            case 6:
                mostrar_cronograma(sistema);
                break;
            case 7:
                mostrar_fila_prioridade(sistema);
                break;
            case 8:
                buscar_por_intervalo_horario(sistema);
                break;
            case 9:
                imprimir_estatisticas(sistema->stats);
                break;
            case 10:
                imprimir_status_pistas(sistema->pistas);
                break;
            case 11:
                imprimir_clima(sistema->clima);
                break;
            case 12:
                atualizar_clima_manual(sistema);
                break;
            case 13:
                atualizar_pistas(sistema->pistas);
                INFO("Pistas atualizadas!");
                break;
            case 0:
                printf("\n%sEncerrando sistema...%s\n", COR_AMARELO, COR_RESET);
                break;
            default:
                ERRO("Opcao invalida!");
        }

        if (opcao != 0) {
            printf("\n%sPressione ENTER para continuar...%s", COR_DIM, COR_RESET);
            getchar();
            getchar();
        }

    } while(opcao != 0);

    liberar_sistema(sistema);
    printf("\n%s✓ Sistema finalizado. Ate logo!%s\n\n", COR_VERDE, COR_RESET);

    return 0;
}
