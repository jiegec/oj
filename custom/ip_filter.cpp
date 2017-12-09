#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int ip_begin[4], ip_end[4];
  char filter[100];
  scanf("%s",filter);
  // parse filter
  char *token = strtok(filter, ".");
  int i = 0;
  while(token) {
    char *delim;
    if ((delim = strchr(token, '-')) != NULL) {
      // range
      ip_begin[i] = atoi(token);
      ip_end[i] = atoi(delim+1);
    } else if (strcmp(token, "*") == 0) {
      // asterisk
      ip_begin[i] = 0;
      ip_end[i] = 255;
    } else {
      // only one ip
      ip_begin[i] = ip_end[i] = atoi(token);
    }
    token = strtok(NULL, ".");
    i++;
  }
  int n;
  scanf("%d",&n);
  for (int k = 0;k < n;k++) {
    char ip[100];
    scanf("%s", ip);
    // parse ip
    i = 0;
    token = strtok(ip, ".");
    while(token) {
      int temp = atoi(token);
      if (temp < ip_begin[i] || temp > ip_end[i]) {
        printf("Failed\n");
        break;
      }
      token = strtok(NULL, ".");
      i++;
    }
    if (i == 4)
      printf("Accepted\n");
  }
  return 0;
}
