#include <stdio.h>

typedef enum { Newline, Tab, Default } State;

main() {
  long c;

  State s = Default;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      s = Newline;
    } else if (c == '\t') {
      s = Tab;
    } else {
      switch (s) {
      case Newline:
        fputs("\\n", stdout);
      case Tab:
        fputs("\\t", stdout);
      case Default:
        putc(c, stdout);
      }
    }
  }
}
