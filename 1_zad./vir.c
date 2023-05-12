#include <stdio.h>

int main() {
    int result = 0xF1F4 & (0xF1F3 >> 2) / 0xABCD;
    printf("Результат: %d\n", result);

    return 0;
}