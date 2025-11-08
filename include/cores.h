#ifndef CORES_H
#define CORES_H

#define COR_RESET   "\x1b[0m"
#define COR_VERMELHO "\x1b[31m"
#define COR_VERDE   "\x1b[32m"
#define COR_AMARELO "\x1b[33m"
#define COR_AZUL    "\x1b[34m"
#define COR_MAGENTA "\x1b[35m"
#define COR_CIANO   "\x1b[36m"
#define COR_BRANCO  "\x1b[37m"

#define COR_BOLD    "\x1b[1m"
#define COR_DIM     "\x1b[2m"

#define SUCESSO(msg) printf("%s%s[OK]%s %s%s\n", COR_BOLD, COR_VERDE, COR_RESET, msg, COR_RESET)
#define ERRO(msg) printf("%s%s[ERRO]%s %s%s\n", COR_BOLD, COR_VERMELHO, COR_RESET, msg, COR_RESET)
#define AVISO(msg) printf("%s%s[AVISO]%s %s%s\n", COR_BOLD, COR_AMARELO, COR_RESET, msg, COR_RESET)
#define INFO(msg) printf("%s%s[INFO]%s %s%s\n", COR_BOLD, COR_CIANO, COR_RESET, msg, COR_RESET)

#endif
