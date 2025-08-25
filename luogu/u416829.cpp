#include <cassert>
#include <stack>
#include <stdint.h>
#include <stdio.h>
#include <vector>

struct Entry {
  uint64_t count;
  uint64_t value;
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::stack<Entry>> stacks;
  std::vector<uint64_t> sums;
  stacks.resize(n);
  sums.resize(n);
  for (int i = 0; i < m; i++) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int x, w, c;
      scanf("%d%d%d", &x, &w, &c);
      Entry entry;
      entry.count = c;
      entry.value = w;
      stacks[x - 1].push(entry);
      sums[x - 1] += (uint64_t)c * w;
      printf("%ld\n", sums[x - 1]);
    } else if (op == 2) {
      int x, c;
      scanf("%d%d", &x, &c);
      uint64_t sum = 0;
      while (c > 0) {
        assert(!stacks[x - 1].empty());
        Entry &entry = stacks[x - 1].top();
        if (entry.count >= c) {
          // finish
          entry.count -= c;
          sums[x - 1] -= c * entry.value;
          sum += c * entry.value;
          if (entry.count == 0) {
            stacks[x - 1].pop();
          }
          break;
        } else {
          sums[x - 1] -= entry.count * entry.value;
          sum += entry.count * entry.value;
          c -= entry.count;
          stacks[x - 1].pop();
        }
      }
      printf("%ld\n", sum);
    } else if (op == 3) {
      int x, y;
      scanf("%d%d", &x, &y);
      while (!stacks[x - 1].empty()) {
        stacks[y - 1].push(stacks[x - 1].top());
        stacks[x - 1].pop();
      }
      sums[y - 1] += sums[x - 1];
      sums[x - 1] = 0;
      printf("%ld\n", sums[y - 1]);
    }
  }
  return 0;
}