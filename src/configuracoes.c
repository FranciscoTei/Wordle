#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "wordle.h"
#include "autenticacao.h"
#include "configuracoes.h"
#include "suporte.h"
#include "utils.h"

void menuConfiguracoes() {
    int opcao;
    int quantidade = 0;
    Usuario* usuarios = carregarUsuarios(&quantidade);
    do {
        printf("\tCONFIGURAÇÕES\n\n");
        printf("\t1. Meu perfil\n");
        printf("\t2. Alterar email\n");
        printf("\t3. Alterar senha\n");
        printf("\t4. Deletar conta\n");
        printf("\t5. Contatar suporte\n");
        printf("\t0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                Limpar_Tela();
                mostrarPerfil();
                break;
            case 2:
                Limpar_Tela();
                alterarEmail(usuarios, quantidade);
                break;
            case 3:
                Limpar_Tela();
                alterarSenha();
                break;
            case 4:
                Limpar_Tela();
                deletarConta(usuarios, &quantidade);
                return;
            case 5:
                Limpar_Tela();
                enviarMensagemSuporte();
                break;
            case 0:
                return;
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void mostrarPerfil() {
    printf("\n\tMEU PERFIL\n\n");
    printf("\tID: %s\n", usuarioLogado.id);
    printf("\tNome: %s\n", usuarioLogado.nome);
    printf("\tUsername: %s\n", usuarioLogado.username);
    printf("\tData de Nascimento: %s\n", usuarioLogado.data_nascimento);
    printf("\tNacionalidade: %s\n", usuarioLogado.nacionalidade);
    printf("\tEmail: %s\n", usuarioLogado.email);
    printf("\tData de Registro: %s\n", usuarioLogado.data_registro);
    printf("\t\n--- Status do Jogo ---\n");
    printf("\t\tJogos: %d\n", usuarioLogado.status.jogos);
    printf("\t\tPontos: %d\n", usuarioLogado.status.pontos);
    printf("\t\tVitórias: %d\n", usuarioLogado.status.vitorias);
    printf("\t\tPerdidas: %d\n", usuarioLogado.status.perdidas);
    printf("\t\tDesistências: %d\n", usuarioLogado.status.desistencias);
}

void alterarEmail(Usuario* usuarios, int quantidade) {
    char novoEmail[100];
    do {
        printf("Digite o novo email: ");
        fgets(novoEmail, 100, stdin);
        novoEmail[strcspn(novoEmail, "\n")] = '\0';

        if (!validarEmail(novoEmail)) {
            printf("Email inválido! Tente novamente.\n");
        } else if (!verificarEmailUnico(novoEmail, usuarios, quantidade)) {
            printf("Email já em uso! Tente novamente.\n");
        }
    } while (!validarEmail(novoEmail) || !verificarEmailUnico(novoEmail, usuarios, quantidade));

    strcpy(usuarioLogado.email, novoEmail);
    printf("Email alterado com sucesso!\n");
}

void alterarSenha() {
    char novaSenha[50];
    printf("Digite a nova senha: ");
    fgets(novaSenha, 50, stdin);
    novaSenha[strcspn(novaSenha, "\n")] = '\0';
    strcpy(usuarioLogado.senha, novaSenha);
    printf("Senha alterada com sucesso!\n");
}

void deletarConta1(Usuario* usuarios, int* quantidade) {
    char confirmacao;
    printf("Tem certeza que deseja deletar sua conta? (s/n): ");
    scanf(" %c", &confirmacao);
    if (confirmacao == 's' || confirmacao == 'S') {
        for (int i = 0; i < *quantidade; i++) {
            if (strcmp(usuarios[i].id, usuarioLogado.id) == 0) {
                for (int j = i; j < *quantidade - 1; j++) {
                    usuarios[j] = usuarios[j + 1];
                }
                (*quantidade)--;
                salvarUsuarios(usuarios, *quantidade);
                printf("Conta deletada com sucesso!\n");
                return;
            }
        }
    } else {
        printf("Operação cancelada.\n");
    }
}

void deletarConta(Usuario* usuarios, int* quantidade) {
    char confirmacao[100];
    printf("Digite 'CONFIRMAR' para deletar sua conta: ");
    fgets(confirmacao, 100, stdin);
    confirmacao[strcspn(confirmacao, "\n")] = '\0';

    if (strcmp(confirmacao, "CONFIRMAR") == 0) {
        int posicao = -1;
        for (int i = 0; i < *quantidade; i++) {
            if (strcmp(usuarios[i].id, usuarioLogado.id) == 0) {
                posicao = i;
                break;
            }
        }

        if (posicao != -1) {
            for (int i = posicao; i < *quantidade - 1; i++) {
                usuarios[i] = usuarios[i + 1];
            }
            (*quantidade)--;
            usuarios = realloc(usuarios, (*quantidade) * sizeof(Usuario));
            salvarUsuarios(usuarios, *quantidade);
            printf("Conta deletada com sucesso!\n");
        }
    } else {
        printf("Confirmação falhou. A conta não foi deletada.\n");
    }
}
