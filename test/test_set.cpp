#include <gtest/gtest.h>
#include <glog/logging.h>

#include <memory>
#include <set>
#include "../set.hpp"

//  (constructor)
//  (destructor)
//  operator=
//  get_allocator

//  begin
TEST(SetTest, int_basic_begin_1) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  std::set<int>::iterator libitr = libst.begin();
  ft::set<int>::iterator myitr = myst.begin();

  ASSERT_EQ(libst.size(), myst.size());

  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(libitr, libst.end());
  ASSERT_EQ(myitr, myst.end());
}

TEST(SetTest, int_basic_begin_2) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(3);
  libst.insert(4);
  libst.insert(5);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(3);
  myst.insert(4);
  myst.insert(5);

  std::set<int>::iterator libitr = libst.begin();
  ft::set<int>::iterator myitr = myst.begin();

  ASSERT_EQ(libst.size(), myst.size());

  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(libitr, libst.end());
  ASSERT_EQ(myitr, myst.end());
}

TEST(SetTest, int_basic_begin_3) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(2);
  libst.insert(4);
  libst.insert(5);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(2);
  myst.insert(4);
  myst.insert(5);

  std::set<int>::iterator libitr = libst.begin();
  ft::set<int>::iterator myitr = myst.begin();

  ASSERT_EQ(libst.size(), myst.size());

  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(libitr, libst.end());
  ASSERT_EQ(myitr, myst.end());
}

//  end
TEST(SetTest, int_basic_end_1) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  std::set<int>::iterator libitr = libst.end();
  ft::set<int>::iterator myitr = myst.end();

  ASSERT_EQ(libst.size(), myst.size());

  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);

  ASSERT_EQ(libitr, libst.begin());
  ASSERT_EQ(myitr, myst.begin());
}

TEST(SetTest, int_basic_end_2) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(3);
  libst.insert(4);
  libst.insert(5);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(3);
  myst.insert(4);
  myst.insert(5);

  std::set<int>::iterator libitr = libst.end();
  ft::set<int>::iterator myitr = myst.end();

  ASSERT_EQ(libst.size(), myst.size());

  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);

  ASSERT_EQ(libitr, libst.begin());
  ASSERT_EQ(myitr, myst.begin());
}

TEST(SetTest, int_basic_end_3) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(2);
  libst.insert(4);
  libst.insert(5);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(2);
  myst.insert(4);
  myst.insert(5);

  std::set<int>::iterator libitr = libst.end();
  ft::set<int>::iterator myitr = myst.end();

  ASSERT_EQ(libst.size(), myst.size());

  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);

  ASSERT_EQ(libitr, libst.begin());
  ASSERT_EQ(myitr, myst.begin());
}

//  rbegin
TEST(SetTest, int_basic_rbegin_1) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  std::set<int>::reverse_iterator libitr = libst.rbegin();
  ft::set<int>::reverse_iterator myitr = myst.rbegin();

  ASSERT_EQ(libst.size(), myst.size());

  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;

  ASSERT_EQ(libitr, libst.rend());
  ASSERT_EQ(myitr, myst.rend());
}

TEST(SetTest, int_basic_rbegin_2) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(3);
  libst.insert(4);
  libst.insert(5);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(3);
  myst.insert(4);
  myst.insert(5);

  std::set<int>::reverse_iterator libitr = libst.rbegin();
  ft::set<int>::reverse_iterator myitr = myst.rbegin();

  ASSERT_EQ(libst.size(), myst.size());

  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;

  ASSERT_EQ(libitr, libst.rend());
  ASSERT_EQ(myitr, myst.rend());
}

TEST(SetTest, int_basic_rbegin_3) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(2);
  libst.insert(4);
  libst.insert(5);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(2);
  myst.insert(4);
  myst.insert(5);

  std::set<int>::reverse_iterator libitr = libst.rbegin();
  ft::set<int>::reverse_iterator myitr = myst.rbegin();

  ASSERT_EQ(libst.size(), myst.size());

  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;
  ASSERT_EQ(*libitr, *myitr);
  libitr++;
  myitr++;

  ASSERT_EQ(libitr, libst.rend());
  ASSERT_EQ(myitr, myst.rend());
}

//  rend
TEST(SetTest, int_basic_rend_1) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  std::set<int>::reverse_iterator libitr = libst.rend();
  ft::set<int>::reverse_iterator myitr = myst.rend();

  ASSERT_EQ(libst.size(), myst.size());

  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);

  ASSERT_EQ(libitr, libst.rbegin());
  ASSERT_EQ(myitr, myst.rbegin());
}

