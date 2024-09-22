#ifndef WORDLE_H
#define WORDLE_H

#include <ctype.h>

#define RED "\x1b[41m"
#define YELLOW "\x1b[43m"
#define GREEN "\x1b[42m"
#define RESET "\x1b[0m"

#define MAX_LINHA 100
#define MAX_PALAVRAS 262000
#define TAMANHO_PALAVRA 30

typedef enum {
    VENCEU,
    PERDEU,
    DESISTIU
} Status;


typedef struct {
    char chute[6];
    char resultado[60];
} Jogo;


typedef struct {
    char nome[50];
    char palavra[6];
    char data[11];
    Jogo jogadas[6];
    int chutes_totais;
    Status status;
} Historico;

typedef enum {
    CORRETA,
    POSI_ERRADA,
    ERRADA
} Dica;

void wordle(int qtd_letras);
void load_palavras();
int sorteia_palavra(char *palavra);
int validaChute(char* chute, int qtd_letras);
void atualizarHistorico(const char *filename, int index, const Jogo *novoChute);
void comparar_palavras(const char *chute, const char *secreta, char *resultado);
void gerar_resultado(char *resultado, Dica *dica);
void exibirRegras();
void exibirRanking();

#endif
