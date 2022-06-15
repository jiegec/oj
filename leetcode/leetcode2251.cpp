// https://leetcode-cn.com/problems/number-of-flowers-in-full-bloom/
// 线段树 区间加法和查询
#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Node {
  int sum;
  // [left, right]
  int left, right;
  Node *left_child, *right_child;
};

class Solution {
public:
  // [left, right]
  Node *build_tree(int *persons, int left, int right) {
    Node *node = new Node;
    node->sum = 0;
    node->left_child = node->right_child = NULL;
    node->left = persons[left];
    node->right = persons[right];
    assert(node->left <= node->right);
    if (right - left >= 1) {
      int mid = (left + right) / 2;
      node->left_child = build_tree(persons, left, mid);
      node->right_child = build_tree(persons, mid + 1, right);
      assert(node->left == node->left_child->left);
      assert(node->right == node->right_child->right);
      assert(persons[mid] < persons[mid + 1]);
      assert(node->left_child->right < node->right_child->left);
    }
    return node;
  }

  void add(Node *node, int left, int right) {
    assert(left <= right);
    if (node == NULL) {

    } else if (left <= node->left && node->right <= right) {
      node->sum++;
    } else if (node->right < left || node->left > right) {
      return;
    } else {
      add(node->left_child, left, right);
      add(node->right_child, left, right);
    }
    return;
  }

  int query(Node *node, int index) {
    int res = 0;
    if (node == NULL) {
      return 0;
    }

    if (node->left <= index && index <= node->right) {
      res += node->sum;
    } else if (node->right < index || node->left > index) {
      return 0;
    }
    res += query(node->left_child, index);
    res += query(node->right_child, index);
    return res;
  }

  vector<int> fullBloomFlowers(vector<vector<int>> &flowers,
                               vector<int> &persons) {
    vector<int> sorted_persons = persons;
    sort(sorted_persons.begin(), sorted_persons.end());
    auto last = unique(sorted_persons.begin(), sorted_persons.end());
    sorted_persons.erase(last, sorted_persons.end());

    Node *root = build_tree(&sorted_persons[0], 0, sorted_persons.size() - 1);
    for (auto &flower : flowers) {
      add(root, flower[0], flower[1]);
    }

    vector<int> res;
    for (auto &person : persons) {
      res.push_back(query(root, person));
    }
    return res;
  }
};