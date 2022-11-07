#include <gtest/gtest.h>

#include <deque>
#include <memory>
#include "../deque.hpp"

template <typename T>
static void prepareTestData(std::deque<T>& libdeq, ft::deque<T>& mydeq,
                            const std::deque<T>& data) {
  for (size_t i = 0; i < data.size(); ++i) {
    mydeq.push_back(data.at(i));
    libdeq.push_back(data.at(i));
  }
}

template <typename T>
static void assertDeque(const std::deque<T>& libdeq,
                        const ft::deque<T>& mydeq) {
  ASSERT_EQ(libdeq.size(), mydeq.size());
  for (size_t i = 0; i < libdeq.size(); ++i) {
    ASSERT_EQ(libdeq.at(i), mydeq.at(i));
  }
}

// constructor
// 1
TEST(DequeTest, int_basic_constructor_without_argments) {
  ft::deque<int> mydec;
}

// 2
TEST(DequeTest, int_basic_constructor2) {
  std::allocator<int> alloc;
  ft::deque<int> mydec(alloc);
  std::deque<int> libdec(alloc);
  ASSERT_EQ(libdec.size(), mydec.size());
}

// 3
TEST(DequeTest, int_basic_constructor3) {
  ft::deque<int> mydec(10);
  std::deque<int> libdec(10);
  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
  ASSERT_EQ(libdec.at(4), mydec.at(4));
  ASSERT_EQ(libdec.at(5), mydec.at(5));
  ASSERT_EQ(libdec.at(6), mydec.at(6));
  ASSERT_EQ(libdec.at(7), mydec.at(7));
  ASSERT_EQ(libdec.at(8), mydec.at(8));
  ASSERT_EQ(libdec.at(9), mydec.at(9));
}

TEST(DequeTest, int_basic_constructor3_1) {
  ft::deque<int> mydec(10, 42);
  std::deque<int> libdec(10, 42);
  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
  ASSERT_EQ(libdec.at(4), mydec.at(4));
  ASSERT_EQ(libdec.at(5), mydec.at(5));
  ASSERT_EQ(libdec.at(6), mydec.at(6));
  ASSERT_EQ(libdec.at(7), mydec.at(7));
  ASSERT_EQ(libdec.at(8), mydec.at(8));
  ASSERT_EQ(libdec.at(9), mydec.at(9));
}

TEST(DequeTest, int_basic_constructor3_2) {
  std::allocator<int> alloc;
  ft::deque<int> mydec(10, 42, alloc);
  std::deque<int> libdec(10, 42, alloc);
  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
  ASSERT_EQ(libdec.at(4), mydec.at(4));
  ASSERT_EQ(libdec.at(5), mydec.at(5));
  ASSERT_EQ(libdec.at(6), mydec.at(6));
  ASSERT_EQ(libdec.at(7), mydec.at(7));
  ASSERT_EQ(libdec.at(8), mydec.at(8));
  ASSERT_EQ(libdec.at(9), mydec.at(9));
}

// 4
TEST(DequeTest, int_basic_constructor4) {
  ft::deque<int> mydec1;
  mydec1.push_back(1);
  mydec1.push_back(42);
  mydec1.push_back(5);
  mydec1.push_back(-100);
  std::deque<int> libdec1;
  libdec1.push_back(1);
  libdec1.push_back(42);
  libdec1.push_back(5);
  libdec1.push_back(-100);
  ft::deque<int> mydec(mydec1.begin(), mydec1.end());
  std::deque<int> libdec(libdec1.begin(), libdec1.end());
  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
}

TEST(DequeTest, int_basic_constructor4_1) {
  std::allocator<int> alloc;
  ft::deque<int> mydec1;
  mydec1.push_back(1);
  mydec1.push_back(42);
  mydec1.push_back(5);
  mydec1.push_back(-100);
  std::deque<int> libdec1;
  libdec1.push_back(1);
  libdec1.push_back(42);
  libdec1.push_back(5);
  libdec1.push_back(-100);
  ft::deque<int> mydec(mydec1.begin(), mydec1.end(), alloc);
  std::deque<int> libdec(libdec1.begin(), libdec1.end(), alloc);
  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
}

