#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>

using namespace std;

struct Node {
  Node* left = NULL;
  Node* right = NULL;
  int weight = 0;
  int index = 0;

  bool operator()(const Node* a, const Node* b) {
    return a->weight > b->weight;
  }
};

Node* root = NULL;
char buffer[10480];
int len = 0;
int freq[26] = {0};

int calc_length(Node* current, int cur_depth) {
  if (current->left == NULL && current->right == NULL) {
    return freq[current->index] * cur_depth;
  }
  return calc_length(current->left, cur_depth + 1) +
         calc_length(current->right, cur_depth + 1);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  scanf("%s", buffer);
  len = strlen(buffer);
  if (len == 1) {
    // only one char?
    // zero entropy here
    // no reasonable answer
    printf("1\n");
    return 0;
  }
  priority_queue<Node*, std::vector<Node*>, Node> pq;
  for (int i = 0; i < len; i++) {
    freq[buffer[i] - 'a']++;
  }
  for (int i = 0; i < 26; i++) {
    if (freq[i]) {
      Node* node = new Node;
      node->weight = freq[i];
      node->index = i;
      pq.push(node);
    }
  }
  while (pq.size() > 1) {
    Node* first = pq.top();
    pq.pop();

    Node* second = pq.top();
    pq.pop();

    Node* new_node = new Node;
    new_node->left = first;
    new_node->right = second;
    new_node->weight = first->weight + second->weight;
    pq.push(new_node);
  }
  root = pq.top();
  printf("%d\n", calc_length(root, 0));
  return 0;
}
