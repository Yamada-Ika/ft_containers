#include <gtest/gtest.h>

#include <vector>
#include <memory>
#include "../vector.hpp"

// TODO 自作アロケーたーのテスト
// constructor
// vector();
TEST(VectorTest, int_basic_constructor_without_args) {
  ft::vector<int> myvec;
  myvec.push_back(1);
  ASSERT_EQ(myvec.size(), 1);
  ASSERT_EQ(myvec.at(0), 1);
}

// vector( const Allocator& alloc );
TEST(VectorTest, int_basic_constructor_with_allocator) {
  std::allocator<int> alloc;
  ft::vector<int, std::allocator<int> > myvec(alloc);

  myvec.push_back(1);
  ASSERT_EQ(myvec.size(), 1);
  ASSERT_EQ(myvec.at(0), 1);
}

// vector( size_type count,
//                  const T& value = T(),
//                  const Allocator& alloc = Allocator());

// vector( size_type count );
TEST(VectorTest, int_basic_constructor_with_size) {
  ft::vector<int> myvec(10);

  ASSERT_EQ(myvec.size(), 10);
}

// vector( size_type count, const T& value = T() );
TEST(VectorTest, int_basic_constructor_with_size_and_value) {
  ft::vector<int> myvec(10, 42);

  ASSERT_EQ(myvec.size(), 10);
  for (std::vector<int>::size_type i = 0; i < myvec.size(); ++i) {
    ASSERT_EQ(myvec.at(i), 42);
  }
}

// vector( size_type count,
//                  const T& value = T(),
//                  const Allocator& alloc = Allocator());
TEST(VectorTest, int_basic_constructor_with_size_and_value_allocator) {
  std::allocator<int> alloc;
  ft::vector<int> myvec(10, 42, alloc);

  ASSERT_EQ(myvec.size(), 10);
  for (std::vector<int>::size_type i = 0; i < myvec.size(); ++i) {
    ASSERT_EQ(myvec.at(i), 42);
  }
}

// template< class InputIt >
// vector( InputIt first, InputIt last,
//         const Allocator& alloc = Allocator() );

// template< class InputIt >
// vector( InputIt first, InputIt last );
TEST(VectorTest, int_basic_constructor_with_iterator) {
  ft::vector<int> test_set;
  test_set.push_back(1);

  ft::vector<int> myvec(test_set.begin(), test_set.end());

  ASSERT_EQ(myvec.size(), test_set.size());
  for (std::vector<int>::size_type i = 0; i < myvec.size(); ++i) {
    ASSERT_EQ(myvec.at(i), test_set.at(i));
  }
}

// template< class InputIt >
// vector( InputIt first, InputIt last,
//                        const Allocator& alloc = Allocator() );
TEST(VectorTest, int_basic_constructor_with_iterator_and_allocator) {
  ft::vector<int> test_set;
  std::allocator<int> alloc;
  test_set.push_back(1);

  ft::vector<int> myvec(test_set.begin(), test_set.end(), alloc);

  ASSERT_EQ(myvec.size(), test_set.size());
  for (std::vector<int>::size_type i = 0; i < myvec.size(); ++i) {
    ASSERT_EQ(myvec.at(i), test_set.at(i));
  }
}

// vector( const vector& other );
TEST(VectorTest, int_basic_constructor_with_ftvector) {
  ft::vector<int> test_set;
  test_set.push_back(1);

  ft::vector<int> myvec(test_set);
  ASSERT_EQ(myvec.size(), test_set.size());
  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec.at(i), test_set.at(i));
  }
}

// destructor

// operator=
TEST(VectorTest, int_basic_operator_assign) {
  ft::vector<int> test_set;
  test_set.push_back(1);

  ft::vector<int> myvec = test_set;
  ASSERT_EQ(myvec.size(), test_set.size());
  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec.at(i), test_set.at(i));
  }
}

// assign
// void assign( size_type count, const T& value );
TEST(VectorTest, int_basic_assign) {
  ft::vector<int> myvec;
  myvec.assign(100, 42);
  ASSERT_EQ(myvec.size(), 100);
  for (std::vector<int>::size_type i = 0; i < 100; ++i) {
    ASSERT_EQ(myvec.at(i), 42);
  }
}

// template< class InputIt >
// void assign( InputIt first, InputIt last );
TEST(VectorTest, int_basic_assign_iterator) {
  ft::vector<int> test_set;
  test_set.push_back(1);
  test_set.push_back(2);
  test_set.push_back(3);

  ft::vector<int> myvec;
  myvec.assign(test_set.begin(), test_set.end());
  ASSERT_EQ(myvec.size(), test_set.size());
  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec.at(i), test_set.at(i));
  }
}

// get_allocator
TEST(VectorTest, int_basic_get_allocator) {
  ft::vector<int> myvec;
  myvec.get_allocator();
}

