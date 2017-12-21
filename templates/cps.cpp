#include <optional>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>

template <typename T> using arg = std::optional<T>;
template <typename... T> using tp = std::tuple<T...>;

int work(int a, int b, int c, int d) {
  arg<tp<tp<const void *>, int, tp<const void *, int, int>>> f1_arg;
  arg<tp<tp<const void *, int, int>, int>> k1_arg;
  arg<tp<tp<const void *, int, int>, int>> k2_arg;

  f1_arg = {{&&f1}, a + b, {&&k1, c, d}};
  goto f1;

f1 : {
  auto[f2, x, k] = *f1_arg;
  auto k11 = std::get<0>(k);

  k1_arg = {k, 2 * x + 1};
  k2_arg = {k, 2 * x + 1};
  goto *k11;
}
k1 : {
  auto[k2, i] = *k1_arg;

  f1_arg = {{&&f1}, {std::get<1>(k2) + std::get<2>(k2)}, {&&k2, i, 0}};
  goto f1;
}

k2 : {
  auto[k22, j] = *k2_arg;
  return std::get<1>(k22) * j;
}
}

int main() {
  // ((1+2)*2+1) * ((3+4)*2+1) = 105
  printf("%d\n", work(1, 2, 3, 4));
  return 0;
}
