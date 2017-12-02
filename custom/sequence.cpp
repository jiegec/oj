#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <vector>
#include <algorithm>

template <typename T, typename N>
int discretize(int size, const T *copy, T *a, N *map) {
  std::sort(a, a+size);
  size_t size_uniq = std::unique(a, a+size) - a;
  for (size_t i = 0;i < size;i++) {
    map[i] = (N)(std::lower_bound(a, a+size_uniq, copy[i]) - a);
  }
  return (N)size_uniq;
}

int a[100086], b[100086], map[100086];

int main() {
  int n, k;
  scanf("%d%d",&n,&k);
  for (int i = 0;i < n;i++) {
    scanf("%d",&a[i]);
    b[i] = a[i];
  }
  int num = discretize(n, b, a, map);
  int *count;
  count = new int[num];
  /*
  for (int i = 0;i < num;i++) {
    count[i] = new int[n];
  }
  count[map[0]][0]++;
  for (int i = 1;i < n;i++) {
    for (int kk = 0;kk < num;kk++) {
      count[kk][i] = count[kk][i-1];
    }
    count[map[i]][i]++;
  }*/
  int result = 0;
  /*
  for (int j = 0;j < n;j++) {
    for (int kk = 0;kk < num;kk++) {
      if (count[kk] == k) {
        result++;
        break;
      }
      if (kk == map[j]) {
        count[kk]++;
      }
    }
  }*/
  for (int i = 0;i < n;i++) {
    memset(count, 0, sizeof(int)*num);
    for (int j = i;j < n;j++) {
      count[map[j]]++;
      for (int kk = 0;kk < num;kk++) {
        if (count[kk] == k) {
          result++;
          break;
        }
      }
    }
  }
  printf("%d\n",result);
}
