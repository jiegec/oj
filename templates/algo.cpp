#include <algorithm>
#include <cassert>
#include <cmath>

template <typename T, typename N, size_t size>
void discretize(const T copy[size], T (&a)[size], N (&map)[size]) {
  std::sort(a, a + size);
  ptrdiff_t size_uniq = std::unique(a, a + size) - a;
  for (size_t i = 0; i < size; i++) {
    map[i] = (N)(std::lower_bound(a, a + size_uniq, copy[i]) - a);
  }
}

template <typename T> struct majority_vote {
  // the current_winner might be the one that occurs the most times (i.e. > 50%)
  void feed(const T &new_element) {
    if (counter == 0) {
      current_winner = new_element;
      counter++;
    } else if (current_winner == new_element) {
      counter++;
    } else {
      counter--;
    }
  }
  T current_winner;
  size_t counter = 0;
};

// from bit.cpp
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

// select k from stream with uniform probability
template <size_t k, typename T> struct reservoir_sampling {
  void feed(const T &new_element) {
    n++;
    if (current >= end) {
      size_t x = rand() % n;
      if (x < k) {
        selection[x] = new_element;
      }
    } else {
      *(current++) = new_element;
    }
  }
  T selection[k];
  T *current = selection;
  T *end = selection + k;
  size_t n = 0;
};

template <typename T, size_t size> constexpr size_t size_of(T (&)[size]) {
  return size;
};

int main() {
  srand(time(NULL));
  int a[] = {4, 4, 8, 3, 2};
  int map[size_of(a)];
  int b[size_of(a)];
  memcpy(b, a, sizeof(b));
  discretize(b, a, map);
  for (int i = 0; i < sizeof(a) / sizeof(int); i++) {
    assert(a[map[i]] == b[i]);
    printf("%d:%d ", b[i], map[i]);
  }
  printf("\n");

  reservoir_sampling<2, int> sampling;
  for (auto &i : b) {
    sampling.feed(i);
  }
  for (auto &i : sampling.selection) {
    printf("%d ", i);
  }
}
