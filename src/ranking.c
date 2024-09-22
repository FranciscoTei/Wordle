#include <stdio.h>
#include <stdlib.h>
#include "autenticacao.h"
#include "ranking.h"


void trocar(Usuario* a, Usuario* b) {
    Usuario temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(Usuario* usuarios, int baixo, int alto) {
    int pivo = usuarios[alto].status.pontos;
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
        if (usuarios[j].status.pontos >= pivo) {
            i++;
            trocar(&usuarios[i], &usuarios[j]);
        }
    }
    trocar(&usuarios[i + 1], &usuarios[alto]);
    return i + 1;
}

void quickSort(Usuario* usuarios, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(usuarios, baixo, alto);
        quickSort(usuarios, baixo, pi - 1);
        quickSort(usuarios, pi + 1, alto);
    }
}


void exibirRanking() {
    int quantidade = 0;
    Usuario* usuarios = carregarUsuarios(&quantidade);
    quickSort(usuarios, 0, quantidade - 1);

    printf("Posição  Nome           Jogos  Pontos\n");
    printf("--------------------------------------\n");
    for (int i = 0; i < quantidade; i++) {
        printf("%-8d %-15s %-6d %-6d\n", i + 1, usuarios[i].nome, usuarios[i].status.jogos, usuarios[i].status.pontos);
    }
    return;
}

void mostrarRanking() {
    int quantidade = 0;
    Usuario* usuarios = carregarUsuarios(&quantidade);

    if (quantidade > 0) {
        exibirRanking(usuarios, quantidade);
    } else {
        printf("Nenhum usuário registrado ainda.\n");
    }

    free(usuarios);
}
