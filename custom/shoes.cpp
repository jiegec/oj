/*
  Yazid是球星K的粉丝，因此收集K的签名球鞋就成了Yazid的一大爱好。K的签名球鞋共有k款，Yazid正在为收集齐所有的款式而发愁。

  市面上共有n双K的签名球鞋，方便起见，我们把它们从1至n编号。其中，i号球鞋为第bi款（1≤bi≤k），价格为ci元，且种种迹象表明其为正品的概率为e−pi（pi≥0）。现在，Yazid共有m元的总预算，他打算在不超出预算的情况下，购买恰好k双不同款式的K签名球鞋。在此基础上，Yazid希望他购买到的所有球鞋均为正品的概率尽可能大，因为他只要购买到一双假鞋，就会非常失落。请你帮Yazid挑选出最合适的k双球鞋。方便起见，你只需要找到这个最大概率，并输出对其取自然对数后的结果即可（即设最大概率为P，则你需要输出lnP）。

  对于所有测试点，保证T≤5，保证所有数据中0≤n≤100，1≤k≤12，1≤m≤109，1≤ci≤m，0≤pi≤108。
*/

#include <algorithm>
#include <stdint.h>
#include <stdio.h>
#include <vector>

int n, m, k;

struct Shoe {
  int price;
  int value;
};

struct Style {
  std::vector<Shoe> shoes;
};

std::vector<Style> styles;

struct Solution {
  long long total_price;
  long long total_value;
};

bool operator<(const Solution &a, const Solution &b) {
  if (a.total_price != b.total_price) {
    return a.total_price < b.total_price;
  } else {
    return a.total_value < b.total_value;
  }
}

std::vector<Solution> bruteforce(int k_from, int k_to) {
  std::vector<Solution> res;
  if (k_from == k_to) {
    return res;
  }

  // all zeros: first entry
  std::vector<int> index;
  index.resize(k_to - k_from);

  Solution init_sol;
  init_sol.total_price = init_sol.total_value = 0;
  int total_options = 1;
  for (int i = k_from; i < k_to; i++) {
    init_sol.total_price += styles[i].shoes[0].price;
    init_sol.total_value += styles[i].shoes[0].value;
    total_options *= styles[i].shoes.size();
  }

  Solution cur_sol = init_sol;
  // printf("%d %d\n", cur_sol.total_price, cur_sol.total_value);
  res.push_back(cur_sol);
  for (int j = 0; j < total_options - 1; j++) {

    // advance to next solution
    if (index[0] < styles[k_from].shoes.size() - 1) {
      cur_sol.total_price -= styles[k_from].shoes[index[0]].price;
      cur_sol.total_value -= styles[k_from].shoes[index[0]].value;
      index[0]++;
      cur_sol.total_price += styles[k_from].shoes[index[0]].price;
      cur_sol.total_value += styles[k_from].shoes[index[0]].value;
    } else {
      // increment to next index
      int l = 0;

      while (index[l] == styles[k_from + l].shoes.size() - 1) {
        index[l] = 0;
        l++;
      }
      index[l]++;

      // i am lazy
      cur_sol.total_price = cur_sol.total_value = 0;
      for (int i = k_from; i < k_to; i++) {
        cur_sol.total_price += styles[i].shoes[index[i - k_from]].price;
        cur_sol.total_value += styles[i].shoes[index[i - k_from]].value;
      }
    }

    // printf("%d %d\n", cur_sol.total_price, cur_sol.total_value);
    res.push_back(cur_sol);
  }
  return res;
}

int main(int argc, char *argv[]) {
  scanf("%d%d%d", &n, &m, &k);
  styles.resize(k);
  for (int i = 0; i < n; i++) {
    int b, c, p;
    scanf("%d%d%d", &b, &c, &p);

    Shoe shoe;
    shoe.price = c;
    shoe.value = p;
    styles[b - 1].shoes.push_back(shoe);
  }

  // special: one style has no shoes
  for (int i = 0; i < k; i++) {
    if (styles[i].shoes.size() == 0) {
      printf("No solution\n");
      return 0;
    }
  }

  // special: only one style
  if (k == 1) {
    int res = INT32_MAX;
    for (int i = 0; i < styles[0].shoes.size(); i++) {
      if (styles[0].shoes[i].price < m) {
        res = std::min(res, styles[0].shoes[i].value);
      }
    }
    printf("%d\n", -res);
    return 0;
  }

  // find all possible solutions in first half and second half
  std::vector<Solution> first_half = bruteforce(0, k / 2);
  std::vector<Solution> second_half = bruteforce(k / 2, k);

  // sort by price
  std::sort(second_half.begin(), second_half.end());

  // find prefix min
  std::vector<Solution> second_half_prefix_min = second_half;
  for (int i = 0; i < second_half_prefix_min.size(); i++) {
    /*
    printf("%lld %lld\n", second_half_prefix_min[i].total_price,
           second_half_prefix_min[i].total_value);
           */
    if (i > 0) {
      second_half_prefix_min[i].total_value =
          std::min(second_half_prefix_min[i].total_value,
                   second_half_prefix_min[i - 1].total_value);
    }
  }
  // printf("\n\n");

  // permute
  long long result = __LONG_LONG_MAX__;
  for (int i = 0; i < first_half.size(); i++) {
    // printf("%lld %lld:\n", first_half[i].total_price,
    // first_half[i].total_value);
    long long price = first_half[i].total_price;
    struct Solution key;
    key.total_price = m - price;
    key.total_value = __LONG_LONG_MAX__;
    auto it = std::lower_bound(second_half_prefix_min.begin(),
                               second_half_prefix_min.end(), key);
    if (it != second_half_prefix_min.begin()) {
      it--;
      // printf("%lld %lld\n", first_half[i].total_value, it->total_value);
      result = std::min(result, first_half[i].total_value + it->total_value);
    }
  }

  if (result == __LONG_LONG_MAX__) {
    printf("No solution\n");
  } else {
    printf("-%lld\n", result);
  }

  return 0;
}