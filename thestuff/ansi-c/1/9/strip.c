#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define CUTOFF 80

int get_line(char *line, int maxline);

main() {
  int len;
  char line[MAXLINE];

  int current_len = 0;
  while (1) {
    len = get_line(line, MAXLINE);
    if (len == -1) { break; }
    if (len == 0) { continue; }
    current_len += len;
    printf("%s", line);
    if (line[len - 1] == '\n') {
      current_len = 0;
    }
  }
  return 0;
}

int get_line(char *s, int lim) {
  int c, i;
  int last_char = 0;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
    s[i] = c;
    if (c != '\t' && c != ' ') {
      last_char = i;
    }
  }
  if (c == '\n') {
    s[last_char + 1] = c;
  }
  s[last_char + 2] = '\0';
  return c == EOF ? -1 : last_char;
}
