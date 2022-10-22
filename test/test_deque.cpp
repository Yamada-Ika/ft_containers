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
TEST(DequeTest, int_basic_at) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  std::deque<int> libdec;
  libdec.push_front(1);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
}

TEST(DequeTest, int_basic_at1) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  std::deque<int> libdec;
  libdec.push_front(1);

  EXPECT_THROW(libdec.at(100), std::out_of_range);
  EXPECT_THROW(mydec.at(100), std::out_of_range);
}

// operator[]
TEST(DequeTest, int_basic_operator_brace) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  std::deque<int> libdec;
  libdec.push_front(1);

  ASSERT_EQ(libdec[0], mydec[0]);
}

// TEST(DequeTest, int_basic_operator_brace1) {
//   ft::deque<int> mydec;
//   mydec.push_front(1);
//   std::deque<int> libdec;
//   libdec.push_front(1);

//   ASSERT_EQ(libdec[10], mydec[10]);
// }

// front
// Calling front on an empty container is undefined.
// TEST(DequeTest, int_basic_front) {
//   ft::deque<int> mydec;
//   std::deque<int> libdec;

//   ASSERT_EQ(libdec.front(), mydec.front());
// }

TEST(DequeTest, int_basic_front1) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  std::deque<int> libdec;
  libdec.push_front(1);

  ASSERT_EQ(libdec.front(), mydec.front());
}

TEST(DequeTest, int_basic_front2) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_back(42);
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_back(42);

  ASSERT_EQ(libdec.front(), mydec.front());
}

// back
// Calling back on an empty container causes undefined behavior.
// TEST(DequeTest, int_basic_back) {
//   ft::deque<int> mydec;
//   std::deque<int> libdec;

//   ASSERT_EQ(libdec.back(), mydec.back());
// }

TEST(DequeTest, int_basic_back1) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  std::deque<int> libdec;
  libdec.push_back(1);

  ASSERT_EQ(libdec.back(), mydec.back());
}

TEST(DequeTest, int_basic_back2) {
  ft::deque<int> mydec;
  mydec.push_front(42);
  mydec.push_back(1);
  std::deque<int> libdec;
  libdec.push_front(42);
  libdec.push_back(1);

  ASSERT_EQ(libdec.back(), mydec.back());
}

// begin
TEST(DequeTest, int_basic_begin) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  std::deque<int> libdec;
  libdec.push_back(1);

  ASSERT_EQ(*(libdec.begin()), *(mydec.begin()));
}

// iterator
TEST(DequeTest, int_basic_iterator) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(2);
  ft::deque<int>::iterator myitr = mydec.begin();
  ++myitr;
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(2);
  std::deque<int>::iterator libitr = libdec.begin();
  ++libitr;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator1) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(2);
  ft::deque<int>::iterator myitr = mydec.begin();
  myitr++;
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(2);
  std::deque<int>::iterator libitr = libdec.begin();
  libitr++;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator2) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_front(2);
  ft::deque<int>::iterator myitr = mydec.begin();
  ++myitr;
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_front(2);
  std::deque<int>::iterator libitr = libdec.begin();
  ++libitr;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator3) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_front(2);
  ft::deque<int>::iterator myitr = mydec.begin();
  myitr++;
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_front(2);
  std::deque<int>::iterator libitr = libdec.begin();
  libitr++;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator4) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(2);
  ft::deque<int>::iterator myitr = mydec.begin();
  ++myitr;
  --myitr;
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(2);
  std::deque<int>::iterator libitr = libdec.begin();
  ++libitr;
  --libitr;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator5) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(2);
  ft::deque<int>::iterator myitr = mydec.begin();
  ++myitr;
  myitr--;
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(2);
  std::deque<int>::iterator libitr = libdec.begin();
  ++libitr;
  libitr--;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator6) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(2);
  ft::deque<int>::iterator myitr = mydec.begin();
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(2);
  std::deque<int>::iterator libitr = libdec.begin();

  ASSERT_EQ(*(myitr.operator->()), *(libitr.operator->()));
}

TEST(DequeTest, int_basic_iterator7) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(2);
  ft::deque<int>::iterator mi = mydec.begin();
  ft::deque<int>::iterator* myitr = &mi;
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(2);
  std::deque<int>::iterator li = libdec.begin();
  std::deque<int>::iterator* libitr = &li;

  ASSERT_EQ(myitr->operator*(), libitr->operator*());
}

