#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

using namespace std::string_literals;

std::vector<std::tuple<std::string, char, char, int, std::string>> table = {
    {"start", '*', '*', -1, "add"},
    {"add", '0', '1', 1, "return"},
    {"return", '*', '*', 0, "halt"}};

int main() {
  auto data = "*110*"s;
  int offset = 4;
  auto state = "start"s;
  while (state != "halt"s) {
    for (int i = 0; i < 3; i++) {
      printf("%s off:%d %s\n", data.data(), offset, state.data());
      if (state == std::get<0>(table[i]) &&
          data[offset] == std::get<1>(table[i])) {
        data[offset] = std::get<2>(table[i]);
        offset += std::get<3>(table[i]);
        state = std::get<4>(table[i]);
      }
    }
  }
  return 0;
}
