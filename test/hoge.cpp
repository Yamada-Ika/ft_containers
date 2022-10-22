#include "../vector.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <stdio.h>

int main(int ac, char** av) {
  std::deque<int> d = {1, 2, 3};
  std::deque<int>::iterator itr = d.begin();
  itr++;
  std::cout << *(itr.operator->()) << std::endl;
}
