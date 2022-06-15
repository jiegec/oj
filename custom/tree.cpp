#include <complex>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

const int basen = 16;
const int mask = (1 << basen) - 1;
const double PI = acos(-1.0);
const int FFT_THRESOLD = 512;

const int MAXN = 256;

complex<double> aa[2 * MAXN], bb[2 * MAXN];

int highbit(int num) {
  int ret = 0;

  while (num >>= 1)
    ret += 1;

  return ret;
}

void rader(complex<double> y[2 * MAXN], int len) {
  for (int i = 1, j = len >> 1, k; i < len - 1; ++i) {
    if (i < j) {
      swap(y[i], y[j]);
    }
    k = len >> 1;
    while (j >= k) {
      j -= k;
      k >>= 1;
    }
    if (j < k)
      j += k;
  }
}

void fft(complex<double> y[2 * MAXN], int op, int len) {
  rader(y, len);

  for (int h = 2; h <= len; h <<= 1) {
    complex<double> Wn(cos(op * 2 * PI / h), sin(op * 2 * PI / h));

    for (int i = 0; i < len; i += h) {
      complex<double> W(1, 0);
      for (int j = i; j < i + h / 2; ++j) {
        complex<double> u = y[j];
        complex<double> t = W * y[j + h / 2];
        y[j] = u + t;
        y[j + h / 2] = u - t;
        W = W * Wn;
      }
    }
  }
  if (op == -1)
    for (int i = 0; i < len; i++) {
      y[i].real(y[i].real() / len);
    }
}

class BigNumber {
private:
  int num[MAXN];
  int length;

public:
  BigNumber() {
    memset(num, 0, sizeof(num));
    length = 0;
  }

  BigNumber(const char *str, int len) {
    memset(num, 0, sizeof(num));
    length = 0;
    for (int i = len - 1; i >= 0; i -= basen) {
      int begin = max(0, i - basen + 1);
      int n = 0;
      for (int j = i; j >= begin; j--) {
        num[length] |= (str[j] - '0') << n;
        n++;
      }
      length++;
    }
  }

  bool operator<(const BigNumber &b) const {
    if (length < b.length) {
      return true;
    } else if (length > b.length) {
      return false;
    }
    for (int i = length - 1; i >= 0; i--) {
      if (num[i] < b.num[i]) {
        return true;
      } else {
        return false;
      }
    }
    return false;
  }

  bool operator>(const BigNumber &b) const {
    if (length < b.length) {
      return false;
    } else if (length > b.length) {
      return true;
    }
    for (int i = length - 1; i >= 0; i--) {
      if (num[i] < b.num[i]) {
        return false;
      } else {
        return true;
      }
    }
    return true;
  }

  bool operator==(const BigNumber &b) const {
    if (length != b.length) {
      return false;
    }
    for (int i = length - 1; i >= 0; i--) {
      if (num[i] != b.num[i]) {
        return false;
      }
    }
    return true;
  }

  operator string() const {
    char s[MAXN];
    int index = 0;
    if (length == 0) {
      return "0";
    } else {
      int high = highbit(num[length - 1]);
      for (int i = high; i >= 0; i--) {
        s[index++] = (((1 << i) & num[length - 1]) != 0) + '0';
      }
      for (int i = length - 2; i >= 0; i--) {
        for (int j = basen - 1; j >= 0; j--) {
          s[index++] = (((1 << j) & num[i]) != 0) + '0';
        }
      }
    }
    s[index++] = '\0';
    return string(s);
  }

  void print() { printf("%s\n", ((string) * this).c_str()); }

  BigNumber operator+(const BigNumber &b) const {
    BigNumber ret;
    ret.length = max(length, b.length);
    for (int i = 0; i < ret.length; i++) {
      ret.num[i] = num[i] + b.num[i];
      ret.num[i + 1] += ret.num[i] >> basen;
      ret.num[i] &= mask;
    }
    ret.length++;
    while (ret.length && ret.num[ret.length - 1] == 0)
      ret.length--;
    return ret;
  }

  BigNumber operator+(int b) const {
    BigNumber ret;
    ret.length = length;
    ret.num[0] += b;
    for (int i = 0; i < ret.length && ret.num[i] >= (1 << basen); i++) {
      ret.num[i + 1] += ret.num[i] >> basen;
      ret.num[i] &= mask;
    }
    ret.length++;
    while (ret.length && ret.num[ret.length - 1] == 0)
      ret.length--;
    return ret;
  }

