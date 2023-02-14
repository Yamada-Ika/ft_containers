#include "main_helper_for_comp_output.hpp"

int main() {
  vec_test(std::vector<int>());
  stack_test(std::stack<int>());
  map_test(std::map<int, int>(), std::pair<int, int>());
  set_test(std::set<int>());
}