TEST(SetTest, int_basic_rend_2) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(3);
  libst.insert(4);
  libst.insert(5);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(3);
  myst.insert(4);
  myst.insert(5);

  std::set<int>::reverse_iterator libitr = libst.rend();
  ft::set<int>::reverse_iterator myitr = myst.rend();

  ASSERT_EQ(libst.size(), myst.size());

  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);

  ASSERT_EQ(libitr, libst.rbegin());
  ASSERT_EQ(myitr, myst.rbegin());
}

TEST(SetTest, int_basic_rend_3) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(2);
  libst.insert(4);
  libst.insert(5);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(2);
  myst.insert(4);
  myst.insert(5);

  std::set<int>::reverse_iterator libitr = libst.rend();
  ft::set<int>::reverse_iterator myitr = myst.rend();

  ASSERT_EQ(libst.size(), myst.size());

  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);
  libitr--;
  myitr--;
  ASSERT_EQ(*libitr, *myitr);

  ASSERT_EQ(libitr, libst.rbegin());
  ASSERT_EQ(myitr, myst.rbegin());
}

// empty
TEST(SetTest, int_basic_empty_1) {
  std::set<int> libst;
  ft::set<int> myst;
  ASSERT_EQ(libst.empty(), myst.empty());
}

TEST(SetTest, int_basic_empty_2) {
  std::set<int> libst;
  ft::set<int> myst;

  libst.insert(1);
  myst.insert(1);

  ASSERT_EQ(libst.empty(), myst.empty());
}

// size
TEST(SetTest, int_basic_size_1) {
  std::set<int> libst;
  ft::set<int> myst;
  ASSERT_EQ(libst.size(), myst.size());
}

TEST(SetTest, int_basic_size_2) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);
  ASSERT_EQ(libst.size(), myst.size());
}

TEST(SetTest, int_basic_size_3) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(1);
  ASSERT_EQ(libst.size(), myst.size());
}

//  max_size
TEST(SetTest, int_basic_max_size) {
  std::set<int> libst;
  ft::set<int> myst;
  ASSERT_EQ(libst.max_size(), myst.max_size());
}

// //  clear
// TEST(SetTest, int_basic_clear) {
//   std::set<int> libst;
//   ft::set<int> myst;

//   libst.insert(1);
//   libst.insert(2);
//   libst.insert(3);
//   libst.insert(4);

//   myst.insert(1);
//   myst.insert(2);
//   myst.insert(3);
//   myst.insert(4);

//   libst.clear();
//   myst.clear();

//   ASSERT_EQ(libst.size(), myst.size());
// }

//  insert
TEST(SetTest, int_basic_insert) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);
  ASSERT_EQ(libst.size(), myst.size());
}

TEST(SetTest, int_basic_insert1) {
  std::set<int> libst;
  std::pair<std::set<int>::iterator, bool> libp = libst.insert(1);
  ft::set<int> myst;
  ft::pair<ft::set<int>::iterator, bool> myp = myst.insert(1);
  ASSERT_EQ(*(libp.first), *(myp.first));
  ASSERT_EQ(libp.second, myp.second);
}

TEST(SetTest, int_basic_insert2) {
  std::set<int> libst;
  libst.insert(2);
  std::pair<std::set<int>::iterator, bool> libp = libst.insert(1);
  ft::set<int> myst;
  myst.insert(2);
  ft::pair<ft::set<int>::iterator, bool> myp = myst.insert(1);
  ASSERT_EQ(*(libp.first), *(myp.first));
  ASSERT_EQ(libp.second, myp.second);
}

TEST(SetTest, int_basic_insert3) {
  std::set<int> libst;
  libst.insert(2);
  libst.insert(42);
  libst.insert(-100);
  std::pair<std::set<int>::iterator, bool> libp = libst.insert(1);
  ft::set<int> myst;
  myst.insert(2);
  myst.insert(42);
  myst.insert(-100);
  ft::pair<ft::set<int>::iterator, bool> myp = myst.insert(1);
  ASSERT_EQ(*(libp.first), *(myp.first));
  ASSERT_EQ(libp.second, myp.second);
}

// void insert(InputIt first, InputIt last)
TEST(SetTest, int_basic_insert3_1) {
  std::set<int> libdata;
  libdata.insert(1);

  ft::set<int> mydata;
  mydata.insert(1);

  std::set<int> libst;
  libst.insert(libdata.begin(), libdata.end());
  ft::set<int> myst;
  myst.insert(mydata.begin(), mydata.end());

  std::set<int>::iterator libitr = libst.begin();
  ft::set<int>::iterator myitr = myst.begin();

  ASSERT_EQ(*libitr, *myitr);
}

TEST(SetTest, int_basic_insert3_2) {
  std::set<int> libdata;
  libdata.insert(1);
  libdata.insert(2);
  libdata.insert(3);

  ft::set<int> mydata;
  mydata.insert(1);
  mydata.insert(2);
  mydata.insert(3);

  std::set<int> libst;
  libst.insert(libdata.begin(), libdata.end());
  ft::set<int> myst;
  myst.insert(mydata.begin(), mydata.end());

  std::set<int>::iterator libitr = libst.begin();
  ft::set<int>::iterator myitr = myst.begin();

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
}

