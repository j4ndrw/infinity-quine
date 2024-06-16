#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_C_LEXER_IMPLEMENTATION
#include "../vendor/stb_c_lexer.h"

void usage() {
  printf("Usage:");
  printf("\t./format-quine <C_PROGRAM> <OUTPUT_FILE_PATH>");
}

int error(char *file_path, FILE *fp, int line) {
  fprintf(stdout, "[%s:%d] Could not read program %s. Reason: %s", __FILE__, line, file_path,
          strerror(errno));
  fclose(fp);
  return 1;
}

char *read_file(FILE *fp) {
  if (fp == NULL)
    return NULL;
  if (fseek(fp, 0, SEEK_END) < 0)
    return NULL;

  long size = ftell(fp);
  if (size < 0)
    return NULL;

  if (fseek(fp, 0, SEEK_SET) < 0)
    return NULL;

  char *buf = malloc(size * sizeof(char));

  fread(buf, size, 1, fp);
  if (ferror(fp))
    return NULL;

  return buf;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    usage();
    return 1;
  }

  char *c_program_file_path = argv[1];
  char* output_file_path = argv[2];

  FILE *fp = fopen(c_program_file_path, "rb");
  if (fp == NULL)
    return error(c_program_file_path, fp, __LINE__);

  char *src = read_file(fp);
  if (src == NULL)
    return error(c_program_file_path, fp, __LINE__);
  fclose(fp);

  fp = fopen(output_file_path, "wb");
  if (fp == NULL)
    return error(c_program_file_path, fp, __LINE__);


  stb_lexer lexer = {0};
  static char string_store[1024];
  stb_c_lexer_init(&lexer, src, src + strlen(src), string_store,
                   sizeof(string_store) / sizeof(string_store[0]));

  int offset = 8;
  int prev_token = 0;
  while (stb_c_lexer_get_token(&lexer)) {
    int n = lexer.where_lastchar - lexer.where_firstchar + 1;
    if ((prev_token == CLEX_id || prev_token == CLEX_intlit) && (lexer.token == CLEX_id || lexer.token == CLEX_intlit)) {
      fprintf(fp, " ");
      offset += 1;
    }
    prev_token = lexer.token;
    fprintf(fp, "%.*s", n, lexer.where_firstchar);
    offset += n;

    if (offset >= 80) {
      fprintf(fp, "\n");
      offset = 0;
    }
  }

  return 0;
}
