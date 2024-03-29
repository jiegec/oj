// Reference:
// https://www.cnblogs.com/HarryGuo2012/p/4722784.html
// http://blog.csdn.net/fcxxzux/article/details/40053937
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int main2(void) __asm__("main2");

int main2() {
  char test[255 << 20];
  memset(test, 42, sizeof(test));
  printf(":)\n");
  exit(0);
}

int main() {
  int size = 256 << 20; // 256Mb
  char *p = (char *)malloc(size) + size;
#ifdef __x86_64__
  __asm__ __volatile__("movq  %0, %%rsp\n"
                       "push %%rsp\n"
                       "jmp main2\n" ::"r"(p));
#endif
  return 0;
}
