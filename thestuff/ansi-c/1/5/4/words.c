#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main() {
  int c, i;
  char *buffer = malloc(sizeof(char) * 256);

  i = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      buffer[i] = '\0';
      if (strcmp(buffer, "") != 0) {
        printf("%s\n", buffer);
      }
      i = 0;
    } else {
      buffer[i] = c;
      ++i;
    }
  }
  free(buffer);
}
