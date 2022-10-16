#include "../vector.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <glog/logging.h>

int main(int ac, char** av) {
  google::InitGoogleLogging(av[0]);
  std::deque<int> deq(10, 42);

  deq.push_back(100);
}
