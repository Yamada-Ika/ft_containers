#include <gtest/gtest.h>

#include <deque>
#include "../deque.hpp"

// template <typename T>
// static void prepareTestData(std::deque<T>& libdeque, ft::deque<T>& mydeque,
//                             std::deque<T>& test_data) {
//   for (std::deqeu<T>::const_iterator itr = test_data.begin(); itr != test_data;
//        ++itr) {
//     libdeque.push_back(*itr);
//     mydeque.push_back(*itr);
//   }
// }

// constructor
TEST(DequeTest, int_basic_constructor_without_argments) {
  ft::deque<int> mydec;
}

// operator=
// assign
// get_allocator
// at
// operator[]
// front
// back
// begin
// end
// rbegin
// empty
// size
// max_size
// clear
// insert
// erase
// push_back
TEST(DequeTest, int_basic_push_back) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  std::deque<int> libdec;
  libdec.push_back(1);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
}

TEST(DequeTest, int_basic_push_back2) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(42);
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(42);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
}

TEST(DequeTest, int_basic_push_back3) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(42);
  mydec.push_back(2011);
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(42);
  libdec.push_back(2011);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
}

// pop_back
// push_front
// pop_front
// resize
// swap
