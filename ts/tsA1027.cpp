// http://oj.tsinsen.com/A1027
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

int dp[25][25];

int dist(string a, string b) {
  int lena = a.length();
  int lenb = b.length();
  for (int i = 0; i < lena; i++) {
    dp[i][0] = i;
  }
  for (int i = 0; i < lenb; i++) {
    dp[0][i] = i;
  }
  for (int i = 1; i <= lena; i++) {
    for (int j = 1; j <= lenb; j++) {
      int temp = !(a[i - 1] == b[j - 1]);
      dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
      dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + temp);
    }
  }
  return dp[lena][lenb];
}

int main() {
  vector<string> vec;
  string temp;
  string target;
  cin >> target;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> temp;
    vec.push_back(temp);
  }
  for (int i = 0; i < n; i++) {
    if (dist(vec[i], target) == 0) {
      cout << vec[i] << endl;
      return 0;
    }
  }
  for (int i = 0; i < n; i++) {
    if (dist(vec[i], target) == 1) {
      cout << vec[i] << endl;
      return 0;
    }
  }
  cout << "NOANSWER" << endl;
}
