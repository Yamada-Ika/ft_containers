#include <gtest/gtest.h>

#include <memory>
#include <map>
#include "../map.hpp"

// constructor
// operator=
// get_allocator

// at
TEST(MapTest, int_basic_at) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  ASSERT_EQ(libmp.at(1), mymp.at(1));
}

TEST(MapTest, int_basic_at1) {
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

TEST(MapTest, int_basic_at2) {
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

TEST(MapTest, int_basic_at3) {
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
TEST(MapTest, int_basic_bracket_operator) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  libmp.insert(libpair);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  mymp.insert(mypair);
  ASSERT_EQ(libmp[1], mymp[1]);
}

TEST(MapTest, int_basic_bracket_operato1) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  libmp.insert(libpair);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  mymp.insert(mypair);
  ASSERT_EQ(libmp.size(), mymp.size());
  ASSERT_EQ(libmp[1], mymp[1]);
  ASSERT_EQ(libmp[2], mymp[2]);
}

TEST(MapTest, int_basic_bracket_operato2) {
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
  ASSERT_EQ(libmp.size(), mymp.size());
  ASSERT_EQ(libmp[1], mymp[1]);
  ASSERT_EQ(libmp[2], mymp[2]);
  ASSERT_EQ(libmp[3], mymp[3]);
}

TEST(MapTest, int_basic_bracket_operato3) {
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
  ASSERT_EQ(libmp.size(), mymp.size());
  ASSERT_EQ(libmp[1], mymp[1]);
  ASSERT_EQ(libmp[2], mymp[2]);
}

// begin
TEST(MapTest, int_basic_begin) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  libmp.insert(libpair);
  std::map<int, int>::iterator libitr = libmp.begin();
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  mymp.insert(mypair);
  ft::map<int, int>::iterator myitr = mymp.begin();
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_begin1) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  std::map<int, int>::iterator libitr = libmp.begin();
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  ft::map<int, int>::iterator myitr = mymp.begin();
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
  ++libitr;
  ++myitr;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_begin2) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  std::map<int, int>::iterator libitr = libmp.begin();
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  ft::map<int, int>::iterator myitr = mymp.begin();
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
  libitr++;
  myitr++;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

// end
TEST(MapTest, int_basic_end) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  libmp.insert(libpair);
  std::map<int, int>::iterator libitr = libmp.end();
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  mymp.insert(mypair);
  ft::map<int, int>::iterator myitr = mymp.end();
  --libitr;
  --myitr;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_end1) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  std::map<int, int>::iterator libitr = libmp.end();
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  ft::map<int, int>::iterator myitr = mymp.end();
  --libitr;
  --myitr;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
  --libitr;
  --myitr;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

// rbegin
TEST(MapTest, int_basic_rbegin) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  libmp.insert(libpair);
  std::map<int, int>::reverse_iterator libitr = libmp.rbegin();
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  mymp.insert(mypair);
  ft::map<int, int>::reverse_iterator myitr = mymp.rbegin();
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_rbegin1) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  std::map<int, int>::reverse_iterator libitr = libmp.rbegin();
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  ft::map<int, int>::reverse_iterator myitr = mymp.rbegin();
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
  ++libitr;
  ++myitr;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

// rend
TEST(MapTest, int_basic_rend) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  libmp.insert(libpair);
  std::map<int, int>::reverse_iterator libitr = libmp.rend();
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  mymp.insert(mypair);
  ft::map<int, int>::reverse_iterator myitr = mymp.rend();
  --libitr;
  --myitr;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_rend1) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  std::pair<int, int> libpair1(2, 2);
  libmp.insert(libpair);
  libmp.insert(libpair1);
  std::map<int, int>::reverse_iterator libitr = libmp.rend();
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  ft::pair<int, int> mypair1(2, 2);
  mymp.insert(mypair);
  mymp.insert(mypair1);
  ft::map<int, int>::reverse_iterator myitr = mymp.rend();
  --libitr;
  --myitr;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
  --libitr;
  --myitr;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

// empty
TEST(MapTest, int_basic_empty) {
  std::map<int, int> libmp;
  ft::map<int, int> mymp;
  ASSERT_EQ(libmp.empty(), mymp.empty());
}

// size && insert
TEST(MapTest, int_basic_size) {
  std::map<int, int> libmp;
  ft::map<int, int> mymp;
  ASSERT_EQ(libmp.size(), mymp.size());
}

TEST(MapTest, int_basic_size1) {
  std::map<int, int> libmp;
  std::pair<int, int> libpair(1, 1);
  libmp.insert(libpair);
  ft::map<int, int> mymp;
  ft::pair<int, int> mypair(1, 1);
  mymp.insert(mypair);
  ASSERT_EQ(libmp.size(), mymp.size());
}

TEST(MapTest, int_basic_size2) {
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

TEST(MapTest, int_basic_size3) {
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

TEST(MapTest, int_basic_size4) {
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

TEST(MapTest, int_basic_size5) {
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