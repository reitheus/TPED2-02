# Variáveis
CC = gcc
CFLAGS = -Wall -Iinclude
EXEC = ordena
SRC_DIR =  src
OBJ_DIR = src


SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#regra padrão
all: $(EXEC)
	
# Regra de compilação
$(EXEC): $(OBJS)
	@$(CC) -o $@ $^ 
	@rm -f $(OBJ_DIR)/*.o

# Regra de compilação dos objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

