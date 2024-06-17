int *e;
char *f = "@", *k, *l;
h = 18, w = 65, g = 15, y = 0, x = 0;

void p(char c) {
  if (x == 0 || x == w - 1  || ((y == 0 || y == h - 1) && x < 20) ||
    ((y == 0 || y == h - 1) && x > 30) ||
    (0 < y && y < h - 1 && (x - y == 20 || x + y == 30))) {
    int q = 0;
    for (int i = 0; i < g; ++i) {
      if (e[i] == x)
        q = 1;
    }
    if (q == 1) {
      printf("\033[30m%c\033[47m", c);
    } else {
      printf("\033[30m%c\033[0m", c);
    }
  } else {
    printf("\033[30m%c\033[0m", c);
  }
  if (c == '\n') {
    y += 1;
    x = 0;
  } else {
    x += 1;
  }
}

int main() {
  e = malloc(sizeof(char) * w * g);
  for (int i = 0; i < g; ++i) {
    e[i] = i;
  }


  for (;;printf("\n\033[%dA\033[%dD", y + 1, x),usleep(1000 * 10)) {
    for (k = f, x = 0, y = 0; *k; k++) {
      if (*k != 64) {
        p(*k);
      } else {
        for (l = f; *l; l++) {
          switch (*l) {
          case '\n':
            p('\\');
            p('n');
            p('\"');
            p('\n');
            p('\"');
            break;
          case '"':
            p('\\');
            p('\"');
            break;
          case '\\':
            p('\\');
            p('\\');
            break;
          default:
            p(*l);
          }
        }
      }
    }
    for (int i = 0; i < g; ++i) {
      e[i] = (e[i] + 1) % w;
    }
  }
  return 0;
}
