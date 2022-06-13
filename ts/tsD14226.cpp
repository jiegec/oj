// http://oj.tsinsen.com/D14226
#include <algorithm>
#include <stdio.h>
#include <vector>

struct item {
  int a;
  int b;
  int index;
} items[1024];
int s, n = 0;
int chosen[1024], top=0;

bool operator<(const item &lhs, const item &rhs) {
  if (lhs.b != rhs.b)
    return lhs.b > rhs.b;
  if (lhs.b) {
    if (lhs.a != rhs.a)
      return lhs.a > rhs.a;
    return lhs.index < rhs.index;
  } else {
    if (lhs.a != rhs.a)
      return lhs.a < rhs.a;
    return lhs.index < rhs.index;
  }
}

int main() {
  scanf("%d%d", &s, &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &items[i].a, &items[i].b);
    items[i].index = i;
  }
  std::sort(items + 1, items + n + 1);
  s *= 2;
  // can have half price
  for (int i = 1; i <= n && s > 0; i++) {
    int real_price = items[i].b ? items[i].a : (items[i].a * 2);
    if (s >= real_price) {
      chosen[top++] = items[i].index;
      s -= real_price;
    }
  }
  if (top == 0) {
    printf("0\n");
  } else {
    std::sort(chosen, chosen+top);
    printf("%d", chosen[0]);
    for (int i = 1; i < top; i++) {
      printf(" %d", chosen[i]);
    }
    printf("\n");
  }

  return 0;
}
