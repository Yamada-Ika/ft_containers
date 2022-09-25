#include "../is_integral.hpp"
#include <cassert>

int main(void) {
  assert(ft::is_integral<int>::value == true);
  assert(ft::is_integral<int>::value == false);
}