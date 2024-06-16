#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage() {
  printf("Usage:");
  printf("\t./compile-quine <C_PROGRAM>");
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
  if (argc != 2) {
    usage();
    return 1;
  }

  char *c_program_file_path = argv[1];
  FILE *fp = fopen(c_program_file_path, "rb");
  if (fp == NULL)
    return error(c_program_file_path, fp, __LINE__);

  char *src = read_file(fp);
  if (src == NULL)
    return error(c_program_file_path, fp, __LINE__);

  for (size_t i = 0; i < strlen(src); ++i) {
    if (src[i] != '@') printf("%c", src[i]);
    else {
      for (size_t j = 0; j < strlen(src); ++j) {
        switch (src[j]) {
          case '\n': printf("\\n\"\n\""); break;
          case '\\': printf("\\\\"); break;
          case '"':  printf("\\\""); break;
          default: printf("%c", src[j]);
        }
      }
    }
  }

  fclose(fp);
  return 0;
}
