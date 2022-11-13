#include <gtest/gtest.h>

#include <memory>
#include <map>
#include "../map.hpp"

// constructor
// operator=

// get_allocator
TEST(MapTest, int_basic_get_allocator) {
  ft::map<int, int> mymp;
  mymp.get_allocator();
}

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
TEST(MapTest, int_basic_max_size) {
  std::map<int, int> libmp;
  ft::map<int, int> mymp;
  ASSERT_EQ(libmp.max_size(), mymp.max_size());
}

// insert
TEST(MapTest, int_basic_insert) {
  std::map<int, int> libmp;
  std::pair<std::map<int, int>::iterator, bool> libret =
      libmp.insert(std::make_pair(1, 1));
  ft::map<int, int> mymp;
  ft::pair<ft::map<int, int>::iterator, bool> myret =
      mymp.insert(ft::make_pair(1, 1));
  ASSERT_EQ(libmp.size(), mymp.size());
  ASSERT_EQ(libret.first->first, myret.first->first);
  ASSERT_EQ(libret.first->second, myret.first->second);
  ASSERT_EQ(libret.second, myret.second);
}

TEST(MapTest, int_basic_insert1) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(2, 2));
  std::pair<std::map<int, int>::iterator, bool> libret =
      libmp.insert(std::make_pair(1, 1));
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(2, 2));
  ft::pair<ft::map<int, int>::iterator, bool> myret =
      mymp.insert(ft::make_pair(1, 1));
  ASSERT_EQ(libmp.size(), mymp.size());
  ASSERT_EQ(libret.first->first, myret.first->first);
  ASSERT_EQ(libret.first->second, myret.first->second);
  ASSERT_EQ(libret.second, myret.second);
}

TEST(MapTest, int_basic_insert2) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(-1, -1));
  libmp.insert(std::make_pair(2, 2));
  std::pair<std::map<int, int>::iterator, bool> libret =
      libmp.insert(std::make_pair(1, 1));
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(-1, -1));
  mymp.insert(ft::make_pair(2, 2));
  ft::pair<ft::map<int, int>::iterator, bool> myret =
      mymp.insert(ft::make_pair(1, 1));
  ASSERT_EQ(libmp.size(), mymp.size());
  ASSERT_EQ(libret.first->first, myret.first->first);
  ASSERT_EQ(libret.first->second, myret.first->second);
  ASSERT_EQ(libret.second, myret.second);
}

TEST(MapTest, int_basic_insert3) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(-1, -1));
  libmp.insert(std::make_pair(2, 2));
  libmp.insert(std::make_pair(2, 100));
  libmp.insert(std::make_pair(2, 1));
  std::pair<std::map<int, int>::iterator, bool> libret =
      libmp.insert(std::make_pair(1, 1));
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(-1, -1));
  mymp.insert(ft::make_pair(2, 2));
  mymp.insert(ft::make_pair(2, 100));
  mymp.insert(ft::make_pair(2, 1));
  ft::pair<ft::map<int, int>::iterator, bool> myret =
      mymp.insert(ft::make_pair(1, 1));
  ASSERT_EQ(libmp.size(), mymp.size());
  ASSERT_EQ(libret.first->first, myret.first->first);
  ASSERT_EQ(libret.first->second, myret.first->second);
  ASSERT_EQ(libret.second, myret.second);
}

// erase
// swap
// count
TEST(MapTest, int_basic_count) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  ASSERT_EQ(libmp.count(1), mymp.count(1));
}

TEST(MapTest, int_basic_count1) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  ASSERT_EQ(libmp.count(2), mymp.count(2));
}

TEST(MapTest, int_basic_count2) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(2, 2));
  libmp.insert(std::make_pair(3, 3));
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(2, 2));
  mymp.insert(ft::make_pair(3, 3));
  ASSERT_EQ(libmp.count(2), mymp.count(2));
}

