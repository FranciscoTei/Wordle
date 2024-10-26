#include "unity.h"
#include "wordle.h"
#include <stdio.h>

void setUp(void) {
    // Configurações antes de cada teste
}

void tearDown(void) {
    // Limpeza após cada teste
}

void test_sorteia_palavra(void) {
    char palavra[MAX_LINHA];
    int result = sorteia_palavra(palavra);
    TEST_ASSERT_EQUAL_INT(5, strlen(palavra));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sorteia_palavra);
    return UNITY_END();
}