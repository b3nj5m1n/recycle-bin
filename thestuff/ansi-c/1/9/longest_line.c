#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int get_line(char *line, int maxline);
void copy(char *to, char *from);

main() {
  int len, max;
  char line[MAXLINE];
  char longest[MAXLINE];

  max = 0;
  int current_len = 0;
  while ((len = get_line(line, MAXLINE)) > 0) {
    current_len += len;
    if (current_len > max && line[len - 1] == '\n') {
      max = current_len;
      copy(longest, line);
    }
    if (line[len - 1] == '\n') {
      current_len = 0;
    }
  }
  if (max > 0 && strlen(longest) < MAXLINE) {
    printf("... ");
  }
  if (max > 0) {
    printf("%s(%d)\n", longest, max);
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

void copy(char *to, char *from) {
  int i = 0;
  while ((to[i] = from[i]) != '\0') {
    ++i;
  }
}
