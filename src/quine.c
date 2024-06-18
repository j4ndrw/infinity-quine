#include <stdio.h>
#include <string.h>

int main() {
  const char *src = "@";
  const char src_length = strlen(src);
  const int quine_char_ascii = 64;
  for (size_t i = 0; i < src_length; ++i) {
    if (src[i] != quine_char_ascii)
      printf("%c", src[i]);
    else {
      for (size_t j = 0; j < src_length; ++j) {
        switch (src[j]) {
        case '\n':
          printf("\\n\"\n\"");
          break;
        case '"':
          printf("\\\"");
          break;
        case '\\':
          printf("\\\\");
          break;
        default:
          printf("%c", src[j]);
        }
      }
    }
  }
  return 0;
}
