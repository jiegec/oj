#include <stdio.h>
#include <vector>

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    int n, k;
    scanf("%d%d", &n, &k);
    std::vector<int> numbers;
    for (int i = 0;i < n;i++) {
      int temp;
      scanf("%d", &temp);
      numbers.push_back(temp);
    }

    if (k == 1) {
      printf("%d\n", (n - 1) / 2);
    } else {
      int ans = 0;
      for (int i = 1;i < n-1;i++) {
        if (numbers[i] > numbers[i-1] + numbers[i+1]) {
          ans ++;
        }
      }
      printf("%d\n", ans);
    }
  }
	return 0;
}