// at()
TEST(VectorTest, int_basic_at) {
  std::vector<int> test_set = {1};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec.at(i), libvec.at(i));
  }
}

TEST(VectorTest, int_basic_at2) {
  std::vector<int> test_set = {42, 1};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec.at(i), libvec.at(i));
  }
}

TEST(VectorTest, int_basic_at3) {
  std::vector<int> test_set = {42, 1, -10};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec.at(i), libvec.at(i));
  }
}

TEST(VectorTest, int_basic_at4) {
  std::vector<int> test_set = {42, 1, -10, 4242};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec.at(i), libvec.at(i));
  }
}

TEST(VectorTest, int_basic_at_exception) {
  ft::vector<int> myvec;

  EXPECT_THROW(myvec.at(42), std::out_of_range);
}

// operator[]
TEST(VectorTest, int_basic_bracket_operator) {
  std::vector<int> test_set = {42};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec[i], libvec[i]);
  }
}

TEST(VectorTest, int_basic_bracket_operator2) {
  std::vector<int> test_set = {42, 1};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec[i], libvec[i]);
  }
}

TEST(VectorTest, int_basic_bracket_operator3) {
  std::vector<int> test_set = {42, 1, -10};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec[i], libvec[i]);
  }
}

TEST(VectorTest, int_basic_bracket_operator4) {
  std::vector<int> test_set = {42, 1, -10, 4242};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
    ASSERT_EQ(myvec[i], libvec[i]);
  }
}

// front()
TEST(VectorTest, int_basic_front) {
  std::vector<int> test_set = {42};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.front(), libvec.front());
}

TEST(VectorTest, int_basic_front2) {
  std::vector<int> test_set = {42, 1};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.front(), libvec.front());
}

TEST(VectorTest, int_basic_front3) {
  std::vector<int> test_set = {42, 1, -10};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.front(), libvec.front());
}

TEST(VectorTest, int_basic_front4) {
  std::vector<int> test_set = {42, 1, -10, 4242};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.front(), libvec.front());
}

// back()
TEST(VectorTest, int_basic_back) {
  std::vector<int> test_set = {42};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.back(), libvec.back());
}

TEST(VectorTest, int_basic_back2) {
  std::vector<int> test_set = {42, 1};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.back(), libvec.back());
}

TEST(VectorTest, int_basic_back3) {
  std::vector<int> test_set = {42, 1, -10};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.back(), libvec.back());
}

TEST(VectorTest, int_basic_back4) {
  std::vector<int> test_set = {42, 1, -10, 4242};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.back(), libvec.back());
}

// data()
TEST(VectorTest, int_basic_data) {
  std::vector<int> test_set = {42};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  int* myvec_data = myvec.data();
  int* libvec_data = libvec.data();

  ASSERT_EQ(myvec.size(), libvec.size());

  for (size_t i = 0; i < myvec.size(); ++i) {
    ASSERT_EQ(myvec_data[i], libvec_data[i]);
  }
}

TEST(VectorTest, int_basic_data2) {
  std::vector<int> test_set = {42, 1};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  int* myvec_data = myvec.data();
  int* libvec_data = libvec.data();

  ASSERT_EQ(myvec.size(), libvec.size());

  for (size_t i = 0; i < myvec.size(); ++i) {
    ASSERT_EQ(myvec_data[i], libvec_data[i]);
  }
}

TEST(VectorTest, int_basic_data3) {
  std::vector<int> test_set = {42, 1, -10};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  int* myvec_data = myvec.data();
  int* libvec_data = libvec.data();

  ASSERT_EQ(myvec.size(), libvec.size());

  for (size_t i = 0; i < myvec.size(); ++i) {
    ASSERT_EQ(myvec_data[i], libvec_data[i]);
  }
}

TEST(VectorTest, int_basic_data4) {
  std::vector<int> test_set = {42, 1, -10, 4242};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  int* myvec_data = myvec.data();
  int* libvec_data = libvec.data();

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

TEST(VectorTest, int_basic_empty2) {
  std::vector<int> test_set = {42};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.empty(), libvec.empty());
}

// size()
TEST(VectorTest, int_basic_size) {
  std::vector<int> test_set = {42};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.size(), libvec.size());
}

TEST(VectorTest, int_basic_size2) {
  std::vector<int> test_set = {42, 1};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.size(), libvec.size());
}

TEST(VectorTest, int_basic_size3) {
  std::vector<int> test_set = {42, 1, -10};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.size(), libvec.size());
}

TEST(VectorTest, int_basic_size4) {
  std::vector<int> test_set = {42, 1, -10, 4242};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  ASSERT_EQ(myvec.size(), libvec.size());
}

// max_size()
TEST(VectorTest, int_basic_max_size) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  ASSERT_EQ(myvec.max_size(), libvec.max_size());
}

