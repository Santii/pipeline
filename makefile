# Makefile para "Simulador de pipeline com 5 estagios do MIPS" 
# Criado por Bianca Cristiane Ferreira Santiago
#
# Makefile, separando os diferentes elementos da aplicacao
# como codigo (src), cabecalhos (include), executaveis (build), bibliotecas (lib), etc.
# Cada elemento e alocado em uma pasta especifica, organizando melhor o codigo fonte.
#
# Algumas variaveis sao usadas com significado especial:
#
# $@ nome do alvo (target)
# $^ lista com os nomes de todos os pre-requisitos sem duplicatas
# $< nome do primeiro pre-requisito
#
# Comandos do sistema operacional
# Linux: rm -rf
# Windows: cmd //C del
RM = rm -rf

# Compilador
CC = g++

# Variaveis para os subdiretorios
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./build
BIN_DIR = ./bin
DOC_DIR = ./doc
DAT_DIR = ./data
TEST_DIR = ./test

# Outras variaveis

# Opcoes de compilacao
CFLAGS = -Wall -pedantic -ansi -std=c++11 -I $(INC_DIR)

# Garante que os alvos desta lista nao sejam confundidos com arquivos de mesmo nome
.PHONY: all clean distclean doxy

# Define o alvo (target) para a compilacao completa.
# Ao final da compilacao, remove os arquivos objeto.
all: pipeline doxy
debug: CFLAGS += -g -O0
debug: pipeline

# Alvo (target) para a construcao do executavel pipeline.exe
# Define os arquivos command.o, files.o e main.o como dependencias
pipeline: $(OBJ_DIR)/command.o $(OBJ_DIR)/files.o $(OBJ_DIR)/main.o
	@echo "============="
	@echo "Ligando o alvo $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@.exe $^
	@echo "+++ [Executavel pipeline.exe criado em $(BIN_DIR)] +++"
	@echo "============="

# Alvo (target) para a construcao do objeto command.o
# Define os arquivos command.cpp e command.h como dependencias.
$(OBJ_DIR)/command.o: $(SRC_DIR)/command.cpp $(INC_DIR)/command.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto files.o
# Define os arquivos files.cpp e files.h como dependencias.
$(OBJ_DIR)/files.o: $(SRC_DIR)/files.cpp $(INC_DIR)/files.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto main.o
# Define o arquivo main.cpp como dependencias.
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a geração automatica de documentacao usando o Doxygen.
# Sempre remove a documentacao anterior (caso exista) e gera uma nova.
#doxy:
#	$(RM) $(DOC_DIR)/*
#	doxygen Doxyfile

# Alvo (target) usado para limpar os arquivos temporarios (objeto)
# gerados durante a compilacao, assim como os arquivos binarios/executaveis.
clean:
	$(RM) $(BIN_DIR)/*.exe
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(DAT_DIR)/output/*.dat
