#include <stdio.h>

struct TreeNode {
  TreeNode *left, *right;
};

template<typename Callable>
void morrisTraversal(TreeNode *root, Callable f) {
  TreeNode *cur = root, *pred = NULL;
  while(cur != NULL) {
    if (cur->left == NULL) {
      f(cur);
      cur = cur->right;
    } else {
      pred = cur->left;
      while(pred->right != NULL && pred->right != cur)
        pred = pred->right;

      if (pred->right == NULL) {
        pred->right = cur;
        cur = cur->left;
      } else {
        pred->right = NULL;
        f(cur);
        cur = cur->right;
      }
    }
  }
}

int main() {

}
