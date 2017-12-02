#include <algorithm>
#include <cassert>

template <typename T, typename N, size_t size>
void discretize(const T copy[size], T (&a)[size], N (&map)[size]) {
  std::sort(a, a+size);
  ptrdiff_t size_uniq = std::unique(a, a+size) - a;
  for (size_t i = 0;i < size;i++) {
    map[i] = (N)(std::lower_bound(a, a+size_uniq, copy[i]) - a);
  }
}

template<typename T, size_t size>
constexpr size_t size_of(T (&)[size]) {
  return size;
};

int main () {
  int a[] = {4, 4, 8, 3, 2};
  int map[size_of(a)];
  int b[size_of(a)];
  memcpy(b, a, sizeof(b));
  discretize(b, a, map);
  for (int i = 0;i < sizeof(a) / sizeof(int);i++) {
    assert(a[map[i]] == b[i]);
    printf("%d:%d ", b[i], map[i]);
  }
}
