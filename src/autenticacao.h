#ifndef AUTENTICACAO_H
#define AUTENTICACAO_H
typedef struct {
    int pontos;
    int jogos;
    int vitorias;
    int perdidas;
    int desistencias;
} Stats;

typedef struct {
    char id[20]; 
    char nome[100];
    char username[25];
    char data_nascimento[11];
    char nacionalidade[50];
    char email[100];
    char senha[50];
    char data_registro[11];
    Stats status;
} Usuario;

extern Usuario usuarioLogado;

void menuLogin();
int loginUsuario();
int cadastroUsuario();
char* obterDataAtual();
int validarEmail(const char *email);
Usuario* carregarUsuarios(int* quantidade);
void salvarUsuarios(Usuario* usuarios, int quantidade);
Usuario* encontrarUsuarioPorEmail(Usuario* usuarios, int quantidade, const char* email);
Usuario* encontrarUsuarioPorUsername(Usuario* usuarios, int quantidade, const char* username);
int verificarEmailUnico(const char* email, Usuario* usuarios, int quantidade);
int verificarUsernameUnico(const char* username, Usuario* usuarios, int quantidade);

#endif