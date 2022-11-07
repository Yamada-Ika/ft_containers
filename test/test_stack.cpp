#include <gtest/gtest.h>

#include <stack>
#include <vector>
#include <deque>
#include "../stack.hpp"

template <typename T>
static void prepareTestData(std::stack<T>& libstack, ft::stack<T>& mystack,
                            const std::vector<T>& test_data) {
  for (typename std::vector<T>::const_iterator itr = test_data.begin();
       itr != test_data.end(); ++itr) {
    libstack.push(*itr);
    mystack.push(*itr);
  }
}

template <typename T>
static void assertStack(std::stack<T> libstack, ft::stack<T> mystack) {
  ASSERT_EQ(libstack.size(), mystack.size());
  for (typename ft::stack<T>::size_type i = 0; i < mystack.size(); ++i) {
    ASSERT_EQ(libstack.top(), mystack.top());
    libstack.pop();
    mystack.pop();
  }
}

// constructor
TEST(StackTest, int_basic_constructor_without_container) {
  ft::stack<int> myst;
}

TEST(StackTest, int_basic_constructor_with_container) {
  std::deque<int> container;
  ft::stack<int, std::deque<int> > myst(container);
}

// TODO 要素もチェックするテスト追加する
TEST(StackTest, int_basic_constructor_copy) {
  ft::stack<int> src;
  ft::stack<int> myst(src);
}

// TODO 要素もチェックするテスト追加する
TEST(StackTest, int_basic_constructor_assign) {
  ft::stack<int> src;
  ft::stack<int> myst = src;
}

TEST(StackTest, int_basic_constructor_top) {
  std::vector<int> test_data = {1, 2, 42};
  std::stack<int> libst;
  ft::stack<int> myst;
  prepareTestData(libst, myst, test_data);

  ASSERT_EQ(libst.top(), myst.top());
}

TEST(StackTest, int_basic_constructor_empty) {
  std::vector<int> test_data = {1, 2, 42};
  std::stack<int> libst;
  ft::stack<int> myst;
  prepareTestData(libst, myst, test_data);

  ASSERT_EQ(libst.empty(), myst.empty());
}

TEST(StackTest, int_basic_constructor_empty2) {
  std::stack<int> libst;
  ft::stack<int> myst;

  ASSERT_EQ(libst.empty(), myst.empty());
}

TEST(StackTest, int_basic_constructor_size) {
  std::vector<int> test_data = {1, 2, 42};
  std::stack<int> libst;
  ft::stack<int> myst;
  prepareTestData(libst, myst, test_data);

  ASSERT_EQ(libst.size(), myst.size());
}

TEST(StackTest, int_basic_constructor_size2) {
  std::stack<int> libst;
  ft::stack<int> myst;

  ASSERT_EQ(libst.size(), myst.size());
}

TEST(StackTest, int_basic_constructor_push) {
  std::vector<int> test_data = {1, 2, 42};
  std::stack<int> libst;
  ft::stack<int> myst;
  prepareTestData(libst, myst, test_data);
}

TEST(StackTest, int_basic_constructor_pop) {
  std::vector<int> test_data = {1, 2, 42};
  std::stack<int> libst;
  ft::stack<int> myst;
  prepareTestData(libst, myst, test_data);

  libst.pop();
  myst.pop();

  assertStack(libst, myst);
}
