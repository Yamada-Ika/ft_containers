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

  std::deque<int> dec = {0, 1, 2};
  std::deque<int>::iterator itr = dec.begin();
  ++itr;
  ++itr;
  LOG(ERROR) << "*itr " << *itr;

  dec.resize(1);
  LOG(ERROR) << "*itr " << *itr;
}
