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
    printf("Digite sua mensagem: ");
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