// find
TEST(MapTest, int_basic_find) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  std::map<int, int>::iterator libitr = libmp.find(1);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  ft::map<int, int>::iterator myitr = mymp.find(1);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_find1) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(2, 2));
  std::map<int, int>::iterator libitr = libmp.find(1);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(2, 2));
  ft::map<int, int>::iterator myitr = mymp.find(1);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_find2) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(2, 2));
  libmp.insert(std::make_pair(-1, -1));
  std::map<int, int>::iterator libitr = libmp.find(1);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(2, 2));
  mymp.insert(ft::make_pair(-1, -1));
  ft::map<int, int>::iterator myitr = mymp.find(1);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_find3) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(2, 2));
  libmp.insert(std::make_pair(-1, -1));
  std::map<int, int>::iterator libitr = libmp.find(-1);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(2, 2));
  mymp.insert(ft::make_pair(-1, -1));
  ft::map<int, int>::iterator myitr = mymp.find(-1);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_find4) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(2, 2));
  libmp.insert(std::make_pair(-1, -1));
  libmp.insert(std::make_pair(-1, -1));
  libmp.insert(std::make_pair(-1, 42));
  std::map<int, int>::iterator libitr = libmp.find(-1);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(2, 2));
  mymp.insert(ft::make_pair(-1, -1));
  mymp.insert(ft::make_pair(-1, -1));
  mymp.insert(ft::make_pair(-1, 42));
  ft::map<int, int>::iterator myitr = mymp.find(-1);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

// insert 3
// void insert(InputIt first, InputIt last)
TEST(MapTest, int_basic_insert3_1) {
  std::map<int, int> libdata;
  libdata.insert(std::make_pair(1, 1));
  libdata.insert(std::make_pair(2, 2));
  libdata.insert(std::make_pair(3, 3));

  ft::map<int, int> mydata;
  mydata.insert(ft::make_pair(1, 1));
  mydata.insert(ft::make_pair(2, 2));
  mydata.insert(ft::make_pair(3, 3));

  std::map<int, int> libmp;
  libmp.insert(libdata.begin(), libdata.end());
  ft::map<int, int> mymp;
  mymp.insert(mydata.begin(), mydata.end());

  ASSERT_EQ(libmp.size(), mymp.size());
  std::map<int, int>::iterator libitr = libmp.begin();
  ft::map<int, int>::iterator myitr = mymp.begin();

  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
  ++libitr;
  ++myitr;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
  ++libitr;
  ++myitr;
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
  ++libitr;
  ++myitr;
}

// equal_range
TEST(MapTest, int_basic_equal_range) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator> libp =
      libmp.equal_range(1);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> myp =
      mymp.equal_range(1);
  ASSERT_EQ(libp.first->first, myp.first->first);
  ASSERT_EQ(libp.first->second, myp.first->second);
  ASSERT_EQ(libp.second == libmp.end(), myp.second == mymp.end());
}

TEST(MapTest, int_basic_equal_range1) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(2, 2));
  libmp.insert(std::make_pair(3, 3));
  std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator> libp =
      libmp.equal_range(1);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(2, 2));
  mymp.insert(ft::make_pair(3, 3));
  ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> myp =
      mymp.equal_range(1);
  ASSERT_EQ(libp.first->first, myp.first->first);
  ASSERT_EQ(libp.first->second, myp.first->second);
  ASSERT_EQ(libp.second->first, myp.second->first);
  ASSERT_EQ(libp.second->second, myp.second->second);
}

