// NOIP 2003 提高组 侦探推理 模拟
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<string> people;
  vector<vector<int>> is_guilty;
  vector<vector<int>> not_guilty;
  vector<vector<int>> days;
  int m, n, p;
  cin >> m >> n >> p;
  for (int i = 0; i < m; i++) {
    string person;
    cin >> person;
    people.push_back(person);
    vector<int> g, ng, d;
    is_guilty.push_back(g);
    not_guilty.push_back(ng);
    days.push_back(d);
  }
  string empty;
  getline(cin, empty);
  for (int i = 0; i < p; i++) {
    string line;
    getline(cin, line);
    int id = line.find(':');
    string name = line.substr(0, id);
    string say = line.substr(id + 2);
    if (say == "I am guilty.") {
      say = name + " is guilty.";
    } else if (say == "I am not guilty.") {
      say = name + " is not guilty.";
    }

    int index = 0;
    for (int j = 0; j < m; j++) {
      if (name == people[j]) {
        index = j;
        break;
      }
    }

    for (int j = 0; j < m; j++) {
      if (say == people[j] + " is guilty.") {
        is_guilty[index].push_back(j);
        break;
      } else if (say == people[j] + " is not guilty.") {
        not_guilty[index].push_back(j);
        break;
      }
    }

    if (say.compare(0, 9, "Today is ") == 0) {
      string day = say.substr(9);
      if (day == "Sunday.") {
        days[index].push_back(0);
      } else if (day == "Monday.") {
        days[index].push_back(1);
      } else if (day == "Tuesday.") {
        days[index].push_back(2);
      } else if (day == "Wednesday.") {
        days[index].push_back(3);
      } else if (day == "Thursday.") {
        days[index].push_back(4);
      } else if (day == "Friday.") {
        days[index].push_back(5);
      } else if (day == "Saturday.") {
        days[index].push_back(6);
      }
    }
  }

  int solution = 0, s_i = 0;
  for (int i = 0; i < m; i++) {
    // i is guilty
    for (int j = 0; j < 7; j++) {
      // j is day
      bool flag = true;
      int good = 0, bad = 0, not_sure = 0;
      for (int k = 0; k < m && flag; k++) {
        int state = 0; // 1 for true, 2 for false
        int size = is_guilty[k].size();
        for (int l = 0; l < size && flag; l++) {
          if (is_guilty[k][l] == i) {
            if (state == 0) {
              state = 1;
            } else if (state == 2) {
              flag = false;
              break;
            }
          } else if (is_guilty[k][l] != i) {
            if (state == 0) {
              state = 2;
            } else if (state == 1) {
              flag = false;
              break;
            }
          }
        }

        int size2 = not_guilty[k].size();
        for (int l = 0; l < size2 && flag; l++) {
          if (not_guilty[k][l] != i) {
            if (state == 0) {
              state = 1;
            } else if (state == 2) {
              flag = false;
              break;
            }
          } else if (not_guilty[k][l] == i) {
            if (state == 0) {
              state = 2;
            } else if (state == 1) {
              flag = false;
              break;
            }
          }
        }

        int size3 = days[k].size();
        for (int l = 0; l < size3 && flag; l++) {
          if (days[k][l] == j) {
            if (state == 0) {
              state = 1;
            } else if (state == 2) {
              flag = false;
              break;
            }
          } else if (days[k][l] != j) {
            if (state == 0) {
              state = 2;
            } else if (state == 1) {
              flag = false;
              break;
            }
          }
        }

        if (flag) {
          good += state == 1;
          bad += state == 2;
          not_sure += state == 0;
        }
      }

      if (flag) {
        if (bad <= n && n <= bad + not_sure) {
          solution++;
          s_i = i;
          break;
        }
      }
    }
  }

  if (solution == 0) {
    cout << "Impossible" << endl;
  } else if (solution == 1) {
    cout << people[s_i] << endl;
  } else {
    cout << "Cannot Determine" << endl;
  }
}
