#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef long long ll;

struct seg {
  ll start;
  ll end;
} s[1024];

int cmp(seg &p, seg &q) {
  if (p.start != q.start) {
    return p.start < q.start;
  }
  return p.end < q.end;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld", &s[i].start, &s[i].end);
  }
  // quicksort(s,0,n-1);
  std::sort(s, s + n, cmp);
  ll length = 0, start = 0, end = 0;
  for (int i = 0; i < n; i++) {
    start = s[i].start;
    end = s[i].end;
    while (end >= s[i + 1].start && (i + 1) < n) {
      i++;
      end = end > s[i].end ? end : s[i].end;
    }
    length += end - start;
  }
  printf("%lld\n", length);
  return 0;
}
