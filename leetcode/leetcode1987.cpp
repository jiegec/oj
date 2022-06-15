// https://leetcode-cn.com/problems/number-of-unique-good-subsequences/

#include <string>

using namespace std;

class Solution {
public:
  int numberOfUniqueGoodSubsequences(string binary) {
    int begin = 0;
    long long res = 0;
    for (int i = 0; i < binary.size(); i++) {
      if (binary[i] == '0') {
        res = 1;
        break;
      }
    }

    if (binary[0] == '0') {
      while (begin < binary.size() && binary[begin] == '0') {
        begin++;
      }
    }

    long long hist_acc[2] = {0};
    long long mod = 1000000000 + 7;
    char last_ch = '\0';
    int length = 1;
    for (int i = begin; i < binary.size(); i++) {
      char ch = binary[i] - '0';

      if (i == begin) {
        res += 1;
        hist_acc[ch] = 1;
      } else if (i == begin + 1) {
        res += 1;
        hist_acc[ch] = 1;
      } else {
        if (ch == last_ch) {
          long long acc = hist_acc[ch];
          res = (res + acc) % mod;
        } else {
          long long acc = (hist_acc[1 - ch] * length) % mod;
          acc = (acc + hist_acc[ch]) % mod;
          res = (res + acc) % mod;
          hist_acc[ch] = acc;
        }
      }

      if (i != begin && ch == last_ch) {
        length++;
      } else {
        length = 1;
      }

      last_ch = ch;
    }
    return res;
  }
};