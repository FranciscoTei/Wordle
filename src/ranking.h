#ifndef RANKING_H
#define RANKING_H

#include "autenticacao.h"

void trocar(Usuario* a, Usuario* b);

int particionar(Usuario* usuarios, int baixo, int alto);

void quickSort(Usuario* usuarios, int baixo, int alto);

void exibirRanking();

void mostrarRanking();

#endif
