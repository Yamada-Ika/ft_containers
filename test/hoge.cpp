#include "../vector.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <stdio.h>

int main(int ac, char** av) {
  std::deque<int> d1 = {1, 2, 3};
  std::deque<int> d2 = {4, 5};

  std::cerr << d2.begin() - d1.begin() << std::endl;
}
