// I don't remember how I made it word before and I'm too tired to restore it...
// So you'll have to deal with the obfuscated quine version
// soz

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int width = 30;
  int height = 10;
  int column_window_size = 3;
  char *column_window = malloc(sizeof(char) * width * column_window_size);
  for (int i = 0; i < column_window_size; ++i) {
    column_window[i] = i;
  }

  char *buf = malloc(sizeof(char) * width * height);

  for (;;) {
    for (size_t row = 0; row < height; ++row) {
      for (size_t col = 0; col < width; ++col) {
        if (col == 0 || col == width - 1 ||
            ((row == 0 || row == height - 1) && col < 10) ||
            ((row == 0 || row == height - 1) && col > 15) ||
            (0 < row && row < height - 1 &&
             (col - row == 10 || col + row == 15))) {
          bool should_display = false;
          for (int i = 0; i < column_window_size; ++i) {
            if (column_window[i] == col) {
              should_display = true;
              break;
            }
          }

          if (should_display == true)
            buf[row * col] = '#';
          else
            buf[row * col] = ' ';
        } else {
          buf[row * col] = ' ';
        }
      }
    }
    for (size_t row = 0; row < height; ++row) {
      for (size_t col = 0; col < width; ++col) {
        printf("%c", buf[row * col]);
      }
      printf("\n");
    }
    for (int i = 0; i < column_window_size; ++i) {
      column_window[i] = (column_window[i] + 1) % width;
    }
    printf("\033[%dA\033[%dD", height, width);
    usleep(1000 * 10);
  }
  return 0;
}