// 5
TEST(DequeTest, int_basic_constructor5) {
  std::allocator<int> alloc;
  ft::deque<int> mydec1;
  mydec1.push_back(1);
  mydec1.push_back(42);
  mydec1.push_back(5);
  mydec1.push_back(-100);
  std::deque<int> libdec1;
  libdec1.push_back(1);
  libdec1.push_back(42);
  libdec1.push_back(5);
  libdec1.push_back(-100);
  ft::deque<int> mydec = mydec1;
  std::deque<int> libdec = libdec1;
  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
}

TEST(DequeTest, int_basic_constructor5_1) {
  std::allocator<int> alloc;
  ft::deque<int> mydec1;
  mydec1.push_back(1);
  mydec1.push_back(42);
  mydec1.push_back(5);
  mydec1.push_back(-100);
  std::deque<int> libdec1;
  libdec1.push_back(1);
  libdec1.push_back(42);
  libdec1.push_back(5);
  libdec1.push_back(-100);
  ft::deque<int> mydec(mydec1);
  std::deque<int> libdec(libdec1);
  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
}

// operator=
TEST(DequeTest, int_basic_operator_assign) {

  ft::deque<int> mydec2;
  mydec2.push_back(1);
  mydec2.push_back(42);
  mydec2.push_back(5);
  std::deque<int> libdec2;
  libdec2.push_back(1);
  libdec2.push_back(42);
  libdec2.push_back(5);

  ft::deque<int> mydec = mydec2;
  std::deque<int> libdec = libdec2;

  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
}

// assign
TEST(DequeTest, int_basic_assign) {
  ft::deque<int> mydec;
  std::deque<int> libdec;

  mydec.assign(4, 1);
  libdec.assign(4, 1);

  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
}

TEST(DequeTest, int_basic_assign1) {
  ft::deque<int> mydec;
  std::deque<int> libdec;

  mydec.assign(0, 1);
  libdec.assign(0, 1);

  ASSERT_EQ(libdec.size(), mydec.size());
}

TEST(DequeTest, int_basic_assign2) {
  ft::deque<int> mydec;
  std::deque<int> libdec;

  ft::deque<int> mydec1;
  std::deque<int> libdec1;
  std::deque<int> data = {0, 3, 10000, 2, -1, -400};
  prepareTestData(libdec1, mydec1, data);

  mydec.assign(mydec1.begin(), mydec1.end());
  libdec.assign(libdec1.begin(), libdec1.end());

  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
  ASSERT_EQ(libdec.at(4), mydec.at(4));
  ASSERT_EQ(libdec.at(5), mydec.at(5));
}

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

  ASSERT_EQ(*myitr, *libitr);
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

  ASSERT_EQ(*myitr, *libitr);
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

TEST(DequeTest, int_basic_iterator22) {
  ft::deque<int> mydec;
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(5);
  mydec.push_back(100);
  std::deque<int> libdec;
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(5);
  libdec.push_back(100);

  ASSERT_EQ(mydec.end() - mydec.begin(), libdec.end() - libdec.begin());
}

TEST(DequeTest, int_basic_iterator23) {
  ft::deque<int> mydec;
  mydec.push_back(2);
  mydec.push_back(42);
  mydec.push_back(5);
  mydec.push_back(100);
  std::deque<int> libdec;
  libdec.push_back(2);
  libdec.push_back(42);
  libdec.push_back(5);
  libdec.push_back(100);

  ASSERT_EQ((mydec.begin() + 1) - mydec.begin(),
            (libdec.begin() + 1) - libdec.begin());
}

