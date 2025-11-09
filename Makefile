CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
TARGET = aeroporto
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "\033[1;32m✓ Compilacao concluida com sucesso!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "\033[1;33m✓ Arquivos limpos!\033[0m"

run: $(TARGET)
	./$(TARGET)

help:
	@echo "Comandos disponiveis:"
	@echo "  make          - Compila o projeto"
	@echo "  make run      - Compila e executa o projeto"
	@echo "  make clean    - Remove arquivos compilados"
	@echo "  make help     - Mostra esta mensagem"

.PHONY: all clean run help
