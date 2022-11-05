#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include "../pair.hpp"

// constuctor
TEST(PairTest, int_basic_constructor1) {
  ft::pair<int, int> myp;
  std::pair<int, int> libp;
  ASSERT_EQ(myp.first, libp.first);
  ASSERT_EQ(myp.second, libp.second);
}

TEST(PairTest, int_basic_constructor2) {
  ft::pair<int, int> myp(1, 2);
  std::pair<int, int> libp(1, 2);
  ASSERT_EQ(myp.first, libp.first);
  ASSERT_EQ(myp.second, libp.second);
}

TEST(PairTest, int_basic_constructor3) {
  ft::pair<int, int> myp(1, 2);
  std::pair<int, int> libp(1, 2);
  ft::pair<int, int> myp2(myp);
  std::pair<int, int> libp2(libp);
  ASSERT_EQ(myp2.first, libp2.first);
  ASSERT_EQ(myp2.second, libp2.second);
}

// const
TEST(PairTest, int_basic_constructor4) {
  ft::pair<int, int> myp(1, 2);
  std::pair<int, int> libp(1, 2);
  std::pair<const int, int> libp2(libp);
  ft::pair<const int, int> myp2(myp);
  ASSERT_EQ(myp2.first, libp2.first);
  ASSERT_EQ(myp2.second, libp2.second);
}

TEST(PairTest, int_basic_constructor5) {
  std::pair<const int, int> libp(1, 2);
  std::pair<const int, int> libp2(libp);
  ft::pair<const int, int> myp(1, 2);
  ft::pair<const int, int> myp2(myp);
  ASSERT_EQ(myp2.first, libp2.first);
  ASSERT_EQ(myp2.second, libp2.second);
}

// operator=
TEST(PairTest, int_basic_assign_operator) {
  ft::pair<int, int> myp(1, 2);
  std::pair<int, int> libp(1, 2);
  ft::pair<int, int> myp2;
  myp2 = myp;
  std::pair<int, int> libp2;
  libp2 = libp;
  ASSERT_EQ(myp2.first, libp2.first);
  ASSERT_EQ(myp2.second, libp2.second);
}

// make_pair
TEST(PairTest, int_basic_make_pair) {
  ft::pair<int, int> myp = ft::make_pair(1, 2);
  std::pair<int, int> libp = std::make_pair(1, 2);
  ASSERT_EQ(myp.first, libp.first);
  ASSERT_EQ(myp.second, libp.second);
}

// compare operators
TEST(PairTest, int_basic_assign_operator1) {
  ft::pair<int, int> myp(1, 2);
  std::pair<int, int> libp(1, 2);
  ft::pair<int, int> myp2;
  myp2 = myp;
  std::pair<int, int> libp2;
  libp2 = libp;
  ASSERT_EQ(myp == myp2, libp == libp2);
  ASSERT_EQ(myp != myp2, libp != libp2);
  ASSERT_EQ(myp > myp2, libp > libp2);
  ASSERT_EQ(myp < myp2, libp < libp2);
  ASSERT_EQ(myp <= myp2, libp <= libp2);
  ASSERT_EQ(myp >= myp2, libp >= libp2);
}

TEST(PairTest, int_basic_assign_operator2) {
  ft::pair<int, int> myp(1, 2);
  std::pair<int, int> libp(1, 2);
  ft::pair<int, int> myp2(2, 1);
  std::pair<int, int> libp2(2, 1);
  ASSERT_EQ(myp == myp2, libp == libp2);
  ASSERT_EQ(myp != myp2, libp != libp2);
  ASSERT_EQ(myp < myp2, libp < libp2);
  ASSERT_EQ(myp > myp2, libp > libp2);
  ASSERT_EQ(myp <= myp2, libp <= libp2);
  ASSERT_EQ(myp >= myp2, libp >= libp2);
}

TEST(PairTest, int_basic_assign_operator3) {
  ft::pair<int, int> myp(1, 2);
  std::pair<int, int> libp(1, 2);
  ft::pair<int, int> myp2(2, 100);
  std::pair<int, int> libp2(2, 100);
  ASSERT_EQ(myp == myp2, libp == libp2);
  ASSERT_EQ(myp != myp2, libp != libp2);
  ASSERT_EQ(myp > myp2, libp > libp2);
  ASSERT_EQ(myp < myp2, libp < libp2);
  ASSERT_EQ(myp <= myp2, libp <= libp2);
  ASSERT_EQ(myp >= myp2, libp >= libp2);
}

TEST(PairTest, int_basic_assign_operator4) {
  ft::pair<int, int> myp(1, 2);
  std::pair<int, int> libp(1, 2);
  ft::pair<int, int> myp2(1, 1);
  std::pair<int, int> libp2(1, 1);
  ASSERT_EQ(myp == myp2, libp == libp2);
  ASSERT_EQ(myp != myp2, libp != libp2);
  ASSERT_EQ(myp > myp2, libp > libp2);
  ASSERT_EQ(myp < myp2, libp < libp2);
  ASSERT_EQ(myp <= myp2, libp <= libp2);
  ASSERT_EQ(myp >= myp2, libp >= libp2);
}

TEST(PairTest, int_basic_assign_operator5) {
  ft::pair<int, int> myp(1, 2);
  std::pair<int, int> libp(1, 2);
  ft::pair<int, int> myp2(1, 100);
  std::pair<int, int> libp2(1, 100);
  ASSERT_EQ(myp == myp2, libp == libp2);
  ASSERT_EQ(myp != myp2, libp != libp2);
  ASSERT_EQ(myp > myp2, libp > libp2);
  ASSERT_EQ(myp < myp2, libp < libp2);
  ASSERT_EQ(myp <= myp2, libp <= libp2);
  ASSERT_EQ(myp >= myp2, libp >= libp2);
}
