#include "main_helper_for_perf.hpp"

int main() {
  vec_test(std::vector<int>());
  vec_stack(std::stack<int>());
  vec_map(std::map<int, int>(), std::pair<int, int>());
  vec_set(std::set<int>());
}
