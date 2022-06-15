#include <stdio.h>
#include <stdlib.h>

int interpreter(int *sp, int *ip) {
  static const void *jump_table[] = {&&init, &&push, &&add, &&ret};

init:
  goto *jump_table[*ip++];
push:
  *sp++ = *ip++;
  goto *jump_table[*ip++];
add : {
  int add_1 = *--sp, add_2 = *--sp;
  *sp++ = add_1 + add_2;
}
  goto *jump_table[*ip++];
ret:
  return *--sp;
}

int main() {
  int byte_code[] = {1, 1, 1, 2, 2, 3};
  int *stack = (int *)malloc(sizeof(int) * 16);
  scanf("%d%d", &byte_code[1], &byte_code[3]);
  int result = interpreter(stack, (int *)byte_code);

  printf("%d\n", result);
  return 0;
}
