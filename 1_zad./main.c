#include "zad1.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc > 1) {
    FILE *test = fopen("test", "wb");
    uint32_t code_point;
    uint8_t code_unit[4];
    sscanf(argv[1], "%x", &code_point);
    int length = encode_varint(code_point, code_unit);
    fwrite(code_unit, sizeof(uint8_t), length, test);
    fclose(test);

    FILE *test_read = fopen("test", "rb");
    const uint8_t *bufp = (const uint8_t *)malloc(sizeof(uint8_t) * length);
    fread((void *)bufp, sizeof(uint8_t), length, test_read);
    fclose(test_read);

    uint32_t decoded_code_point = decode_varint(&bufp);
    printf("%u\n", decoded_code_point);

    free((void *)bufp);

    // calculate compression ratio
    float compression_ratio = (float)length / (float)sizeof(uint32_t);
    printf("Compression ratio: %.2f\n", compression_ratio);
  }

  const char *compress = "compressed.dat", *uncompress = "uncompressed.dat";

  write_rand(uncompress, compress, MaxNumbers);
  uint32_t *uncom_buff = read_uncompress(uncompress);
  uint32_t *com_buff = read_compress(compress);

  for (int i = 0; i < MaxNumbers; i++)
    if (uncom_buff[i] != com_buff[i]) {
      fprintf(stderr, "Not identity");
      return 1;
    }

  fprintf(stdout, "Identity\n");

  // calculate compression ratio
  float compression_ratio =
      (float)sizeof(uint32_t) * MaxNumbers / (float)filesize(compress);
  printf("Compression ratio: %.2f\n", compression_ratio);

  free(uncom_buff);
  free(com_buff);
  return 0;
}