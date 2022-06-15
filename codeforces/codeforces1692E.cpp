// https://codeforces.com/contest/1692/problem/E
#include <stdio.h>
#include <vector>

int a[300000];

int main() {
	int t;
  scanf("%d", &t);
	while(t--) {
    int n, s;
    scanf("%d%d", &n, &s);
    std::vector<int> index;
    for (int i = 0;i < n;i++) {
      scanf("%d", &a[i]);
      if (a[i]) {
        index.push_back(i);
      }
    }

    int ans = -1;
    if (index.size() < s) {
      ans = -1;
    } else if (index.size() == s) {
      ans = 0;
    } else {
      for (int i = 0;i <= index.size() - s;i++) {
        // [i, i+s-1]
        int cur = 0;
        if (i > 0) {
          cur += index[i-1] + 1;
        }
        if (i+s < index.size()) {
          cur += n - index[i+s];
        }
        if (ans == -1 || cur < ans) {
          ans = cur;
        }
      }
    }
    printf("%d\n", ans);
	}
  return 0;
}