TEST(DequeTest, int_basic_iterator8) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(2);
  ft::deque<int>::iterator myitr = mydec.begin();
  myitr += 1;
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(2);
  std::deque<int>::iterator libitr = libdec.begin();
  libitr += 1;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator9) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(2);
  ft::deque<int>::iterator myitr = mydec.begin();
  myitr += 1;
  myitr -= 1;
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(2);
  std::deque<int>::iterator libitr = libdec.begin();
  libitr += 1;
  libitr -= 1;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator10) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(100);
  mydec.push_back(1234);
  ft::deque<int>::iterator myitr = mydec.begin();
  myitr += 3;
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(100);
  libdec.push_back(1234);
  std::deque<int>::iterator libitr = libdec.begin();
  libitr += 3;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator11) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_front(3);
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(100);
  mydec.push_back(1234);
  ft::deque<int>::iterator myitr = mydec.begin();
  myitr += 3;
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_front(3);
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(100);
  libdec.push_back(1234);
  std::deque<int>::iterator libitr = libdec.begin();
  libitr += 3;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator12) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_front(3);
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(100);
  mydec.push_back(1234);
  ft::deque<int>::iterator myitr = mydec.begin();
  myitr += 3;
  myitr -= 3;
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_front(3);
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(100);
  libdec.push_back(1234);
  std::deque<int>::iterator libitr = libdec.begin();
  libitr += 3;
  libitr -= 3;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_iterator13) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(3);
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(100);
  mydec.push_back(1234);
  ft::deque<int>::iterator myitr = mydec.begin();
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(3);
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(100);
  libdec.push_back(1234);
  std::deque<int>::iterator libitr = libdec.begin();

  ASSERT_EQ(myitr[4], libitr[4]);
}

TEST(DequeTest, int_basic_iterator14) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_front(3);
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(100);
  mydec.push_back(1234);
  ft::deque<int>::iterator myitr = mydec.begin();
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_front(3);
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(100);
  libdec.push_back(1234);
  std::deque<int>::iterator libitr = libdec.begin();

  ASSERT_EQ(myitr[4], libitr[4]);
}

TEST(DequeTest, int_basic_iterator15) {
  ft::deque<int> mydec;
  mydec.push_back(2);
  ft::deque<int>::iterator myitr1 = mydec.begin();
  ft::deque<int>::iterator myitr2 = mydec.begin();
  std::deque<int> libdec;
  libdec.push_back(2);
  std::deque<int>::iterator libitr1 = libdec.begin();
  std::deque<int>::iterator libitr2 = libdec.begin();

  ASSERT_EQ(myitr1 == myitr2, libitr1 == libitr2);
  ASSERT_EQ(myitr1 != myitr2, libitr1 != libitr2);
}

TEST(DequeTest, int_basic_iterator16) {
  ft::deque<int> mydec;
  mydec.push_back(2);
  ft::deque<int>::iterator myitr1 = mydec.begin();
  ft::deque<int>::iterator myitr2 = mydec.begin();
  myitr2++;
  std::deque<int> libdec;
  libdec.push_back(2);
  std::deque<int>::iterator libitr1 = libdec.begin();
  std::deque<int>::iterator libitr2 = libdec.begin();
  libitr2++;

  ASSERT_EQ(myitr1 != myitr2, libitr1 != libitr2);
  ASSERT_EQ(myitr1 == myitr2, libitr1 == libitr2);
}

TEST(DequeTest, int_basic_iterator18) {
  ft::deque<int> mydec;
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(100);
  mydec.push_back(-10);
  ft::deque<int>::iterator myitr = mydec.begin();

  std::deque<int> libdec;
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(100);
  libdec.push_back(-10);
  std::deque<int>::iterator libitr = libdec.begin();

  ASSERT_EQ(*(myitr + 1), *(libitr + 1));
  ASSERT_EQ(*(myitr + 2), *(libitr + 2));
  ASSERT_EQ(*(myitr + 3), *(libitr + 3));
}

