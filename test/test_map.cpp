#include <gtest/gtest.h>

#include <memory>
#include <map>
#include "../map.hpp"

// constructor
// operator=
// get_allocator

// at
TEST(TreeTest, int_basic_at) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  libmp.insert(libpair);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  mymp.insert(mypair);
  ASSERT_EQ(libmp.at(1), mymp.at(1));
}

TEST(TreeTest, int_basic_at1) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  ASSERT_EQ(libmp.at(1), mymp.at(1));
  ASSERT_EQ(libmp.at(2), mymp.at(2));
}

TEST(TreeTest, int_basic_at2) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  std::pair<int, int> libpair2(3, 3);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  libmp.insert(libpair2);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  ft::pair<int, int> mypair2(3, 3);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  mymp.insert(mypair2);
  ASSERT_EQ(libmp.at(1), mymp.at(1));
  ASSERT_EQ(libmp.at(2), mymp.at(2));
  ASSERT_EQ(libmp.at(3), mymp.at(3));
}

TEST(TreeTest, int_basic_at3) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  std::pair<int, int> libpair2(2, 3);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  libmp.insert(libpair2);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  ft::pair<int, int> mypair2(2, 3);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  mymp.insert(mypair2);
  ASSERT_EQ(libmp.at(1), mymp.at(1));
  ASSERT_EQ(libmp.at(2), mymp.at(2));
}

// operator[]
TEST(TreeTest, int_basic_bracket_operator) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  libmp.insert(libpair);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  mymp.insert(mypair);
  ASSERT_EQ(libmp[1], mymp[1]);
}

TEST(TreeTest, int_basic_bracket_operato1) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  libmp.insert(libpair);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  mymp.insert(mypair);
  ASSERT_EQ(libmp[1], mymp[1]);
  ASSERT_EQ(libmp[2], mymp[2]);
}

TEST(TreeTest, int_basic_bracket_operato2) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  std::pair<int, int> libpair2(3, 3);
  libmp.insert(libpair);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  ft::pair<int, int> mypair2(3, 3);
  mymp.insert(mypair);
  ASSERT_EQ(libmp[1], mymp[1]);
  ASSERT_EQ(libmp[2], mymp[2]);
  ASSERT_EQ(libmp[3], mymp[3]);
}

TEST(TreeTest, int_basic_bracket_operato3) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  std::pair<int, int> libpair2(2, 3);
  libmp.insert(libpair);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  ft::pair<int, int> mypair2(2, 3);
  mymp.insert(mypair);
  ASSERT_EQ(libmp[1], mymp[1]);
  ASSERT_EQ(libmp[2], mymp[2]);
}

// begin
// end
// rbegin
// rend

// empty
TEST(TreeTest, int_basic_empty) {
  std::map<int, int> libmp;
  ft::map<int, int> mymp;
  ASSERT_EQ(libmp.empty(), mymp.empty());
}

// size && insert
TEST(TreeTest, int_basic_size) {
  std::map<int, int> libmp;
  ft::map<int, int> mymp;
  ASSERT_EQ(libmp.size(), mymp.size());
}

TEST(TreeTest, int_basic_size1) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  libmp.insert(libpair);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  mymp.insert(mypair);
  ASSERT_EQ(libmp.size(), mymp.size());
}

TEST(TreeTest, int_basic_size2) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  ASSERT_EQ(libmp.size(), mymp.size());
}

TEST(TreeTest, int_basic_size3) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  std::pair<int, int> libpair2(3, 3);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  libmp.insert(libpair2);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  ft::pair<int, int> mypair2(3, 3);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  mymp.insert(mypair2);
  ASSERT_EQ(libmp.size(), mymp.size());
}

TEST(TreeTest, int_basic_size4) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  std::pair<int, int> libpair2(3, 3);
  std::pair<int, int> libpair3(3, 3);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  libmp.insert(libpair2);
  libmp.insert(libpair3);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  ft::pair<int, int> mypair2(3, 3);
  ft::pair<int, int> mypair3(3, 3);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  mymp.insert(mypair2);
  mymp.insert(mypair3);
  ASSERT_EQ(libmp.size(), mymp.size());
}

TEST(TreeTest, int_basic_size5) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  std::pair<int, int> libpair2(3, 3);
  std::pair<int, int> libpair3(3, 3);
  std::pair<int, int> libpair4(3, 4);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  libmp.insert(libpair2);
  libmp.insert(libpair3);
  libmp.insert(libpair4);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  ft::pair<int, int> mypair2(3, 3);
  ft::pair<int, int> mypair3(3, 3);
  ft::pair<int, int> mypair4(3, 4);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  mymp.insert(mypair2);
  mymp.insert(mypair3);
  mymp.insert(mypair4);
  ASSERT_EQ(libmp.size(), mymp.size());
}

// max_size
// erase
// swap
// count
// find
// equal_range
// lower_bound
// upper_bound
// key_comp
// value_comp
// compare operators