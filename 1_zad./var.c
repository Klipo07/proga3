#include "zad1.h"
#include <stdio.h>

int main() {
    uint32_t code_point = 0xAFC41;
    uint8_t code_unit[4];
    int length = encode_varint(code_point, code_unit);
    printf("Varint: ");
    for(int i = 0; i < length; i++)
    {
        printf("%02x", code_unit[i]);
    }
    printf("\n");

    return 0;
}