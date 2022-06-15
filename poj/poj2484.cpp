// http://poj.org/problem?id=2484
#include <cstdio>

int n;

int main() {
  while (scanf("%d", &n) && n) {
    printf(n <= 2 ? "Alice\n" : "Bob\n");
  }
}
