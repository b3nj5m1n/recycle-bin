#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define CUTOFF  80

int get_line(char *line, int maxline);

main() {
  int len;
  char line[MAXLINE];

  int current_len = 0;
  while ((len = get_line(line, MAXLINE)) > 0) {
    current_len += len;
    if (current_len > CUTOFF) {
      printf("%s", line);
    }
    if (line[len - 1] == '\n') {
      current_len = 0;
    }
  }
  return 0;
}

int get_line(char *s, int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    s[i] = c;
  }
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

