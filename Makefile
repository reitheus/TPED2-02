# Variáveis
CC = gcc
CFLAGS = -Wall -g -Iinclude
EXEC = programa.exe
SRC_DIR =  src
OBJ_DIR = obj


SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#regra padrão
all: $(EXEC)
	
# Regra de compilação
$(EXEC): $(OBJS)
	$(CC) -o $@ $^

# Regra de compilação dos objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	rm -f $(OBJ_DIR)/*.o 

distclean: clean
	rm -rf $(OBJ_DIR)

