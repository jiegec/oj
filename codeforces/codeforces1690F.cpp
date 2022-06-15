// https://codeforces.com/contest/1690/problem/F
#include <stdio.h>
#include <vector>

long long gcd(long long a, long long b) {
  if (a < b) {
    long long temp = a;
    a = b;
    b = temp;
  }

  while (b) {
    long long temp = a % b;
    a = b;
    b = temp;
  }

  return a;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d\n", &n);
    char s[300];
    fgets(s, 300, stdin);

    std::vector<int> p;
    for (int i = 0; i < n; i++) {
      int num;
      scanf("%d", &num);
      p.push_back(num - 1);
    }

    int visit[300] = {0};
    std::vector<std::vector<int> > chains;
    for (int i = 0; i < n; i++) {
      if (visit[i] == 0) {
        std::vector<int> chain;
        visit[i] = 1;

        chain.push_back(i);
        int cur = p[i];
        while (cur != i) {
          visit[cur] = 1;
          chain.push_back(cur);
          cur = p[cur];
        }

        chains.push_back(chain);
      }
    }

    long long ans = 1;
    for (int i = 0; i < chains.size(); i++) {
      std::vector<int> &chain = chains[i];
      std::vector<char> str;
      for (auto index : chain) {
        str.push_back(s[index]);
      }
      std::vector<char> rotate = str;

      long long count = 0;
      while (1) {
        rotate.insert(rotate.begin(), rotate[rotate.size() - 1]);
        rotate.pop_back();
        count++;

        if (rotate == str) {
          break;
        }
      }

      ans = ans * count / gcd(ans, count);
    }

    printf("%lld\n", ans);
  }
  return 0;
}