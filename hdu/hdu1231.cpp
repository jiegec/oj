// http://acm.hdu.edu.cn/showproblem.php?pid=1231
#include <iostream>
using namespace std;

int main() {
  int N, a[10001], f[10001];
  while (1) {
    cin >> N;
    if (N == 0) {
      break;
    }
    for (int i = 1; i <= N; i++) {
      cin >> a[i];
    }
    f[1] = a[1];
    for (int k = 2; k <= N; k++) {
      if (f[k - 1] + a[k] >= a[k]) {
        f[k] = f[k - 1] + a[k];
      } else {
        f[k] = a[k];
      }
    }
    int fmax = -2147483647;
    int lmax = -2147483647;
    for (int l = 1; l <= N; l++) {
      if (fmax < f[l]) {
        fmax = f[l];
        lmax = l;
      }
    }
    int sum = 0;
    int start = 0;

    for (int m = lmax; m >= 1; m--) {
      sum += a[m];
      if (sum == fmax) {
        start = m;
      }
    }

    if (fmax < 0) {
      cout << "0 " << a[1] << " " << a[N] << endl;
    } else {
      cout << fmax << " " << a[start] << " " << a[lmax] << endl;
    }
  }
  return 0;
}