TEST(DequeTest, int_basic_iterator24) {
  ft::deque<int> mydec;
  std::deque<int> libdec;

  ASSERT_EQ(mydec.begin() - mydec.begin(), libdec.begin() - libdec.begin());
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

TEST(DequeTest, int_basic_rbegin1) {
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
  ASSERT_EQ(*myitr, *libitr);
  myitr++;
  libitr++;
  ASSERT_EQ(*myitr, *libitr);
  myitr++;
  libitr++;
  ASSERT_EQ(*myitr, *libitr);
  myitr++;
  libitr++;
  ASSERT_EQ(*myitr, *libitr);
  myitr++;
  libitr++;
}

// rend
// TEST(DequeTest, int_basic_rend) {
//   ft::deque<int> mydec;
//   mydec.push_front(1234);
//   mydec.push_back(42);
//   mydec.push_back(2);
//   mydec.push_back(1020202);
//   ft::deque<int>::reverse_iterator myitr = mydec.rend();
//   std::deque<int> libdec;
//   libdec.push_front(1234);
//   libdec.push_back(42);
//   libdec.push_back(2);
//   libdec.push_back(1020202);
//   std::deque<int>::reverse_iterator libitr = libdec.rend();
//   myitr--;
//   libitr--;
//   ASSERT_EQ(*(myitr), *(libitr));
// }

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
TEST(DequeTest, int_basic_insert) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);

  ft::deque<int>::iterator myitr = mydec.insert(mydec.begin(), 2);
  std::deque<int>::iterator libitr = libdec.insert(libdec.begin(), 2);

  ASSERT_EQ(*libitr, *myitr);
  assertDeque(libdec, mydec);
}

TEST(DequeTest, int_basic_insert1) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);

  ft::deque<int>::iterator myitr = mydec.insert(mydec.begin() + 3, 2);
  std::deque<int>::iterator libitr = libdec.insert(libdec.begin() + 3, 2);

  ASSERT_EQ(*libitr, *myitr);
  assertDeque(libdec, mydec);
}

TEST(DequeTest, int_basic_insert2) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);

  ft::deque<int>::iterator myitr = mydec.insert(mydec.end(), 2);
  std::deque<int>::iterator libitr = libdec.insert(libdec.end(), 2);

  ASSERT_EQ(*libitr, *myitr);
  assertDeque(libdec, mydec);
}

TEST(DequeTest, int_basic_insert3) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);

  ft::deque<int>::iterator myitr = mydec.insert(mydec.begin(), 3, 2);
  std::deque<int>::iterator libitr = libdec.insert(libdec.begin(), 3, 2);

  ASSERT_EQ(*libitr, *myitr);
  assertDeque(libdec, mydec);
}

TEST(DequeTest, int_basic_insert4) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);

  ft::deque<int>::iterator myitr = mydec.insert(mydec.begin(), 1, 2);
  std::deque<int>::iterator libitr = libdec.insert(libdec.begin(), 1, 2);

  ASSERT_EQ(*libitr, *myitr);
  assertDeque(libdec, mydec);
}

TEST(DequeTest, int_basic_insert5) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);

  ft::deque<int>::iterator myitr = mydec.insert(mydec.begin() + 2, 2, 2);
  std::deque<int>::iterator libitr = libdec.insert(libdec.begin() + 2, 2, 2);

  ASSERT_EQ(*libitr, *myitr);
  assertDeque(libdec, mydec);
}

TEST(DequeTest, int_basic_insert6) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);

  ft::deque<int>::iterator myitr = mydec.insert(mydec.end(), 1, 2);
  std::deque<int>::iterator libitr = libdec.insert(libdec.end(), 1, 2);

  ASSERT_EQ(*libitr, *myitr);
  assertDeque(libdec, mydec);
}

// The behavior is undefined if first and last are iterators into *this.
// TEST(DequeTest, int_basic_insert7) {
//   std::deque<int> data = {1, 3, 42, 12, -10};
//   ft::deque<int> mydec;
//   std::deque<int> libdec;

//   prepareTestData(libdec, mydec, data);

//   ft::deque<int>::iterator myitr =
//       mydec.insert(mydec.begin(), mydec.begin(), mydec.end());
//   std::deque<int>::iterator libitr =
//       libdec.insert(libdec.begin(), libdec.begin(), libdec.end());

