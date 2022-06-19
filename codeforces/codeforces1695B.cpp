// https://codeforces.com/contest/1695/problem/B
#include <stdio.h>
#include <algorithm>

int piles[100];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &piles[i]);
    }
    if (n % 2 == 1) {
      printf("Mike\n");
      continue;
    }
    int min_mike = piles[0];
    int min_mike_index = 0;
    int min_joe = piles[1];
    int min_joe_index = 1;
    for (int i = 0; i < n; i++) {
      if (i % 2 == 0) {
        if (piles[i] < min_mike) {
          min_mike = piles[i];
          min_mike_index = i;
        }
      } else {
        if (piles[i] < min_joe) {
          min_joe = piles[i];
          min_joe_index = i;
        }
      }
    }
    if (min_mike > min_joe) {
      printf("Mike\n");
    } else if (min_mike == min_joe) {
      if (min_mike_index < min_joe_index) {
        printf("Joe\n");
      } else {
        printf("Mike\n");
      }
    } else {
      printf("Joe\n");
    }
  }
  return 0;
}