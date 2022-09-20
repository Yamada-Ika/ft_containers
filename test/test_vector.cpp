#include <gtest/gtest.h>

#include <vector>
#include "../vector.hpp"

// TODO
// constructor
// destructor
// operator=
// assign
// get_allocator

// at()
TEST(VectorTest, int_basic_at) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  myvec.push_back(1);
  myvec.push_back(2);
  myvec.push_back(3);
  libvec.push_back(1);
  libvec.push_back(2);
  libvec.push_back(3);

  ASSERT_EQ(myvec.at(0), libvec.at(0));
  ASSERT_EQ(myvec.at(1), libvec.at(1));
  ASSERT_EQ(myvec.at(2), libvec.at(2));
}

// operator[]
TEST(VectorTest, int_basic_bracket_operator) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  myvec.push_back(1);
  myvec.push_back(2);
  myvec.push_back(3);
  libvec.push_back(1);
  libvec.push_back(2);
  libvec.push_back(3);

  ASSERT_EQ(myvec[0], libvec[0]);
  ASSERT_EQ(myvec[1], libvec[1]);
  ASSERT_EQ(myvec[2], libvec[2]);
}

// front()
TEST(VectorTest, int_basic_front) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  myvec.push_back(1);
  libvec.push_back(1);

  ASSERT_EQ(myvec.front(), libvec.front());
}

// back()
TEST(VectorTest, int_basic_back) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  myvec.push_back(1);
  libvec.push_back(1);

  ASSERT_EQ(myvec.back(), libvec.back());
}

// data()
TEST(VectorTest, int_basic_data) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  myvec.push_back(1);
  myvec.push_back(2);
  myvec.push_back(3);
  libvec.push_back(1);
  libvec.push_back(2);
  libvec.push_back(3);

  int *myvec_data = myvec.data();
  int *libvec_data = libvec.data();

  ASSERT_EQ(myvec.size(), libvec.size());

  for (size_t i = 0; i < myvec.size(); ++i) {
    ASSERT_EQ(myvec_data[i], libvec_data[i]);
  }
}

// empty()
TEST(VectorTest, int_basic_empty) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  ASSERT_EQ(myvec.empty(), libvec.empty());
}

// size()
TEST(VectorTest, int_basic_size) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  myvec.push_back(1);
  myvec.push_back(2);
  myvec.push_back(3);
  libvec.push_back(1);
  libvec.push_back(2);
  libvec.push_back(3);

  ASSERT_EQ(myvec.size(), libvec.size());
}

// max_size()
TEST(VectorTest, int_basic_max_size) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  ASSERT_EQ(myvec.max_size(), libvec.max_size());
}

// TODO reserve()
// TODO capacity()

// TODO Iterators
// begin()
// end()
// rbegin()
// rend()

// TODO Modifiers
// clear()
// insert()
// erase()

// push_back()
TEST(VectorTest, int_basic_push_back) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  myvec.push_back(1);
  libvec.push_back(1);
}

// pop_back()
// resize()
// swap()

// TODO Non-member functions
// operator==
// operator!=
// operator<
// operator<=
// operator>
// operator>=
// std::swap(std::vector)
 

