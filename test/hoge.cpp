#include "../vector.hpp"
#include "../stack.hpp"
#include "../pair.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <set>
#include <list>
#include <map>
#include <stdio.h>
#include <utility>
#include <memory>

int main(int ac, char** av) {
  std::set<int> st;
  std::map<int> mp;
  st.insert(1);
  std::set<int>::iterator itr = st.begin();

  std::cerr << *itr << std::endl;
}
