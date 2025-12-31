# Compilador e Flags
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm

# Dependências comuns (Objetos)
COMMON_OBJS = vertice.o warden.o

# Headers (para garantir recompilação se mudar o .h)
HEADERS = vertice.h warden.h funcoes.h heap.h array.h

# --- ALVOS (TARGETS) ---

all: trab1 second improve

# 1. Implementação Principal (Heap) - Nome obrigatório: trab1
trab1: vanilla.o heap.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o trab1 vanilla.o heap.o $(COMMON_OBJS) $(LDFLAGS)

# 2. Segunda Implementação (Array)
second: second.o array.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o second second.o array.o $(COMMON_OBJS) $(LDFLAGS)

# 3. Melhoria Prática (Fast I/O)
improve: improve.o heap.o $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o improve improve.o heap.o $(COMMON_OBJS) $(LDFLAGS)

# --- REGRAS DE COMPILAÇÃO GENÉRICAS ---

# Compila qualquer .c para .o, verificando os headers
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# # Limpeza
# clean:
# 	rm -f *.o trab1 second improve rascunho

# Teste Rápido (Opcional)
run: all
	@echo "--- Rodando trab1 (Heap) ---"
	./trab1 caso_teste_pequeno_3.txt saida_heap.txt
	@echo "--- Rodando second (Array) ---"
	./second caso_teste_pequeno_3.txt saida_array.txt
	@echo "--- Rodando improve (Melhoria) ---"
	./improve caso_teste_pequeno_3.txt saida_improve.txt