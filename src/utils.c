#include "utils.h"

void Limpar_Tela(){

    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");   
    #endif
}

void Configura_Terminal() {
    #ifdef _WIN32
        system("chcp 65001 > NUL");

    #else
        setlocale(LC_ALL, "");
    #endif
}