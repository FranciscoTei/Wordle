TARGET = main

CC = gcc
CFLAGS = -Wall -Wextra -g 

SRC = main.c src/wordle.c src/utils.c src/funcoes.c src/autenticacao.c src/configuracoes.c src/suporte.c src/ranking.c

TESTE_TARGET = teste
TESTE_SRC = testes/teste.c

TEST_TARGET = test
TEST_SRC = tests/test_wordle.c lib/Unity/unity.c src/wordle.c src/utils.c src/funcoes.c src/autenticacao.c src/configuracoes.c src/suporte.c src/ranking.c

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE_EXT = .exe
else
    RM = rm -f
    EXE_EXT =
endif

.PHONY: all
all: $(TARGET)$(EXE_EXT)

$(TARGET)$(EXE_EXT): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET)$(EXE_EXT) $(SRC)
	./$(TARGET)$(EXE_EXT)
	$(RM) $(TARGET)$(EXE_EXT)

.PHONY: teste
teste: $(TEST_TARGET)$(EXE_EXT)

$(TEST_TARGET)$(EXE_EXT): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TARGET)$(EXE_EXT) $(TEST_SRC)
	./$(TEST_TARGET)$(EXE_EXT)
	$(RM) $(TEST_TARGET)$(EXE_EXT)

.PHONY: coverage
coverage: $(TEST_TARGET)$(EXE_EXT)
	./$(TEST_TARGET)$(EXE_EXT)
	gcovr -r . --html --html-details -o coverage.html


.PHONY: clean
clean:
	$(RM) $(TARGET)$(EXE_EXT) $(TEST_TARGET)$(EXE_EXT)

.PHONY: gdb
gdb: $(TARGET)$(EXE_EXT)
	$(CC) $(CFLAGS) -o $(TARGET)$(EXE_EXT) $(SRC)
	gdb ./$(TARGET)$(EXE_EXT)