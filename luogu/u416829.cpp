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
  // count of numbers in whole
  uint64_t count;
  // sum of numbers in whole
  uint64_t sum;

  Node() { count = sum = 0; }

  void validate() const {
    uint64_t temp_count = 0;
    uint64_t temp_sum = 0;
    for (auto entry : data) {
      temp_count += entry.count;
      temp_sum += entry.count * entry.value;
    }
    for (auto node : reversed) {
      temp_count += node->count;
      temp_sum += node->sum;
      node->validate();
    }
    assert(temp_count == count);
    assert(temp_sum == sum);
  }

  void push(struct Entry &entry) {
    if (reversed.empty()) {
      data.push_back(entry);
      count += entry.count;
      sum += entry.count * entry.value;
    } else {
      reversed.back()->data.push_front(entry);
      reversed.back()->count += entry.count;
      reversed.back()->sum += entry.count * entry.value;
      count += entry.count;
      sum += entry.count * entry.value;
    }
  }

  // return pair of (count, sum) popped
  std::pair<uint64_t, uint64_t> pop_inner(uint64_t count_to_pop) {
    if (count_to_pop >= count) {
      // pop everything
      std::pair<uint64_t, uint64_t> res = std::make_pair(count, sum);
      count = 0;
      sum = 0;
      data.clear();
      reversed.clear();
      return res;
    }

    // popped count & sum
    uint64_t pop_sum = 0;
    uint64_t pop_count = 0;
    while (count_to_pop > 0) {
      if (reversed.empty()) {
        // no reversed, pop from data.back
        while (count_to_pop > 0) {
          assert(!data.empty());
          if (count_to_pop > data.back().count) {
            count_to_pop -= data.back().count;
            pop_count += data.back().count;
            pop_sum += data.back().count * data.back().value;
            data.pop_back();
          } else {
            pop_count += count_to_pop;
            pop_sum += count_to_pop * data.back().value;
            data.back().count -= count_to_pop;
            count_to_pop = 0;
            if (data.back().count == 0) {
              data.pop_back();
            }
            break;
          }
        }
        assert(count_to_pop == 0);
        break;
      } else {
        // some reversed
        if (reversed.back()->count <= count_to_pop) {
          // pop as a whole
          count_to_pop -= reversed.back()->count;
          pop_count += reversed.back()->count;
          pop_sum += reversed.back()->sum;
          reversed.pop_back();
          continue;
        }

        if (!reversed.back()->data.empty()) {
          // last reversed has data, pop from front
          while (count_to_pop > 0 && !reversed.back()->data.empty()) {
            if (count_to_pop > reversed.back()->data.front().count) {
              uint64_t count = reversed.back()->data.front().count;
              uint64_t sum = count * reversed.back()->data.front().value;
              count_to_pop -= count;
              pop_count += count;
              pop_sum += sum;
              reversed.back()->data.pop_front();
              // maintain
              reversed.back()->count -= count;
              reversed.back()->sum -= sum;
            } else {
              uint64_t count = count_to_pop;
              uint64_t sum = count * reversed.back()->data.front().value;

              count_to_pop -= count;
              pop_count += count;
              pop_sum += sum;
              reversed.back()->data.front().count -= count;
              if (reversed.back()->data.front().count == 0) {
                reversed.back()->data.pop_front();
              }

              // maintain
              reversed.back()->count -= count;
              reversed.back()->sum -= sum;

              break;
            }
          }
          continue;
        } else if (reversed.back()->reversed.empty()) {
          // last reversed has no data, and it has no reversed
          // drop it
          reversed.pop_back();
          continue;
        } else {
          // last reversed has no data, but it has reversed
          // it is in normal order now, pop its last
          // recurse
          std::pair<uint64_t, uint64_t> res =
              reversed.back()->reversed.front()->pop_inner(count_to_pop);
          // maintain
          reversed.back()->count -= res.first;
          reversed.back()->sum -= res.second;
          count_to_pop -= res.first;
          pop_count += res.first;
          pop_sum += res.second;
          if (reversed.back()->reversed.front()->count == 0) {
            // no data
            reversed.back()->reversed.pop_front();
          }
          continue;
        }
      }
    }

    count -= pop_count;
    sum -= pop_sum;
    return std::make_pair(pop_count, pop_sum);
  }

  uint64_t pop(uint64_t count) {
    std::pair<uint64_t, uint64_t> res = pop_inner(count);
    assert(res.first == count);
    return res.second;
  }
};

struct MyStack {
  Node *root;
  MyStack() { root = new Node; }

  void push(struct Entry &entry) { root->push(entry); }

  uint64_t pop(uint64_t count) { return root->pop(count); }

  void takeover(struct MyStack &stack) {
    root->reversed.push_back(stack.root);
    root->sum += stack.root->sum;
    root->count += stack.root->count;
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
      uint64_t sum = stacks[x - 1].pop(c);
      sums[x - 1] -= sum;
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
    } else {
      assert(false);
    }
  }
  return 0;
}