#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n, m;
  vector<int> a, b, i, u, d;
  int temp;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &temp), a.push_back(temp);
  scanf("%d", &m);
  for (int i = 0; i < m; i++)
    scanf("%d", &temp), b.push_back(temp);
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  set_union(a.begin(), a.end(), b.begin(), b.end(),
            std::inserter(u, u.begin()));
  set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                   std::inserter(i, i.begin()));
  set_difference(a.begin(), a.end(), b.begin(), b.end(),
                 std::inserter(d, d.begin()));
  cout << std::accumulate(i.begin(), i.end(), std::string(),
                          [](const std::string &a, int b) -> std::string {
                            return a + (a.empty() ? "" : " ") +
                                   std::to_string(b);
                          })
       << endl;
  cout << std::accumulate(u.begin(), u.end(), std::string(),
                          [](const std::string &a, int b) -> std::string {
                            return a + (a.empty() ? "" : " ") +
                                   std::to_string(b);
                          })
       << endl;
  cout << std::accumulate(d.begin(), d.end(), std::string(),
                          [](const std::string &a, int b) -> std::string {
                            return a + (a.empty() ? "" : " ") +
                                   std::to_string(b);
                          })
       << endl;
}
