// https://codeforces.com/contest/1681/problem/A
#include <algorithm>
#include <stdio.h>
#include <vector>

int compute(int first_turn, std::vector<int> cards[2]) {
  int max = cards[first_turn][cards[first_turn].size() - 1];
  int other_max = cards[1 - first_turn][cards[1 - first_turn].size() - 1];
  if (max >= other_max) {
    return first_turn;
  } else {
    return 1 - first_turn;
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    // 0: Alice, 1: Bob
    std::vector<int> cards[2];

    for (int i = 0; i < 2; i++) {
      int n;
      scanf("%d", &n);
      for (int j = 0; j < n; j++) {
        int num;
        scanf("%d", &num);
        cards[i].push_back(num);
      }
    }
    std::sort(cards[0].begin(), cards[0].end());
    std::sort(cards[1].begin(), cards[1].end());

    int res_0 = compute(0, cards);
    printf("%s\n", res_0 ? "Bob" : "Alice");
    int res_1 = compute(1, cards);
    printf("%s\n", res_1 ? "Bob" : "Alice");
  }
  return 0;
}