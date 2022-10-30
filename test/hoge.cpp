#include "../vector.hpp"
#include "../stack.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <set>
#include <list>
#include <map>
#include <stdio.h>

int main(int ac, char** av) {
  ft::vector<int> v1;
  v1.push_back(1);
  std::cerr << "v1 value : " << v1.at(0) << std::endl;
}