//   for (size_t i = 0; i < mydec.size(); ++i) {
//     LOG(ERROR) << " mydec[" << i << "] : " << mydec.at(i);
//   }
//   for (size_t i = 0; i < libdec.size(); ++i) {
//     LOG(ERROR) << "libdec[" << i << "] : " << libdec.at(i);
//   }

//   ASSERT_EQ(*libitr, *myitr);
//   ASSERT_EQ(libdec.size(), mydec.size());
//   ASSERT_EQ(libdec.at(0), mydec.at(0));
//   ASSERT_EQ(libdec.at(1), mydec.at(1));
//   ASSERT_EQ(libdec.at(2), mydec.at(2));
//   ASSERT_EQ(libdec.at(3), mydec.at(3));
//   ASSERT_EQ(libdec.at(4), mydec.at(4));
// }

TEST(DequeTest, int_basic_insert8) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);
  std::deque<int> data2 = {1, 3, 42, 12, -10, 10, 2, -1, -2930, 43};
  ft::deque<int> mydec2;
  std::deque<int> libdec2;

  prepareTestData(libdec2, mydec2, data2);

  ft::deque<int>::iterator myitr =
      mydec.insert(mydec.begin(), mydec2.begin(), mydec2.end());
  std::deque<int>::iterator libitr =
      libdec.insert(libdec.begin(), libdec2.begin(), libdec2.end());

  for (size_t i = 0; i < mydec.size(); ++i) {
    LOG(ERROR) << " mydec[" << i << "] : " << mydec.at(i);
  }
  for (size_t i = 0; i < libdec.size(); ++i) {
    LOG(ERROR) << "libdec[" << i << "] : " << libdec.at(i);
  }

  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(*libitr, *myitr);
  assertDeque(libdec, mydec);
}

TEST(DequeTest, int_basic_insert9) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);

  ft::deque<int>::iterator myitr = mydec.insert(mydec.begin(), 100, 2);
  std::deque<int>::iterator libitr = libdec.insert(libdec.begin(), 100, 2);

  ASSERT_EQ(*libitr, *myitr);
  assertDeque(libdec, mydec);
}

TEST(DequeTest, int_basic_insert10) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);

  ft::deque<int>::iterator myitr = mydec.insert(mydec.begin() + 1, 2);
  std::deque<int>::iterator libitr = libdec.insert(libdec.begin() + 1, 2);

  ASSERT_EQ(*libitr, *myitr);
  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
  ASSERT_EQ(libdec.at(4), mydec.at(4));
  ASSERT_EQ(libdec.at(5), mydec.at(5));
}

TEST(DequeTest, int_basic_insert11) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  prepareTestData(libdec, mydec, data);

  ft::deque<int> mydec1;
  std::deque<int> libdec1;
  std::deque<int> data1 = {3, 5, 62, 67, 8, 9};
  prepareTestData(libdec1, mydec1, data1);
  ft::deque<int>::iterator myitr =
      mydec.insert(mydec.begin(), mydec1.begin(), mydec1.end());
  std::deque<int>::iterator libitr =
      libdec.insert(libdec.begin(), libdec1.begin(), libdec1.end());
  ASSERT_EQ(*libitr, *myitr);
  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(libdec.at(0), mydec.at(0));
  ASSERT_EQ(libdec.at(1), mydec.at(1));
  ASSERT_EQ(libdec.at(2), mydec.at(2));
  ASSERT_EQ(libdec.at(3), mydec.at(3));
  ASSERT_EQ(libdec.at(4), mydec.at(4));
  ASSERT_EQ(libdec.at(5), mydec.at(5));
  ASSERT_EQ(libdec.at(6), mydec.at(6));
  ASSERT_EQ(libdec.at(7), mydec.at(7));
  ASSERT_EQ(libdec.at(8), mydec.at(8));
  ASSERT_EQ(libdec.at(9), mydec.at(9));
  ASSERT_EQ(libdec.at(10), mydec.at(10));
}

