#include <random>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  float value1;
  int value2;
};

Node *values[10];

template <typename T, typename CLASS, T CLASS::*member>
static int compare(const void *a, const void *b) {
  const T &ta = (*(CLASS **)a)->*member;
  const T &tb = (*(CLASS **)b)->*member;
  if (ta > tb)
    return 1;
  if (ta < tb)
    return -1;
  return 0;
};

enum SortAlgorithm { Quicksort, Mergesort };

template <typename T, SortAlgorithm algo> class generic_sort {
public:
  void operator()(T *begin, T *end);
};

template <typename T> class generic_sort<T, Quicksort> {
public:
  void operator()(T *begin, T *end) { printf("Quicksort\n"); }
};

template <typename T> class generic_sort<T, Mergesort> {
public:
  void operator()(T *begin, T *end) { printf("Mergesort\n"); }
};

template <SortAlgorithm algo, typename T,
          typename std::enable_if<algo == Quicksort, bool>::type = true>
void generic_sort2(T *begin, T *end) {
  printf("Quicksort\n");
};

template <SortAlgorithm algo, typename T,
          typename std::enable_if<algo == Mergesort, bool>::type = true>
void generic_sort2(T *begin, T *end) {
  printf("Mergesort\n");
};

int main() {
  auto seed =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::random_device device;
  std::mt19937 rnd(device());
  for (auto &value : values) {
    value = new Node;
    value->value1 = rnd();
    value->value2 = rnd();
  }
  generic_sort<Node *, (SortAlgorithm)Mergesort> sorter;
  int temp[10];
  generic_sort2<Quicksort>(temp, temp + 10);
  generic_sort2<Mergesort>(values, values + 10);
  sorter(values, values + 10);
  qsort(values, 10, sizeof(Node *), compare<float, Node, &Node::value1>);
  for (auto &value : values) {
    printf("%f %d\n", value->value1, value->value2);
  }
  return 0;
}
