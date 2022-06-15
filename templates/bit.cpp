#include <functional>
#include <stdio.h>
#include <type_traits>

template <typename T>
using u = typename std::enable_if<std::is_unsigned<T>::value, int>::type;

// difference or zero
template <typename T> T doz(T x, T y) { return (x - y) & -(x >= y); }

uint32_t nlz(uint32_t x) {
  if (x == 0)
    return 32;
  uint32_t n = 0;
  if ((x & 0xFFFF0000) == 0) {
    n = n + 16;
    x = x << 16;
  }
  if ((x & 0xFF000000) == 0) {
    n = n + 8;
    x = x << 8;
  }
  if ((x & 0xF0000000) == 0) {
    n = n + 4;
    x = x << 4;
  }
  if ((x & 0x30000000) == 0) {
    n = n + 2;
    x = x << 2;
  }
  if ((x & 0x10000000) == 0) {
    n = n + 1;
    x = x << 1;
  }
  return n;
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

// find contiguous 1s of length n in x
uint32_t ffstr1(uint32_t x, uint32_t n) {
  uint32_t s;
  while (n > 1) {
    s = n >> 1;
    x = x & (x >> s);
    n = n - s;
  }
  return nlz(x);
}

uint32_t rev(uint32_t x) {
  x = (x & 0x55555555) << 1 | ((x >> 1) & 0x55555555);
  x = (x & 0x33333333) << 2 | ((x >> 2) & 0x33333333);
  x = (x & 0x0F0F0F0F) << 4 | ((x >> 4) & 0x0F0F0F0F);
  x = (x << 24) | ((x & 0xFF00) << 8) | ((x >> 8) & 0xFF00) | (x >> 24);
  return x;
}

// Knuth
uint32_t rev_alt(uint32_t x) {
  uint32_t t;
  x = (x << 15) | (x >> 17);
  t = (x ^ (x >> 10)) & 0x003F801F;
  x = (t | (t << 10)) ^ x;
  t = (x ^ (x >> 4)) & 0x0E038421;
  x = (t | (t << 4)) ^ x;
  t = (x ^ (x >> 2)) & 0x22488842;
  x = (t | (t << 2)) ^ x;
  return x;
}

// Knuth
uint64_t rev(uint64_t x) {
  uint64_t t;
  x = (x << 31) | (x >> 33);
  t = (x ^ (x >> 20)) & 0x00000FFF800007FFULL;
  x = (t | (t << 20)) ^ x;
  t = (x ^ (x >> 8)) & 0x00F8000F80700807ULL;
  x = (t | (t << 8)) ^ x;
  t = (x ^ (x >> 4)) & 0x0808708080807008ULL;
  x = (t | (t << 4)) ^ x;
  t = (x ^ (x >> 2)) & 0x1111111111111111ULL;
  x = (t | (t << 2)) ^ x;
  return x;
}

// turn:
// 0000 0000 0000 0000 abcd efgh ijkl mnop
// to:
// ponm lkji hgfe dcba .... .... .... ....
uint32_t refl(uint32_t x) {
  x = x | ((x & 0x000000FF) << 16);
  x = (x & 0xF0F0F0F0) | ((x & 0x0F0F0F0F) << 8);
  x = (x & 0xCCCCCCCC) | ((x & 0x33333333) << 4);
  x = (x & 0xAAAAAAAA) | ((x & 0x55555555) << 2);
  x = x << 1;
  return x;
}

uint16_t rev(uint16_t x) { return (uint16_t)(refl(x) >> 16); }

// de Bruijn cycle, by Danny Dube
uint32_t ntz_alt(uint32_t x) {
  static uint8_t table[32] = {0,  1,  2,  24, 3,  19, 6,  25, 22, 4,  20,
                              10, 16, 7,  12, 26, 31, 23, 18, 5,  21, 9,
                              15, 11, 30, 17, 8,  14, 29, 13, 28, 27};
  if (x == 0)
    return 32;
  x = (x & -x) * 0x04D7651F;
  return table[x >> 27];
}

// John Reiser's algorithm
uint32_t ntz_alt2(uint32_t x) {
  static uint8_t table[37] = {32, 0, 1,  26, 2,  23, 27, 0,  3,  16, 24, 30, 28,
                              11, 0, 13, 4,  7,  17, 0,  25, 22, 31, 15, 29, 10,
                              12, 6, 0,  21, 14, 9,  5,  20, 8,  19, 18};
  x = (x & -x) % 37;
  return table[x];
}

uint32_t pop(uint32_t x) {
  x = x - ((x >> 1) & 0x55555555);
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
  x = (x + (x >> 4)) & 0x0F0F0F0F;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x0000003F;
}

uint32_t hamming_distance(uint32_t x, uint32_t y) { return pop(x ^ y); }

uint32_t pop_alt(uint32_t x) {
  uint32_t n;
  n = (x >> 1) & 0x77777777;
  x = x - n;
  n = (n >> 1) & 0x77777777;
  x = x - n;
  n = (n >> 1) & 0x77777777;
  x = x - n;
  x = (x + (x >> 4)) & 0x0F0F0F0F;
  x = x * 0x01010101;
  return x >> 24;
}

// 01011000 -> 01010000
template <typename T, u<T>> T toggle_least_1(T s) { return s & (s - 1); };

// 10100111 -> 10101111
template <typename T, u<T>> T toggle_least_0(T s) { return s | (s + 1); };

// 10100111 -> 10100000
// can be used to check if s is 2^{n-1}, 0 or all 1
template <typename T, u<T>> T toggle_trailing_1(T s) { return s & (s + 1); };

// 10101000 -> 10101111
template <typename T, u<T>> T toggle_trailing_0(T s) { return s | (s - 1); };

// 01011000 -> 00001000
template <typename T, u<T>> T extract_least_1(T s) { return s & (-s); }

// 10101000 -> 11110111
template <typename T, u<T>> T extract_least_1_alt(T s) { return ~s | (s - 1); }

// 10101000 -> 00001111
template <typename T, u<T>> T extract_least_1_alt2(T s) { return s ^ (s - 1); }

// 10100111 -> 00001000
template <typename T, u<T>> T extract_least_0(T s) { return ~s & (s + 1); }

// 10100111 -> 00001111
template <typename T, u<T>> T extract_least_0_alt(T s) { return s ^ (s + 1); }

// 01011000 -> 0000111
// or ~(s|-s) or (s&-s)-1
template <typename T, u<T>> T extract_trailing_0(T s) { return ~s & (s - 1); }

// 10100111 -> 11111000
template <typename T, u<T>> T extract_trailing_1(T s) { return ~s | (s + 1); }

// 01011100 -> 01000000
// can be used to check if s is 2^j-2^k
// or ((s&-s)+s)&s
template <typename T, u<T> = 1> T toggle_trailing_contiguous_1(T s) {
  return ((s | (s - 1)) + 1) & s;
}

template <typename T, typename Callable, u<T> = 1>
void enumerate_subset(T s, Callable func) {
  for (T i = s; i; i = (i - 1) & s) {
    func(i);
  }
}

// R. W. Gosper
// snoob
template <typename T, typename Callable, u<T> = 1>
void enumerate_subset_size_r(T n, T r, Callable func) {
  for (T s = (1 << r) - 1; s < (1 << n);) {
    func(s);
    T x = s & (-s);
    T y = s + x;
    // or y | ((x ^ y) >> (2 + ntz(x))) (ntz: number of trailing zeros)
    // or y | ((x ^ y) >> (33 - nlz(s))) (nlz: number of leading zeros)
    // or y | ((1 << (pop(x ^ y)-2))-1) (pop: number of ones)
    s = (((s ^ y) / x) >> 2) | y;
  }
}

template <typename T, u<T> = 1>
void rotate_left(T s, T n, size_t bits = sizeof(T) * 8) {
  return (s << n) | (s >> (bits - n));
};

template <typename T, u<T> = 1>
void rotate_right(T s, T n, size_t bits = sizeof(T) * 8) {
  return (s >> n) | (s << (bits - n));
};

template <typename T, u<T> = 1> void round_down_to(T s, T t) {
  static_assert((t & (t - 1)) == 0, "t must be a power of 2");
  return s & (-t);
};

template <typename T, u<T> = 1> void round_up_to(T s, T t) {
  static_assert((t & (t - 1)) == 0, "t must be a power of 2");
  return (s + t - 1) & (-t);
};

uint32_t parity(uint32_t x) {
  uint32_t y = x ^ (x >> 1);
  y = y ^ (y >> 2);
  y = y ^ (y >> 4);
  y = y ^ (y >> 8);
  y = y ^ (y >> 16);
  return y;
}

uint32_t ceil_power_of_2(uint32_t x) {
  x -= 1;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  return x + 1;
}

uint32_t floor_power_of_2(uint32_t x) {
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  return x - (x >> 1);
}

// [a, a+l) has a power of p
template <typename T, u<T> = 1> bool cross_power_of_2(T a, T l, T p) {
  // or p-(a&(p-1))<l
  return -(a | -p) < l;
}

template <typename T, u<T> = 1>
void print_binary(T s, size_t bits = sizeof(T) * 8) {
  printf("pop count:%d ", pop(s));
  for (T i = bits, j = 1 << (i - 1); i >= 1; i--, j >>= 1) {
    putchar(((s & j) >> (i - 1)) + '0');
  }
  putchar('\n');
}

int main() {
  print_binary(10u);
  putchar('\n');
  enumerate_subset(0b01001001u, [](uint8_t i) { print_binary(i, 8); });
  putchar('\n');
  enumerate_subset_size_r(8u, 3u, [](uint8_t i) { print_binary(i, 8); });
}
