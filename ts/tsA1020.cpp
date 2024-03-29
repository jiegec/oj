// http://oj.tsinsen.com/A1020
#include <algorithm>
#include <functional>
#include <stdio.h>

using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  int array[234];
  for (int i = 0; i < n; i++) {
    scanf("%d", &array[i]);
  }
  std::sort(array, array + n, std::less<int>());
  for (int i = 0; i < n - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d\n", array[n - 1]);
}
