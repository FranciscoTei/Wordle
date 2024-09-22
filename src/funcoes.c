#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "wordle.h"
#include "autenticacao.h"
#include "configuracoes.h"
#include "suporte.h"
#include "utils.h"
#include "ranking.h"

void printBanner() {
    printf("╔════════════════════════════════════════╗\n");
    printf("║              W O R D L E               ║\n");
    printf("║     Você pode adivinhar a palavra?     ║\n");
    printf("╚════════════════════════════════════════╝\n");
}


void sair() {
    printf("\nSaindo do sistema...\n");
}

void listar_usuarios() {
    FILE *arquivo = fopen("dados/usuarios.bin", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivoo");
        return;
    }

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, arquivo) == 1) {
        printf("ID: %s\n", usuario.id);
        printf("Nome: %s\n", usuario.nome);
        printf("Data de Nascimento: %s\n", usuario.data_nascimento);
        printf("Nacionalidade: %s\n", usuario.nacionalidade);
        printf("Email: %s\n", usuario.email);
        printf("Data de Registro: %s\n", usuario.data_registro);
        printf("Status: \n");
        printf("  Jogos: %d\n", usuario.status.jogos);
        printf("  Vitórias: %d\n", usuario.status.vitorias);
        printf("  Perdidas: %d\n", usuario.status.perdidas);
        printf("  Desistências: %d\n", usuario.status.desistencias);
        printf("\n");
    }

    fclose(arquivo);
}

void menuInicial() {
    int opcao;
    load_palavras();

    printf("\n\tMENU INICIAL\n\n");
    printf("\t1. Jogar\n");
    printf("\t2. Regras\n");
    printf("\t3. Ranking\n");
    printf("\t4. Configurações\n");
    printf("\t5. Sair\n");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            Limpar_Tela();
            wordle(5);
            break;
        case 2:
            Limpar_Tela();
            exibirRegras();
            break;
        case 3:
            Limpar_Tela();
            exibirRanking();
            break;
        case 4:
            Limpar_Tela();
            menuConfiguracoes();
            break;
        case 5:
            sair();
            break;
        default:
            Limpar_Tela();
            printf("Opção inválida! Tente novamente.\n");
    }
}