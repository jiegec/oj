#include <stdio.h>
#include <string.h>

int main() {
  char buffer[512];
  scanf("%s",buffer);
  int len = strlen(buffer);
  int las = (len & 1) ? (len-2) : (len-1);
  for(int i = 1;i < las;i += 2,las -= 2) {
    char temp = buffer[i];
    buffer[i] = buffer[las];
    buffer[las] = temp;
  }
  printf("%s\n", buffer);
}
