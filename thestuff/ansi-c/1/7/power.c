#include <stdio.h>

int power(int m, int n);

main() {
  for (int i = 0; i < 10; ++i) {
    printf("%d %d %d\n", i, power(2, i), power(-3, i));
  }
  return 0;
}

int power(int base, int n) {
  int result = 1;
  for (int i = 0; i < n; ++i) {
    result = result * base;
  }
  return result;
}