TEST(MapTest, int_basic_equal_range2) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(2, 2));
  libmp.insert(std::make_pair(3, 3));
  libmp.insert(std::make_pair(100, 3));
  libmp.insert(std::make_pair(10, 3));
  libmp.insert(std::make_pair(11, 3));
  libmp.insert(std::make_pair(13, 3));
  libmp.insert(std::make_pair(-42, 3));
  libmp.insert(std::make_pair(-10, 3));
  libmp.insert(std::make_pair(-11, 3));
  libmp.insert(std::make_pair(-13, 3));
  std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator> libp =
      libmp.equal_range(10);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(2, 2));
  mymp.insert(ft::make_pair(3, 3));
  mymp.insert(ft::make_pair(100, 3));
  mymp.insert(ft::make_pair(10, 3));
  mymp.insert(ft::make_pair(11, 3));
  mymp.insert(ft::make_pair(13, 3));
  mymp.insert(ft::make_pair(-42, 3));
  mymp.insert(ft::make_pair(-11, 3));
  mymp.insert(ft::make_pair(-13, 3));
  ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> myp =
      mymp.equal_range(10);
  ASSERT_EQ(libp.first->first, myp.first->first);
  ASSERT_EQ(libp.first->second, myp.first->second);
  ASSERT_EQ(libp.second->first, myp.second->first);
  ASSERT_EQ(libp.second->second, myp.second->second);
}

// lower_bound
TEST(MapTest, int_basic_lower_bound) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  std::map<int, int>::iterator libitr = libmp.lower_bound(1);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  ft::map<int, int>::iterator myitr = mymp.lower_bound(1);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_lower_bound1) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  std::map<int, int>::iterator libitr = libmp.lower_bound(2);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  ft::map<int, int>::iterator myitr = mymp.lower_bound(2);
  ASSERT_EQ(libitr == libmp.end(), myitr == mymp.end());
}

TEST(MapTest, int_basic_lower_bound2) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(3, 1));
  std::map<int, int>::iterator libitr = libmp.lower_bound(2);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(3, 1));
  ft::map<int, int>::iterator myitr = mymp.lower_bound(2);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_lower_bound3) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(3, 1));
  libmp.insert(std::make_pair(5, 1));
  libmp.insert(std::make_pair(7, 1));
  libmp.insert(std::make_pair(9, 1));
  libmp.insert(std::make_pair(-3, 1));
  libmp.insert(std::make_pair(-5, 1));
  libmp.insert(std::make_pair(-7, 1));
  libmp.insert(std::make_pair(-9, 1));
  std::map<int, int>::iterator libitr = libmp.lower_bound(4);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(3, 1));
  mymp.insert(ft::make_pair(5, 1));
  mymp.insert(ft::make_pair(42, 1));
  mymp.insert(ft::make_pair(7, 1));
  mymp.insert(ft::make_pair(9, 1));
  mymp.insert(ft::make_pair(-3, 1));
  mymp.insert(ft::make_pair(-5, 1));
  mymp.insert(ft::make_pair(-42, 1));
  mymp.insert(ft::make_pair(-7, 1));
  mymp.insert(ft::make_pair(-9, 1));
  ft::map<int, int>::iterator myitr = mymp.lower_bound(4);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

// upper_bound
TEST(MapTest, int_basic_upper_bound) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  std::map<int, int>::iterator libitr = libmp.upper_bound(1);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  ft::map<int, int>::iterator myitr = mymp.upper_bound(1);
  ASSERT_EQ(libitr == libmp.end(), myitr == mymp.end());
}

TEST(MapTest, int_basic_upper_bound1) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(2, 2));
  std::map<int, int>::iterator libitr = libmp.upper_bound(1);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(2, 2));
  ft::map<int, int>::iterator myitr = mymp.upper_bound(1);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_upper_bound2) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(2, 2));
  libmp.insert(std::make_pair(4, 2));
  std::map<int, int>::iterator libitr = libmp.upper_bound(3);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(2, 2));
  mymp.insert(ft::make_pair(4, 2));
  ft::map<int, int>::iterator myitr = mymp.upper_bound(3);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

