#ifndef CONFIGURACOES_H
#define CONFIGURACOES_H

#include "autenticacao.h"


void menuConfiguracoes();

void mostrarPerfil();

void alterarEmail(Usuario* usuarios, int quantidade);

void alterarSenha();

void deletarConta(Usuario* usuarios, int* quantidade);

#endif
