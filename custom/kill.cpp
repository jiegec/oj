#include <algorithm>
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<string> people;
  vector<vector<int>> is_killer;
  vector<vector<int>> not_killer;
  int state[15] = {0};
  int count[4] = {0};
  count[0] = n;
  for (int i = 0; i < n; i++) {
    string person;
    getline(cin, person);
    cin >> person;
    people.push_back(person);
    vector<int> g, ng, d;
    is_killer.push_back(g);
    not_killer.push_back(ng);
  }
  string empty;
  getline(cin, empty);
  for (int i = 0; i < m; i++) {
    string line;
    getline(cin, line);
    int id = line.find(':');
    string name = line.substr(0, id);
    string say = line.substr(id + 2);
    int index = -1;
    for (int j = 0; j < n; j++) {
      if (name == people[j]) {
        index = j;
        break;
      }
    }
    for (int j = 0; j < n; j++) {
      int i_not = say.find("not");
      if (say.substr(0, 3) == people[j] && i_not == -1) {
        is_killer[index].push_back(j);
        break;
      } else if (say.substr(0, 3) == people[j] && i_not != -1) {
        not_killer[index].push_back(j);
        break;
      }
    }
  }
  int max_p = 0, max_k = 0;
  while (1) {
    count[state[n - 1]]--;
    count[++state[n - 1]]++;
    int i = n - 1;
    while (state[i] == 3 && i > 0) {
      count[3]--;
      state[i] = 0;
      count[0]++;
      i--;
      count[state[i]]--;
      count[++state[i]]++;
    }
    if (i == 0 && state[0] == 3) {
      break;
    }
    if (count[0] && count[1] && count[2]) {
      bool flag = true;
      for (int i = 0; i < n && flag; i++) {
        if (state[i] == 1) {
          // police
          int len = is_killer[i].size();
          for (int j = 0; j < len; j++) {
            if (state[is_killer[i][j]] != 2) {
              flag = false;
              break;
            }
          }

          int len2 = not_killer[i].size();
          for (int j = 0; j < len2 && flag; j++) {
            if (state[not_killer[i][j]] == 2) {
              flag = false;
              break;
            }
          }
        } else if (state[i] == 2) {
          // killer
          int len = is_killer[i].size();
          for (int j = 0; j < len; j++) {
            if (state[is_killer[i][j]] == 2) {
              flag = false;
              break;
            }
          }
        }
      }

      if (flag) {
        max_p = max(max_p, count[1]);
        max_k = max(max_k, count[2]);
      }
    }
  }

  if (max_p == 0 || max_k == 0) {
    cout << "impossible";
  } else {
    cout << max_p << " " << max_k;
  }
}