// erase
TEST(DequeTest, int_basic_erase) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  for (size_t i = 0; i < data.size(); ++i) {
    mydec.push_back(data.at(i));
    libdec.push_back(data.at(i));
  }

  ft::deque<int>::iterator myitr = mydec.erase(mydec.begin());
  std::deque<int>::iterator libitr = libdec.erase(libdec.begin());

  for (size_t i = 0; i < mydec.size(); ++i) {
    LOG(ERROR) << "mydec[" << i << "] = " << mydec.at(i);
  }

  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(*libitr, *myitr);
  for (size_t i = 0; i < libdec.size(); ++i) {
    ASSERT_EQ(libdec.at(i), mydec.at(i));
  }
}

TEST(DequeTest, int_basic_erase1) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  for (size_t i = 0; i < data.size(); ++i) {
    if (i % 2 == 0) {
      mydec.push_front(data.at(i));
      libdec.push_front(data.at(i));
    } else {
      mydec.push_back(data.at(i));
      libdec.push_back(data.at(i));
    }
  }

  ft::deque<int>::iterator myitr = mydec.erase(mydec.begin());
  std::deque<int>::iterator libitr = libdec.erase(libdec.begin());

  for (size_t i = 0; i < mydec.size(); ++i) {
    LOG(ERROR) << "mydec[" << i << "] = " << mydec.at(i);
  }

  ASSERT_EQ(libdec.size(), mydec.size());
  ASSERT_EQ(*libitr, *myitr);
  for (size_t i = 0; i < libdec.size(); ++i) {
    ASSERT_EQ(libdec.at(i), mydec.at(i));
  }
}

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
TEST(DequeTest, int_basic_resize) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  for (size_t i = 0; i < data.size(); ++i) {
    if (i % 2 == 0) {
      mydec.push_front(data.at(i));
      libdec.push_front(data.at(i));
    } else {
      mydec.push_back(data.at(i));
      libdec.push_back(data.at(i));
    }
  }

  mydec.resize(10);
  libdec.resize(10);

  ASSERT_EQ(libdec.size(), mydec.size());
  for (size_t i = 0; i < libdec.size(); ++i) {
    ASSERT_EQ(libdec.at(i), mydec.at(i));
  }
}

TEST(DequeTest, int_basic_resize1) {
  std::deque<int> data = {1, 3, 42, 12, -10};
  ft::deque<int> mydec;
  std::deque<int> libdec;

  for (size_t i = 0; i < data.size(); ++i) {
    if (i % 2 == 0) {
      mydec.push_front(data.at(i));
      libdec.push_front(data.at(i));
    } else {
      mydec.push_back(data.at(i));
      libdec.push_back(data.at(i));
    }
  }

  mydec.resize(2);
  libdec.resize(2);

  ASSERT_EQ(libdec.size(), mydec.size());
  for (size_t i = 0; i < libdec.size(); ++i) {
    ASSERT_EQ(libdec.at(i), mydec.at(i));
  }
}

// swap
TEST(DequeTest, int_basic_swap) {
  std::deque<int> data1 = {1, 2, 6, 100, 2, -1903};
  ft::deque<int> mydec1;
  std::deque<int> libdec1;
  prepareTestData(libdec1, mydec1, data1);
  std::deque<int> data2 = {1, 0, -1939, -34, 292, 193848, 2};
  ft::deque<int> mydec2;
  std::deque<int> libdec2;
  prepareTestData(libdec2, mydec2, data2);

  mydec1.swap(mydec2);
  libdec1.swap(libdec2);

  ASSERT_EQ(libdec1.size(), mydec1.size());
  ASSERT_EQ(libdec1.at(0), mydec1.at(0));
  ASSERT_EQ(libdec1.at(1), mydec1.at(1));
  ASSERT_EQ(libdec1.at(2), mydec1.at(2));
  ASSERT_EQ(libdec1.at(3), mydec1.at(3));
  ASSERT_EQ(libdec1.at(4), mydec1.at(4));
  ASSERT_EQ(libdec1.at(5), mydec1.at(5));
  ASSERT_EQ(libdec1.at(6), mydec1.at(6));
}

