#include "../vector.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <stdio.h>
#include <glog/logging.h>

int main(int ac, char** av) {
  google::InitGoogleLogging(av[0]);

  std::deque<int> dec;
  LOG(ERROR) << dec.front();
  LOG(ERROR) << dec.back();
}
