#include <algorithm>
#include <stdio.h>

char str[] = "BANANA";
int n;
int rank[100];
int sa[100];

bool cmp(const char *a, const char *b) { return strcmp(a, b) < 0; }

void dumb_sa() {
  char **suffix = new char *[n];
  for (int i = 0; i < n; i++) {
    suffix[i] = str + i;
  }
  std::sort(suffix, suffix + n, cmp);
  for (int i = 0; i < n; i++) {
    rank[i] = suffix[i] - str;
    sa[rank[i]] = i;
  }
}

int main() {
  n = strlen(str);
  dumb_sa();
  for (int i = 0; i < n; i++) {
    printf("%d\n", sa[i]);
  }
}