//  erase
TEST(SetTest, int_basic_erase_1_1) {
  std::set<int> libdata;
  libdata.insert(1);
  libdata.insert(2);
  libdata.insert(3);
  libdata.insert(4);

  ft::set<int> mydata;
  mydata.insert(1);
  mydata.insert(2);
  mydata.insert(3);
  mydata.insert(4);

  ASSERT_EQ(libdata.erase(1), mydata.erase(1));

  std::set<int>::iterator libitr = libdata.begin();
  ft::set<int>::iterator myitr = mydata.begin();

  ASSERT_EQ(libdata.size(), mydata.size());

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
}

TEST(SetTest, int_basic_erase_1_2) {
  LOG(ERROR) << "@@@ int_basic_erase_1_2/ start";
  std::set<int> libdata;
  libdata.insert(1);
  libdata.insert(2);
  libdata.insert(3);
  libdata.insert(4);

  ft::set<int> mydata;
  mydata.insert(1);
  mydata.insert(2);
  mydata.insert(3);
  mydata.insert(4);

  //            2b
  //     +------+------+
  //    1b             3b
  //               +---+---+
  //                       4r

  ASSERT_EQ(libdata.erase(1), mydata.erase(1));
  ASSERT_EQ(libdata.erase(2), mydata.erase(2));

  std::set<int>::iterator libitr = libdata.begin();
  ft::set<int>::iterator myitr = mydata.begin();

  ASSERT_EQ(libdata.size(), mydata.size());

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  LOG(ERROR) << "@@@ int_basic_erase_1_2/ end";
}

TEST(SetTest, int_basic_erase_2_1) {
  std::set<int> libdata;
  libdata.insert(1);
  libdata.insert(2);
  libdata.insert(3);
  libdata.insert(4);

  ft::set<int> mydata;
  mydata.insert(1);
  mydata.insert(2);
  mydata.insert(3);
  mydata.insert(4);

  ASSERT_EQ(libdata.erase(1), mydata.erase(1));
  ASSERT_EQ(libdata.erase(2), mydata.erase(2));
  ASSERT_EQ(libdata.erase(3), mydata.erase(3));

  std::set<int>::iterator libitr = libdata.begin();
  ft::set<int>::iterator myitr = mydata.begin();

  ASSERT_EQ(libdata.size(), mydata.size());

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(libitr, libdata.end());
  ASSERT_EQ(myitr, mydata.end());
}

TEST(SetTest, int_basic_erase_2_2) {
  std::set<int> libdata;
  libdata.insert(1);
  libdata.insert(2);
  libdata.insert(3);
  libdata.insert(4);

  ft::set<int> mydata;
  mydata.insert(1);
  mydata.insert(2);
  mydata.insert(3);
  mydata.insert(4);

  ASSERT_EQ(libdata.erase(1), mydata.erase(1));
  ASSERT_EQ(libdata.erase(2), mydata.erase(2));
  ASSERT_EQ(libdata.erase(3), mydata.erase(3));
  ASSERT_EQ(libdata.erase(4), mydata.erase(4));

  ASSERT_EQ(libdata.size(), mydata.size());
}

TEST(SetTest, int_basic_erase_2_3) {
  std::set<int> libdata;
  libdata.insert(10);
  libdata.insert(1);
  libdata.insert(3);
  libdata.insert(2);
  libdata.insert(5);
  libdata.insert(6);

  ft::set<int> mydata;
  mydata.insert(10);
  mydata.insert(1);
  mydata.insert(3);
  mydata.insert(2);
  mydata.insert(5);
  mydata.insert(6);

  ASSERT_EQ(libdata.erase(1), mydata.erase(1));

  std::set<int>::iterator libitr = libdata.begin();
  ft::set<int>::iterator myitr = mydata.begin();

  ASSERT_EQ(libdata.size(), mydata.size());

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(libitr, libdata.end());
  ASSERT_EQ(myitr, mydata.end());

  ASSERT_EQ(libdata.erase(5), mydata.erase(5));
  ASSERT_EQ(libdata.size(), mydata.size());
  libitr = libdata.begin();
  myitr = mydata.begin();

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(libitr, libdata.end());
  ASSERT_EQ(myitr, mydata.end());

  ASSERT_EQ(libdata.erase(2), mydata.erase(2));
  ASSERT_EQ(libdata.size(), mydata.size());
  libitr = libdata.begin();
  myitr = mydata.begin();

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(libitr, libdata.end());
  ASSERT_EQ(myitr, mydata.end());

  ASSERT_EQ(libdata.erase(3), mydata.erase(3));
  ASSERT_EQ(libdata.size(), mydata.size());
  libitr = libdata.begin();
  myitr = mydata.begin();

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(libitr, libdata.end());
  ASSERT_EQ(myitr, mydata.end());

  ASSERT_EQ(libdata.erase(10), mydata.erase(10));
  ASSERT_EQ(libdata.size(), mydata.size());
  libitr = libdata.begin();
  myitr = mydata.begin();

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(libitr, libdata.end());
  ASSERT_EQ(myitr, mydata.end());

  ASSERT_EQ(libdata.erase(6), mydata.erase(6));
  ASSERT_EQ(libdata.size(), mydata.size());
}

