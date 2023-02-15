#include "main_helper_for_perf.hpp"

int main() {
  vec_test(ft::vector<int>());
  vec_stack(ft::stack<int>());
  vec_map(ft::map<int, int>(), ft::pair<int, int>());
  vec_set(ft::set<int>());
}
