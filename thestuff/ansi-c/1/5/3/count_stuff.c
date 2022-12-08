#include <stdio.h>

main() {
  long c, nlines, tabs, blanks;

  nlines = 0;
  tabs = 0;
  blanks = 0;
  while ((c = getchar()) != EOF) {
    switch (c) {
      case '\n':
        ++nlines;
      case '\t':
        ++tabs;
      case ' ':
        ++blanks;
    }
  }
  printf("Nlines:\t%ld\n", nlines);
  printf("Tabs:\t%ld\n", tabs);
  printf("Spaces:\t%ld\n", blanks);
}
