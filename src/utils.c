#include "utils.h"
#include "funcoes.h"

void Limpar_Tela(){

    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");   
    #endif
    printBanner();
}

void Configura_Terminal() {
    #ifdef _WIN32
        system("chcp 65001 > NUL");

    #else
        setlocale(LC_ALL, "");
    #endif
}
