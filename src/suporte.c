#include <stdio.h>
#include <string.h>
#include <time.h>
#include "autenticacao.h"
#include "utils.h"
#include "suporte.h"

void enviarMensagemSuporte() {
    MensagemSuporte novaMensagem;
    
    strcpy(novaMensagem.nome, usuarioLogado.nome);
    strcpy(novaMensagem.email, usuarioLogado.email);
    printf("\tSUPORTE\n\n");
    printf("Digite sua mensagem: (Até 500 caracteres)\n");
    fgets(novaMensagem.mensagem, 500, stdin);
    novaMensagem.mensagem[strcspn(novaMensagem.mensagem, "\n")] = '\0';
    strcpy(novaMensagem.data_hora, obterDataAtual());

    FILE* arquivo = fopen("mensagens_suporte.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "Nome: %s\n", novaMensagem.nome);
        fprintf(arquivo, "Email: %s\n", novaMensagem.email);
        fprintf(arquivo, "Data/Hora: %s\n", novaMensagem.data_hora);
        fprintf(arquivo, "Mensagem: %s\n\n", novaMensagem.mensagem);
        fclose(arquivo);
        Limpar_Tela();
        printf("Mensagem enviada com sucesso!\n");
    } else {
        Limpar_Tela();
        printf("Erro ao abrir o arquivo.\n");
    }
}


NoMensagemSuporte* novoNoMensagemSuporte(MensagemSuporte mensagem) {
    NoMensagemSuporte* novo = (NoMensagemSuporte*) malloc(sizeof(NoMensagemSuporte));
    if (novo != NULL) {
        novo->mensagem = mensagem;
        novo->proximo = NULL;
    }
    return novo;
}

void imprimirMensagensSuporte(NoMensagemSuporte* lista) {
    NoMensagemSuporte* atual = lista;
    while (atual != NULL) {
        printf("Nome: %s\n", atual->mensagem.nome);
        printf("Email: %s\n", atual->mensagem.email);
        printf("Data/Hora: %s\n", atual->mensagem.data_hora);
        printf("Mensagem: %s\n\n", atual->mensagem.mensagem);
        atual = atual->proximo;
    }
}

NoMensagemSuporte* carregarMensagensSuporte() {
    FILE* arquivo = fopen("mensagens_suporte.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    NoMensagemSuporte* comeco = NULL;
    NoMensagemSuporte* atual = NULL;
    MensagemSuporte mensagem;

    while (fscanf(arquivo, "Nome: %[^\n]\n", mensagem.nome) == 1) {
        fscanf(arquivo, "Email: %[^\n]\n", mensagem.email);
        fscanf(arquivo, "Data/Hora: %[^\n]\n", mensagem.data_hora);
        fscanf(arquivo, "Mensagem: %[^\n]\n\n", mensagem.mensagem);

        NoMensagemSuporte* novoNo = novoNoMensagemSuporte(mensagem);
        if (novoNo == NULL) {
            printf("Erro ao alocar memória.\n");
            fclose(arquivo);
            return NULL;
        }

        if (comeco == NULL) {
            comeco = novoNo;
            atual = comeco;
        } else {
            atual->proximo = novoNo;
            atual = atual->proximo;
        }
    }

    fclose(arquivo);
    return comeco;
}

