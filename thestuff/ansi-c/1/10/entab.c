#include <stdio.h>

#define TABSTOP 4

main() {
  int c;
  int space_counter = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      ++space_counter;
      if (space_counter == TABSTOP) {
        putc('\t', stdout);
        space_counter = 0;
      }
    } else {
      if (space_counter > 0) {
        for (int i = 0; i < space_counter; ++i) {
          putc(' ', stdout);
        }
        space_counter = 0;
      }
      putc(c, stdout);
    }
  }
  return 0;
}