TEST(DequeTest, int_basic_iterator19) {
  ft::deque<int> mydec;
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(100);
  mydec.push_back(-10);
  ft::deque<int>::iterator myitr = mydec.begin();
  myitr += 3;

  std::deque<int> libdec;
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(100);
  libdec.push_back(-10);
  std::deque<int>::iterator libitr = libdec.begin();
  libitr += 3;

  ASSERT_EQ(*(myitr - 1), *(libitr - 1));
  ASSERT_EQ(*(myitr - 2), *(libitr - 2));
  ASSERT_EQ(*(myitr - 3), *(libitr - 3));
}

TEST(DequeTest, int_basic_iterator20) {
  ft::deque<int> mydec;
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(5);
  mydec.push_back(100);
  ft::deque<int>::iterator myitr1 = mydec.begin();
  ft::deque<int>::iterator myitr2 = mydec.begin();
  myitr2++;
  std::deque<int> libdec;
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(5);
  libdec.push_back(100);
  std::deque<int>::iterator libitr1 = libdec.begin();
  std::deque<int>::iterator libitr2 = libdec.begin();
  libitr2++;

  ASSERT_EQ(myitr1 < myitr2, libitr1 < libitr2);
  ASSERT_EQ(myitr1 <= myitr2, libitr1 <= libitr2);
}

TEST(DequeTest, int_basic_iterator21) {
  ft::deque<int> mydec;
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(5);
  mydec.push_back(100);
  ft::deque<int>::iterator myitr1 = mydec.begin();
  ft::deque<int>::iterator myitr2 = mydec.begin();
  std::deque<int> libdec;
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(5);
  libdec.push_back(100);
  std::deque<int>::iterator libitr1 = libdec.begin();
  std::deque<int>::iterator libitr2 = libdec.begin();

  myitr1++;
  libitr1++;
  ASSERT_EQ(myitr1 > myitr2, libitr1 > libitr2);
  ASSERT_EQ(myitr1 >= myitr2, libitr1 >= libitr2);
}

// end
TEST(DequeTest, int_basic_end) {
  ft::deque<int> mydec;
  mydec.push_back(42);
  mydec.push_back(2);
  ft::deque<int>::iterator myitr = mydec.end();
  --myitr;
  std::deque<int> libdec;
  libdec.push_back(42);
  libdec.push_back(2);
  std::deque<int>::iterator libitr = libdec.end();
  --libitr;

  ASSERT_EQ(*myitr, *libitr);
}

TEST(DequeTest, int_basic_end1) {
  ft::deque<int> mydec;
  mydec.push_front(1234);
  mydec.push_back(42);
  mydec.push_back(2);
  mydec.push_back(1020202);
  ft::deque<int>::iterator myitr = mydec.end();
  --myitr;
  std::deque<int> libdec;
  libdec.push_front(1234);
  libdec.push_back(42);
  libdec.push_back(2);
  libdec.push_back(1020202);
  std::deque<int>::iterator libitr = libdec.end();
  --libitr;

  ASSERT_EQ(*myitr, *libitr);
}

// rbegin
TEST(DequeTest, int_basic_rbegin) {
  ft::deque<int> mydec;
  mydec.push_front(1234);
  mydec.push_back(42);
  mydec.push_back(2);
  mydec.push_back(1020202);
  ft::deque<int>::reverse_iterator myitr = mydec.rbegin();
  std::deque<int> libdec;
  libdec.push_front(1234);
  libdec.push_back(42);
  libdec.push_back(2);
  libdec.push_back(1020202);
  std::deque<int>::reverse_iterator libitr = libdec.rbegin();

  ASSERT_EQ(*(myitr), *(libitr));
  ASSERT_EQ(*(myitr + 1), *(libitr + 1));
  ASSERT_EQ(*(myitr + 2), *(libitr + 2));
  ASSERT_EQ(*(myitr + 3), *(libitr + 3));
}

// rend
TEST(DequeTest, int_basic_rend) {
  ft::deque<int> mydec;
  mydec.push_front(1234);
  mydec.push_back(42);
  mydec.push_back(2);
  mydec.push_back(1020202);
  ft::deque<int>::reverse_iterator myitr = mydec.rend();
  std::deque<int> libdec;
  libdec.push_front(1234);
  libdec.push_back(42);
  libdec.push_back(2);
  libdec.push_back(1020202);
  std::deque<int>::reverse_iterator libitr = libdec.rend();
  myitr--;
  libitr--;
  ASSERT_EQ(*(myitr), *(libitr));
}

