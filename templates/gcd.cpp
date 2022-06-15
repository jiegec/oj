#include <cassert>
#include <type_traits>

// helper methods
template <typename T, typename U = typename std::make_unsigned<T>::type>
U powMod(U a, U b, U mod) {
  U ans = 1;
  a %= mod;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    b >>= 1;
    a = a * a % mod;
  }
  return ans;
}

// begin
int gcd(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

// ax + by = gcd(a,b)
// when b is prime, x * a = 1 (mod b)
int gcdEx(int a, int b, int *x, int *y) {
  if (b == 0) {
    *x = 1, *y = 0;
    return a;
  } else {
    int r = gcdEx(b, a % b, x, y);
    int t = *x;
    *x = *y;
    *y = t - a / b * *y;
    return r;
  }
}

// a * modInv(a, b) = 1 (mod b)
int modInv(int a, int mod) {
  int x, y;
  gcdEx(a, mod, &x, &y);
  return (x + mod) % mod;
}

// require mod to be prime
template <typename T> T modInv2(T a, T mod) {
  return powMod<T>(a, (mod - 2), mod);
}

template <int N, int MOD> struct modInv3 {
  int inv[N]{};

  modInv3() {
    inv[1] = 1;
    for (int i = 2; i < N; i++) {
      inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    }
  }

  int operator[](size_t pos) { return inv[pos]; }
};

int main() {
  assert(gcd(20, 40) == 20);
  assert(modInv(2, 1000000007) == 500000004);
  assert(modInv2(2LL, 1000000007LL) == 500000004);
  modInv3<7000, 10007> inv3;
  assert(inv3[2] == 5004);
  assert(inv3[6666] == modInv(6666, 10007));
}
