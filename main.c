#include <stdio.h>
#include <stdlib.h>

#include "src/wordle.h"
#include "src/utils.h"
#include "src/funcoes.h"
#include "src/autenticacao.h"

//int main(void) {
//    Configura_Terminal();
//    load_palavras();
//    wordle(5);
//
//}

int main() {
    Configura_Terminal();
    Limpar_Tela();
    int opcao;
    int logado = 0;

    while (!logado) {
        menuLogin();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                Limpar_Tela();
                logado = loginUsuario();
                break;
            case 2:
                Limpar_Tela();
                logado = cadastroUsuario();
                break;
            case 3:
                sair();
                break;
            case 4:
                listar_usuarios();
                break;
            default:
                printf("Opção inválida!  Tente novamente.\n");
        }
    }
    
    menuInicial();

    return 0;
}