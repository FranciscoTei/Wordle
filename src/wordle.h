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

/**
 * @enum Status
 * @brief Representa o status de um jogo de Wordle.
 * 
 * @var VENCEU
 * Indica que o jogador venceu o jogo.
 * @var PERDEU
 * Indica que o jogador perdeu o jogo.
 * @var DESISTIU
 * Indica que o jogador desistiu do jogo.
 */
typedef enum {
    VENCEU,
    PERDEU,
    DESISTIU
} Status;

/**
 * @struct Jogo
 * @brief Representa uma jogada no jogo de Wordle.
 * 
 * @var chute
 * Armazena a palavra chutada pelo jogador.
 * @var resultado
 * Armazena o resultado do chute, indicando quais letras estão corretas.
 */
typedef struct {
    char chute[6];
    char resultado[60];
} Jogo;

/**
 * @struct Historico
 * @brief Armazena o histórico de um jogo de Wordle.
 * 
 * @var nome
 * Nome do jogador.
 * @var palavra
 * Palavra correta que o jogador deve adivinhar.
 * @var data
 * Data em que o jogo foi jogado.
 * @var jogadas
 * Lista de jogadas feitas pelo jogador.
 * @var chutes_totais
 * Número total de chutes feitos pelo jogador.
 * @var status
 * Status final do jogo.
 */
typedef struct {
    char nome[50];
    char palavra[6];
    char data[11];
    Jogo jogadas[6];
    int chutes_totais;
    Status status;
} Historico;

/**
 * @enum Dica
 * @brief Representa o tipo de dica fornecida ao jogador.
 * 
 * @var CORRETA
 * Indica que a letra está na posição correta.
 * @var POSI_ERRADA
 * Indica que a letra está na palavra, mas na posição errada.
 * @var ERRADA
 * Indica que a letra não está na palavra.
 */
typedef enum {
    CORRETA,
    POSI_ERRADA,
    ERRADA
} Dica;

/**
 * @brief Inicia um jogo de Wordle com a quantidade de letras especificada.
 * 
 * @param qtd_letras
 * Número de letras na palavra a ser adivinhada.
 */
void wordle(int qtd_letras);

/**
 * @brief Carrega a lista de palavras possíveis para o jogo.
 */
void load_palavras();

/**
 * @brief Sorteia uma palavra aleatória.
 *
 * Esta função seleciona uma palavra aleatória e a armazena no buffer fornecido.
 *
 * @param palavra Ponteiro para um buffer onde a palavra sorteada será armazenada.
 *                 O buffer deve ser grande o suficiente para armazenar a palavra.
 *
 * @return Retorna 0 em caso de sucesso, ou um valor negativo em caso de erro.
 */
int sorteia_palavra(char *palavra);

/**
 * @brief Valida o chute do jogador.
 * 
 * @param chute Ponteiro para a string contendo o chute do jogador.
 * @param qtd_letras Número de letras que o chute deve conter.
 * @return int Retorna 1 se o chute for válido, 0 caso contrário.
 */
int validaChute(char* chute, int qtd_letras);

/**
 * @brief Atualiza o histórico de chutes no arquivo especificado.
 * 
 * @param filename Nome do arquivo onde o histórico será atualizado.
 * @param index Índice do chute no histórico.
 * @param novoChute Ponteiro para a estrutura Jogo contendo o novo chute.
 */
void atualizarHistorico(const char *filename, int index, const Jogo *novoChute);

/**
 * @brief Compara o chute do jogador com a palavra secreta.
 * 
 * @param chute Ponteiro para a string contendo o chute do jogador.
 * @param secreta Ponteiro para a string contendo a palavra secreta.
 * @param resultado Ponteiro para a string onde o resultado da comparação será armazenado.
 */
void comparar_palavras(const char *chute, const char *secreta, char *resultado);

/**
 * @brief Gera o resultado da comparação entre o chute e a palavra secreta.
 * 
 * @param resultado Ponteiro para a string onde o resultado será armazenado.
 * @param dica Ponteiro para a estrutura Dica que será atualizada com o resultado.
 */
void gerar_resultado(char *resultado, Dica *dica);

/**
 * @brief Exibe as regras do jogo.
 */
void exibirRegras();

/**
 * @brief Exibe o ranking dos jogadores.
 */
void exibirRanking();

#endif