  BigNumber operator*(const BigNumber &b) const {
    BigNumber ret;
    if (length <= FFT_THRESOLD && b.length <= FFT_THRESOLD) {
      for (int i = 0; i < length; i++) {
        for (int j = 0; j < b.length; j++) {
          ret.num[i + j] += num[i] * b.num[j];
          ret.num[i + j + 1] += ret.num[i + j] >> basen;
          ret.num[i + j] &= mask;
        }
      }
      ret.length = length + b.length;
      while (ret.length && ret.num[ret.length - 1] == 0)
        ret.length--;
      return ret;
    }
    int maxlen = max(length, b.length);
    int twolen = 1;

    while (twolen < (maxlen << 1))
      twolen <<= 1;

    for (int i = 0; i < length; i++) {
      aa[i] = num[i];
    }
    for (int i = length; i < twolen; i++) {
      aa[i] = 0;
    }

    for (int i = 0; i < b.length; i++) {
      bb[i] = b.num[i];
    }
    for (int i = b.length; i < twolen; i++) {
      bb[i] = 0;
    }

    fft(aa, 1, twolen);
    fft(bb, 1, twolen);
    for (int i = 0; i < twolen; i++) {
      aa[i] = aa[i] * bb[i];
    }
    fft(aa, -1, twolen);

    for (int i = 0; i < twolen; i++) {
      ret.num[i] = int(aa[i].real() + 0.5);
    }

    for (int i = 0; i < twolen; i++) {
      ret.num[i + 1] += ret.num[i] >> basen;
      ret.num[i] &= mask;
    }

    ret.length = twolen;
    while (ret.length && ret.num[ret.length - 1] == 0)
      ret.length--;

    return ret;
  }
};

const BigNumber TWO("10", 2);
const BigNumber ONE("1", 1);
const BigNumber ZERO("0", 0);

struct LinkNode {
  BigNumber index;
  int data;
  LinkNode *next;
};

class Array {
private:
  LinkNode *head;

public:
  Array() { head = NULL; }

  int get(BigNumber index) {
    LinkNode *current = head;
    while (current != NULL) {
      if (current->index == index) {
        return current->data;
      }
      if (current->index > index) {
        return 0;
      }
      current = current->next;
    }
    return 0;
  }

  BigNumber pre(BigNumber index) {
    LinkNode *current = head;
    if (current == NULL ||
        (current->index > index || current->index == index)) {
      return ZERO;
    }
    BigNumber sum;
    while (current != NULL) {
      sum = sum + ONE;
      if ((current->next &&
           (current->next->index > index || current->next->index == index)) ||
          current->next == NULL) {
        return sum;
      }
      current = current->next;
    }
    return sum;
  }

  void set(BigNumber index, int n) {
    LinkNode *current = head;
    if (current == NULL) {
      head = new LinkNode;
      head->data = n;
      head->index = index;
      head->next = NULL;
    } else {
      while (current != NULL) {
        if (current->index == index) {
          current->data = n;
        }
        if ((current->next && current->next->index > index) ||
            current->next == NULL) {
          LinkNode *oldnext = current->next;
          current->next = new LinkNode;
          current->next->data = n;
          current->next->index = index;
          current->next->next = oldnext;
          return;
        }
        current = current->next;
      }
    }
  }
};

Array *tree[MAXN] = {NULL};
BigNumber nodes[MAXN];

int main(int argc, char **argv) {
  char buffer[MAXN];
  tree[0] = new Array();
  tree[0]->set(ZERO, 1);
  nodes[0] = ONE;
  while (scanf("%s", buffer) != EOF && buffer[0]) {
    int len = strlen(buffer);
    for (int i = 0; i < len; i++) {
      if (buffer[i] == 'l') {
        buffer[i] = '0';
      } else {
        buffer[i] = '1';
      }
    }
    BigNumber index;
    for (int depth = 1; depth <= len; depth++) {
      index = index * TWO;
      if (buffer[depth - 1] == '1') {
        index = index + ONE;
      }
      if (!tree[depth]) {
        tree[depth] = new Array();
      }
      if (tree[depth]->get(index) == 0) {
        nodes[depth] = nodes[depth] + ONE;
        tree[depth]->set(index, 1);
      }
    }
    BigNumber sum;
    for (int i = 0; i < len; i++) {
      sum = sum + nodes[i];
    }
    sum = sum + tree[len]->pre(index);
    sum.print();
  }
}