TEST(DequeTest, int_basic_swap1) {
  std::deque<int> data1 = {1, 2, 6, 100, 2, -1903};
  ft::deque<int> mydec1;
  std::deque<int> libdec1;
  prepareTestData(libdec1, mydec1, data1);
  std::deque<int> data2 = {1, 0, -1939, -34, 292, 193848, 2};
  ft::deque<int> mydec2;
  std::deque<int> libdec2;
  prepareTestData(libdec2, mydec2, data2);

  ft::swap(mydec1, mydec2);
  std::swap(libdec1, libdec2);

  ASSERT_EQ(libdec1.size(), mydec1.size());
  ASSERT_EQ(libdec1.at(0), mydec1.at(0));
  ASSERT_EQ(libdec1.at(1), mydec1.at(1));
  ASSERT_EQ(libdec1.at(2), mydec1.at(2));
  ASSERT_EQ(libdec1.at(3), mydec1.at(3));
  ASSERT_EQ(libdec1.at(4), mydec1.at(4));
  ASSERT_EQ(libdec1.at(5), mydec1.at(5));
  ASSERT_EQ(libdec1.at(6), mydec1.at(6));
}

// compare operators
TEST(DequeTest, int_basic_compare_operators) {
  ft::deque<int> mydec1;
  mydec1.push_back(1);
  mydec1.push_back(3);
  mydec1.push_back(42);
  mydec1.push_back(-100);
  std::deque<int> libdec1;
  libdec1.push_back(1);
  libdec1.push_back(3);
  libdec1.push_back(42);
  libdec1.push_back(-100);
  ft::deque<int> mydec(mydec1);
  std::deque<int> libdec(libdec1);

  ASSERT_EQ(libdec == libdec1, mydec == mydec1);
  ASSERT_EQ(libdec != libdec1, mydec != mydec1);
  ASSERT_EQ(libdec < libdec1, mydec < mydec1);
  ASSERT_EQ(libdec > libdec1, mydec > mydec1);
  ASSERT_EQ(libdec <= libdec1, mydec <= mydec1);
  ASSERT_EQ(libdec >= libdec1, mydec >= mydec1);
}

TEST(DequeTest, int_basic_compare_operators2) {
  ft::deque<int> mydec1;
  mydec1.push_back(1);
  std::deque<int> libdec1;
  libdec1.push_back(1);
  libdec1.push_back(3);
  libdec1.push_back(42);
  libdec1.push_back(-100);
  ft::deque<int> mydec(mydec1);
  std::deque<int> libdec(libdec1);

  ASSERT_EQ(libdec == libdec1, mydec == mydec1);
  ASSERT_EQ(libdec != libdec1, mydec != mydec1);
  ASSERT_EQ(libdec < libdec1, mydec < mydec1);
  ASSERT_EQ(libdec > libdec1, mydec > mydec1);
  ASSERT_EQ(libdec <= libdec1, mydec <= mydec1);
  ASSERT_EQ(libdec >= libdec1, mydec >= mydec1);
}

TEST(DequeTest, int_basic_compare_operators3) {
  ft::deque<int> mydec1;
  mydec1.push_back(1);
  mydec1.push_back(3);
  mydec1.push_back(42);
  mydec1.push_back(-100);
  std::deque<int> libdec1;
  libdec1.push_back(1);
  ft::deque<int> mydec(mydec1);
  std::deque<int> libdec(libdec1);

  ASSERT_EQ(libdec == libdec1, mydec == mydec1);
  ASSERT_EQ(libdec != libdec1, mydec != mydec1);
  ASSERT_EQ(libdec < libdec1, mydec < mydec1);
  ASSERT_EQ(libdec > libdec1, mydec > mydec1);
  ASSERT_EQ(libdec <= libdec1, mydec <= mydec1);
  ASSERT_EQ(libdec >= libdec1, mydec >= mydec1);
}