//  swap
//  count
TEST(SetTest, int_basic_count) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  ASSERT_EQ(libst.count(1), myst.count(1));
}

TEST(SetTest, int_basic_count1) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);

  ASSERT_EQ(libst.count(1), myst.count(1));
}

TEST(SetTest, int_basic_count2) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(2);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(2);

  ASSERT_EQ(libst.count(2), myst.count(2));
}

TEST(SetTest, int_basic_count3) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(2);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(2);

  ASSERT_EQ(libst.count(42), myst.count(42));
}

//  find
TEST(SetTest, int_basic_find) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  ASSERT_EQ(*(libst.find(1)), *(myst.find(1)));
}

TEST(SetTest, int_basic_find1) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  ASSERT_EQ(libst.find(42) == libst.end(), myst.find(42) == myst.end());
}

TEST(SetTest, int_basic_find2) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(42);
  libst.insert(3);
  libst.insert(-100);
  libst.insert(-10);
  libst.insert(4);
  libst.insert(5);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(42);
  myst.insert(3);
  myst.insert(-100);
  myst.insert(-10);
  myst.insert(4);
  myst.insert(5);

  std::set<int>::iterator libitr = libst.find(42);
  ft::set<int>::iterator myitr = myst.find(42);

  ASSERT_EQ(*libitr, *myitr);
}

//  equal_range
TEST(SetTest, int_basic_equal_range) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  std::pair<std::set<int>::iterator, std::set<int>::iterator> libp =
      libst.equal_range(1);
  ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> myp =
      myst.equal_range(1);

  ASSERT_EQ(*(libp.first), *(myp.first));
  ASSERT_EQ(libp.second == libst.end(), myp.second == myst.end());
}

TEST(SetTest, int_basic_equal_range1) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(3);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(3);

  std::pair<std::set<int>::iterator, std::set<int>::iterator> libp =
      libst.equal_range(1);
  ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> myp =
      myst.equal_range(1);

  ASSERT_EQ(*(libp.first), *(myp.first));
  ASSERT_EQ(*(libp.second), *(myp.second));
}

//  lower_bound
TEST(SetTest, int_basic_lower_bound) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  std::set<int>::iterator libitr = libst.lower_bound(1);
  ft::set<int>::iterator myitr = myst.lower_bound(1);

  ASSERT_EQ(*libitr, *myitr);
}

TEST(SetTest, int_basic_lower_bound1) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  std::set<int>::iterator libitr = libst.lower_bound(2);
  ft::set<int>::iterator myitr = myst.lower_bound(2);

  ASSERT_EQ(libitr == libst.end(), myitr == myst.end());
}

TEST(SetTest, int_basic_lower_bound2) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(3);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(3);

  std::set<int>::iterator libitr = libst.lower_bound(2);
  ft::set<int>::iterator myitr = myst.lower_bound(2);

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
}

//  upper_bound
TEST(SetTest, int_basic_upper_bound) {
  std::set<int> libst;
  libst.insert(1);
  ft::set<int> myst;
  myst.insert(1);

  std::set<int>::iterator libitr = libst.lower_bound(1);
  ft::set<int>::iterator myitr = myst.lower_bound(1);

  ASSERT_EQ(libitr == libst.end(), myitr == myst.end());
}

TEST(SetTest, int_basic_upper_bound1) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);

  std::set<int>::iterator libitr = libst.lower_bound(1);
  ft::set<int>::iterator myitr = myst.lower_bound(1);

  ASSERT_EQ(*libitr, *myitr);
}

TEST(SetTest, int_basic_upper_bound2) {
  std::set<int> libst;
  libst.insert(1);
  libst.insert(2);
  libst.insert(3);
  libst.insert(42);
  libst.insert(10);
  ft::set<int> myst;
  myst.insert(1);
  myst.insert(2);
  myst.insert(3);
  myst.insert(42);
  myst.insert(10);

  std::set<int>::iterator libitr = libst.lower_bound(1);
  ft::set<int>::iterator myitr = myst.lower_bound(1);

  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
  ASSERT_EQ(*libitr, *myitr);
  ++libitr;
  ++myitr;
}

//  key_comp
//  value_comp