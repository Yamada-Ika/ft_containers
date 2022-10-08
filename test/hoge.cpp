#include "../vector.hpp"
#include <cassert>
#include <vector>

int main(void) {
  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);
  vec.push_back(6);
  vec.push_back(7);

  std::iterator itr = vec.insert(2, 10);
}