// reserve()
TEST(VectorTest, int_basic_reserve) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  std::size_t size = 100;
  myvec.reserve(size);
  libvec.reserve(size);

  ASSERT_EQ(myvec.size(), libvec.size());
}

TEST(VectorTest, int_basic_reserve2) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  std::size_t size = 100;
  myvec.reserve(size);
  libvec.reserve(size);
  size = 10;
  myvec.reserve(size);
  libvec.reserve(size);

  ASSERT_EQ(myvec.size(), libvec.size());
}

// TODO capacity()

// TODO Iterators
// begin()
// end()
// rbegin()
// rend()

// TODO Modifiers
// clear()
TEST(VectorTest, int_basic_clear) {
  ft::vector<int> myvec;
  std::vector<int> libvec;

  myvec.clear();
  libvec.clear();

  ASSERT_EQ(myvec.size(), libvec.size());
}

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
TEST(VectorTest, int_basic_pop_back) {
  std::vector<int> test_set = {100};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  myvec.pop_back();
  libvec.pop_back();

  ASSERT_EQ(myvec.size(), libvec.size());
  ASSERT_EQ(myvec.empty(), libvec.empty());
}

TEST(VectorTest, int_basic_pop_back2) {
  std::vector<int> test_set = {100, 42};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  myvec.pop_back();
  libvec.pop_back();

  ASSERT_EQ(myvec.size(), libvec.size());
  for (std::vector<int>::size_type i = 0; i < test_set.size() - 1; ++i) {
    ASSERT_EQ(myvec.at(i), libvec.at(i));
  }
}

TEST(VectorTest, int_basic_pop_back3) {
  std::vector<int> test_set = {100, 42, -10};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  myvec.pop_back();
  libvec.pop_back();

  ASSERT_EQ(myvec.size(), libvec.size());
  for (std::vector<int>::size_type i = 0; i < test_set.size() - 1; ++i) {
    ASSERT_EQ(myvec.at(i), libvec.at(i));
  }
}

// resize()
TEST(VectorTest, int_basic_resize) {
  std::vector<int> test_set = {100};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  myvec.resize(1);
  libvec.resize(1);

  ASSERT_EQ(myvec.size(), libvec.size());
  for (std::vector<int>::size_type i = 0; i < libvec.size(); ++i) {
    ASSERT_EQ(myvec.at(i), libvec.at(i));
  }
}

TEST(VectorTest, int_basic_resize2) {
  std::vector<int> test_set = {100};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  myvec.resize(100);
  libvec.resize(100);

  ASSERT_EQ(myvec.size(), libvec.size());
  for (std::vector<int>::size_type i = 0; i < libvec.size(); ++i) {
    ASSERT_EQ(myvec.at(i), libvec.at(i));
  }
}

TEST(VectorTest, int_basic_resize3) {
  std::vector<int> test_set = {100, 42, -1, -100, 4242};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  myvec.resize(1);
  libvec.resize(1);

  ASSERT_EQ(myvec.size(), libvec.size());
  for (std::vector<int>::size_type i = 0; i < libvec.size(); ++i) {
    ASSERT_EQ(myvec.at(i), libvec.at(i));
  }
}

TEST(VectorTest, int_basic_resize4) {
  std::vector<int> test_set = {100, 42, -1, -100, 4242};

  ft::vector<int> myvec;
  std::vector<int> libvec;

  for (std::vector<int>::iterator itr = test_set.begin(); itr != test_set.end();
       ++itr) {
    myvec.push_back(*itr);
    libvec.push_back(*itr);
  }

  myvec.resize(0);
  libvec.resize(0);

  ASSERT_EQ(myvec.size(), libvec.size());
  ASSERT_EQ(myvec.empty(), libvec.empty());
}

// swap()
TEST(VectorTest, int_basic_swap) {
  std::vector<int> test_set1 = {2};
  std::vector<int> test_set2 = {2};

  ft::vector<int> myvec;
  ft::vector<int> other;

  for (std::vector<int>::iterator itr = test_set1.begin();
       itr != test_set1.end(); ++itr) {
    myvec.push_back(*itr);
  }
  for (std::vector<int>::iterator itr = test_set2.begin();
       itr != test_set2.end(); ++itr) {
    other.push_back(*itr);
  }

  myvec.swap(other);

  ASSERT_EQ(myvec.size(), test_set2.size());
  for (std::vector<int>::size_type i = 0; i < test_set2.size(); ++i) {
    ASSERT_EQ(myvec.at(i), test_set2.at(i));
  }
  ASSERT_EQ(other.size(), test_set1.size());
  for (std::vector<int>::size_type i = 0; i < test_set1.size(); ++i) {
    ASSERT_EQ(other.at(i), test_set1.at(i));
  }
}

// TODO Non-member functions
// operator==
// operator!=
// operator<
// operator<=
// operator>
// operator>=
// std::swap(std::vector)
