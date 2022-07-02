#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <vector>

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    std::vector<long long> numbers;
    for (int i = 0; i < n; i++) {
      int temp;
      scanf("%d", &temp);
      numbers.push_back(temp);
    }
    std::sort(numbers.begin(), numbers.end());

    int pos = 0, neg = 0;
    int last_pos = 0, last_neg = 0;
    for (int i = 0; i < n; i++) {
      pos += numbers[i] > 0;
      neg += numbers[i] < 0;
      if (numbers[i] > 0) {
        last_pos = numbers[i];
      }
      if (numbers[i] < 0) {
        last_neg = numbers[i];
      }
    }

    bool ans = false;

    if (n <= 10) {
      ans = true;
      for (int i = 0; i < n && ans; i++) {
        for (int j = i + 1; j < n && ans; j++) {
          for (int k = j + 1; k < n && ans; k++) {
            int sum = numbers[i] + numbers[j] + numbers[k];

            bool found = false;
            for (int l = 0;l < n;l++) {
              if (sum == numbers[l]) {
                found = true;
                break;
              }
            }
            if (!found) {
              ans = false;
            }
          }
        }
      }
    } else if (pos >= 2 || neg >= 2) {
      ans = false;
    } else if (pos == 1 && neg == 1) {
      ans = last_pos == -last_neg;
    } else if (pos == 1 && neg == 0) {
      ans = true;
    } else if (pos == 0 && neg == 1) {
      ans = true;
    } else if (pos == 0 && neg == 0) {
      ans = true;
    } else {
      assert(false);
    }
    printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}