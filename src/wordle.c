#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "wordle.h"
#include "utils.h"

//char palavras[260000][10];

#define MAX_LINHA 100

int sorteia_palavra(char *palavra) {
    FILE *palavras = fopen("dados/lista_sem_acentos.txt", "r");
    if (!palavras) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    srand(time(NULL));
    int qtd_palavras = 262001;
    int linha_sorteada = rand() % qtd_palavras + 1;
    int linha_atual = 1;
    while (strlen(palavra) != 5) {
        linha_sorteada = rand() % qtd_palavras + 1;
        fseek(palavras, 0, SEEK_SET);
        linha_atual = 1;
        while (fgets(palavra, MAX_LINHA, palavras)) {
            if (linha_atual == linha_sorteada) {
                palavra[strcspn(palavra, "\n")] = '\0';
                break;
            }
            linha_atual++;
        }
    }
    printf("A Palavra sorteada foi: %s (linha %d)\n", palavra, linha_sorteada);
    fclose(palavras);
    return 0;
}

#define MAX_PALAVRAS 262000
#define TAMANHO_PALAVRA 30



char (*palavras)[TAMANHO_PALAVRA];

void load_palavras() {
    FILE *arq_palavras = fopen("dados/lista_sem_acentos.txt", "r");
    int linha_palavra = 0;

    if (arq_palavras == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    palavras = malloc(MAX_PALAVRAS * TAMANHO_PALAVRA * sizeof(char));
    if (!palavras) {
        printf("Erro ao alocar memória");
        fclose(arq_palavras);
        return;
    }

    while (fgets(palavras[linha_palavra], TAMANHO_PALAVRA, arq_palavras)) {
        palavras[linha_palavra][strcspn(palavras[linha_palavra], "\n")] = '\0';
        linha_palavra++;
    }
    printf("Palavras carregadas com sucesso\n");
    fclose(arq_palavras);
}

int validaChute(char* chute, int qtd_letras) {
    if (strlen(chute) != (size_t)qtd_letras) {
        printf("O chute deve ter 5 letras\n");
        return 0;
    }

    int esquerda = 0, direita = MAX_PALAVRAS - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(palavras[meio], chute);
        if (cmp == 0) {
            return 1;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return 0;
}

void atualizarHistorico(const char *filename, int index, const Jogo *novoChute) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    long offset = index * sizeof(Historico);

    fseek(file, offset, SEEK_SET);

    Historico historico;
    if (fread(&historico, sizeof(Historico), 1, file) != 1) {
        perror("Erro ao ler o registro");
        fclose(file);
        return;
    }

    if (historico.chutes_totais < 6) {
        historico.jogadas[historico.chutes_totais] = *novoChute;
        historico.chutes_totais++;
    } else {
        printf("Número máximo de chutes alcançado.\n");
    }

    fseek(file, offset, SEEK_SET);

    if (fwrite(&historico, sizeof(Historico), 1, file) != 1) {
        perror("Erro ao escrever o registro");
    }

    fclose(file);
}

void print_palavra_formatada(const char *palavra) {
    for (int i = 0; i < 5; i++) {
        printf("%c ", toupper(palavra[i]));
    }
    printf("\n");
}

void comparar_palavras(const char *chute, const char *secreta, char *resultado) {
    Dica dica[5];
    int letras_checadas[5] = {0};


    memset(dica, ERRADA, sizeof(dica));

    for (int i = 0; i < 5; i++) {
        if (chute[i] == secreta[i]) {
            dica[i] = CORRETA;
            letras_checadas[i] = 1;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (dica[i] != CORRETA) {
            for (int j = 0; j < 5; j++) {
                if (i != j && chute[i] == secreta[j] && !letras_checadas[j]) {
                    dica[i] = POSI_ERRADA;
                    letras_checadas[j] = 1;
                    break;
                }
            }
            if (dica[i] != POSI_ERRADA) {
                dica[i] = ERRADA;
            }
        }
    }
    gerar_resultado(resultado, dica);
    //printf("%s\n", resultado);
}

void gerar_resultado(char *resultado, Dica *dica) {
    resultado[0] = '\0';

    for (int i = 0; i < 5; i++) {
        switch (dica[i]) {
            case CORRETA:
                strcat(resultado, GREEN);
                strcat(resultado, "  ");
                strcat(resultado, RESET);
                break;
            case POSI_ERRADA:
                strcat(resultado, YELLOW);
                strcat(resultado, "  ");
                strcat(resultado, RESET);
                break;
            case ERRADA:
                strcat(resultado, RED);
                strcat(resultado, "  ");
                strcat(resultado, RESET);
                break;
            default:
                break;
        }
    }
}

void wordle(int qtd_letras) {
    Historico historico;
    char palavra[6], chute[6];
    sorteia_palavra(palavra);

    int status_temp;
    char dados_jogador[] = "Jogador1 04/09/2024 0 1";
    sscanf(dados_jogador, "%s %s %d %d", historico.nome, historico.data, &historico.chutes_totais, &status_temp);
    strcpy(historico.palavra, palavra);
    historico.status = (Status)status_temp;

    FILE *file = fopen("dados/historico.bin", "rb+");
    
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    if(fwrite(&historico, sizeof(Historico), 1, file) != 1) {
        perror("Erro ao escrever o registro");
        fclose(file);
        return;
    }

    fclose(file);


    int qtd_chutes = 0;
    while (qtd_chutes < 6) {

        printf("Digite seu chute:\n");
        scanf("%s", chute);
        if (validaChute(chute, qtd_letras)) {
            char resultado_dica[60];;
            //print_palavra_formatada(chute);
            comparar_palavras(chute, palavra, resultado_dica);
            Jogo novoChute;
            strcpy(novoChute.chute, chute);
            strcpy(novoChute.resultado, resultado_dica);
            //printf("resultado: %s\n", resultado_dica);
            atualizarHistorico("dados/historico.bin", 0, &novoChute);

            Historico historico1;
            FILE *file1 = fopen("dados/historico.bin", "rb+");
            Limpar_Tela();
            if(fread(&historico1, sizeof(Historico), 1, file1) == 1) {
                for (int i = 0; i < historico1.chutes_totais; i++) {
                    print_palavra_formatada(historico1.jogadas[i].chute);
                    printf("%s\n", historico1.jogadas[i].resultado);
                }
            }
            if (strcmp(chute, palavra) == 0) {
                printf("Voce acertou!\n");
                return;
            }
        }
        qtd_chutes++;
    }
}