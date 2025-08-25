#include <cassert>
#include <cstddef>
#include <list>
#include <stack>
#include <stdint.h>
#include <stdio.h>
#include <vector>

struct Entry {
  uint64_t count;
  uint64_t value;
};

struct Node {
  // data + reverse(reversed[0]) + reverse(reversed[1]) + ...
  std::list<Entry> data;
  std::deque<Node *> reversed;

  bool top(struct Entry **entry) {
  try_again:
    if (reversed.empty()) {
      // no reversed, get data.back
      if (data.empty()) {
        return false; // no data
      }
      *entry = &data.back();
      return true;
    } else {
      // some reversed
      if (!reversed.back()->data.empty()) {
        // last reversed has data, pop from front
        assert(!reversed.back()->data.empty());
        *entry = &reversed.back()->data.front();
        return true;
      } else if (reversed.back()->reversed.empty()) {
        // last reversed has no data, and it has no reversed
        // drop it
        reversed.pop_back();
        goto try_again;
      } else {
        // last reversed has no data, but it has reversed
        // it is in normal order now, pop its last
        bool good = reversed.back()->reversed.front()->top(entry);
        if (good) {
          return true;
        } else {
          // no data
          reversed.back()->reversed.pop_front();
        }
        goto try_again;
      }
    }
  }

  bool pop() {
  try_again:
    if (reversed.empty()) {
      // no reversed, pop from data.back
      if (data.empty()) {
        return false; // cannot pop
      }
      data.pop_back();
      return true;
    } else {
      // some reversed
      if (!reversed.back()->data.empty()) {
        // last reversed has data, pop from front
        assert(!reversed.back()->data.empty());
        reversed.back()->data.pop_front();
        return true;
      } else if (reversed.back()->reversed.empty()) {
        // last reversed has no data, and it has no reversed
        // drop it
        reversed.pop_back();
        goto try_again;
      } else {
        // last reversed has no data, but it has reversed
        // it is in normal order now, pop its last
        bool good = reversed.back()->reversed.front()->pop();
        if (good) {
          return true;
        } else {
          // no data
          reversed.back()->reversed.pop_front();
        }
        goto try_again;
      }
    }
  }
};

struct MyStack {
  Node *root;
  MyStack() { root = new Node; }

  void push(struct Entry &entry) {
    if (root->reversed.empty()) {
      root->data.push_back(entry);
    } else {
      root->reversed.back()->data.push_front(entry);
    }
  }

  void pop() { assert(root->pop()); }

  struct Entry *top() {
    struct Entry *ret;
    assert(root->top(&ret));
    return ret;
  }

  void takeover(struct MyStack &stack) {
    root->reversed.push_back(stack.root);
    stack.root = new Node;
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  // std::vector<std::stack<Entry>> stacks;
  std::vector<MyStack> stacks;
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
        Entry *entry = stacks[x - 1].top();
        if (entry->count >= c) {
          // finish
          entry->count -= c;
          sums[x - 1] -= c * entry->value;
          sum += c * entry->value;
          if (entry->count == 0) {
            stacks[x - 1].pop();
          }
          break;
        } else {
          sums[x - 1] -= entry->count * entry->value;
          sum += entry->count * entry->value;
          c -= entry->count;
          stacks[x - 1].pop();
        }
      }
      printf("%ld\n", sum);
    } else if (op == 3) {
      int x, y;
      scanf("%d%d", &x, &y);
      stacks[y - 1].takeover(stacks[x - 1]);
      // while (!stacks[x - 1].empty()) {
      //   stacks[y - 1].push(stacks[x - 1].top());
      //   stacks[x - 1].pop();
      // }
      sums[y - 1] += sums[x - 1];
      sums[x - 1] = 0;
      printf("%ld\n", sums[y - 1]);
    }
  }
  return 0;
}