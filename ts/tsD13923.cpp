#include <vector>
#include <utility>
#include <algorithm>
#include <stdio.h>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
  return a.first < b.first;
}

int main() {
  int n;
  scanf("%d",&n);
  vector< pair<int, int> > vec;
  for (int i = 0;i < n;i++)  {
    int l, r;
    scanf("%d%d", &l, &r);
    vec.push_back(pair<int, int>(l, r));
  }
  sort(vec.begin(), vec.end(), cmp);
  int size = vec.size();
  int length = 0;
  int las_end = -1;
  for (int i = 0;i < size;i++) {
    pair<int, int> cur = vec[i];
    if (cur.first <= las_end) {
      if (cur.second > las_end) {
        length += cur.second - las_end;
        las_end = cur.second;
      }
    } else {
      las_end = cur.second;
      length += cur.second - cur.first;
    }
  }

  printf("%d\n", length);
}
