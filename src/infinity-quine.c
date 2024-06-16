#include <stdio.h>
#include <string.h>

int main()
{
  const char *src = "@";
  for (size_t i = 0; i < strlen(src); ++i) {
    if (src[i] != 64) printf("%c", src[i]);
    else {
      for (size_t j = 0; j < strlen(src); ++j) {
        switch (src[j]) {
          case '\n': printf("\\n\"\n\""); break;
          case '"':  printf("\\\""); break;
          case '\\': printf("\\\\"); break;
          default: printf("%c", src[j]);
        }
      }
    }
  }
  return 0;
}
