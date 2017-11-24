#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <chrono>

struct Node {
  float value1;
  int value2;
};

Node *values[10];

template<typename T, typename CLASS, T CLASS::*member>
static int compare(const void *a, const void *b) {
  const T &ta = (*(CLASS**)a)->*member;
  const T &tb = (*(CLASS**)b)->*member;
  if (ta > tb)
    return 1;
  if (ta < tb)
    return -1;
  return 0;
};

int main() {
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::random_device device;
  std::mt19937 rnd(device());
  for (auto &value : values) {
    value = new Node;
    value->value1 = rnd();
    value->value2 = rnd();
  }
  qsort(values, 10, sizeof(Node*), compare<float,Node,&Node::value1>);
  for (auto &value : values) {
    printf("%f %d\n", value->value1, value->value2);
  }
  return 0;
}