// empty
TEST(DequeTest, int_basic_empty) {
  ft::deque<int> mydec;
  std::deque<int> libdec;

  ASSERT_EQ(libdec.empty(), mydec.empty());
}

TEST(DequeTest, int_basic_empty1) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  std::deque<int> libdec;
  libdec.push_back(1);

  ASSERT_EQ(libdec.empty(), mydec.empty());
}

// size
TEST(DequeTest, int_basic_size) {
  ft::deque<int> mydec;
  std::deque<int> libdec;

  ASSERT_EQ(libdec.size(), mydec.size());
}

TEST(DequeTest, int_basic_size1) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  std::deque<int> libdec;
  libdec.push_back(1);

  ASSERT_EQ(libdec.size(), mydec.size());
}

TEST(DequeTest, int_basic_size2) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(42);
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(42);

  ASSERT_EQ(libdec.size(), mydec.size());
}

TEST(DequeTest, int_basic_siz3) {
  ft::deque<int> mydec;
  mydec.push_front(2);
  mydec.push_front(52);
  mydec.push_back(1);
  mydec.push_back(42);
  std::deque<int> libdec;
  libdec.push_front(2);
  libdec.push_front(52);
  libdec.push_back(1);
  libdec.push_back(42);

  ASSERT_EQ(libdec.size(), mydec.size());
}

// max_size
TEST(DequeTest, int_basic_max_size) {
  ft::deque<int> mydec;
  std::deque<int> libdec;

  ASSERT_EQ(libdec.max_size(), mydec.max_size());
}

// clear
TEST(DequeTest, int_basic_clear) {
  ft::deque<int> mydec;
  mydec.clear();
  std::deque<int> libdec;
  libdec.clear();

  ASSERT_EQ(libdec.size(), mydec.size());
}

TEST(DequeTest, int_basic_clear1) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_back(42);
  mydec.clear();
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_back(42);
  libdec.clear();

  ASSERT_EQ(libdec.size(), mydec.size());
}

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
TEST(DequeTest, int_basic_pop_back) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.pop_back();
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.pop_back();

  ASSERT_EQ(libdec.size(), mydec.size());
}

TEST(DequeTest, int_basic_pop_back1) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_back(42);
  mydec.pop_back();
  mydec.push_front(142);
  mydec.pop_back();
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_back(42);
  libdec.pop_back();
  libdec.push_front(142);
  libdec.pop_back();

  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
}

// push_front
TEST(DequeTest, int_basic_push_front) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.push_front(2);
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.push_front(2);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
}

TEST(DequeTest, int_basic_push_front1) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  std::deque<int> libdec;
  libdec.push_front(1);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
}

TEST(DequeTest, int_basic_push_front2) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_front(2);
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_front(2);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
}

TEST(DequeTest, int_basic_push_front3) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_front(2);
  mydec.push_front(42);
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_front(2);
  libdec.push_front(42);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
}

// pop_front
TEST(DequeTest, int_basic_pop_front) {
  ft::deque<int> mydec;
  mydec.push_back(1);
  mydec.pop_front();
  std::deque<int> libdec;
  libdec.push_back(1);
  libdec.pop_front();

  ASSERT_EQ(libdec.size(), mydec.size());
}

TEST(DequeTest, int_basic_pop_front1) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_back(42);
  mydec.pop_front();
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_back(42);
  libdec.pop_front();

  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
}

TEST(DequeTest, int_basic_pop_front2) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_back(42);
  mydec.push_back(100);
  mydec.pop_front();
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_back(42);
  libdec.push_back(100);
  libdec.pop_front();

  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
}

TEST(DequeTest, int_basic_push_pop_mix1) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_back(3);
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_back(3);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
}

TEST(DequeTest, int_basic_push_pop_mix2) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_back(3);
  mydec.push_front(42);
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_back(3);
  libdec.push_front(42);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
}

TEST(DequeTest, int_basic_pus_pop_mix3) {
  ft::deque<int> mydec;
  mydec.push_front(1);
  mydec.push_back(3);
  mydec.push_front(42);
  mydec.push_back(12);
  mydec.push_front(-10);
  std::deque<int> libdec;
  libdec.push_front(1);
  libdec.push_back(3);
  libdec.push_front(42);
  libdec.push_back(12);
  libdec.push_front(-10);

  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
  ASSERT_EQ(libdec.at(4), mydec.at(4));
}

// resize
// swap
