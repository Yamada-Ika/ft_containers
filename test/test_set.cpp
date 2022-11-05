#include <gtest/gtest.h>

#include <memory>
#include <set>
#include "../set.hpp"

// constructor

// empty
TEST(TreeTest, int_basic_empty) {
  std::set<int> libst;
  ft::set<int> myst;
  ASSERT_EQ(libst.empty(), myst.empty());
}

// size
TEST(TreeTest, int_basic_size) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);
  ASSERT_EQ(libst.size(), myst.size());
}

// max_size
// clear
// swap
// key_comp
// value_comp
// compare operators
