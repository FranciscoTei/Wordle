#include <stdio.h>
#include <stdlib.h>

#include "src/wordle.h"
#include "src/utils.h"

int main(void) {
    Configura_Terminal();
    load_palavras();
    wordle(5);

}