TEST(MapTest, int_basic_upper_bound3) {
  std::map<int, int> libmp;
  libmp.insert(std::make_pair(1, 1));
  libmp.insert(std::make_pair(2, 2));
  libmp.insert(std::make_pair(4, 2));
  libmp.insert(std::make_pair(-10, 2));
  libmp.insert(std::make_pair(-1, 2));
  libmp.insert(std::make_pair(42, 2));
  std::map<int, int>::iterator libitr = libmp.upper_bound(-4);
  ft::map<int, int> mymp;
  mymp.insert(ft::make_pair(1, 1));
  mymp.insert(ft::make_pair(2, 2));
  mymp.insert(ft::make_pair(4, 2));
  mymp.insert(ft::make_pair(-10, 2));
  mymp.insert(ft::make_pair(-1, 2));
  mymp.insert(ft::make_pair(42, 2));
  ft::map<int, int>::iterator myitr = mymp.upper_bound(-4);
  ASSERT_EQ(libitr->first, myitr->first);
  ASSERT_EQ(libitr->second, myitr->second);
}

// key_comp
// value_comp

// compare operators
TEST(MapTest, int_basic_compare_operator) {
  std::map<int, int> libmp1;
  std::map<int, int> libmp2;
  libmp1.insert(std::make_pair(1, 1));
  libmp2.insert(std::make_pair(1, 1));

  ft::map<int, int> mymp1;
  ft::map<int, int> mymp2;
  mymp1.insert(ft::make_pair(1, 1));
  mymp2.insert(ft::make_pair(1, 1));

  ASSERT_EQ(libmp1 == libmp2, mymp1 == mymp2);
  ASSERT_EQ(libmp1 != libmp2, mymp1 != mymp2);
  ASSERT_EQ(libmp1 < libmp2, mymp1 < mymp2);
  ASSERT_EQ(libmp1 > libmp2, mymp1 > mymp2);
  ASSERT_EQ(libmp1 >= libmp2, mymp1 >= mymp2);
  ASSERT_EQ(libmp1 <= libmp2, mymp1 <= mymp2);
}

TEST(MapTest, int_basic_compare_operator1) {
  std::map<int, int> libmp1;
  std::map<int, int> libmp2;
  libmp1.insert(std::make_pair(1, 1));
  libmp2.insert(std::make_pair(2, 2));

  ft::map<int, int> mymp1;
  ft::map<int, int> mymp2;
  mymp1.insert(ft::make_pair(1, 1));
  mymp2.insert(ft::make_pair(2, 2));

  ASSERT_EQ(libmp1 == libmp2, mymp1 == mymp2);
  ASSERT_EQ(libmp1 != libmp2, mymp1 != mymp2);
  ASSERT_EQ(libmp1 < libmp2, mymp1 < mymp2);
  ASSERT_EQ(libmp1 > libmp2, mymp1 > mymp2);
  ASSERT_EQ(libmp1 >= libmp2, mymp1 >= mymp2);
  ASSERT_EQ(libmp1 <= libmp2, mymp1 <= mymp2);
}

TEST(MapTest, int_basic_compare_operator2) {
  std::map<int, int> libmp1;
  std::map<int, int> libmp2;
  libmp1.insert(std::make_pair(1, 1));
  libmp2.insert(std::make_pair(2, 1));
  libmp2.insert(std::make_pair(-42, 1));

  ft::map<int, int> mymp1;
  ft::map<int, int> mymp2;
  mymp1.insert(ft::make_pair(1, 1));
  mymp2.insert(ft::make_pair(2, 2));
  mymp2.insert(ft::make_pair(-42, 1));

  ASSERT_EQ(libmp1 == libmp2, mymp1 == mymp2);
  ASSERT_EQ(libmp1 != libmp2, mymp1 != mymp2);
  ASSERT_EQ(libmp1 < libmp2, mymp1 < mymp2);
  ASSERT_EQ(libmp1 > libmp2, mymp1 > mymp2);
  ASSERT_EQ(libmp1 >= libmp2, mymp1 >= mymp2);
  ASSERT_EQ(libmp1 <= libmp2, mymp1 <= mymp2);
}
