#include <stdio.h>

#define TABSTOP 4

main() {
  int c;
  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      for (int i = 0; i < TABSTOP; ++i) {
        putc(' ', stdout);
      }
    } else {
      putc(c, stdout);
    }
  }
  return 0;
}
