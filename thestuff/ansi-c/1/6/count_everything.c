#include <stdio.h>

main() {
  int c, i, nwhite, nother;
  int ndigit[10];

  nwhite = nother = 0;
  for (i = 0; i < 10; ++i) {
    ndigit[i] = 0;
  }

  while ((c = getchar()) != EOF) {
    if (c >= '0' && c <= '9') {
      ++ndigit[c - '0'];
    } else if (c == ' ' || c == '\n' || c == '\t') {
      ++nwhite;
    } else {
      ++nother;
    }
  }

  int max = 0;
  for (i = 0; i < 10; ++i) {
    if (ndigit[i] > max) {
      max = ndigit[i];
    }
  }

  printf("digits:\n");
  for (i = 0; i < 10; ++i) {
    printf("%d %.*s\n", i, (ndigit[i]*10 / max*10)/2, "██████████████████████████████");
  }
  printf("white space = %d, other = %d\n", nwhite, nother);
}
