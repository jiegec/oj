#include <stdio.h>
#include <vector>

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);

    std::vector<int> a;
    for (int i = 0; i < n; i++) {
      int temp;
      scanf("%d", &temp);
      a.push_back(temp);
    }

    int xored = 0;
    for (int i = 0; i < n; i++) {
      xored ^= a[i];
    }

    for (int i = 0;i < n;i++) {
      int check = a[i] ^ xored;
      if (a[i] == check) {
        printf("%d\n", check);
        break;
      }
    }
  }
  return 0;
}