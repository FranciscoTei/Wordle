#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "autenticacao.h"
#include "utils.h"

Usuario usuarioLogado;

void menuLogin() {
    printf("\n\t MENU LOGIN\n\n");
    printf("\t1. Login\n");
    printf("\t2. Cadastro\n");
    printf("\t3. Suporte\n");
    printf("\t4. Sair\n");
    printf("======================\n");
}


int validarEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return at != NULL && dot != NULL && at < dot;
}


int gerarNovoID(Usuario* usuarios, int quantidade) {
    int ultimoID = 0;
    for (int i = 0; i < quantidade; i++) {
        int idAtual = atoi(usuarios[i].id);
        if (idAtual > ultimoID) {
            ultimoID = idAtual;
        }
    }
    return ultimoID + 1;
}

int verificarUsernameUnico(const char* username, Usuario* usuarios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(usuarios[i].username, username) == 0) {
            return 0;
        }
    }
    return 1;
}

int verificarEmailUnico(const char* email, Usuario* usuarios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            return 0;
        }
    }
    return 1;
}

char* obterDataAtual() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    static char dataAtual[11];
    snprintf(dataAtual, 11, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    return dataAtual;
}

int cadastroUsuario() {
    Usuario novoUsuario;
    int quantidade = 0;
    Usuario* usuarios = carregarUsuarios(&quantidade);

    int novoID = gerarNovoID(usuarios, quantidade);
    snprintf(novoUsuario.id, 20, "%d", novoID);
    printf("\tCADASTRO\n\n");
    printf("Digite seu nome: ");
    fgets(novoUsuario.nome, 100, stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = '\0';
    do {
        printf("Digite seu username: ");
        fgets(novoUsuario.username, 50, stdin);
        novoUsuario.username[strcspn(novoUsuario.username, "\n")] = '\0';

        if (!verificarUsernameUnico(novoUsuario.username, usuarios, quantidade)) {
            printf("Username já em uso, escolha outro.\n");
        }
    } while (!verificarUsernameUnico(novoUsuario.username, usuarios, quantidade));

    printf("Digite sua data de nascimento (DD/MM/AAAA): ");
    fgets(novoUsuario.data_nascimento, 11, stdin);
    novoUsuario.data_nascimento[strcspn(novoUsuario.data_nascimento, "\n")] = '\0';
    getchar();

    printf("Digite sua nacionalidade: ");
    fgets(novoUsuario.nacionalidade, 50, stdin);
    novoUsuario.nacionalidade[strcspn(novoUsuario.nacionalidade, "\n")] = '\0';

    do {
        printf("Digite seu email: ");
        fgets(novoUsuario.email, 100, stdin);
        novoUsuario.email[strcspn(novoUsuario.email, "\n")] = '\0';

        if (!validarEmail(novoUsuario.email)) {
            printf("Email inválido! Tente novamente.\n");
        } else if (!verificarEmailUnico(novoUsuario.email, usuarios, quantidade)) {
            printf("Email já em uso! Tente novamente.\n");
        }
    } while (!validarEmail(novoUsuario.email) || !verificarEmailUnico(novoUsuario.email, usuarios, quantidade));
    printf("Digite sua senha: ");
    fgets(novoUsuario.senha, 50, stdin);
    novoUsuario.senha[strcspn(novoUsuario.senha, "\n")] = '\0';

    strcpy(novoUsuario.data_registro, obterDataAtual());

    novoUsuario.status.jogos = 0;
    novoUsuario.status.vitorias = 0;
    novoUsuario.status.perdidas = 0;
    novoUsuario.status.desistencias = 0;
    novoUsuario.status.pontos = 0;

    usuarios = realloc(usuarios, (quantidade + 1) * sizeof(Usuario));
    usuarios[quantidade] = novoUsuario;
    quantidade++;

    salvarUsuarios(usuarios, quantidade);
    free(usuarios);
    usuarioLogado = novoUsuario;
    Limpar_Tela();
    printf("Usuário cadastrado com sucesso!\n");
    return 1;
}

Usuario* encontrarUsuarioPorUsername(Usuario* usuarios, int quantidade, const char* username) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(usuarios[i].username, username) == 0) {
            return &usuarios[i];
        }
    }
    return NULL;
}

int loginUsuario() {
    char username[50];
    char senha[50];
    int quantidade = 0;
    Usuario* usuarios = carregarUsuarios(&quantidade);
    printf("\tLOGIN\n\n");
    printf("Digite seu username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Digite sua senha: ");
    fgets(senha, 50, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    Usuario* usuarioEncontrado = encontrarUsuarioPorUsername(usuarios, quantidade, username);

    if (usuarioEncontrado != NULL && strcmp(usuarioEncontrado->senha, senha) == 0) {
        Limpar_Tela();
        printf("Login bem-sucedido! Bem-vindo, %s\n", usuarioEncontrado->nome);
        usuarioLogado = *usuarioEncontrado;
        free(usuarios);
        return 1;
    } else {
        Limpar_Tela();
        printf("Username ou senha incorretos.\n");
        free(usuarios);
        return 0;
    }
}

Usuario* carregarUsuarios(int* quantidade) {
    FILE* arquivo = fopen("dados/usuarios.bin", "rb");
    if (arquivo == NULL) {
        *quantidade = 0;
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    *quantidade = tamanhoArquivo / sizeof(Usuario);
    Usuario* usuarios = malloc(tamanhoArquivo);
    fread(usuarios, sizeof(Usuario), *quantidade, arquivo);

    fclose(arquivo);
    return usuarios;
}

void salvarUsuarios(Usuario* usuarios, int quantidade) {
    FILE* arquivo = fopen("dados/usuarios.bin", "wb");
    if (arquivo != NULL) {
        fwrite(usuarios, sizeof(Usuario), quantidade, arquivo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo para salvar os usuários.\n");
    }
}