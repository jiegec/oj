#include <stdio.h>
#include <complex>

typedef complex<double> cplx;

uint32_t rev(uint32_t x) {
  x = (x & 0x55555555) << 1 | ((x >> 1) & 0x55555555);
  x = (x & 0x33333333) << 2 | ((x >> 2) & 0x33333333);
  x = (x & 0x0F0F0F0F) << 4 | ((x >> 4) & 0x0F0F0F0F);
  x = (x << 24) | ((x & 0xFF00) << 8) |
    ((x >> 8) & 0xFF00) | (x >> 24);
  return x;
}

uint32_t ntz(uint32_t x) {
  if (x == 0)
    return 32;
  uint32_t n = 1;
  if ((x & 0x0000FFFF) == 0) {
    n = n + 16;
    x = x >> 16;
  }
  if ((x & 0x000000FF) == 0) {
    n = n + 8;
    x = x >> 8;
  }
  if ((x & 0x0000000F) == 0) {
    n = n + 4;
    x = x >> 4;
  }
  if ((x & 0x00000003) == 0) {
    n = n + 2;
    x = x >> 2;
  }
  return n - (x & 1);
}

// n must be power of 2
// 1 for dft, -1 for idft
// idft must divide n after use
void fft(int sign, cplx * data, int n) {
  int d = 1 + ntz(n);
  double theta = sign * 2.0 * _M_PI / n;
  for (int m = n;m >>= 2;m >>= 1, theta *= 2) {
    cplx tri = cplx(cos(theta), sin(theta));
    cplx w = cplx(1, 0);

    for (int i = 0, mh = m >> 1;i < mh;i++) {
      for (int j = i;j < n;j += m) {
        int k = j + mh;
        cplx tmp = data[j]-data[k];

        data[j] += data[k];
        data[k] = w * tmp;
      }
      w *= tri;

    }
  }
  for (int i = 0;i < n;i++) {
    int j = rev(i) >> d;
    if (j < i)
      swap(data[i], data[j]);
  }
}


int main() {
  p
    }
