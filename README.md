# 📋 Avaliação Unidade III - Lista Encadeada

## Introdução
A atualização deste projeto faz parte da avaliação da terceira unidade de Algoritmos e Estruturas de Dados. A tarefa pede a implementação de uma lista encadeada. Optei por expandi o sistema de suporte para isso, antes era possível apenas enviar mensagens ao suporte. E agora com a lista encadeada é possível também visualizar as mensagens. Quando um usuário envia uma mensagem, ela é armazenada em um arquivo de texto.

## Funções Implementadas
### Enviar Mensagem ao Suporte
Os usuários podem enviar mensagens ao suporte, que são registradas em um arquivo de texto `mensagens_suporte.txt`. A função captura o nome, email e mensagem do usuário, registra a data atual e armazena essas informações no arquivo.

### Carregar Mensagens do Suporte
As mensagens enviadas ao suporte são carregadas do arquivo `mensagens_suporte.txt` para uma lista encadeada em memória. Cada mensagem é representada por uma estrutura `MensagemSuporte`.

## Como Funciona
### Estruturas
#### `MensagemSuporte`
Estrutura que armazena informações para o suporte, contendo nome, email, mensagem e data/hora.
```c
typedef struct {
    char nome[100];
    char email[100];
    char mensagem[500];
    char data_hora[50];
} MensagemSuporte;
```
#### `NoMensagemSuporte`
Estrutura de nó para a lista encadeada, que contém um objeto `MensagemSuporte` e um ponteiro para o próximo nó na lista.
```c
struct MensagemSuporteNo {
    MensagemSuporte mensagem;
    struct MensagemSuporteNo* proximo;
};
```
### Funções
### Enviar Mensagem ao Suporte

#### `enviarMensagemSuporte`

A função `enviarMensagemSuporte` permite que um usuário envie uma mensagem ao suporte. Ela captura o nome e email do usuário logado, solicita a mensagem do usuário e registra a data e hora atuais. Em seguida, a função armazena essas informações em um arquivo de texto chamado `mensagens_suporte.txt`. Se a mensagem for enviada com sucesso, uma confirmação é exibida; caso contrário, uma mensagem de erro é mostrada.
```c
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
```
#### `novoNoMensagemSuporte`
Função para criar um novo nó da lista encadeada `NoMensagemSuporte`.
```c
NoMensagemSuporte* novoNoMensagemSuporte(MensagemSuporte mensagem) {
    NoMensagemSuporte* novo = (NoMensagemSuporte*) malloc(sizeof(NoMensagemSuporte));
    if (novo != NULL) {
        novo->mensagem = mensagem;
        novo->proximo = NULL;
    }
    return novo;
}
```

#### `carregarMensagensSuporte`
Função para carregar todas as mensagens do arquivo `mensagens_suporte.txt` para uma lista encadeada em memória.
```c
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

```

#### `imprimirMensagensSuporte`
Função para imprimir todas as mensagens carregadas na lista encadeada.
```c
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
```

## 
Para mais informações do projeto consultar o README original no arquivo `README_.md`.
