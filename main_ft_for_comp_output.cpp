#include "main_helper_for_comp_output.hpp"

int main() {
  vec_test(ft::vector<int>());
  stack_test(ft::stack<int>());
  map_test(ft::map<int, int>(), ft::pair<int, int>());
  set_test(ft::set<int>());
}
