// http://oj.tsinsen.com/D13920
#include <algorithm>
#include <set>
#include <stdio.h>
#include <vector>

using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  set<int> s;
  for (int i = 0; i < n; i++) {
    int temp;
    scanf("%d", &temp);
    s.insert(temp);
  }
  vector<int> v(s.begin(), s.end());
  sort(v.begin(), v.end());
  printf("%d\n", (int)v.size());
  for (int i = 0; i < v.size(); i++)
    printf("%d ", v[i]);
}
