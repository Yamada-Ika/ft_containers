#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <map>
#include <utility>
#include "set.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "pair.hpp"

#include <cassert>
#include <memory>
#include <limits>
#include <stdio.h>
#include <unistd.h>

struct ModCmp {
  bool operator()(const int lhs, const int rhs) const {
    return (lhs % 97) < (rhs % 97);
  }
};

template <typename T1, typename T2>
static void assert_eq(T1 expected, T2 got, const char* filename, int lineno) {
  if (expected != got) {
    dprintf(STDERR_FILENO, "%s:%d assertion failed\n", filename, lineno);
  }
  assert(expected == got);
}

template <typename T1, typename T2>
static void assert_neq(T1 expected, T2 got, const char* filename, int lineno) {
  if (expected == got) {
    dprintf(STDERR_FILENO, "%s:%d assertion failed\n", filename, lineno);
  }
  assert(expected != got);
}

#define ASSERT_EQ(exp, got) assert_eq(exp, got, __FILE__, __LINE__)
#define ASSERT_NEQ(exp, got) assert_neq(exp, got, __FILE__, __LINE__)

template <typename T>
static void assertVector(std::vector<T>& libvec, ft::vector<T>& myvec) {
  ASSERT_EQ(libvec.size(), myvec.size());
  for (size_t i = 0; i < libvec.size(); ++i) {
    ASSERT_EQ(libvec[i], myvec[i]);
  }
}

template <typename T>
static void prepareVectorTestData(std::vector<T>& libvector,
                                  ft::vector<T>& myvector,
                                  const std::vector<T>& data) {
  for (typename std::vector<T>::const_iterator itr = data.begin();
       itr != data.end(); ++itr) {
    libvector.push_back(*itr);
    myvector.push_back(*itr);
  }
}

template <typename T>
static void prepareDequeTestData(std::deque<T>& libdeq, ft::deque<T>& mydeq,
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

template <class T>
class AlwaysThrowAllocator {
public:
  typedef std::size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T value_type;

  template <typename U>
  struct rebind {
    typedef AlwaysThrowAllocator<U> other;
  };

  AlwaysThrowAllocator() {}
  AlwaysThrowAllocator(const AlwaysThrowAllocator&) {}
  template <typename U>
  AlwaysThrowAllocator(const AlwaysThrowAllocator<U>&) {}
  ~AlwaysThrowAllocator() {}
  pointer allocate(size_type n, const void* hint = 0) {
    throw std::runtime_error("AlwaysThrowAllocator throw exception !");
  }
  void deallocate(pointer p, size_type num) { ::operator delete(p); }
  void construct(pointer p, const T& value) { new ((void*)p) T(value); }
  void destroy(pointer p) { ((T*)p)->~T(); }
  pointer address(reference value) const { return &value; }
  const_pointer address(const_reference value) const { return &value; }
  size_type max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }
};

void test_map() {
  // constructor (1)
  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ASSERT_EQ(ftmp.size(), stdmp.size());
  }

  // constructor (2)
  {
    ft::greater<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::map<int, int, ft::greater<int> > mymp(ftcomp, ftalloc);

    std::greater<int> libcomp;
    std::allocator<int> liballoc;
    std::map<int, int, std::greater<int> > libmp(libcomp, liballoc);

    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(2, 1));
    mymp.insert(ft::make_pair(3, 1));
    mymp.insert(ft::make_pair(4, 1));
    mymp.insert(ft::make_pair(5, 1));
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(2, 1));
    libmp.insert(std::make_pair(3, 1));
    libmp.insert(std::make_pair(4, 1));
    libmp.insert(std::make_pair(5, 1));

    ft::map<int, int, ft::greater<int> >::iterator myitr = mymp.begin();
    std::map<int, int, ft::greater<int> >::iterator libitr = libmp.begin();

    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;

    ASSERT_EQ(mymp.size(), libmp.size());

    ASSERT_EQ(libitr, libmp.end());
    ASSERT_EQ(myitr, mymp.end());
  }

  // constructor (2)
  {
    try {
      ft::greater<int> ftcomp;
      AlwaysThrowAllocator<int> myalloc;
      ft::map<int, int, ft::greater<int>, AlwaysThrowAllocator<int> > mymp(
          ftcomp, myalloc);
    } catch (const std::runtime_error& e) {
      // do nothing
      ASSERT_EQ(std::string(e.what()),
                std::string("AlwaysThrowAllocator throw exception !"));
    } catch (const std::exception& e) {
      // unknown exception
      printf("[ERROR] unknown exception : %s:%d\n", __FILE__, __LINE__);
      printf("   caused by %s\n", e.what());
      std::exit(1);
    }

    // try {
    //   std::greater<int> libcomp;
    //   AlwaysThrowAllocator<int> myalloc;
    //   std::map<int, int, std::greater<int>, AlwaysThrowAllocator<int> > libmp(
    //       libcomp, myalloc);
    // } catch (const std::runtime_error& e) {
    //   // do nothing
    //   ASSERT_EQ(e.what(), "AlwaysThrowAllocator throw exception !");
    // } catch (const std::exception& e) {
    //   // unknown exception
    //   printf("[ERROR] unknown exception : %s:%d\n", __FILE__, __LINE__);
    //   printf("   caused by %s\n", e.what());
    //   std::exit(1);
    // }
  }

  // (3)
  {
    ft::greater<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::map<int, int, ft::greater<int> > myorigin(ftcomp, ftalloc);
    myorigin.insert(ft::make_pair(1, 1));
    myorigin.insert(ft::make_pair(2, 2));
    myorigin.insert(ft::make_pair(3, 3));

    ft::map<int, int, ft::greater<int> > mymp(myorigin.begin(), myorigin.end(),
                                              ftcomp, ftalloc);

    std::greater<int> libcomp;
    std::allocator<int> stdalloc;
    std::map<int, int, std::greater<int> > liborigin(libcomp, stdalloc);
    liborigin.insert(std::make_pair(1, 1));
    liborigin.insert(std::make_pair(2, 2));
    liborigin.insert(std::make_pair(3, 3));

    std::map<int, int, std::greater<int> > libmp(
        liborigin.begin(), liborigin.end(), libcomp, stdalloc);

    ft::map<int, int, ft::greater<int> >::iterator myitr = mymp.begin();
    std::map<int, int, ft::greater<int> >::iterator libitr = libmp.begin();

    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;

    ASSERT_EQ(mymp.size(), libmp.size());

    ASSERT_EQ(libitr, libmp.end());
    ASSERT_EQ(myitr, mymp.end());
  }

  // // (3)
  // {
  //   try {
  //     ft::greater<int> ftcomp;
  //     std::allocator<int> ftalloc;
  //     ft::map<int, int, ft::greater<int> > myorigin(ftcomp, ftalloc);
  //     myorigin.insert(ft::make_pair(1, 1));
  //     myorigin.insert(ft::make_pair(2, 2));
  //     myorigin.insert(ft::make_pair(3, 3));

  //     AlwaysThrowAllocator<int> myalloc;
  //     ft::map<int, int, ft::greater<int>, AlwaysThrowAllocator<int> > mymp(
  //         myorigin.begin(), myorigin.end(), ftcomp, myalloc);
  //   } catch (const std::runtime_error& e) {
  //     // do nothing
  //     ASSERT_EQ(e.what(), "AlwaysThrowAllocator throw exception !");
  //   } catch (const std::exception& e) {
  //     // unknown exception
  //     printf("[ERROR] unknown exception : %s:%d\n", __FILE__, __LINE__);
  //     printf("   caused by %s\n", e.what());
  //     std::exit(1);
  //   }
  // }

  // (4)
  {
    ft::map<int, int> myorg;
    myorg.insert(ft::make_pair(1, 2));
    myorg.insert(ft::make_pair(2, 2));
    myorg.insert(ft::make_pair(3, 2));
    ft::map<int, int> mymp(myorg);

    std::map<int, int> liborg;
    liborg.insert(std::make_pair(1, 2));
    liborg.insert(std::make_pair(2, 2));
    liborg.insert(std::make_pair(3, 2));
    std::map<int, int> libmp(liborg);

    ft::map<int, int>::iterator myitr = mymp.begin();
    std::map<int, int>::iterator libitr = libmp.begin();

    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;

    ASSERT_EQ(mymp.size(), libmp.size());

    ASSERT_EQ(libitr, libmp.end());
    ASSERT_EQ(myitr, mymp.end());
  }

  // destructor
  {
    ft::map<int, int> mymp;
    std::map<int, int> libmp;
  }

  // operator =
  {
    ft::map<int, int> myorigin;
    myorigin.insert(ft::make_pair(1, 1));
    std::map<int, int> liborigin;
    liborigin.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp;
    mymp = myorigin;
    std::map<int, int> libmp;
    libmp = liborigin;

    ASSERT_EQ(mymp.size(), libmp.size());

    ft::map<int, int>::iterator myitr = mymp.begin();
    std::map<int, int>::iterator libitr = libmp.begin();

    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(libitr, libmp.end());
    ASSERT_EQ(myitr, mymp.end());
  }

  {
    ft::map<int, int> myorigin;
    myorigin.insert(ft::make_pair(1, 1));
    myorigin.insert(ft::make_pair(2, 1));
    myorigin.insert(ft::make_pair(3, 1));
    myorigin.insert(ft::make_pair(4, 1));
    std::map<int, int> liborigin;
    liborigin.insert(std::make_pair(1, 1));
    liborigin.insert(std::make_pair(2, 1));
    liborigin.insert(std::make_pair(3, 1));
    liborigin.insert(std::make_pair(4, 1));
    ft::map<int, int> mymp;
    mymp = myorigin;
    std::map<int, int> libmp;
    libmp = liborigin;

    ASSERT_EQ(mymp.size(), libmp.size());

    ft::map<int, int>::iterator myitr = mymp.begin();
    std::map<int, int>::iterator libitr = libmp.begin();

    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(myitr->first, libitr->first);
    ASSERT_EQ(myitr->second, libitr->second);
    ++myitr;
    ++libitr;
    ASSERT_EQ(libitr, libmp.end());
    ASSERT_EQ(myitr, mymp.end());
  }

  // get_allocator
  {
    ft::greater<int> mycomp;
    std::allocator<int> alloc;
    ft::map<int, int, ft::greater<int> > mymp(mycomp, alloc);

    std::greater<int> libcomp;
    std::map<int, int, std::greater<int> > libmp(libcomp, alloc);

    ASSERT_EQ(mymp.get_allocator(), libmp.get_allocator());
  }

  // get_allocator const
  {
    ft::greater<int> mycomp;
    std::allocator<int> alloc;
    const ft::map<int, int, ft::greater<int> > mymp(mycomp, alloc);

    std::greater<int> libcomp;
    const std::map<int, int, std::greater<int> > libmp(libcomp, alloc);

    ASSERT_EQ(mymp.get_allocator(), libmp.get_allocator());
  }

  // at
  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    ASSERT_EQ(libmp.at(1), mymp.at(1));
  }

  {
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

  {
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

  {
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

  // at const
  {
    std::map<int, int> liborg;
    liborg.insert(std::make_pair(1, 1));
    liborg.insert(std::make_pair(2, 2));
    liborg.insert(std::make_pair(3, 3));
    const std::map<int, int> libmp(liborg.begin(), liborg.end());
    ft::map<int, int> myorg;
    myorg.insert(ft::make_pair(1, 1));
    myorg.insert(ft::make_pair(2, 2));
    myorg.insert(ft::make_pair(3, 3));
    const ft::map<int, int> mymp(myorg.begin(), myorg.end());
    ASSERT_EQ(libmp.at(1), mymp.at(1));
    ASSERT_EQ(libmp.at(2), mymp.at(2));
    ASSERT_EQ(libmp.at(3), mymp.at(3));
  }

  // at exception
  {
    bool has_exception_occured = false;
    try {
      ft::map<int, int> mymp;
      mymp.at(100);
    } catch (const std::out_of_range& e) {
      // do nothing
      has_exception_occured = true;
    } catch (const std::exception& e) {
      std::exit(1);
    }
    ASSERT_EQ(has_exception_occured, true);
    has_exception_occured = false;
    try {
      std::map<int, int> libmp;
      libmp.at(100);
    } catch (const std::out_of_range& e) {
      // do nothing
      has_exception_occured = true;
    } catch (const std::exception& e) {
      std::exit(1);
    }
    ASSERT_EQ(has_exception_occured, true);
  }

  // operator[]
  {
    std::map<int, int> libmp;
    std::pair<int, int> libpair(1, 1);
    libmp.insert(libpair);
    ft::map<int, int> mymp;
    ft::pair<int, int> mypair(1, 1);
    mymp.insert(mypair);
    ASSERT_EQ(libmp[1], mymp[1]);
  }

  {
    std::map<int, int> libmp;
    std::pair<int, int> libpair(1, 1);
    libmp.insert(libpair);
    ft::map<int, int> mymp;
    ft::pair<int, int> mypair(1, 1);
    mymp.insert(mypair);
    ASSERT_EQ(libmp.size(), mymp.size());
    ASSERT_EQ(libmp[1], mymp[1]);
    ASSERT_EQ(libmp[2], mymp[2]);
  }

  {
    std::map<int, int> libmp;
    std::pair<int, int> libpair(1, 1);
    libmp.insert(libpair);
    ft::map<int, int> mymp;
    ft::pair<int, int> mypair(1, 1);
    mymp.insert(mypair);
    ASSERT_EQ(libmp.size(), mymp.size());
    ASSERT_EQ(libmp[1], mymp[1]);
    ASSERT_EQ(libmp[2], mymp[2]);
    ASSERT_EQ(libmp[3], mymp[3]);
  }

  {
    std::map<int, int> libmp;
    std::pair<int, int> libpair(1, 1);
    libmp.insert(libpair);
    ft::map<int, int> mymp;
    ft::pair<int, int> mypair(1, 1);
    mymp.insert(mypair);
    ASSERT_EQ(libmp.size(), mymp.size());
    ASSERT_EQ(libmp[1], mymp[1]);
    ASSERT_EQ(libmp[2], mymp[2]);
  }

  // operator [] does not throw exception
  {
    bool has_exception_occured = false;
    try {
      ft::map<int, int> mymp;
      mymp[100];
    } catch (const std::out_of_range& e) {
      // do nothing
      has_exception_occured = true;
    } catch (const std::exception& e) {
      std::exit(1);
    }
    ASSERT_EQ(has_exception_occured, false);
    has_exception_occured = false;
    try {
      std::map<int, int> libmp;
      libmp[100];
    } catch (const std::out_of_range& e) {
      // do nothing
    } catch (const std::exception& e) {
      std::exit(1);
    }
    ASSERT_EQ(has_exception_occured, false);
  }

  // begin
  {
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

  {
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

  {
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

  // begin const (immutable instance)
  {
    std::map<int, int> liborg;
    liborg.insert(std::make_pair(1, 1));
    const std::map<int, int> libmp(liborg.begin(), liborg.end());

    ft::map<int, int> myorg;
    myorg.insert(ft::make_pair(1, 1));
    const ft::map<int, int> mymp(myorg.begin(), myorg.end());

    std::map<int, int>::const_iterator libitr = libmp.begin();
    ft::map<int, int>::const_iterator myitr = mymp.begin();
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
  }

  {
    std::map<int, int> liborg;
    liborg.insert(std::make_pair(1, 1));
    liborg.insert(std::make_pair(2, 1));
    const std::map<int, int> libmp(liborg.begin(), liborg.end());

    ft::map<int, int> myorg;
    myorg.insert(ft::make_pair(1, 1));
    myorg.insert(ft::make_pair(2, 1));
    const ft::map<int, int> mymp(myorg.begin(), myorg.end());

    std::map<int, int>::const_iterator libitr = libmp.begin();
    ft::map<int, int>::const_iterator myitr = mymp.begin();
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    libitr++;
    myitr++;
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
  }

  {
    std::map<int, int> liborg;
    liborg.insert(std::make_pair(1, 1));
    liborg.insert(std::make_pair(2, 1));
    const std::map<int, int> libmp(liborg.begin(), liborg.end());

    ft::map<int, int> myorg;
    myorg.insert(ft::make_pair(1, 1));
    myorg.insert(ft::make_pair(2, 1));
    const ft::map<int, int> mymp(myorg.begin(), myorg.end());

    std::map<int, int>::const_iterator libitr = libmp.begin();
    ft::map<int, int>::const_iterator myitr = mymp.begin();
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
  }

  // // begin const (mutable instance)
  // {
  //   std::map<int, int> libmp;
  //   libmp.insert(std::make_pair(1, 1));
  //   ft::map<int, int> mymp;
  //   mymp.insert(ft::make_pair(1, 1));
  //   std::map<int, int>::const_iterator libitr = libmp.begin();
  //   ft::map<int, int>::const_iterator myitr = mymp.begin();
  //   ASSERT_EQ(libitr->first, myitr->first);
  //   ASSERT_EQ(libitr->second, myitr->second);
  //   ++libitr;
  //   ++myitr;
  //   ASSERT_EQ(libitr->first, myitr->first);
  //   ASSERT_EQ(libitr->second, myitr->second);
  // }

  // end
  {
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

  {
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

  // end const
  {
    std::map<int, int> liborg;
    liborg.insert(std::make_pair(1, 1));
    liborg.insert(std::make_pair(2, 1));
    const std::map<int, int> libmp(liborg.begin(), liborg.end());

    ft::map<int, int> myorg;
    myorg.insert(ft::make_pair(1, 1));
    myorg.insert(ft::make_pair(2, 1));
    const ft::map<int, int> mymp(myorg.begin(), myorg.end());

    std::map<int, int>::const_iterator libitr = libmp.end();
    ft::map<int, int>::const_iterator myitr = mymp.end();
    libitr--;
    myitr--;
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
  }

  // rbegin
  {
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

  {
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

  // // rbegin const
  // {
  //   std::map<int, int> liborigin;
  //   liborigin.insert(std::make_pair(1, 1));
  //   ft::map<int, int> myorigin;
  //   myorigin.insert(ft::make_pair(1, 1));
  //   const std::map<int, int> libmp(liborigin.begin(), liborigin.end());
  //   const ft::map<int, int> mymp(myorigin.begin(), myorigin.end());
  //   std::map<int, int>::const_reverse_iterator libitr = libmp.rbegin();
  //   ft::map<int, int>::const_reverse_iterator myitr = mymp.rbegin();
  //   ASSERT_EQ(libitr->first, myitr->first);
  //   ASSERT_EQ(libitr->second, myitr->second);
  //   ++libitr;
  //   ++myitr;
  //   ASSERT_EQ(libitr, libmp.rend());
  //   ASSERT_EQ(myitr, mymp.rend());
  // }

  // rend
  {
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

  {
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

  // // rend const
  // {
  //   std::map<int, int> liborigin;
  //   liborigin.insert(std::make_pair(1, 1));
  //   ft::map<int, int> myorigin;
  //   myorigin.insert(ft::make_pair(1, 1));
  //   const std::map<int, int> libmp(liborigin.begin(), liborigin.end());
  //   const ft::map<int, int> mymp(myorigin.begin(), myorigin.end());
  //   std::map<int, int>::const_reverse_iterator libitr = libmp.rend();
  //   ft::map<int, int>::const_reverse_iterator myitr = mymp.rend();
  //   --libitr;
  //   --myitr;
  //   ASSERT_EQ(libitr->first, myitr->first);
  //   ASSERT_EQ(libitr->second, myitr->second);
  //   ASSERT_EQ(libitr, libmp.rbegin());
  //   ASSERT_EQ(myitr, mymp.rbegin());
  // }

  // empty
  {
    std::map<int, int> libmp;
    ft::map<int, int> mymp;
    ASSERT_EQ(libmp.empty(), mymp.empty());
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    ASSERT_EQ(libmp.empty(), mymp.empty());
  }

  // empty const
  {
    const std::map<int, int> libmp;
    const ft::map<int, int> mymp;
    ASSERT_EQ(libmp.empty(), mymp.empty());
  }

  {
    std::map<int, int> libdata;
    libdata.insert(std::make_pair(1, 1));
    ft::map<int, int> mydata;
    mydata.insert(ft::make_pair(1, 1));
    const std::map<int, int> libmp(libdata.begin(), libdata.end());
    const ft::map<int, int> mymp(mydata.begin(), mydata.end());
    ASSERT_EQ(libmp.empty(), mymp.empty());
  }

  // size && insert
  {
    std::map<int, int> libmp;
    ft::map<int, int> mymp;
    ASSERT_EQ(libmp.size(), mymp.size());
  }

  {
    std::map<int, int> libmp;
    std::pair<int, int> libpair(1, 1);
    libmp.insert(libpair);
    ft::map<int, int> mymp;
    ft::pair<int, int> mypair(1, 1);
    mymp.insert(mypair);
    ASSERT_EQ(libmp.size(), mymp.size());
  }

  {
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

  {
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

  {
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

  {
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

  // size const
  {
    const std::map<int, int> libmp;
    const ft::map<int, int> mymp;
    ASSERT_EQ(libmp.size(), mymp.size());
  }

  {
    std::map<int, int> libdata;
    libdata.insert(std::make_pair(1, 1));
    ft::map<int, int> mydata;
    mydata.insert(ft::make_pair(1, 1));
    const std::map<int, int> libmp(libdata.begin(), libdata.end());
    const ft::map<int, int> mymp(mydata.begin(), mydata.end());
    ASSERT_EQ(libmp.size(), mymp.size());
  }

  // max_size
  {
    std::map<int, int> libmp;
    ft::map<int, int> mymp;
    ASSERT_EQ(libmp.max_size(), mymp.max_size());
  }

  // max_size const
  {
    const std::map<int, int> libmp;
    const ft::map<int, int> mymp;
    ASSERT_EQ(libmp.max_size(), mymp.max_size());
  }

  // clear
  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));

    libmp.clear();
    mymp.clear();
    ASSERT_EQ(libmp.size(), mymp.size());
    ASSERT_EQ(libmp.empty(), mymp.empty());
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(2, 1));
    libmp.insert(std::make_pair(3, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(2, 1));
    mymp.insert(ft::make_pair(3, 1));

    libmp.clear();
    mymp.clear();
    ASSERT_EQ(libmp.size(), mymp.size());
    ASSERT_EQ(libmp.empty(), mymp.empty());
  }

  // insert 1
  {
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

    std::map<int, int>::iterator stditr = libmp.begin();
    ft::map<int, int>::iterator ftitr = mymp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, libmp.end());
    ASSERT_EQ(ftitr, mymp.end());
  }

  {
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

    std::map<int, int>::iterator stditr = libmp.begin();
    ft::map<int, int>::iterator ftitr = mymp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, libmp.end());
    ASSERT_EQ(ftitr, mymp.end());
  }

  {
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

    std::map<int, int>::iterator stditr = libmp.begin();
    ft::map<int, int>::iterator ftitr = mymp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, libmp.end());
    ASSERT_EQ(ftitr, mymp.end());
  }

  {
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

    std::map<int, int>::iterator stditr = libmp.begin();
    ft::map<int, int>::iterator ftitr = mymp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, libmp.end());
    ASSERT_EQ(ftitr, mymp.end());
  }

  // insert 2
  // insert 3
  {
    std::map<int, int> stddata;
    stddata.insert(std::make_pair(-1, -1));
    stddata.insert(std::make_pair(2, 2));
    stddata.insert(std::make_pair(2, 100));
    stddata.insert(std::make_pair(2, 1));
    ft::map<int, int> ftdata;
    ftdata.insert(ft::make_pair(-1, -1));
    ftdata.insert(ft::make_pair(2, 2));
    ftdata.insert(ft::make_pair(2, 100));
    ftdata.insert(ft::make_pair(2, 1));

    std::map<int, int> stdmp(stddata.begin(), stddata.end());
    ft::map<int, int> ftmp(ftdata.begin(), ftdata.end());

    std::map<int, int>::iterator stditr = stdmp.begin();
    ft::map<int, int>::iterator ftitr = ftmp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  // erase 1
  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(2, 2));
    libmp.insert(std::make_pair(-2, -2));
    std::map<int, int>::iterator libitr1 = libmp.begin();

    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(2, 2));
    mymp.insert(ft::make_pair(-2, -2));
    ft::map<int, int>::iterator myitr1 = mymp.begin();

    std::map<int, int>::iterator libret = libmp.erase(libitr1);
    ft::map<int, int>::iterator myret = mymp.erase(myitr1);

    ASSERT_EQ(libret->first, myret->first);
    ASSERT_EQ(libret->second, myret->second);
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
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(2, 2));
    libmp.insert(std::make_pair(-2, -2));
    std::map<int, int>::iterator libitr1 = libmp.begin();
    ++libitr1;

    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(2, 2));
    mymp.insert(ft::make_pair(-2, -2));
    ft::map<int, int>::iterator myitr1 = mymp.begin();
    ++myitr1;

    std::map<int, int>::iterator libret = libmp.erase(libitr1);
    ft::map<int, int>::iterator myret = mymp.erase(myitr1);

    ASSERT_EQ(libret->first, myret->first);
    ASSERT_EQ(libret->second, myret->second);
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
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(2, 2));
    libmp.insert(std::make_pair(-2, -2));
    std::map<int, int>::iterator libitr1 = libmp.begin();
    std::map<int, int>::iterator libitr2 = libmp.end();

    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(2, 2));
    mymp.insert(ft::make_pair(-2, -2));
    ft::map<int, int>::iterator myitr1 = mymp.begin();
    ft::map<int, int>::iterator myitr2 = mymp.end();

    std::map<int, int>::iterator libret = libmp.erase(libitr1, libitr2);
    ft::map<int, int>::iterator myret = mymp.erase(myitr1, myitr2);

    ASSERT_EQ(libmp.size(), mymp.size());
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(2, 2));
    libmp.insert(std::make_pair(3, 3));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(2, 2));
    mymp.insert(ft::make_pair(3, 3));

    ASSERT_EQ(libmp.erase(2), mymp.erase(2));
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
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(10, 1));
    libmp.insert(std::make_pair(5, 1));
    libmp.insert(std::make_pair(15, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(10, 1));
    mymp.insert(ft::make_pair(5, 1));
    mymp.insert(ft::make_pair(15, 1));

    ASSERT_EQ(libmp.erase(5), mymp.erase(5));
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

  // erase 2
  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(10, 1));
    stdmp.insert(std::make_pair(5, 1));
    stdmp.insert(std::make_pair(15, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(10, 1));
    ftmp.insert(ft::make_pair(5, 1));
    ftmp.insert(ft::make_pair(15, 1));

    std::map<int, int>::iterator stdret =
        stdmp.erase(stdmp.begin(), stdmp.end());
    ft::map<int, int>::iterator ftret = ftmp.erase(ftmp.begin(), ftmp.end());

    ASSERT_EQ(stdmp.size(), ftmp.size());
    ASSERT_EQ(stdmp.empty(), ftmp.empty());
  }

  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(10, 1));
    stdmp.insert(std::make_pair(5, 1));
    stdmp.insert(std::make_pair(15, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(10, 1));
    ftmp.insert(ft::make_pair(5, 1));
    ftmp.insert(ft::make_pair(15, 1));

    std::map<int, int>::iterator stdret =
        stdmp.erase(stdmp.begin(), ++stdmp.begin());
    ft::map<int, int>::iterator ftret =
        ftmp.erase(ftmp.begin(), ++ftmp.begin());

    ASSERT_EQ(stdmp.size(), ftmp.size());

    std::map<int, int>::iterator stditr = stdmp.begin();
    ft::map<int, int>::iterator ftitr = ftmp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(10, 1));
    stdmp.insert(std::make_pair(5, 1));
    stdmp.insert(std::make_pair(15, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(10, 1));
    ftmp.insert(ft::make_pair(5, 1));
    ftmp.insert(ft::make_pair(15, 1));

    std::map<int, int>::iterator stditr = stdmp.begin();
    ft::map<int, int>::iterator ftitr = ftmp.begin();
    ++stditr;
    ++ftitr;

    std::map<int, int>::iterator stdret = stdmp.erase(stditr, ++stditr);
    ft::map<int, int>::iterator ftret = ftmp.erase(ftitr, ++ftitr);

    ASSERT_EQ(stdmp.size(), ftmp.size());

    stditr = stdmp.begin();
    ftitr = ftmp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(10, 1));
    stdmp.insert(std::make_pair(5, 1));
    stdmp.insert(std::make_pair(15, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(10, 1));
    ftmp.insert(ft::make_pair(5, 1));
    ftmp.insert(ft::make_pair(15, 1));

    std::map<int, int>::iterator stditr = stdmp.begin();
    ft::map<int, int>::iterator ftitr = ftmp.begin();
    ++stditr;
    ++ftitr;
    ++stditr;
    ++ftitr;

    std::map<int, int>::iterator stdret = stdmp.erase(stditr, ++stditr);
    ft::map<int, int>::iterator ftret = ftmp.erase(ftitr, ++ftitr);

    ASSERT_EQ(stdmp.size(), ftmp.size());

    stditr = stdmp.begin();
    ftitr = ftmp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(10, 1));
    stdmp.insert(std::make_pair(5, 1));
    stdmp.insert(std::make_pair(15, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(10, 1));
    ftmp.insert(ft::make_pair(5, 1));
    ftmp.insert(ft::make_pair(15, 1));

    std::map<int, int>::iterator stditr = stdmp.begin();
    ft::map<int, int>::iterator ftitr = ftmp.begin();
    ++stditr;
    ++ftitr;
    ++stditr;
    ++ftitr;
    ++stditr;
    ++ftitr;

    std::map<int, int>::iterator stdret = stdmp.erase(stditr, ++stditr);
    ft::map<int, int>::iterator ftret = ftmp.erase(ftitr, ++ftitr);

    ASSERT_EQ(stdmp.size(), ftmp.size());

    stditr = stdmp.begin();
    ftitr = ftmp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(10, 1));
    stdmp.insert(std::make_pair(5, 1));
    stdmp.insert(std::make_pair(15, 1));
    stdmp.insert(std::make_pair(-100, 1));
    stdmp.insert(std::make_pair(42, 1));
    stdmp.insert(std::make_pair(11111, 1));
    stdmp.insert(std::make_pair(90, 1));
    stdmp.insert(std::make_pair(-40, 1));
    stdmp.insert(std::make_pair(-10, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(10, 1));
    ftmp.insert(ft::make_pair(5, 1));
    ftmp.insert(ft::make_pair(15, 1));
    ftmp.insert(ft::make_pair(-100, 1));
    ftmp.insert(ft::make_pair(42, 1));
    ftmp.insert(ft::make_pair(11111, 1));
    ftmp.insert(ft::make_pair(90, 1));
    ftmp.insert(ft::make_pair(-40, 1));
    ftmp.insert(ft::make_pair(-10, 1));

    std::map<int, int>::iterator stditr = stdmp.begin();
    ft::map<int, int>::iterator ftitr = ftmp.begin();

    std::map<int, int>::iterator stdret = stdmp.erase(stditr, ++stditr);
    ft::map<int, int>::iterator ftret = ftmp.erase(ftitr, ++ftitr);

    ASSERT_EQ(stdmp.size(), ftmp.size());

    stditr = stdmp.begin();
    ftitr = ftmp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(10, 1));
    stdmp.insert(std::make_pair(5, 1));
    stdmp.insert(std::make_pair(15, 1));
    stdmp.insert(std::make_pair(-100, 1));
    stdmp.insert(std::make_pair(42, 1));
    stdmp.insert(std::make_pair(11111, 1));
    stdmp.insert(std::make_pair(90, 1));
    stdmp.insert(std::make_pair(-40, 1));
    stdmp.insert(std::make_pair(-10, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(10, 1));
    ftmp.insert(ft::make_pair(5, 1));
    ftmp.insert(ft::make_pair(15, 1));
    ftmp.insert(ft::make_pair(-100, 1));
    ftmp.insert(ft::make_pair(42, 1));
    ftmp.insert(ft::make_pair(11111, 1));
    ftmp.insert(ft::make_pair(90, 1));
    ftmp.insert(ft::make_pair(-40, 1));
    ftmp.insert(ft::make_pair(-10, 1));

    std::map<int, int>::iterator stditr = stdmp.begin();
    ft::map<int, int>::iterator ftitr = ftmp.begin();
    ++stditr;
    ++ftitr;
    ++stditr;
    ++ftitr;
    ++stditr;
    ++ftitr;

    std::map<int, int>::iterator stdret = stdmp.erase(stditr, ++stditr);
    ft::map<int, int>::iterator ftret = ftmp.erase(ftitr, ++ftitr);

    ASSERT_EQ(stdmp.size(), ftmp.size());

    stditr = stdmp.begin();
    ftitr = ftmp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  // erase 3
  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));

    ASSERT_EQ(libmp.erase(1), mymp.erase(1));
    ASSERT_EQ(libmp.size(), mymp.size());
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));

    size_t libret = libmp.erase(2);
    size_t myret = mymp.erase(2);

    ASSERT_EQ(libret, myret);
    ASSERT_EQ(libmp.size(), mymp.size());
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(10, 1));
    libmp.insert(std::make_pair(5, 1));
    libmp.insert(std::make_pair(15, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(10, 1));
    mymp.insert(ft::make_pair(5, 1));
    mymp.insert(ft::make_pair(15, 1));

    //              1b
    //       +------+------+
    //      5b             10b
    //                 +---+---+
    //                        15r

    ASSERT_EQ(libmp.erase(5), mymp.erase(5));
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

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(10, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(10, 1));

    ASSERT_EQ(libmp.erase(10), mymp.erase(10));
    ASSERT_EQ(libmp.size(), mymp.size());

    std::map<int, int>::iterator libitr = libmp.begin();
    ft::map<int, int>::iterator myitr = mymp.begin();

    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(-10, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(-10, 1));

    ASSERT_EQ(libmp.erase(-10), mymp.erase(-10));
    ASSERT_EQ(libmp.size(), mymp.size());

    std::map<int, int>::iterator libitr = libmp.begin();
    ft::map<int, int>::iterator myitr = mymp.begin();

    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(-10, 1));
    libmp.insert(std::make_pair(10, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(-10, 1));
    mymp.insert(ft::make_pair(10, 1));

    ASSERT_EQ(libmp.erase(-10), mymp.erase(-10));
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
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(-10, 1));
    libmp.insert(std::make_pair(10, 1));
    libmp.insert(std::make_pair(-5, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(-10, 1));
    mymp.insert(ft::make_pair(10, 1));
    mymp.insert(ft::make_pair(-5, 1));

    ASSERT_EQ(libmp.erase(-1), mymp.erase(-1));
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

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(-10, 1));
    libmp.insert(std::make_pair(10, 1));
    libmp.insert(std::make_pair(-5, 1));
    libmp.insert(std::make_pair(15, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(-10, 1));
    mymp.insert(ft::make_pair(10, 1));
    mymp.insert(ft::make_pair(-5, 1));
    mymp.insert(ft::make_pair(15, 1));

    //               1b
    //        +------+------+
    //      -5b            10b
    //   +---+---+      +---+---+
    // -10r                    15r

    //               10b
    //        +------+------+
    //      -5b            1b
    //   +---+---+      +---+---+
    // -10r                    15r

    ASSERT_EQ(libmp.erase(1), mymp.erase(1));
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
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(-10, 1));
    libmp.insert(std::make_pair(10, 1));
    libmp.insert(std::make_pair(-5, 1));
    libmp.insert(std::make_pair(15, 1));
    libmp.insert(std::make_pair(20, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(-10, 1));
    mymp.insert(ft::make_pair(10, 1));
    mymp.insert(ft::make_pair(-5, 1));
    mymp.insert(ft::make_pair(15, 1));
    mymp.insert(ft::make_pair(20, 1));

    ASSERT_EQ(libmp.erase(10), mymp.erase(10));
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
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(-10, 1));
    libmp.insert(std::make_pair(10, 1));
    libmp.insert(std::make_pair(-5, 1));
    libmp.insert(std::make_pair(15, 1));
    libmp.insert(std::make_pair(20, 1));
    libmp.insert(std::make_pair(-12, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(-10, 1));
    mymp.insert(ft::make_pair(10, 1));
    mymp.insert(ft::make_pair(-5, 1));
    mymp.insert(ft::make_pair(15, 1));
    mymp.insert(ft::make_pair(20, 1));
    mymp.insert(ft::make_pair(-12, 1));

    ASSERT_EQ(libmp.erase(-5), mymp.erase(-5));
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

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(-10, 1));
    libmp.insert(std::make_pair(10, 1));
    libmp.insert(std::make_pair(-5, 1));
    libmp.insert(std::make_pair(15, 1));
    libmp.insert(std::make_pair(20, 1));
    libmp.insert(std::make_pair(-12, 1));
    libmp.insert(std::make_pair(100, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(-10, 1));
    mymp.insert(ft::make_pair(10, 1));
    mymp.insert(ft::make_pair(-5, 1));
    mymp.insert(ft::make_pair(15, 1));
    mymp.insert(ft::make_pair(20, 1));
    mymp.insert(ft::make_pair(-12, 1));
    mymp.insert(ft::make_pair(100, 1));

    //                     1b
    //              +------+------+
    //            -10b           15r
    //         +---+---+     +---+---+
    //       -12r     -5r   10b      20b
    //                            +---+---+
    //                                   100r
    ASSERT_EQ(libmp.erase(15), mymp.erase(15));
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
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(-10, 1));
    libmp.insert(std::make_pair(-5, 1));
    libmp.insert(std::make_pair(-100, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(-10, 1));
    mymp.insert(ft::make_pair(-5, 1));
    mymp.insert(ft::make_pair(-100, 1));

    //               -5b
    //        +------+------+
    //      -10b            1b
    //    +---+---+
    // -100r

    ASSERT_EQ(libmp.erase(-10), mymp.erase(-10));
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

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(-10, 1));
    libmp.insert(std::make_pair(-5, 1));
    libmp.insert(std::make_pair(-100, 1));
    libmp.insert(std::make_pair(10, 1));
    libmp.insert(std::make_pair(12, 1));
    libmp.insert(std::make_pair(5, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(-10, 1));
    mymp.insert(ft::make_pair(-5, 1));
    mymp.insert(ft::make_pair(-100, 1));
    mymp.insert(ft::make_pair(10, 1));
    mymp.insert(ft::make_pair(12, 1));
    mymp.insert(ft::make_pair(5, 1));

    ASSERT_EQ(libmp.erase(-10), mymp.erase(-10));
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

    ASSERT_EQ(libmp.end(), libitr);
    ASSERT_EQ(mymp.end(), myitr);
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(-10, 1));
    libmp.insert(std::make_pair(-5, 1));
    libmp.insert(std::make_pair(-100, 1));
    libmp.insert(std::make_pair(10, 1));
    libmp.insert(std::make_pair(12, 1));
    libmp.insert(std::make_pair(5, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(-10, 1));
    mymp.insert(ft::make_pair(-5, 1));
    mymp.insert(ft::make_pair(-100, 1));
    mymp.insert(ft::make_pair(10, 1));
    mymp.insert(ft::make_pair(12, 1));
    mymp.insert(ft::make_pair(5, 1));

    ASSERT_EQ(libmp.erase(-10), mymp.erase(-10));
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

    ASSERT_EQ(libmp.end(), libitr);
    ASSERT_EQ(mymp.end(), myitr);

    ASSERT_EQ(libmp.erase(10), mymp.erase(10));
    ASSERT_EQ(libmp.size(), mymp.size());

    libitr = libmp.begin();
    myitr = mymp.begin();

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
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;

    ASSERT_EQ(libmp.end(), libitr);
    ASSERT_EQ(mymp.end(), myitr);

    ASSERT_EQ(libmp.erase(-100), mymp.erase(-100));
    ASSERT_EQ(libmp.size(), mymp.size());

    libitr = libmp.begin();
    myitr = mymp.begin();

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
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;

    ASSERT_EQ(libmp.end(), libitr);
    ASSERT_EQ(mymp.end(), myitr);

    ASSERT_EQ(libmp.erase(12), mymp.erase(12));
    ASSERT_EQ(libmp.size(), mymp.size());

    libitr = libmp.begin();
    myitr = mymp.begin();

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

    ASSERT_EQ(libmp.end(), libitr);
    ASSERT_EQ(mymp.end(), myitr);

    ASSERT_EQ(libmp.erase(5), mymp.erase(5));
    ASSERT_EQ(libmp.size(), mymp.size());

    libitr = libmp.begin();
    myitr = mymp.begin();

    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;

    ASSERT_EQ(libmp.end(), libitr);
    ASSERT_EQ(mymp.end(), myitr);

    ASSERT_EQ(libmp.erase(1), mymp.erase(1));
    ASSERT_EQ(libmp.size(), mymp.size());

    libitr = libmp.begin();
    myitr = mymp.begin();

    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;

    ASSERT_EQ(libmp.end(), libitr);
    ASSERT_EQ(mymp.end(), myitr);

    ASSERT_EQ(libmp.erase(-5), mymp.erase(-5));
    ASSERT_EQ(libmp.size(), mymp.size());
    ASSERT_EQ(libmp.empty(), mymp.empty());
  }

  // swap

  // count
  {
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    ASSERT_EQ(mymp.count(1), 1);
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    ASSERT_EQ(libmp.count(1), mymp.count(1));
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    ASSERT_EQ(libmp.count(2), mymp.count(2));
  }

  {
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
  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    std::map<int, int>::iterator libitr = libmp.find(1);
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    ft::map<int, int>::iterator myitr = mymp.find(1);
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(42, 1));
    std::map<int, int>::iterator libitr = libmp.find(42);
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(42, 1));
    ft::map<int, int>::iterator myitr = mymp.find(42);
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
  }

  {
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

  {
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

  {
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

  {
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

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    ASSERT_EQ(libmp.find(2), libmp.end());
    ASSERT_EQ(mymp.find(2), mymp.end());
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(2, 1));
    libmp.insert(std::make_pair(3, 1));
    libmp.insert(std::make_pair(4, 1));
    libmp.insert(std::make_pair(5, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(2, 1));
    mymp.insert(ft::make_pair(3, 1));
    mymp.insert(ft::make_pair(4, 1));
    mymp.insert(ft::make_pair(5, 1));
    ASSERT_EQ(libmp.find(42), libmp.end());
    ASSERT_EQ(mymp.find(42), mymp.end());
  }

  // swap
  {
    std::map<int, int> stdmp1;
    stdmp1.insert(std::make_pair(2, 2));
    std::map<int, int> stdmp2;
    stdmp2.insert(std::make_pair(1, 1));
    ft::map<int, int> ftmp1;
    ftmp1.insert(ft::make_pair(2, 2));
    ft::map<int, int> ftmp2;
    ftmp2.insert(ft::make_pair(1, 1));

    stdmp1.swap(stdmp2);
    ftmp1.swap(ftmp2);

    ASSERT_EQ(stdmp1.size(), ftmp1.size());
    ASSERT_EQ(stdmp2.size(), ftmp2.size());

    std::map<int, int>::iterator stditr1 = stdmp1.begin();
    ft::map<int, int>::iterator ftitr1 = ftmp1.begin();
    while ((stditr1 != stdmp1.end()) && (ftitr1 != ftmp1.end())) {
      ASSERT_EQ(stditr1->first, ftitr1->first);
      ASSERT_EQ(stditr1->second, ftitr1->second);
      ++stditr1;
      ++ftitr1;
    }
    ASSERT_EQ(stditr1, stdmp1.end());
    ASSERT_EQ(ftitr1, ftmp1.end());

    std::map<int, int>::iterator stditr2 = stdmp2.begin();
    ft::map<int, int>::iterator ftitr2 = ftmp2.begin();
    while ((stditr2 != stdmp2.end()) && (ftitr2 != ftmp2.end())) {
      ASSERT_EQ(stditr2->first, ftitr2->first);
      ASSERT_EQ(stditr2->second, ftitr2->second);
      ++stditr2;
      ++ftitr2;
    }
    ASSERT_EQ(stditr2, stdmp2.end());
    ASSERT_EQ(ftitr2, ftmp2.end());
  }

  {
    std::map<int, int> stdmp1;
    stdmp1.insert(std::make_pair(2, 2));
    stdmp1.insert(std::make_pair(1, 2));
    stdmp1.insert(std::make_pair(-100, 2));
    stdmp1.insert(std::make_pair(-11, 2));
    std::map<int, int> stdmp2;
    stdmp2.insert(std::make_pair(1, 1));
    stdmp2.insert(std::make_pair(-10, 1));
    stdmp2.insert(std::make_pair(2, 1));
    stdmp2.insert(std::make_pair(3, 1));
    stdmp2.insert(std::make_pair(4, 1));
    stdmp2.insert(std::make_pair(5, 1));
    stdmp2.insert(std::make_pair(6, 1));
    stdmp2.insert(std::make_pair(1000000, 1));
    ft::map<int, int> ftmp1;
    ftmp1.insert(ft::make_pair(2, 2));
    ftmp1.insert(ft::make_pair(1, 2));
    ftmp1.insert(ft::make_pair(-100, 2));
    ftmp1.insert(ft::make_pair(-11, 2));
    ft::map<int, int> ftmp2;
    ftmp2.insert(ft::make_pair(1, 1));
    ftmp2.insert(ft::make_pair(-10, 1));
    ftmp2.insert(ft::make_pair(2, 1));
    ftmp2.insert(ft::make_pair(3, 1));
    ftmp2.insert(ft::make_pair(4, 1));
    ftmp2.insert(ft::make_pair(5, 1));
    ftmp2.insert(ft::make_pair(6, 1));
    ftmp2.insert(ft::make_pair(1000000, 1));

    stdmp1.swap(stdmp2);
    ftmp1.swap(ftmp2);

    ASSERT_EQ(stdmp1.size(), ftmp1.size());
    ASSERT_EQ(stdmp2.size(), ftmp2.size());

    std::map<int, int>::iterator stditr1 = stdmp1.begin();
    ft::map<int, int>::iterator ftitr1 = ftmp1.begin();
    while ((stditr1 != stdmp1.end()) && (ftitr1 != ftmp1.end())) {
      ASSERT_EQ(stditr1->first, ftitr1->first);
      ASSERT_EQ(stditr1->second, ftitr1->second);
      ++stditr1;
      ++ftitr1;
    }
    ASSERT_EQ(stditr1, stdmp1.end());
    ASSERT_EQ(ftitr1, ftmp1.end());

    std::map<int, int>::iterator stditr2 = stdmp2.begin();
    ft::map<int, int>::iterator ftitr2 = ftmp2.begin();
    while ((stditr2 != stdmp2.end()) && (ftitr2 != ftmp2.end())) {
      ASSERT_EQ(stditr2->first, ftitr2->first);
      ASSERT_EQ(stditr2->second, ftitr2->second);
      ++stditr2;
      ++ftitr2;
    }
    ASSERT_EQ(stditr2, stdmp2.end());
    ASSERT_EQ(ftitr2, ftmp2.end());
  }

  // // count
  // {
  //   std::map<int, int> stdmp;
  //   stdmp.insert(std::make_pair(1, 1));
  //   ft::map<int, int> ftmp;
  //   ftmp.insert(ft::make_pair(1, 1));
  //   ASSERT_EQ(stdmp.count(1), ftmp.count(1));
  //   ASSERT_EQ(stdmp.count(0), ftmp.count(0));
  // }

  // {
  //   std::map<int, int> stdmp;
  //   stdmp.insert(std::make_pair(1, 1));
  //   stdmp.insert(std::make_pair(-1, 1));
  //   stdmp.insert(std::make_pair(1000, 1));
  //   ft::map<int, int> ftmp;
  //   ftmp.insert(ft::make_pair(1, 1));
  //   ftmp.insert(ft::make_pair(-1, 1));
  //   ftmp.insert(ft::make_pair(1000, 1));
  //   ASSERT_EQ(stdmp.count(1), ftmp.count(1));
  //   ASSERT_EQ(stdmp.count(0), ftmp.count(0));
  // }

  // {
  //   std::map<int, int> stddata;
  //   stddata.insert(std::make_pair(1, 1));
  //   ft::map<int, int> ftdata;
  //   ftdata.insert(ft::make_pair(1, 1));
  //   const std::map<int, int> stdmp(stddata.begin(), stddata.end());
  //   const ft::map<int, int> ftmp(ftdata.begin(), ftdata.end());
  //   ASSERT_EQ(stdmp.count(1), ftmp.count(1));
  //   ASSERT_EQ(stdmp.count(0), ftmp.count(0));
  // }

  // equal_range
  {
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

  {
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

  {
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

  // equal_range const
  {
    std::map<int, int> stddata;
    stddata.insert(std::make_pair(1, 1));
    ft::map<int, int> ftdata;
    ftdata.insert(ft::make_pair(1, 1));

    const std::map<int, int> stdmp(stddata.begin(), stddata.end());
    const ft::map<int, int> ftmp(ftdata.begin(), ftdata.end());
    std::pair<std::map<int, int>::const_iterator,
              std::map<int, int>::const_iterator>
        stdp = stdmp.equal_range(1);
    ft::pair<ft::map<int, int>::const_iterator,
             ft::map<int, int>::const_iterator>
        ftp = ftmp.equal_range(1);
    ASSERT_EQ(stdp.first->first, ftp.first->first);
    ASSERT_EQ(stdp.first->second, ftp.first->second);
    ASSERT_EQ(stdp.second == stdmp.end(), ftp.second == ftmp.end());
  }

  {
    std::map<int, int> stddata;
    stddata.insert(std::make_pair(1, 1));
    stddata.insert(std::make_pair(-10, 1));
    stddata.insert(std::make_pair(123, 1));
    stddata.insert(std::make_pair(12, 1));
    stddata.insert(std::make_pair(43, 1));
    ft::map<int, int> ftdata;
    ftdata.insert(ft::make_pair(1, 1));
    ftdata.insert(ft::make_pair(-10, 1));
    ftdata.insert(ft::make_pair(123, 1));
    ftdata.insert(ft::make_pair(12, 1));
    ftdata.insert(ft::make_pair(43, 1));

    const std::map<int, int> stdmp(stddata.begin(), stddata.end());
    const ft::map<int, int> ftmp(ftdata.begin(), ftdata.end());
    std::pair<std::map<int, int>::const_iterator,
              std::map<int, int>::const_iterator>
        stdp = stdmp.equal_range(2);
    ft::pair<ft::map<int, int>::const_iterator,
             ft::map<int, int>::const_iterator>
        ftp = ftmp.equal_range(2);
    ASSERT_EQ(stdp.first->first, ftp.first->first);
    ASSERT_EQ(stdp.first->second, ftp.first->second);
  }

  // lower_bound
  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    std::map<int, int>::iterator libitr = libmp.lower_bound(1);
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    ft::map<int, int>::iterator myitr = mymp.lower_bound(1);
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
  }

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    std::map<int, int>::iterator libitr = libmp.lower_bound(2);
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    ft::map<int, int>::iterator myitr = mymp.lower_bound(2);
    ASSERT_EQ(libitr == libmp.end(), myitr == mymp.end());
  }

  {
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

  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    libmp.insert(std::make_pair(3, 1));
    std::map<int, int>::iterator libitr = libmp.lower_bound(4);
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    mymp.insert(ft::make_pair(3, 1));
    ft::map<int, int>::iterator myitr = mymp.lower_bound(4);
    ASSERT_EQ(libitr, libmp.end());
    ASSERT_EQ(myitr, mymp.end());
  }

  {
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

  // lower_bound const
  {
    std::map<int, int> stddata;
    stddata.insert(std::make_pair(1, 1));
    ft::map<int, int> ftdata;
    ftdata.insert(ft::make_pair(1, 1));

    const std::map<int, int> stdmp(stddata.begin(), stddata.end());
    const ft::map<int, int> ftmp(ftdata.begin(), ftdata.end());
    std::map<int, int>::const_iterator libitr = stdmp.lower_bound(1);
    ft::map<int, int>::const_iterator myitr = ftmp.lower_bound(1);
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
  }

  {
    std::map<int, int> stddata;
    stddata.insert(std::make_pair(1, 1));
    stddata.insert(std::make_pair(10, 1));
    stddata.insert(std::make_pair(100, 1));
    ft::map<int, int> ftdata;
    ftdata.insert(ft::make_pair(1, 1));
    ftdata.insert(ft::make_pair(10, 1));
    ftdata.insert(ft::make_pair(100, 1));

    const std::map<int, int> stdmp(stddata.begin(), stddata.end());
    const ft::map<int, int> ftmp(ftdata.begin(), ftdata.end());
    std::map<int, int>::const_iterator libitr = stdmp.lower_bound(2);
    ft::map<int, int>::const_iterator myitr = ftmp.lower_bound(2);
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
  }

  // upper_bound
  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    std::map<int, int>::iterator libitr = libmp.upper_bound(1);
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    ft::map<int, int>::iterator myitr = mymp.upper_bound(1);
    ASSERT_EQ(libitr == libmp.end(), myitr == mymp.end());
  }

  {
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

  {
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

  {
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

  // upper_bound const
  {
    std::map<int, int> stddata;
    stddata.insert(std::make_pair(1, 1));
    ft::map<int, int> ftdata;
    ftdata.insert(ft::make_pair(1, 1));

    const std::map<int, int> stdmp(stddata.begin(), stddata.end());
    const ft::map<int, int> ftmp(ftdata.begin(), ftdata.end());

    std::map<int, int>::const_iterator libitr = stdmp.upper_bound(1);
    ft::map<int, int>::const_iterator myitr = ftmp.upper_bound(1);
    ASSERT_EQ(libitr == stdmp.end(), myitr == ftmp.end());
  }

  {
    std::map<int, int> stddata;
    stddata.insert(std::make_pair(1, 1));
    stddata.insert(std::make_pair(2, 1));
    stddata.insert(std::make_pair(-100, 1));
    stddata.insert(std::make_pair(3, 1));
    stddata.insert(std::make_pair(4, 1));
    stddata.insert(std::make_pair(10, 1));
    ft::map<int, int> ftdata;
    ftdata.insert(ft::make_pair(1, 1));
    ftdata.insert(ft::make_pair(2, 1));
    ftdata.insert(ft::make_pair(-100, 1));
    ftdata.insert(ft::make_pair(3, 1));
    ftdata.insert(ft::make_pair(4, 1));
    ftdata.insert(ft::make_pair(10, 1));

    const std::map<int, int> stdmp(stddata.begin(), stddata.end());
    const ft::map<int, int> ftmp(ftdata.begin(), ftdata.end());

    std::map<int, int>::const_iterator libitr = stdmp.upper_bound(5);
    ft::map<int, int>::const_iterator myitr = ftmp.upper_bound(5);
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
  }

  //  key_comp
  {
    std::map<int, int, ModCmp> stdmp;
    ft::map<int, int, ModCmp> ftmp;

    std::map<int, int, ModCmp>::key_compare libcomp = stdmp.key_comp();
    ft::map<int, int, ModCmp>::key_compare mycomp = ftmp.key_comp();

    ASSERT_EQ(libcomp(1, 2), mycomp(1, 2));
    ASSERT_EQ(libcomp(100, 2), mycomp(100, 2));
    ASSERT_EQ(libcomp(100, 200), mycomp(100, 200));
    ASSERT_EQ(libcomp(97, 98), mycomp(97, 98));
  }

  {
    std::map<int, int, ModCmp> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(97, 1));
    stdmp.insert(std::make_pair(100, 1));
    ft::map<int, int, ModCmp> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(97, 1));
    ftmp.insert(ft::make_pair(100, 1));

    std::map<int, int, ModCmp>::iterator stditr = stdmp.begin();
    ft::map<int, int, ModCmp>::iterator ftitr = ftmp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  //  key_comp const
  {
    const std::map<int, int, ModCmp> stdmp;
    const ft::map<int, int, ModCmp> ftmp;

    std::map<int, int, ModCmp>::key_compare libcomp = stdmp.key_comp();
    ft::map<int, int, ModCmp>::key_compare mycomp = ftmp.key_comp();

    ASSERT_EQ(libcomp(1, 2), mycomp(1, 2));
    ASSERT_EQ(libcomp(100, 2), mycomp(100, 2));
    ASSERT_EQ(libcomp(100, 200), mycomp(100, 200));
    ASSERT_EQ(libcomp(97, 98), mycomp(97, 98));
  }

  {
    std::map<int, int, ModCmp> stddata;
    stddata.insert(std::make_pair(1, 1));
    stddata.insert(std::make_pair(-100, 1));
    stddata.insert(std::make_pair(100, 1));
    stddata.insert(std::make_pair(97, 1));
    ft::map<int, int, ModCmp> ftdata;
    ftdata.insert(ft::make_pair(1, 1));
    ftdata.insert(ft::make_pair(-100, 1));
    ftdata.insert(ft::make_pair(100, 1));
    ftdata.insert(ft::make_pair(97, 1));
    const std::map<int, int, ModCmp> stdmp(stddata.begin(), stddata.end());
    const ft::map<int, int, ModCmp> ftmp(ftdata.begin(), ftdata.end());

    std::map<int, int, ModCmp>::const_iterator stditr = stdmp.begin();
    ft::map<int, int, ModCmp>::const_iterator ftitr = ftmp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  //  value_comp
  {
    std::map<int, int, ModCmp> stdmp;
    ft::map<int, int, ModCmp> ftmp;

    std::map<int, int, ModCmp>::value_compare libcomp = stdmp.value_comp();
    ft::map<int, int, ModCmp>::value_compare mycomp = ftmp.value_comp();

    ASSERT_EQ(libcomp(std::make_pair(1, 1), std::make_pair(2, 2)),
              mycomp(ft::make_pair(1, 1), ft::make_pair(2, 2)));
    ASSERT_EQ(libcomp(std::make_pair(100, 1), std::make_pair(100, 1)),
              mycomp(ft::make_pair(100, 1), ft::make_pair(100, 1)));
    ASSERT_EQ(libcomp(std::make_pair(97, 1), std::make_pair(97, 1)),
              mycomp(ft::make_pair(97, 1), ft::make_pair(97, 1)));
    ASSERT_EQ(libcomp(std::make_pair(98, 1), std::make_pair(98, 1)),
              mycomp(ft::make_pair(98, 1), ft::make_pair(98, 1)));
  }

  {
    std::map<int, int, ModCmp> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(100, 1));
    stdmp.insert(std::make_pair(98, 1));
    stdmp.insert(std::make_pair(97, 1));
    ft::map<int, int, ModCmp> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(100, 1));
    ftmp.insert(ft::make_pair(98, 1));
    ftmp.insert(ft::make_pair(97, 1));

    std::map<int, int, ModCmp>::iterator stditr = stdmp.begin();
    ft::map<int, int, ModCmp>::iterator ftitr = ftmp.begin();

    ASSERT_EQ(stdmp.size(), ftmp.size());
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  //  value_comp const
  {
    std::map<int, int, ModCmp> stddata;
    stddata.insert(std::make_pair(1, 1));
    stddata.insert(std::make_pair(100, 1));
    stddata.insert(std::make_pair(98, 1));
    stddata.insert(std::make_pair(97, 1));
    ft::map<int, int, ModCmp> ftdata;
    ftdata.insert(ft::make_pair(1, 1));
    ftdata.insert(ft::make_pair(100, 1));
    ftdata.insert(ft::make_pair(98, 1));
    ftdata.insert(ft::make_pair(97, 1));

    const std::map<int, int, ModCmp> stdmp(stddata.begin(), stddata.end());
    const ft::map<int, int, ModCmp> ftmp(ftdata.begin(), ftdata.end());

    std::map<int, int, ModCmp>::const_iterator stditr = stdmp.begin();
    ft::map<int, int, ModCmp>::const_iterator ftitr = ftmp.begin();

    ASSERT_EQ(stdmp.size(), ftmp.size());
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }

  // compare operators
  {
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

  {
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

  {
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

  // compare operators const
  {
    std::map<int, int> stdmp1;
    stdmp1.insert(std::make_pair(1, 1));
    stdmp1.insert(std::make_pair(2, 1));
    stdmp1.insert(std::make_pair(3, 1));
    std::map<int, int> stdmp2;
    stdmp2.insert(std::make_pair(1, 1));
    ft::map<int, int> ftmp1;
    ftmp1.insert(ft::make_pair(1, 1));
    ftmp1.insert(ft::make_pair(2, 1));
    ftmp1.insert(ft::make_pair(3, 1));
    ft::map<int, int> ftmp2;
    ftmp2.insert(ft::make_pair(1, 1));

    const std::map<int, int> libmp1(stdmp1.begin(), stdmp1.end());
    const std::map<int, int> libmp2(stdmp2.begin(), stdmp2.end());
    const ft::map<int, int> mymp1(ftmp1.begin(), ftmp1.end());
    const ft::map<int, int> mymp2(ftmp2.begin(), ftmp2.end());

    ASSERT_EQ(libmp1 == libmp2, mymp1 == mymp2);
    ASSERT_EQ(libmp1 != libmp2, mymp1 != mymp2);
    ASSERT_EQ(libmp1 < libmp2, mymp1 < mymp2);
    ASSERT_EQ(libmp1 > libmp2, mymp1 > mymp2);
    ASSERT_EQ(libmp1 >= libmp2, mymp1 >= mymp2);
    ASSERT_EQ(libmp1 <= libmp2, mymp1 <= mymp2);
  }

  // const_iterator
  {
    std::map<int, int> stddata;
    stddata.insert(std::make_pair(1, 1));
    ft::map<int, int> ftdata;
    ftdata.insert(ft::make_pair(1, 1));

    const std::map<int, int> stdmap(stddata.begin(), stddata.end());
    const ft::map<int, int> ftmap(ftdata.begin(), ftdata.end());
    std::map<int, int>::const_iterator stditr = stdmap.begin();
    ft::map<int, int>::const_iterator ftitr = ftmap.begin();
    assert(stditr->first == ftitr->first);
    assert(stditr->second == ftitr->second);
    stditr++;
    ftitr++;
    assert(stditr == stdmap.end());
    assert(ftitr == ftmap.end());
  }

  // swap
  {
    std::map<int, int> stdmp1;
    stdmp1.insert(std::make_pair(2, 2));
    stdmp1.insert(std::make_pair(1, 2));
    stdmp1.insert(std::make_pair(-100, 2));
    stdmp1.insert(std::make_pair(-11, 2));
    std::map<int, int> stdmp2;
    stdmp2.insert(std::make_pair(1, 1));
    stdmp2.insert(std::make_pair(-10, 1));
    stdmp2.insert(std::make_pair(2, 1));
    stdmp2.insert(std::make_pair(3, 1));
    stdmp2.insert(std::make_pair(4, 1));
    stdmp2.insert(std::make_pair(5, 1));
    stdmp2.insert(std::make_pair(6, 1));
    stdmp2.insert(std::make_pair(1000000, 1));
    ft::map<int, int> ftmp1;
    ftmp1.insert(ft::make_pair(2, 2));
    ftmp1.insert(ft::make_pair(1, 2));
    ftmp1.insert(ft::make_pair(-100, 2));
    ftmp1.insert(ft::make_pair(-11, 2));
    ft::map<int, int> ftmp2;
    ftmp2.insert(ft::make_pair(1, 1));
    ftmp2.insert(ft::make_pair(-10, 1));
    ftmp2.insert(ft::make_pair(2, 1));
    ftmp2.insert(ft::make_pair(3, 1));
    ftmp2.insert(ft::make_pair(4, 1));
    ftmp2.insert(ft::make_pair(5, 1));
    ftmp2.insert(ft::make_pair(6, 1));
    ftmp2.insert(ft::make_pair(1000000, 1));

    std::swap(stdmp1, stdmp2);
    ft::swap(ftmp1, ftmp2);

    ASSERT_EQ(stdmp1.size(), ftmp1.size());
    ASSERT_EQ(stdmp2.size(), ftmp2.size());

    std::map<int, int>::iterator stditr1 = stdmp1.begin();
    ft::map<int, int>::iterator ftitr1 = ftmp1.begin();
    while ((stditr1 != stdmp1.end()) && (ftitr1 != ftmp1.end())) {
      ASSERT_EQ(stditr1->first, ftitr1->first);
      ASSERT_EQ(stditr1->second, ftitr1->second);
      ++stditr1;
      ++ftitr1;
    }
    ASSERT_EQ(stditr1, stdmp1.end());
    ASSERT_EQ(ftitr1, ftmp1.end());

    std::map<int, int>::iterator stditr2 = stdmp2.begin();
    ft::map<int, int>::iterator ftitr2 = ftmp2.begin();
    while ((stditr2 != stdmp2.end()) && (ftitr2 != ftmp2.end())) {
      ASSERT_EQ(stditr2->first, ftitr2->first);
      ASSERT_EQ(stditr2->second, ftitr2->second);
      ++stditr2;
      ++ftitr2;
    }
    ASSERT_EQ(stditr2, stdmp2.end());
    ASSERT_EQ(ftitr2, ftmp2.end());
  }
}

void test_set() {
  //  (constructor)
  // 1
  { ft::set<int> myst; }

  {
    ft::greater<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::set<int, ft::greater<int> > myst(ftcomp, ftalloc);

    std::greater<int> libcomp;
    std::allocator<int> liballoc;
    std::set<int, std::greater<int> > libst(libcomp, liballoc);

    myst.insert(1);
    myst.insert(2);
    myst.insert(3);
    myst.insert(4);
    myst.insert(5);
    libst.insert(1);
    libst.insert(2);
    libst.insert(3);
    libst.insert(4);
    libst.insert(5);

    ft::set<int, ft::greater<int> >::iterator myitr = myst.begin();
    std::set<int, ft::greater<int> >::iterator libitr = libst.begin();

    ASSERT_EQ(*myitr, *libitr);
    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;
    ASSERT_EQ(*myitr, *libitr);
    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;
    ASSERT_EQ(*myitr, *libitr);
    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;
    ASSERT_EQ(*myitr, *libitr);
    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;
    ASSERT_EQ(*myitr, *libitr);
    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;

    ASSERT_EQ(myst.size(), libst.size());

    ASSERT_EQ(libitr, libst.end());
    ASSERT_EQ(myitr, myst.end());
  }

  // 2
  {
    ft::greater<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::set<int, ft::greater<int> > myorigin(ftcomp, ftalloc);
    myorigin.insert(1);
    myorigin.insert(2);
    myorigin.insert(3);

    ft::set<int, ft::greater<int> > myst(myorigin.begin(), myorigin.end(),
                                         ftcomp, ftalloc);

    std::greater<int> libcomp;
    std::allocator<int> stdalloc;
    std::set<int, std::greater<int> > liborigin(libcomp, stdalloc);
    liborigin.insert(1);
    liborigin.insert(2);
    liborigin.insert(3);

    std::set<int, std::greater<int> > libst(liborigin.begin(), liborigin.end(),
                                            libcomp, stdalloc);

    ft::set<int, ft::greater<int> >::iterator myitr = myst.begin();
    std::set<int, ft::greater<int> >::iterator libitr = libst.begin();

    ASSERT_EQ(*myitr, *libitr);
    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;
    ASSERT_EQ(*myitr, *libitr);
    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;
    ASSERT_EQ(*myitr, *libitr);
    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;

    ASSERT_EQ(myst.size(), libst.size());

    ASSERT_EQ(libitr, libst.end());
    ASSERT_EQ(myitr, myst.end());
  }

  {
    ft::set<int> myorg;
    myorg.insert(1);
    myorg.insert(2);
    myorg.insert(3);
    ft::set<int> myst(myorg);

    std::set<int> liborg;
    liborg.insert(1);
    liborg.insert(2);
    liborg.insert(3);
    std::set<int> libst(liborg);

    ft::set<int>::iterator myitr = myst.begin();
    std::set<int>::iterator libitr = libst.begin();

    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;
    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;
    ASSERT_EQ(*myitr, *libitr);
    ++myitr;
    ++libitr;

    ASSERT_EQ(myst.size(), libst.size());

    ASSERT_EQ(libitr, libst.end());
    ASSERT_EQ(myitr, myst.end());
  }

  // destructor
  {
    ft::set<int> myst;
    std::set<int> libst;
  }

  //  operator=

  // //  get_allocator
  // {
  //   ft::greater<int> mycomp;
  //   std::allocator<int> alloc;
  //   ft::set<int, ft::greater<int> > mymp(mycomp, alloc);

  //   std::greater<int> libcomp;
  //   std::set<int, std::greater<int> > libmp(libcomp, alloc);

  //   ASSERT_EQ(mymp.get_allocator(), libmp.get_allocator());
  // }

  // {
  //   ft::greater<int> mycomp;
  //   std::allocator<int> alloc;
  //   const ft::set<int, ft::greater<int> > mymp(mycomp, alloc);

  //   std::greater<int> libcomp;
  //   const std::set<int, std::greater<int> > libmp(libcomp, alloc);

  //   ASSERT_EQ(mymp.get_allocator(), libmp.get_allocator());
  // }

  //  begin
  {
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

  {
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

  {
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

  {
    std::set<int> libdata;
    libdata.insert(1);
    ft::set<int> mydata;
    mydata.insert(1);

    std::set<int>::iterator libditr = libdata.begin();
    ft::set<int>::iterator myditr = mydata.begin();

    ASSERT_EQ(*libditr, *myditr);
    ++libditr;
    ++myditr;
    ASSERT_EQ(libditr, libdata.end());
    ASSERT_EQ(myditr, mydata.end());

    const std::set<int> libst(libdata.begin(), libdata.end());
    const ft::set<int> myst(mydata.begin(), mydata.end());

    std::set<int>::const_iterator libitr = libst.begin();
    ft::set<int>::const_iterator myitr = myst.begin();

    ASSERT_EQ(libst.size(), myst.size());

    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(libitr, libst.end());
    ASSERT_EQ(myitr, myst.end());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);

    const std::set<int> libst(libdata.begin(), libdata.end());
    const ft::set<int> myst(mydata.begin(), mydata.end());

    std::set<int>::const_iterator libitr = libst.begin();
    ft::set<int>::const_iterator myitr = myst.begin();

    ASSERT_EQ(libst.size(), myst.size());

    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(libitr, libst.end());
    ASSERT_EQ(myitr, myst.end());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    libdata.insert(3);
    libdata.insert(4);
    libdata.insert(5);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);
    mydata.insert(4);
    mydata.insert(5);

    const std::set<int> libst(libdata.begin(), libdata.end());
    const ft::set<int> myst(mydata.begin(), mydata.end());

    std::set<int>::const_iterator libitr = libst.begin();
    ft::set<int>::const_iterator myitr = myst.begin();

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

  {
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

  // end
  {
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

  {
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

  // end const
  {
    std::set<int> libdata;
    libdata.insert(1);
    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_iterator libitr = libst.end();
    ft::set<int>::const_iterator myitr = myst.end();

    ASSERT_EQ(libst.size(), myst.size());

    libitr--;
    myitr--;
    ASSERT_EQ(*libitr, *myitr);

    ASSERT_EQ(libitr, libst.begin());
    ASSERT_EQ(myitr, myst.begin());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_iterator libitr = libst.end();
    ft::set<int>::const_iterator myitr = myst.end();

    ASSERT_EQ(libst.size(), myst.size());

    libitr--;
    myitr--;
    ASSERT_EQ(*libitr, *myitr);
    libitr--;
    myitr--;
    ASSERT_EQ(*libitr, *myitr);

    ASSERT_EQ(libitr, libst.begin());
    ASSERT_EQ(myitr, myst.begin());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    libdata.insert(3);
    libdata.insert(4);
    libdata.insert(5);
    libdata.insert(6);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);
    mydata.insert(4);
    mydata.insert(5);
    mydata.insert(6);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_iterator libitr = libst.end();
    ft::set<int>::const_iterator myitr = myst.end();

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
    libitr--;
    myitr--;
    ASSERT_EQ(*libitr, *myitr);

    ASSERT_EQ(libitr, libst.begin());
    ASSERT_EQ(myitr, myst.begin());
  }

  //  rbegin
  {
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

  {
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

  {
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

  // rbegin const
  {
    std::set<int> libdata;
    libdata.insert(1);

    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_reverse_iterator libitr = libst.rbegin();
    ft::set<int>::const_reverse_iterator myitr = myst.rbegin();

    ASSERT_EQ(libst.size(), myst.size());

    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;

    ASSERT_EQ(libitr, libst.rend());
    ASSERT_EQ(myitr, myst.rend());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);

    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_reverse_iterator libitr = libst.rbegin();
    ft::set<int>::const_reverse_iterator myitr = myst.rbegin();

    ASSERT_EQ(libst.size(), myst.size());

    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;

    ASSERT_EQ(libitr, libst.rend());
    ASSERT_EQ(myitr, myst.rend());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    libdata.insert(3);
    libdata.insert(4);
    libdata.insert(5);
    libdata.insert(6);

    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);
    mydata.insert(4);
    mydata.insert(5);
    mydata.insert(6);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_reverse_iterator libitr = libst.rbegin();
    ft::set<int>::const_reverse_iterator myitr = myst.rbegin();

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
    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;

    ASSERT_EQ(libitr, libst.rend());
    ASSERT_EQ(myitr, myst.rend());
  }

  //  rend
  {
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

  {
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

  {
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

  // rend const
  {
    std::set<int> libdata;
    libdata.insert(1);

    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_reverse_iterator libitr = libst.rend();
    ft::set<int>::const_reverse_iterator myitr = myst.rend();

    ASSERT_EQ(libst.size(), myst.size());

    libitr--;
    myitr--;
    ASSERT_EQ(*libitr, *myitr);

    ASSERT_EQ(libitr, libst.rbegin());
    ASSERT_EQ(myitr, myst.rbegin());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);

    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_reverse_iterator libitr = libst.rend();
    ft::set<int>::const_reverse_iterator myitr = myst.rend();

    ASSERT_EQ(libst.size(), myst.size());

    libitr--;
    myitr--;
    ASSERT_EQ(*libitr, *myitr);
    libitr--;
    myitr--;
    ASSERT_EQ(*libitr, *myitr);

    ASSERT_EQ(libitr, libst.rbegin());
    ASSERT_EQ(myitr, myst.rbegin());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    libdata.insert(3);
    libdata.insert(4);
    libdata.insert(5);
    libdata.insert(6);

    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);
    mydata.insert(4);
    mydata.insert(5);
    mydata.insert(6);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_reverse_iterator libitr = libst.rend();
    ft::set<int>::const_reverse_iterator myitr = myst.rend();

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
    libitr--;
    myitr--;
    ASSERT_EQ(*libitr, *myitr);

    ASSERT_EQ(libitr, libst.rbegin());
    ASSERT_EQ(myitr, myst.rbegin());
  }

  // empty
  {
    std::set<int> libst;
    ft::set<int> myst;
    ASSERT_EQ(libst.empty(), myst.empty());
  }

  {
    std::set<int> libst;
    ft::set<int> myst;

    libst.insert(1);
    myst.insert(1);

    ASSERT_EQ(libst.empty(), myst.empty());
  }

  {
    const std::set<int> libst;
    const ft::set<int> myst;
    ASSERT_EQ(libst.empty(), myst.empty());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);
    ASSERT_EQ(libst.empty(), myst.empty());
  }

  // size
  {
    std::set<int> libst;
    ft::set<int> myst;
    ASSERT_EQ(libst.size(), myst.size());
  }

  {
    std::set<int> libst;
    libst.insert(1);
    ft::set<int> myst;
    myst.insert(1);
    ASSERT_EQ(libst.size(), myst.size());
  }

  {
    std::set<int> libst;
    libst.insert(1);
    libst.insert(1);
    ft::set<int> myst;
    myst.insert(1);
    myst.insert(1);
    ASSERT_EQ(libst.size(), myst.size());
  }

  // size const
  {
    const std::set<int> libst;
    const ft::set<int> myst;
    ASSERT_EQ(libst.size(), myst.size());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);
    ASSERT_EQ(libst.size(), myst.size());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);
    ASSERT_EQ(libst.size(), myst.size());
  }

  // //  max_size
  // {
  //   std::set<int> libst;
  //   ft::set<int> myst;
  //   std::cerr << "lib max_size " << libst.max_size() << std::endl;
  //   std::cerr << "my  max_size " << myst.max_size() << std::endl;
  //   ASSERT_EQ(libst.max_size(), myst.max_size());
  // }

  // {
  //   const std::set<int> libst;
  //   const ft::set<int> myst;
  //   ASSERT_EQ(libst.max_size(), myst.max_size());
  // }

  //  clear
  {
    std::set<int> libst;
    ft::set<int> myst;

    libst.insert(1);
    libst.insert(2);
    libst.insert(3);
    libst.insert(4);

    myst.insert(1);
    myst.insert(2);
    myst.insert(3);
    myst.insert(4);

    libst.clear();
    myst.clear();

    ASSERT_EQ(libst.size(), myst.size());
    ASSERT_EQ(libst.empty(), myst.empty());
  }

  //  insert
  //  1
  {
    std::set<int> libst;
    libst.insert(1);
    ft::set<int> myst;
    myst.insert(1);
    ASSERT_EQ(libst.size(), myst.size());
  }

  {
    std::set<int> libst;
    std::pair<std::set<int>::iterator, bool> libp = libst.insert(1);
    ft::set<int> myst;
    ft::pair<ft::set<int>::iterator, bool> myp = myst.insert(1);
    ASSERT_EQ(*(libp.first), *(myp.first));
    ASSERT_EQ(libp.second, myp.second);
  }

  {
    std::set<int> libst;
    libst.insert(2);
    std::pair<std::set<int>::iterator, bool> libp = libst.insert(1);
    ft::set<int> myst;
    myst.insert(2);
    ft::pair<ft::set<int>::iterator, bool> myp = myst.insert(1);
    ASSERT_EQ(*(libp.first), *(myp.first));
    ASSERT_EQ(libp.second, myp.second);
  }

  {
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

  {
    std::set<int> libst;
    libst.insert(2);
    libst.insert(1);
    libst.insert(4);
    libst.insert(1000);
    libst.insert(111);
    libst.insert(11111);
    libst.insert(1111111);
    libst.insert(-1);
    libst.insert(-1102);
    libst.insert(-11);

    ft::set<int> myst;
    myst.insert(2);
    myst.insert(1);
    myst.insert(4);
    myst.insert(1000);
    myst.insert(111);
    myst.insert(11111);
    myst.insert(1111111);
    myst.insert(-1);
    myst.insert(-1102);
    myst.insert(-11);

    ASSERT_EQ(libst.size(), myst.size());

    std::set<int>::iterator libitr = libst.begin();
    ft::set<int>::iterator myitr = myst.begin();
    for (; libitr != libst.end(); ++libitr, ++myitr) {
      ASSERT_EQ(*libitr, *myitr);
    }
  }

  // insert 2
  {
    std::set<int> stdst;
    stdst.insert(1);
    ft::set<int> ftst;
    ftst.insert(1);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 2);
    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 2);

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(1);
    stdst.insert(2);
    ft::set<int> ftst;
    ftst.insert(1);
    ftst.insert(2);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 10);
    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 10);

    // std::cerr << "stdret  : " << *stdret << std::endl;
    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(1);
    stdst.insert(2);
    stdst.insert(10);
    ft::set<int> ftst;
    ftst.insert(1);
    ftst.insert(2);
    ftst.insert(10);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 3);
    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 3);

    // std::cerr << "stdret  : " << *stdret << std::endl;
    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(1);
    stdst.insert(2);
    stdst.insert(10);
    ft::set<int> ftst;
    ftst.insert(1);
    ftst.insert(2);
    ftst.insert(10);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 5);
    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 5);

    // std::cerr << "stdret  : " << *stdret << std::endl;
    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(1);
    stdst.insert(2);
    stdst.insert(10);
    ft::set<int> ftst;
    ftst.insert(1);
    ftst.insert(2);
    ftst.insert(10);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 10);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 10);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 1);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 1);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 2);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 2);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 3);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 3);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 4);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 4);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 5);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 5);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 6);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 6);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 7);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 7);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 8);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 8);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 9);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 9);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 10);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 10);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 11);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 11);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 12);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 12);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 13);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 13);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 14);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 14);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 15);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 15);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 16);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 16);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 17);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 17);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  {
    std::set<int> stdst;
    stdst.insert(10);
    stdst.insert(5);
    stdst.insert(15);
    stdst.insert(2);
    stdst.insert(17);
    ft::set<int> ftst;
    ftst.insert(10);
    ftst.insert(5);
    ftst.insert(15);
    ftst.insert(2);
    ftst.insert(17);

    std::set<int>::iterator stditr = stdst.begin();
    std::set<int>::iterator stdret = stdst.insert(stditr, 18);
    // std::cerr << "stdret  : " << *stdret << std::endl;

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 18);

    // std::cerr << "stdsize : " << stdst.size() << std::endl;

    ASSERT_EQ(*stdret, *ftret);

    stditr = stdst.begin();
    ftitr = ftst.begin();
    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
  }

  // insert 3
  {
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

  {
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

  // erase 1
  {
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

    std::set<int>::iterator libitr = libdata.begin();
    ft::set<int>::iterator myitr = mydata.begin();

    std::set<int>::iterator libitr2 = libdata.erase(libitr);
    ft::set<int>::iterator myitr2 = mydata.erase(myitr);

    ASSERT_EQ(libdata.size(), mydata.size());

    ASSERT_EQ(*libitr2, *myitr2);
    while (libitr2 != libdata.end() && myitr2 != mydata.end()) {
      ASSERT_EQ(*libitr2, *myitr2);
      libitr2++;
      myitr2++;
    }
    ASSERT_EQ(libitr2, libdata.end());
    ASSERT_EQ(myitr2, mydata.end());

    libitr = libdata.begin();
    myitr = mydata.begin();

    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(libitr, libdata.end());
    ASSERT_EQ(myitr, mydata.end());
  }

  // erase 2
  {
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

    std::set<int>::iterator libitr = libdata.begin();
    ft::set<int>::iterator myitr = mydata.begin();

    std::set<int>::iterator libitr2 = libdata.erase(libitr, ++libitr);
    ft::set<int>::iterator myitr2 = mydata.erase(myitr, ++myitr);

    ASSERT_EQ(libdata.size(), mydata.size());

    ASSERT_EQ(*libitr2, *myitr2);
    while (libitr2 != libdata.end() && myitr2 != mydata.end()) {
      ASSERT_EQ(*libitr2, *myitr2);
      libitr2++;
      myitr2++;
    }
    ASSERT_EQ(libitr2, libdata.end());
    ASSERT_EQ(myitr2, mydata.end());

    libitr = libdata.begin();
    myitr = mydata.begin();

    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(libitr, libdata.end());
    ASSERT_EQ(myitr, mydata.end());
  }

  {
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);
    mydata.insert(4);

    ft::set<int>::iterator myitr = mydata.begin();

    ft::set<int>::iterator myitr2 = mydata.erase(myitr, ++myitr);

    ASSERT_EQ(mydata.size(), 3);

    myitr = mydata.begin();

    ASSERT_EQ(*myitr, 2);
    myitr++;
    ASSERT_EQ(*myitr, 3);
    myitr++;
    ASSERT_EQ(*myitr, 4);
    myitr++;
    ASSERT_EQ(myitr, mydata.end());
  }

  // erase 3
  {
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

  {
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
  }

  {
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

  {
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

  {
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

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    libdata.insert(3);
    libdata.insert(-110);
    libdata.insert(-11);
    libdata.insert(-1);
    libdata.insert(-203);
    libdata.insert(102);
    libdata.insert(10);

    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);
    mydata.insert(-110);
    mydata.insert(-11);
    mydata.insert(-1);
    mydata.insert(-203);
    mydata.insert(102);
    mydata.insert(10);

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
  }

  {
    std::set<int> libdata;
    libdata.insert(2);
    libdata.insert(-1);
    libdata.insert(-2);
    libdata.insert(-3);
    libdata.insert(-4);
    libdata.insert(10000);
    libdata.insert(10);
    libdata.insert(122323);

    ft::set<int> mydata;
    mydata.insert(2);
    mydata.insert(-1);
    mydata.insert(-2);
    mydata.insert(-3);
    mydata.insert(-4);
    mydata.insert(10000);
    mydata.insert(10);
    mydata.insert(122323);

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
  }

  //  swap
  {
    std::set<int> libdata1;
    libdata1.insert(1);
    std::set<int> libdata2;
    libdata2.insert(2);

    ft::set<int> mydata1;
    mydata1.insert(1);
    ft::set<int> mydata2;
    mydata2.insert(2);

    libdata1.swap(libdata2);
    mydata1.swap(mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    libdata1.insert(2);
    libdata1.insert(3);
    std::set<int> libdata2;
    libdata2.insert(2);

    ft::set<int> mydata1;
    mydata1.insert(1);
    mydata1.insert(2);
    mydata1.insert(3);
    ft::set<int> mydata2;
    mydata2.insert(2);

    libdata1.swap(libdata2);
    mydata1.swap(mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    std::set<int> libdata2;
    libdata2.insert(2);
    libdata2.insert(3);
    libdata2.insert(4);

    ft::set<int> mydata1;
    mydata1.insert(1);
    ft::set<int> mydata2;
    mydata2.insert(2);
    mydata2.insert(3);
    mydata2.insert(4);

    libdata1.swap(libdata2);
    mydata1.swap(mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    libdata1.insert(-1);
    libdata1.insert(31);
    libdata1.insert(-1111);
    std::set<int> libdata2;
    libdata2.insert(2);
    libdata2.insert(1);
    libdata2.insert(4);
    libdata2.insert(1000);
    libdata2.insert(111);
    libdata2.insert(11111);
    libdata2.insert(1111111);
    libdata2.insert(-1);
    libdata2.insert(-1102);
    libdata2.insert(-11);

    ft::set<int> mydata1;
    mydata1.insert(1);
    mydata1.insert(-1);
    mydata1.insert(31);
    mydata1.insert(-1111);
    ft::set<int> mydata2;
    mydata2.insert(2);
    mydata2.insert(1);
    mydata2.insert(4);
    mydata2.insert(1000);
    mydata2.insert(111);
    mydata2.insert(11111);
    mydata2.insert(1111111);
    mydata2.insert(-1);
    mydata2.insert(-1102);
    mydata2.insert(-11);

    libdata1.swap(libdata2);
    mydata1.swap(mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    libdata1.insert(2);
    libdata1.insert(3);
    libdata1.insert(-110);
    libdata1.insert(-11);
    libdata1.insert(-1);
    std::set<int> libdata2;
    libdata2.insert(2);
    libdata2.insert(-1);
    libdata2.insert(-2);
    libdata2.insert(-3);
    libdata2.insert(-4);

    ft::set<int> mydata1;
    mydata1.insert(1);
    mydata1.insert(2);
    mydata1.insert(3);
    mydata1.insert(-110);
    mydata1.insert(-11);
    mydata1.insert(-1);
    ft::set<int> mydata2;
    mydata2.insert(2);
    mydata2.insert(-1);
    mydata2.insert(-2);
    mydata2.insert(-3);
    mydata2.insert(-4);

    libdata1.swap(libdata2);
    mydata1.swap(mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    libdata1.insert(2);
    libdata1.insert(3);
    libdata1.insert(-110);
    libdata1.insert(-11);
    libdata1.insert(-1);
    libdata1.insert(-203);
    std::set<int> libdata2;
    libdata2.insert(2);
    libdata2.insert(-1);
    libdata2.insert(-2);
    libdata2.insert(-3);
    libdata2.insert(-4);
    libdata2.insert(10000);

    ft::set<int> mydata1;
    mydata1.insert(1);
    mydata1.insert(2);
    mydata1.insert(3);
    mydata1.insert(-110);
    mydata1.insert(-11);
    mydata1.insert(-1);
    mydata1.insert(-203);
    ft::set<int> mydata2;
    mydata2.insert(2);
    mydata2.insert(-1);
    mydata2.insert(-2);
    mydata2.insert(-3);
    mydata2.insert(-4);
    mydata2.insert(10000);

    libdata1.swap(libdata2);
    mydata1.swap(mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    libdata1.insert(2);
    libdata1.insert(3);
    libdata1.insert(-110);
    libdata1.insert(-11);
    libdata1.insert(-1);
    libdata1.insert(-203);
    libdata1.insert(102);
    std::set<int> libdata2;
    libdata2.insert(2);
    libdata2.insert(-1);
    libdata2.insert(-2);
    libdata2.insert(-3);
    libdata2.insert(-4);
    libdata2.insert(10000);
    libdata2.insert(10);

    ft::set<int> mydata1;
    mydata1.insert(1);
    mydata1.insert(2);
    mydata1.insert(3);
    mydata1.insert(-110);
    mydata1.insert(-11);
    mydata1.insert(-1);
    mydata1.insert(-203);
    mydata1.insert(102);
    ft::set<int> mydata2;
    mydata2.insert(2);
    mydata2.insert(-1);
    mydata2.insert(-2);
    mydata2.insert(-3);
    mydata2.insert(-4);
    mydata2.insert(10000);
    mydata2.insert(10);

    libdata1.swap(libdata2);
    mydata1.swap(mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    libdata1.insert(2);
    libdata1.insert(3);
    libdata1.insert(-110);
    libdata1.insert(-11);
    libdata1.insert(-1);
    libdata1.insert(-203);
    libdata1.insert(102);
    libdata1.insert(10);
    std::set<int> libdata2;
    libdata2.insert(2);
    libdata2.insert(-1);
    libdata2.insert(-2);
    libdata2.insert(-3);
    libdata2.insert(-4);
    libdata2.insert(10000);
    libdata2.insert(10);
    libdata2.insert(122323);

    ft::set<int> mydata1;
    mydata1.insert(1);
    mydata1.insert(2);
    mydata1.insert(3);
    mydata1.insert(-110);
    mydata1.insert(-11);
    mydata1.insert(-1);
    mydata1.insert(-203);
    mydata1.insert(102);
    mydata1.insert(10);
    ft::set<int> mydata2;
    mydata2.insert(2);
    mydata2.insert(-1);
    mydata2.insert(-2);
    mydata2.insert(-3);
    mydata2.insert(-4);
    mydata2.insert(10000);
    mydata2.insert(10);
    mydata2.insert(122323);

    libdata1.swap(libdata2);
    mydata1.swap(mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  //  count
  {
    std::set<int> libst;
    libst.insert(1);
    ft::set<int> myst;
    myst.insert(1);

    ASSERT_EQ(libst.count(1), myst.count(1));
  }

  {
    std::set<int> libst;
    libst.insert(1);
    libst.insert(2);
    ft::set<int> myst;
    myst.insert(1);
    myst.insert(2);

    ASSERT_EQ(libst.count(1), myst.count(1));
  }

  {
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

  {
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

  // count const
  {
    std::set<int> libdata;
    libdata.insert(1);
    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    ASSERT_EQ(libst.count(1), myst.count(1));
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    libdata.insert(2);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(2);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    ASSERT_EQ(libst.count(2), myst.count(2));
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    libdata.insert(3);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    ASSERT_EQ(libst.count(42), myst.count(42));
  }

  //  find
  {
    std::set<int> libst;
    libst.insert(1);
    ft::set<int> myst;
    myst.insert(1);

    ASSERT_EQ(*(libst.find(1)), *(myst.find(1)));
  }

  {
    std::set<int> libst;
    libst.insert(1);
    ft::set<int> myst;
    myst.insert(1);

    ASSERT_EQ(libst.find(42) == libst.end(), myst.find(42) == myst.end());
  }

  {
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

  // find const
  {
    std::set<int> libdata;
    libdata.insert(1);
    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    ASSERT_EQ(*(libst.find(1)), *(myst.find(1)));
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_iterator libitr = libst.find(1);
    ft::set<int>::const_iterator myitr = myst.find(1);

    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(*libitr, *myitr);
    libitr++;
    myitr++;
    ASSERT_EQ(libitr, libst.end());
    ASSERT_EQ(myitr, myst.end());
  }

  //  equal_range
  {
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

  {
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

  // equal_range const
  {
    std::set<int> libdata;
    libdata.insert(1);
    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator>
        libp = libst.equal_range(1);
    ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> myp =
        myst.equal_range(1);

    ASSERT_EQ(*(libp.first), *(myp.first));
    ASSERT_EQ(libp.second == libst.end(), myp.second == myst.end());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    libdata.insert(3);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator>
        libp = libst.equal_range(1);
    ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> myp =
        myst.equal_range(1);

    ASSERT_EQ(*(libp.first), *(myp.first));
    ASSERT_EQ(*(libp.second), *(myp.second));
  }

  //  lower_bound
  {
    std::set<int> libst;
    libst.insert(1);
    ft::set<int> myst;
    myst.insert(1);

    std::set<int>::iterator libitr = libst.lower_bound(1);
    ft::set<int>::iterator myitr = myst.lower_bound(1);

    ASSERT_EQ(*libitr, *myitr);
  }

  {
    std::set<int> libst;
    libst.insert(1);
    ft::set<int> myst;
    myst.insert(1);

    std::set<int>::iterator libitr = libst.lower_bound(2);
    ft::set<int>::iterator myitr = myst.lower_bound(2);

    ASSERT_EQ(libitr == libst.end(), myitr == myst.end());
  }

  {
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

  //  lower_bound const
  {
    std::set<int> libdata;
    libdata.insert(1);
    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_iterator libitr = libst.lower_bound(1);
    ft::set<int>::const_iterator myitr = myst.lower_bound(1);

    ASSERT_EQ(*libitr, *myitr);
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_iterator libitr = libst.lower_bound(2);
    ft::set<int>::const_iterator myitr = myst.lower_bound(2);

    ASSERT_EQ(libitr == libst.end(), myitr == myst.end());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    libdata.insert(3);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_iterator libitr = libst.lower_bound(2);
    ft::set<int>::const_iterator myitr = myst.lower_bound(2);

    ASSERT_EQ(*libitr, *myitr);
    ++libitr;
    ++myitr;
    ASSERT_EQ(*libitr, *myitr);
    ++libitr;
    ++myitr;
  }

  //  upper_bound
  {
    std::set<int> libst;
    libst.insert(1);
    ft::set<int> myst;
    myst.insert(1);

    std::set<int>::iterator libitr = libst.lower_bound(1);
    ft::set<int>::iterator myitr = myst.lower_bound(1);

    ASSERT_EQ(libitr == libst.end(), myitr == myst.end());
  }

  {
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

  {
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

  // upper_bound const
  {
    std::set<int> libdata;
    libdata.insert(1);
    ft::set<int> mydata;
    mydata.insert(1);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_iterator libitr = libst.lower_bound(1);
    ft::set<int>::const_iterator myitr = myst.lower_bound(1);

    ASSERT_EQ(libitr == libst.end(), myitr == myst.end());
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_iterator libitr = libst.lower_bound(1);
    ft::set<int>::const_iterator myitr = myst.lower_bound(1);

    ASSERT_EQ(*libitr, *myitr);
  }

  {
    std::set<int> libdata;
    libdata.insert(1);
    libdata.insert(2);
    libdata.insert(3);
    libdata.insert(42);
    libdata.insert(10);
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);
    mydata.insert(42);
    mydata.insert(10);

    const std::set<int> libst(libdata);
    const ft::set<int> myst(mydata);

    std::set<int>::const_iterator libitr = libst.lower_bound(1);
    ft::set<int>::const_iterator myitr = myst.lower_bound(1);

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
  {
    std::set<int, ModCmp> libst;
    ft::set<int, ModCmp> myst;

    std::set<int, ModCmp>::key_compare libcomp = libst.key_comp();
    ft::set<int, ModCmp>::key_compare mycomp = myst.key_comp();

    ASSERT_EQ(libcomp(1, 2), mycomp(1, 2));
    ASSERT_EQ(libcomp(100, 2), mycomp(100, 2));
    ASSERT_EQ(libcomp(100, 200), mycomp(100, 200));
    ASSERT_EQ(libcomp(97, 98), mycomp(97, 98));
  }

  //  key_comp const
  {
    const std::set<int, ModCmp> libst;
    const ft::set<int, ModCmp> myst;

    std::set<int, ModCmp>::key_compare libcomp = libst.key_comp();
    ft::set<int, ModCmp>::key_compare mycomp = myst.key_comp();

    ASSERT_EQ(libcomp(1, 2), mycomp(1, 2));
    ASSERT_EQ(libcomp(100, 2), mycomp(100, 2));
    ASSERT_EQ(libcomp(100, 200), mycomp(100, 200));
    ASSERT_EQ(libcomp(97, 98), mycomp(97, 98));
  }

  //  value_comp
  {
    std::set<int, ModCmp> libst;
    ft::set<int, ModCmp> myst;

    std::set<int, ModCmp>::value_compare libcomp = libst.value_comp();
    ft::set<int, ModCmp>::value_compare mycomp = myst.value_comp();

    ASSERT_EQ(libcomp(1, 2), mycomp(1, 2));
    ASSERT_EQ(libcomp(100, 2), mycomp(100, 2));
    ASSERT_EQ(libcomp(100, 200), mycomp(100, 200));
    ASSERT_EQ(libcomp(97, 98), mycomp(97, 98));
  }

  //  value_comp const
  {
    const std::set<int, ModCmp> libst;
    const ft::set<int, ModCmp> myst;

    std::set<int, ModCmp>::value_compare libcomp = libst.value_comp();
    ft::set<int, ModCmp>::value_compare mycomp = myst.value_comp();

    ASSERT_EQ(libcomp(1, 2), mycomp(1, 2));
    ASSERT_EQ(libcomp(100, 2), mycomp(100, 2));
    ASSERT_EQ(libcomp(100, 200), mycomp(100, 200));
    ASSERT_EQ(libcomp(97, 98), mycomp(97, 98));
  }

  // compare
  {
    std::set<int> libst1;
    libst1.insert(1);
    std::set<int> libst2;
    libst2.insert(1);

    ft::set<int> myst1;
    myst1.insert(1);
    ft::set<int> myst2;
    myst2.insert(1);

    ASSERT_EQ(libst1 == libst2, myst1 == myst2);
    ASSERT_EQ(libst1 != libst2, myst1 != myst2);
    ASSERT_EQ(libst1 < libst2, myst1 < myst2);
    ASSERT_EQ(libst1 > libst2, myst1 > myst2);
    ASSERT_EQ(libst1 >= libst2, myst1 >= myst2);
    ASSERT_EQ(libst1 <= libst2, myst1 <= myst2);
  }

  {
    std::set<int> libst1;
    libst1.insert(1);
    std::set<int> libst2;
    libst2.insert(1);
    libst2.insert(2);

    ft::set<int> myst1;
    myst1.insert(1);
    ft::set<int> myst2;
    myst2.insert(1);
    myst2.insert(2);

    ASSERT_EQ(libst1 == libst2, myst1 == myst2);
    ASSERT_EQ(libst1 != libst2, myst1 != myst2);
    ASSERT_EQ(libst1 < libst2, myst1 < myst2);
    ASSERT_EQ(libst1 > libst2, myst1 > myst2);
    ASSERT_EQ(libst1 >= libst2, myst1 >= myst2);
    ASSERT_EQ(libst1 <= libst2, myst1 <= myst2);
  }

  {
    std::set<int> libst1;
    libst1.insert(1);
    libst1.insert(-1);
    std::set<int> libst2;
    libst2.insert(1);
    libst2.insert(2);

    ft::set<int> myst1;
    myst1.insert(1);
    myst1.insert(-1);
    ft::set<int> myst2;
    myst2.insert(1);
    myst2.insert(2);

    ASSERT_EQ(libst1 == libst2, myst1 == myst2);
    ASSERT_EQ(libst1 != libst2, myst1 != myst2);
    ASSERT_EQ(libst1 < libst2, myst1 < myst2);
    ASSERT_EQ(libst1 > libst2, myst1 > myst2);
    ASSERT_EQ(libst1 >= libst2, myst1 >= myst2);
    ASSERT_EQ(libst1 <= libst2, myst1 <= myst2);
  }

  {
    std::set<int> libst1;
    libst1.insert(1);
    libst1.insert(2);
    libst1.insert(3);
    libst1.insert(4);
    libst1.insert(5);
    std::set<int> libst2;
    libst2.insert(1);
    libst2.insert(2);
    libst2.insert(3);
    libst2.insert(4);
    libst2.insert(5);

    ft::set<int> myst1;
    myst1.insert(1);
    myst1.insert(2);
    myst1.insert(3);
    myst1.insert(4);
    myst1.insert(5);
    ft::set<int> myst2;
    myst2.insert(1);
    myst2.insert(2);
    myst2.insert(3);
    myst2.insert(4);
    myst2.insert(5);

    ASSERT_EQ(libst1 == libst2, myst1 == myst2);
    ASSERT_EQ(libst1 != libst2, myst1 != myst2);
    ASSERT_EQ(libst1 < libst2, myst1 < myst2);
    ASSERT_EQ(libst1 > libst2, myst1 > myst2);
    ASSERT_EQ(libst1 >= libst2, myst1 >= myst2);
    ASSERT_EQ(libst1 <= libst2, myst1 <= myst2);
  }

  // non member swap
  {
    std::set<int> libdata1;
    libdata1.insert(1);
    std::set<int> libdata2;
    libdata2.insert(2);

    ft::set<int> mydata1;
    mydata1.insert(1);
    ft::set<int> mydata2;
    mydata2.insert(2);

    std::swap(libdata1, libdata2);
    ft::swap(mydata1, mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    libdata1.insert(2);
    libdata1.insert(3);
    std::set<int> libdata2;
    libdata2.insert(2);

    ft::set<int> mydata1;
    mydata1.insert(1);
    mydata1.insert(2);
    mydata1.insert(3);
    ft::set<int> mydata2;
    mydata2.insert(2);

    std::swap(libdata1, libdata2);
    ft::swap(mydata1, mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    libdata1.insert(2);
    libdata1.insert(3);
    std::set<int> libdata2;
    libdata2.insert(2);
    libdata2.insert(-1);
    libdata2.insert(-2);
    libdata2.insert(-3);
    libdata2.insert(-4);

    ft::set<int> mydata1;
    mydata1.insert(1);
    mydata1.insert(2);
    mydata1.insert(3);
    ft::set<int> mydata2;
    mydata2.insert(2);
    mydata2.insert(-1);
    mydata2.insert(-2);
    mydata2.insert(-3);
    mydata2.insert(-4);

    std::swap(libdata1, libdata2);
    ft::swap(mydata1, mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    libdata1.insert(2);
    libdata1.insert(3);
    libdata1.insert(-110);
    libdata1.insert(-11);
    libdata1.insert(-1);
    libdata1.insert(-203);
    libdata1.insert(102);
    libdata1.insert(10);
    std::set<int> libdata2;
    libdata2.insert(2);
    libdata2.insert(-1);
    libdata2.insert(-2);
    libdata2.insert(-3);
    libdata2.insert(-4);
    libdata2.insert(10000);
    libdata2.insert(10);
    libdata2.insert(122323);

    ft::set<int> mydata1;
    mydata1.insert(1);
    mydata1.insert(2);
    mydata1.insert(3);
    mydata1.insert(-110);
    mydata1.insert(-11);
    mydata1.insert(-1);
    mydata1.insert(-203);
    mydata1.insert(102);
    mydata1.insert(10);
    ft::set<int> mydata2;
    mydata2.insert(2);
    mydata2.insert(-1);
    mydata2.insert(-2);
    mydata2.insert(-3);
    mydata2.insert(-4);
    mydata2.insert(10000);
    mydata2.insert(10);
    mydata2.insert(122323);

    std::swap(libdata1, libdata2);
    ft::swap(mydata1, mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }

  {
    std::set<int> libdata1;
    libdata1.insert(1);
    libdata1.insert(2);
    libdata1.insert(3);
    libdata1.insert(-110);
    libdata1.insert(-11);
    libdata1.insert(-1);
    libdata1.insert(-203);
    libdata1.insert(102);
    libdata1.insert(10);
    std::set<int> libdata2;
    libdata2.insert(2);
    libdata2.insert(-1);
    libdata2.insert(-2);
    libdata2.insert(-3);
    libdata2.insert(-4);
    libdata2.insert(10000);
    libdata2.insert(10);
    libdata2.insert(122323);

    ft::set<int> mydata1;
    mydata1.insert(1);
    mydata1.insert(2);
    mydata1.insert(3);
    mydata1.insert(-110);
    mydata1.insert(-11);
    mydata1.insert(-1);
    mydata1.insert(-203);
    mydata1.insert(102);
    mydata1.insert(10);
    ft::set<int> mydata2;
    mydata2.insert(2);
    mydata2.insert(-1);
    mydata2.insert(-2);
    mydata2.insert(-3);
    mydata2.insert(-4);
    mydata2.insert(10000);
    mydata2.insert(10);
    mydata2.insert(122323);

    std::swap(libdata1, libdata2);
    ft::swap(mydata1, mydata2);

    ASSERT_EQ(libdata1.size(), mydata1.size());
    ASSERT_EQ(libdata2.size(), mydata2.size());

    std::set<int>::iterator libitr1 = libdata1.begin();
    std::set<int>::iterator libitr2 = libdata2.begin();
    ft::set<int>::iterator myitr1 = mydata1.begin();
    ft::set<int>::iterator myitr2 = mydata2.begin();

    for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(*libitr1, *myitr1);
    }
    for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(*libitr2, *myitr2);
    }
  }
}

void test_tree() {
  // __tree_iterator
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr1 = t.__begin();
    ft::__tree<int, int, ft::Identity<int> >::iterator itr2 = t.__begin();

    ASSERT_EQ(itr1 == itr2, true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr1 = t.__begin();
    ft::__tree<int, int, ft::Identity<int> >::iterator itr2 = t.__begin();
    ++itr2;

    ASSERT_EQ(itr1 == itr2, false);
    ASSERT_EQ(itr1 != itr2, true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr1 = t.__begin();
    ft::__tree<int, int, ft::Identity<int> >::iterator itr2 = t.__end();

    ASSERT_EQ(itr1 == itr2, false);
    ASSERT_EQ(itr1 != itr2, true);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::iterator itr1 =
        t.__begin();
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::iterator itr2 =
        t.__begin();

    ASSERT_EQ(itr1 == itr2, true);
    ASSERT_EQ(itr1 != itr2, false);
  }

  // __begin
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);

    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);

    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 4);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);
    t.__insert(5);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 4);
    ++itr;
    ASSERT_EQ(*itr, 5);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);
    t.__insert(5);
    t.__insert(6);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 4);
    ++itr;
    ASSERT_EQ(*itr, 5);
    ++itr;
    ASSERT_EQ(*itr, 6);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-1);
    t.__insert(2);
    t.__insert(-2);
    t.__insert(3);
    t.__insert(-4);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -4);
    ++itr;
    ASSERT_EQ(*itr, -2);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-1);
    t.__insert(2);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-1);
    t.__insert(2);
    t.__insert(-2);

    //            1r
    //      +-----+-----+
    //     -1b           2b
    //  +---+---+
    // -2r

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -2);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-1);
    t.__insert(2);
    t.__insert(-2);
    t.__insert(3);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -2);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-1);
    t.__insert(2);
    t.__insert(-2);
    t.__insert(3);
    t.__insert(-10);
    t.__insert(-5);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();

    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -5);
    ++itr;
    ASSERT_EQ(*itr, -2);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(204);
    t.__insert(205);
    t.__insert(206);
    t.__insert(93);
    t.__insert(192);
    t.__insert(202);
    t.__insert(0);
    t.__insert(305);
    t.__insert(213);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 0);
    ++itr;
    ASSERT_EQ(*itr, 93);
    ++itr;
    ASSERT_EQ(*itr, 192);
    ++itr;
    ASSERT_EQ(*itr, 202);
    ++itr;
    ASSERT_EQ(*itr, 204);
    ++itr;
    ASSERT_EQ(*itr, 205);
    ++itr;
    ASSERT_EQ(*itr, 206);
    ++itr;
    ASSERT_EQ(*itr, 213);
    ++itr;
    ASSERT_EQ(*itr, 305);
    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(200);
    t.__insert(196);
    t.__insert(193);
    t.__insert(187);
    t.__insert(175);
    t.__insert(150);
    t.__insert(125);
    t.__insert(112);
    t.__insert(106);
    t.__insert(103);
    t.__insert(100);
    t.__insert(96);
    t.__insert(93);
    t.__insert(87);
    t.__insert(75);
    t.__insert(50);
    t.__insert(25);
    t.__insert(12);
    t.__insert(6);
    t.__insert(3);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 6);
    ++itr;
    ASSERT_EQ(*itr, 12);
    ++itr;
    ASSERT_EQ(*itr, 25);
    ++itr;
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(*itr, 75);
    ++itr;
    ASSERT_EQ(*itr, 87);
    ++itr;
    ASSERT_EQ(*itr, 93);
    ++itr;
    ASSERT_EQ(*itr, 96);
    ++itr;
    ASSERT_EQ(*itr, 100);
    ++itr;
    ASSERT_EQ(*itr, 103);
    ++itr;
    ASSERT_EQ(*itr, 106);
    ++itr;
    ASSERT_EQ(*itr, 112);
    ++itr;
    ASSERT_EQ(*itr, 125);
    ++itr;
    ASSERT_EQ(*itr, 150);
    ++itr;
    ASSERT_EQ(*itr, 175);
    ++itr;
    ASSERT_EQ(*itr, 187);
    ++itr;
    ASSERT_EQ(*itr, 193);
    ++itr;
    ASSERT_EQ(*itr, 196);
    ++itr;
    ASSERT_EQ(*itr, 200);
    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(6);
    t.__insert(175);
    t.__insert(125);
    t.__insert(100);
    t.__insert(150);
    t.__insert(196);
    t.__insert(103);
    t.__insert(87);
    t.__insert(187);
    t.__insert(200);
    t.__insert(93);
    t.__insert(96);
    t.__insert(3);
    t.__insert(106);
    t.__insert(12);
    t.__insert(193);
    t.__insert(50);
    t.__insert(75);
    t.__insert(25);
    t.__insert(112);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 6);
    ++itr;
    ASSERT_EQ(*itr, 12);
    ++itr;
    ASSERT_EQ(*itr, 25);
    ++itr;
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(*itr, 75);
    ++itr;
    ASSERT_EQ(*itr, 87);
    ++itr;
    ASSERT_EQ(*itr, 93);
    ++itr;
    ASSERT_EQ(*itr, 96);
    ++itr;
    ASSERT_EQ(*itr, 100);
    ++itr;
    ASSERT_EQ(*itr, 103);
    ++itr;
    ASSERT_EQ(*itr, 106);
    ++itr;
    ASSERT_EQ(*itr, 112);
    ++itr;
    ASSERT_EQ(*itr, 125);
    ++itr;
    ASSERT_EQ(*itr, 150);
    ++itr;
    ASSERT_EQ(*itr, 175);
    ++itr;
    ASSERT_EQ(*itr, 187);
    ++itr;
    ASSERT_EQ(*itr, 193);
    ++itr;
    ASSERT_EQ(*itr, 196);
    ++itr;
    ASSERT_EQ(*itr, 200);
    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(204);
    t.__insert(205);
    t.__insert(206);
    t.__insert(93);
    t.__insert(192);
    t.__insert(202);
    t.__insert(0);
    t.__insert(305);
    t.__insert(213);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__end();
    --itr;
    ASSERT_EQ(*itr, 305);
    --itr;
    ASSERT_EQ(*itr, 213);
    --itr;
    ASSERT_EQ(*itr, 206);
    --itr;
    ASSERT_EQ(*itr, 205);
    --itr;
    ASSERT_EQ(*itr, 204);
    --itr;
    ASSERT_EQ(*itr, 202);
    --itr;
    ASSERT_EQ(*itr, 192);
    --itr;
    ASSERT_EQ(*itr, 93);
    --itr;
    ASSERT_EQ(*itr, 0);
    ASSERT_EQ(itr, t.__begin());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(200);
    t.__insert(196);
    t.__insert(193);
    t.__insert(187);
    t.__insert(175);
    t.__insert(150);
    t.__insert(125);
    t.__insert(112);
    t.__insert(106);
    t.__insert(103);
    t.__insert(100);
    t.__insert(96);
    t.__insert(93);
    t.__insert(87);
    t.__insert(75);
    t.__insert(50);
    t.__insert(25);
    t.__insert(12);
    t.__insert(6);
    t.__insert(3);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__end();

    --itr;
    ASSERT_EQ(*itr, 200);
    --itr;
    ASSERT_EQ(*itr, 196);
    --itr;
    ASSERT_EQ(*itr, 193);
    --itr;
    ASSERT_EQ(*itr, 187);
    --itr;
    ASSERT_EQ(*itr, 175);
    --itr;
    ASSERT_EQ(*itr, 150);
    --itr;
    ASSERT_EQ(*itr, 125);
    --itr;
    ASSERT_EQ(*itr, 112);
    --itr;
    ASSERT_EQ(*itr, 106);
    --itr;
    ASSERT_EQ(*itr, 103);
    --itr;
    ASSERT_EQ(*itr, 100);
    --itr;
    ASSERT_EQ(*itr, 96);
    --itr;
    ASSERT_EQ(*itr, 93);
    --itr;
    ASSERT_EQ(*itr, 87);
    --itr;
    ASSERT_EQ(*itr, 75);
    --itr;
    ASSERT_EQ(*itr, 50);
    --itr;
    ASSERT_EQ(*itr, 25);
    --itr;
    ASSERT_EQ(*itr, 12);
    --itr;
    ASSERT_EQ(*itr, 6);
    --itr;
    ASSERT_EQ(*itr, 3);

    ASSERT_EQ(itr, t.__begin());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(6);
    t.__insert(175);
    t.__insert(125);
    t.__insert(100);
    t.__insert(150);
    t.__insert(196);
    t.__insert(103);
    t.__insert(87);
    t.__insert(187);
    t.__insert(200);
    t.__insert(93);
    t.__insert(96);
    t.__insert(3);
    t.__insert(106);
    t.__insert(12);
    t.__insert(193);
    t.__insert(50);
    t.__insert(75);
    t.__insert(25);
    t.__insert(112);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__end();

    --itr;
    ASSERT_EQ(*itr, 200);
    --itr;
    ASSERT_EQ(*itr, 196);
    --itr;
    ASSERT_EQ(*itr, 193);
    --itr;
    ASSERT_EQ(*itr, 187);
    --itr;
    ASSERT_EQ(*itr, 175);
    --itr;
    ASSERT_EQ(*itr, 150);
    --itr;
    ASSERT_EQ(*itr, 125);
    --itr;
    ASSERT_EQ(*itr, 112);
    --itr;
    ASSERT_EQ(*itr, 106);
    --itr;
    ASSERT_EQ(*itr, 103);
    --itr;
    ASSERT_EQ(*itr, 100);
    --itr;
    ASSERT_EQ(*itr, 96);
    --itr;
    ASSERT_EQ(*itr, 93);
    --itr;
    ASSERT_EQ(*itr, 87);
    --itr;
    ASSERT_EQ(*itr, 75);
    --itr;
    ASSERT_EQ(*itr, 50);
    --itr;
    ASSERT_EQ(*itr, 25);
    --itr;
    ASSERT_EQ(*itr, 12);
    --itr;
    ASSERT_EQ(*itr, 6);
    --itr;
    ASSERT_EQ(*itr, 3);

    ASSERT_EQ(itr, t.__begin());
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::iterator itr = t.__begin();
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);

    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(2, 2));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::iterator itr = t.__begin();
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
    ++itr;
    ASSERT_EQ(itr->first, 2);
    ASSERT_EQ(itr->second, 2);

    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(2, 2));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::iterator itr = t.__begin();
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
    ++itr;
    ASSERT_EQ(itr->first, 2);
    ASSERT_EQ(itr->second, 2);

    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  // __begin const
  {
    ft::__tree<int, int, ft::Identity<int> > data;
    data.__insert(1);
    const ft::__tree<int, int, ft::Identity<int> > t(data.__begin(),
                                                     data.__end());
    ft::__tree<int, int, ft::Identity<int> >::__const_iterator itr =
        t.__begin();
    ASSERT_EQ(*itr, 1);

    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  // __end
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__end();
    --itr;
    ASSERT_EQ(*itr, 1);

    ASSERT_EQ(itr, t.__begin());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__end();
    --itr;
    ASSERT_EQ(*itr, 2);
    --itr;
    ASSERT_EQ(*itr, 1);

    ASSERT_EQ(itr, t.__begin());
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::iterator itr = t.__end();
    --itr;
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);

    ASSERT_EQ(itr, t.__begin());
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(2, 2));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::iterator itr = t.__end();
    --itr;
    ASSERT_EQ(itr->first, 2);
    ASSERT_EQ(itr->second, 2);
    --itr;
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);

    ASSERT_EQ(itr, t.__begin());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-1);
    t.__insert(2);
    t.__insert(-2);
    t.__insert(3);
    t.__insert(-10);
    t.__insert(-5);
    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__end();

    --itr;
    ASSERT_EQ(*itr, 3);
    --itr;
    ASSERT_EQ(*itr, 2);
    --itr;
    ASSERT_EQ(*itr, 1);
    --itr;
    ASSERT_EQ(*itr, -1);
    --itr;
    ASSERT_EQ(*itr, -2);
    --itr;
    ASSERT_EQ(*itr, -5);
    --itr;
    ASSERT_EQ(*itr, -10);

    ASSERT_EQ(itr, t.__begin());
  }

  // __rbegin
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    ft::__tree<int, int, ft::Identity<int> >::reverse_iterator itr =
        t.__rbegin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(itr, t.__rend());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    ft::__tree<int, int, ft::Identity<int> >::reverse_iterator itr =
        t.__rbegin();
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(itr, t.__rend());
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::reverse_iterator itr =
        t.__rbegin();
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
    ++itr;
    ASSERT_EQ(itr, t.__rend());
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(2, 2));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::reverse_iterator itr =
        t.__rbegin();
    ASSERT_EQ(itr->first, 2);
    ASSERT_EQ(itr->second, 2);
    ++itr;
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
    ++itr;
    ASSERT_EQ(itr, t.__rend());
  }

  // __rend
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    ft::__tree<int, int, ft::Identity<int> >::reverse_iterator itr = t.__rend();
    --itr;
    ASSERT_EQ(*itr, 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    ft::__tree<int, int, ft::Identity<int> >::reverse_iterator itr = t.__rend();
    --itr;
    ASSERT_EQ(*itr, 1);
    --itr;
    ASSERT_EQ(*itr, 2);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::reverse_iterator itr =
        t.__rend();
    --itr;
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(2, 2));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::reverse_iterator itr =
        t.__rend();
    --itr;
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
    --itr;
    ASSERT_EQ(itr->first, 2);
    ASSERT_EQ(itr->second, 2);
  }

  // __insert
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();

    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->__is_nil_node(), true);

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->left->parent, root);

    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->parent, root);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();
    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->__is_red_node(), true);
    ASSERT_EQ(root->right->right->__is_nil_node(), true);
    ASSERT_EQ(root->right->left->__is_nil_node(), true);

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->right->right->parent, root->right);
    ASSERT_EQ(root->right->left->parent, root->right);

    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->right->value, 2);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-1);
    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();
    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->left->__is_red_node(), true);

    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->left->value, -1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);

    //      2b
    //  +---+---+
    // 1r        3r

    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->left->left->parent, root->left);
    ASSERT_EQ(root->left->right->parent, root->left);
    ASSERT_EQ(root->right->left->parent, root->right);
    ASSERT_EQ(root->right->right->parent, root->right);

    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->left->__is_red_node(), true);
    ASSERT_EQ(root->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->left->right->__is_nil_node(), true);

    ASSERT_EQ(root->right->__is_red_node(), true);
    ASSERT_EQ(root->right->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->right->__is_nil_node(), true);

    ASSERT_EQ(root->value, 2);
    ASSERT_EQ(root->right->value, 3);
    ASSERT_EQ(root->left->value, 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(-1);
    t.__insert(-2);
    t.__insert(-3);
    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();
    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->left->__is_red_node(), true);
    ASSERT_EQ(root->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->left->right->__is_nil_node(), true);
    ASSERT_EQ(root->right->__is_red_node(), true);
    ASSERT_EQ(root->right->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->right->__is_nil_node(), true);

    ASSERT_EQ(root->value, -2);
    ASSERT_EQ(root->right->value, -1);
    ASSERT_EQ(root->left->value, -3);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);

    //               2b
    //        +------+------+
    //        1b            3b
    //    +---+---+     +---+---+
    //                          4r

    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();
    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->left->__is_black_node(), true);
    ASSERT_EQ(root->right->__is_black_node(), true);
    ASSERT_EQ(root->right->right->__is_red_node(), true);

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->right->right->parent, root->right);

    ASSERT_EQ(root->value, 2);
    ASSERT_EQ(root->left->value, 1);
    ASSERT_EQ(root->right->value, 3);
    ASSERT_EQ(root->right->right->value, 4);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);
    t.__insert(5);

    //               2b
    //        +------+------+
    //        1b            4b
    //    +---+---+     +---+---+
    //                  3r       5r

    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();

    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->left->__is_black_node(), true);
    ASSERT_EQ(root->right->__is_black_node(), true);
    ASSERT_EQ(root->right->left->__is_red_node(), true);
    ASSERT_EQ(root->right->right->__is_red_node(), true);

    ASSERT_EQ(root->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->left->right->__is_nil_node(), true);
    ASSERT_EQ(root->right->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->left->right->__is_nil_node(), true);
    ASSERT_EQ(root->right->right->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->right->right->__is_nil_node(), true);

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->left->left->parent, root->left);
    ASSERT_EQ(root->left->right->parent, root->left);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->right->left->parent, root->right);
    ASSERT_EQ(root->right->right->parent, root->right);
    ASSERT_EQ(root->right->left->left->parent, root->right->left);
    ASSERT_EQ(root->right->left->right->parent, root->right->left);
    ASSERT_EQ(root->right->right->left->parent, root->right->right);
    ASSERT_EQ(root->right->right->right->parent, root->right->right);

    ASSERT_EQ(root->value, 2);
    ASSERT_EQ(root->left->value, 1);
    ASSERT_EQ(root->right->value, 4);
    ASSERT_EQ(root->right->left->value, 3);
    ASSERT_EQ(root->right->right->value, 5);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-1);
    t.__insert(2);
    t.__insert(-2);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();

    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->left->__is_black_node(), true);
    ASSERT_EQ(root->left->left->__is_red_node(), true);
    ASSERT_EQ(root->left->right->__is_nil_node(), true);
    ASSERT_EQ(root->left->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->left->left->right->__is_nil_node(), true);
    ASSERT_EQ(root->right->__is_black_node(), true);
    ASSERT_EQ(root->right->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->right->__is_nil_node(), true);

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->left->left->parent, root->left);
    ASSERT_EQ(root->left->right->parent, root->left);
    ASSERT_EQ(root->left->left->left->parent, root->left->left);
    ASSERT_EQ(root->left->left->right->parent, root->left->left);
    ASSERT_EQ(root->right->left->parent, root->right);
    ASSERT_EQ(root->right->right->parent, root->right);

    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->left->value, -1);
    ASSERT_EQ(root->right->value, 2);
    ASSERT_EQ(root->left->left->value, -2);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-1);
    t.__insert(2);
    t.__insert(-2);
    t.__insert(3);
    t.__insert(-3);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();

    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->left->__is_black_node(), true);
    ASSERT_EQ(root->left->left->__is_red_node(), true);
    ASSERT_EQ(root->left->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->left->left->right->__is_nil_node(), true);
    ASSERT_EQ(root->left->right->__is_red_node(), true);
    ASSERT_EQ(root->left->right->left->__is_nil_node(), true);
    ASSERT_EQ(root->left->right->right->__is_nil_node(), true);
    ASSERT_EQ(root->right->__is_black_node(), true);
    ASSERT_EQ(root->right->right->__is_red_node(), true);
    ASSERT_EQ(root->right->right->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->right->right->__is_nil_node(), true);
    ASSERT_EQ(root->right->left->__is_nil_node(), true);

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->left->left->parent, root->left);
    ASSERT_EQ(root->left->right->parent, root->left);
    ASSERT_EQ(root->left->left->left->parent, root->left->left);
    ASSERT_EQ(root->left->left->right->parent, root->left->left);
    ASSERT_EQ(root->left->right->left->parent, root->left->right);
    ASSERT_EQ(root->left->right->right->parent, root->left->right);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->right->left->parent, root->right);
    ASSERT_EQ(root->right->right->parent, root->right);
    ASSERT_EQ(root->right->right->right->parent, root->right->right);
    ASSERT_EQ(root->right->right->left->parent, root->right->right);

    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->left->value, -2);
    ASSERT_EQ(root->left->left->value, -3);
    ASSERT_EQ(root->left->right->value, -1);
    ASSERT_EQ(root->right->value, 2);
    ASSERT_EQ(root->right->right->value, 3);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-10);
    t.__insert(10);
    t.__insert(-5);
    t.__insert(15);
    t.__insert(20);
    t.__insert(-12);
    t.__insert(100);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();

    ASSERT_EQ(root->__is_black_node(), true);

    ASSERT_EQ(root->left->__is_black_node(), true);
    ASSERT_EQ(root->left->left->__is_red_node(), true);
    ASSERT_EQ(root->left->right->__is_red_node(), true);

    ASSERT_EQ(root->left->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->left->left->right->__is_nil_node(), true);

    ASSERT_EQ(root->left->right->left->__is_nil_node(), true);
    ASSERT_EQ(root->left->right->right->__is_nil_node(), true);

    ASSERT_EQ(root->right->__is_red_node(), true);
    ASSERT_EQ(root->right->left->__is_black_node(), true);
    ASSERT_EQ(root->right->right->__is_black_node(), true);

    ASSERT_EQ(root->right->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->left->right->__is_nil_node(), true);

    ASSERT_EQ(root->right->right->right->__is_red_node(), true);
    ASSERT_EQ(root->right->right->right->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->right->right->right->__is_nil_node(), true);

    ASSERT_EQ(root->parent, root);

    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->left->left->parent, root->left);
    ASSERT_EQ(root->left->right->parent, root->left);

    ASSERT_EQ(root->left->left->left->parent, root->left->left);
    ASSERT_EQ(root->left->left->right->parent, root->left->left);

    ASSERT_EQ(root->left->right->left->parent, root->left->right);
    ASSERT_EQ(root->left->right->right->parent, root->left->right);

    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->right->left->parent, root->right);
    ASSERT_EQ(root->right->right->parent, root->right);

    ASSERT_EQ(root->right->left->left->parent, root->right->left);
    ASSERT_EQ(root->right->left->right->parent, root->right->left);

    ASSERT_EQ(root->right->right->left->parent, root->right->right);
    ASSERT_EQ(root->right->right->right->parent, root->right->right);

    ASSERT_EQ(root->right->right->right->left->parent,
              root->right->right->right);
    ASSERT_EQ(root->right->right->right->right->parent,
              root->right->right->right);

    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->left->value, -10);
    ASSERT_EQ(root->left->left->value, -12);
    ASSERT_EQ(root->left->right->value, -5);
    ASSERT_EQ(root->right->value, 15);
    ASSERT_EQ(root->right->left->value, 10);
    ASSERT_EQ(root->right->right->value, 20);
    ASSERT_EQ(root->right->right->right->value, 100);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(204);
    t.__insert(205);
    t.__insert(206);
    t.__insert(93);
    t.__insert(192);
    t.__insert(202);
    t.__insert(0);
    t.__insert(305);
    t.__insert(213);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();

    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->left->__is_red_node(), true);
    ASSERT_EQ(root->left->left->__is_black_node(), true);
    ASSERT_EQ(root->left->left->right->__is_nil_node(), true);
    ASSERT_EQ(root->left->left->left->__is_red_node(), true);
    ASSERT_EQ(root->left->left->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->left->left->left->right->__is_nil_node(), true);
    ASSERT_EQ(root->left->right->__is_black_node(), true);
    ASSERT_EQ(root->left->right->right->__is_nil_node(), true);
    ASSERT_EQ(root->left->right->left->__is_red_node(), true);
    ASSERT_EQ(root->left->right->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->left->right->left->right->__is_nil_node(), true);
    ASSERT_EQ(root->right->__is_black_node(), true);
    ASSERT_EQ(root->right->left->__is_red_node(), true);
    ASSERT_EQ(root->right->left->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->left->right->__is_nil_node(), true);
    ASSERT_EQ(root->right->right->__is_red_node(), true);
    ASSERT_EQ(root->right->right->left->__is_nil_node(), true);
    ASSERT_EQ(root->right->right->right->__is_nil_node(), true);

    ASSERT_EQ(root->value, 205);
    ASSERT_EQ(root->left->value, 192);
    ASSERT_EQ(root->left->left->value, 93);
    ASSERT_EQ(root->left->right->value, 204);
    ASSERT_EQ(root->left->right->left->value, 202);
    ASSERT_EQ(root->left->left->left->value, 0);
    ASSERT_EQ(root->right->value, 213);
    ASSERT_EQ(root->right->left->value, 206);
    ASSERT_EQ(root->right->right->value, 305);

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->left->left->parent, root->left);
    ASSERT_EQ(root->left->left->left->parent, root->left->left);
    ASSERT_EQ(root->left->left->right->parent, root->left->left);
    ASSERT_EQ(root->left->left->left->left->parent, root->left->left->left);
    ASSERT_EQ(root->left->left->left->right->parent, root->left->left->left);
    ASSERT_EQ(root->left->right->parent, root->left);
    ASSERT_EQ(root->left->right->left->parent, root->left->right);
    ASSERT_EQ(root->left->right->right->parent, root->left->right);
    ASSERT_EQ(root->left->right->left->left->parent, root->left->right->left);
    ASSERT_EQ(root->left->right->left->right->parent, root->left->right->left);
    ASSERT_EQ(root->left->right->right->parent, root->left->right);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->right->left->parent, root->right);
    ASSERT_EQ(root->right->left->left->parent, root->right->left);
    ASSERT_EQ(root->right->left->right->parent, root->right->left);
    ASSERT_EQ(root->right->right->parent, root->right);
    ASSERT_EQ(root->right->right->left->parent, root->right->right);
    ASSERT_EQ(root->right->right->right->parent, root->right->right);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(2, 2));
    ft::__tree<int, ft::pair<int, int>,
               ft::Select1st<ft::pair<int, int> > >::node_pointer root =
        t.root();
    ASSERT_EQ(root->__is_black_node(), true);
    ASSERT_EQ(root->value.first, 1);
    ASSERT_EQ(root->value.second, 1);
    ASSERT_EQ(root->right->__is_red_node(), true);
    ASSERT_EQ(root->right->value.first, 2);
    ASSERT_EQ(root->right->value.second, 2);
    ASSERT_EQ(root->right->parent, root);
  }

  // __size
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    ASSERT_EQ(t.__size(), 1);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    ASSERT_EQ(t.__size(), 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    ASSERT_EQ(t.__size(), 2);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    ASSERT_EQ(t.__size(), 3);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(1);
    t.__insert(1);
    ASSERT_EQ(t.__size(), 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(1);
    ASSERT_EQ(t.__size(), 2);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(2, 2));
    ASSERT_EQ(t.__size(), 2);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(2, 2));
    t.__insert(ft::make_pair(3, 3));
    ASSERT_EQ(t.__size(), 3);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(1, 1));
    ASSERT_EQ(t.__size(), 1);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(1, 2));
    t.__insert(ft::make_pair(1, 3));
    ASSERT_EQ(t.__size(), 1);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    t.__insert(ft::make_pair(2, 2));
    t.__insert(ft::make_pair(1, 3));
    ASSERT_EQ(t.__size(), 2);
  }

  // __empty
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    ASSERT_EQ(t.__empty(), true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    ASSERT_EQ(t.__empty(), false);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    ASSERT_EQ(t.__empty(), true);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));
    ASSERT_EQ(t.__empty(), false);
  }

  // __find
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__find(1);

    ASSERT_EQ(*itr, 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__find(1);

    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__find(1);

    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);
    t.__insert(5);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__find(1);

    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 4);
    ++itr;
    ASSERT_EQ(*itr, 5);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);
    t.__insert(5);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__find(3);

    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 4);
    ++itr;
    ASSERT_EQ(*itr, 5);
  }

  // __lower_bound
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__insert(20);
    t.__insert(30);
    t.__insert(40);
    t.__insert(50);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr =
        t.__lower_bound(10);

    ASSERT_EQ(*itr, 10);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(*itr, 50);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__insert(20);
    t.__insert(30);
    t.__insert(40);
    t.__insert(50);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr =
        t.__lower_bound(11);

    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(*itr, 50);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__insert(5);
    t.__insert(15);
    t.__insert(-10);
    t.__insert(20);

    ASSERT_EQ(*(t.__lower_bound(-10)), -10);
    ASSERT_EQ(*(t.__lower_bound(5)), 5);
    ASSERT_EQ(*(t.__lower_bound(10)), 10);
    ASSERT_EQ(*(t.__lower_bound(15)), 15);
    ASSERT_EQ(*(t.__lower_bound(20)), 20);
    ASSERT_EQ(*(t.__lower_bound(-100)), -10);
    ASSERT_EQ(*(t.__lower_bound(1)), 5);
    ASSERT_EQ(*(t.__lower_bound(6)), 10);
    ASSERT_EQ(*(t.__lower_bound(11)), 15);
    ASSERT_EQ(*(t.__lower_bound(16)), 20);
    ASSERT_EQ(t.__lower_bound(100), t.__end());
  }

  // __find_node_pointer
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
        t.__find_node_pointer(1);

    ASSERT_EQ(ptr->value, 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
        t.__find_node_pointer(1);

    ASSERT_EQ(ptr->value, 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
        t.__find_node_pointer(2);

    ASSERT_EQ(ptr->value, 2);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
        t.__find_node_pointer(1);

    ASSERT_EQ(ptr->value, 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
        t.__find_node_pointer(2);

    ASSERT_EQ(ptr->value, 2);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
        t.__find_node_pointer(3);

    ASSERT_EQ(ptr->value, 3);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
        t.__find_node_pointer(4);

    ASSERT_EQ(ptr->value, 4);
  }

  // upper_bound
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__insert(20);
    t.__insert(30);
    t.__insert(40);
    t.__insert(50);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr =
        t.__uppper_bound(10);

    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(*itr, 50);
  }

  // count
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);

    ASSERT_EQ(t.__count(10), 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);

    ASSERT_EQ(t.__count(42), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);

    ASSERT_EQ(t.__count(42), 0);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));

    ASSERT_EQ(t.__count(1), 1);
  }

  {
    ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
    t.__insert(ft::make_pair(1, 1));

    ASSERT_EQ(t.__count(42), 0);
  }

  // // max_size

  // operator==
  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    ft::__tree<int, int, ft::Identity<int> > t2;
    ASSERT_EQ(t1 == t2, true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    ft::__tree<int, int, ft::Identity<int> > t2;
    ASSERT_EQ(t1 != t2, true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    t1.__insert(2);
    ft::__tree<int, int, ft::Identity<int> > t2;
    t2.__insert(1);
    t2.__insert(3);
    ASSERT_EQ(t1 < t2, true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    t1.__insert(2);
    ft::__tree<int, int, ft::Identity<int> > t2;
    t2.__insert(1);
    t2.__insert(2);
    ASSERT_EQ(t1 >= t2, true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    t1.__insert(3);
    ft::__tree<int, int, ft::Identity<int> > t2;
    t2.__insert(1);
    t2.__insert(2);
    ASSERT_EQ(t1 >= t2, true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    t1.__insert(3);
    ft::__tree<int, int, ft::Identity<int> > t2;
    t2.__insert(1);
    t2.__insert(2);
    ASSERT_EQ(t1 > t2, true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    t1.__insert(2);
    ft::__tree<int, int, ft::Identity<int> > t2;
    t2.__insert(1);
    t2.__insert(2);
    ASSERT_EQ(t1 <= t2, true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    t1.__insert(2);
    ft::__tree<int, int, ft::Identity<int> > t2;
    t2.__insert(1);
    t2.__insert(3);
    ASSERT_EQ(t1 <= t2, true);
  }

  // __erase
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__erase(1);

    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__erase(2);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer r = t.root();

    ASSERT_EQ(t.__size(), 1);

    ASSERT_EQ(r->__is_black_node(), true);
    ASSERT_EQ(r->left->__is_nil_node(), true);
    ASSERT_EQ(r->right->__is_nil_node(), true);

    ASSERT_EQ(r->parent, r);

    ASSERT_EQ(r->value, 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);

    t.__erase(1);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer r = t.root();

    ASSERT_EQ(t.__size(), 1);

    ASSERT_EQ(r->__is_black_node(), true);
    ASSERT_EQ(r->left->__is_nil_node(), true);
    ASSERT_EQ(r->right->__is_black_node(), true);
    ASSERT_EQ(r->right->__is_nil_node(), true);

    ASSERT_EQ(r->parent, r);

    ASSERT_EQ(r->value, 2);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);

    t.__erase(1);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer r = t.root();

    ASSERT_EQ(t.__size(), 2);

    ASSERT_EQ(r->__is_black_node(), true);
    ASSERT_EQ(r->left->__is_nil_node(), true);
    ASSERT_EQ(r->right->__is_red_node(), true);
    ASSERT_EQ(r->right->right->__is_nil_node(), true);
    ASSERT_EQ(r->right->left->__is_nil_node(), true);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->right->parent, r);
    ASSERT_EQ(r->right->left->parent, r->right);
    ASSERT_EQ(r->right->right->parent, r->right);

    ASSERT_EQ(r->value, 2);
    ASSERT_EQ(r->right->value, 3);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);

    t.__erase(2);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer r = t.root();

    ASSERT_EQ(t.__size(), 2);

    ASSERT_EQ(r->__is_black_node(), true);
    ASSERT_EQ(r->left->__is_black_node(), false);
    ASSERT_EQ(r->left->__is_red_node(), true);
    ASSERT_EQ(r->left->left->__is_nil_node(), true);
    ASSERT_EQ(r->left->right->__is_nil_node(), true);
    ASSERT_EQ(r->right->__is_nil_node(), true);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->left->left->parent, r->left);
    ASSERT_EQ(r->left->right->parent, r->left);
    ASSERT_EQ(r->right->parent, r);

    ASSERT_EQ(r->value, 3);
    ASSERT_EQ(r->left->value, 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);

    t.__erase(3);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer r = t.root();

    ASSERT_EQ(t.__size(), 2);

    ASSERT_EQ(r->__is_black_node(), true);
    ASSERT_EQ(r->left->__is_red_node(), true);
    ASSERT_EQ(r->left->left->__is_nil_node(), true);
    ASSERT_EQ(r->left->right->__is_nil_node(), true);
    ASSERT_EQ(r->right->__is_nil_node(), true);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->left->left->parent, r->left);
    ASSERT_EQ(r->left->right->parent, r->left);
    ASSERT_EQ(r->right->parent, r);

    ASSERT_EQ(r->value, 2);
    ASSERT_EQ(r->left->value, 1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);

    t.__erase(1);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer r = t.root();

    ASSERT_EQ(t.__size(), 3);

    ASSERT_EQ(r->__is_black_node(), true);
    ASSERT_EQ(r->left->__is_black_node(), true);
    ASSERT_EQ(r->left->left->__is_nil_node(), true);
    ASSERT_EQ(r->left->right->__is_nil_node(), true);
    ASSERT_EQ(r->right->__is_black_node(), true);
    ASSERT_EQ(r->right->left->__is_nil_node(), true);
    ASSERT_EQ(r->right->right->__is_nil_node(), true);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->left->left->parent, r->left);
    ASSERT_EQ(r->left->right->parent, r->left);
    ASSERT_EQ(r->right->parent, r);
    ASSERT_EQ(r->right->left->parent, r->right);
    ASSERT_EQ(r->right->right->parent, r->right);

    ASSERT_EQ(r->value, 3);
    ASSERT_EQ(r->left->value, 2);
    ASSERT_EQ(r->right->value, 4);
  }

  // erase iterator
  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);

    t.__erase(2);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);

    t.__erase(1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);

    t.__erase(-1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);

    t.__erase(1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);

    t.__erase(2);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);

    t.__erase(-1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);

    t.__erase(1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);

    t.__erase(2);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);

    t.__erase(10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);

    t.__erase(-1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);

    t.__erase(1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);

    t.__erase(2);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);

    t.__erase(10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);
    t.__insert(5);

    t.__erase(-10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 5);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);
    t.__insert(5);

    t.__erase(-1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 5);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);
    t.__insert(5);

    t.__erase(1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 5);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);
    t.__insert(5);

    t.__erase(2);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 5);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);
    t.__insert(5);

    t.__erase(5);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);
    t.__insert(5);

    t.__erase(10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 5);
    ++itr;

    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);

    t.__erase(1);
    t.__erase(2);

    ASSERT_EQ(t.__empty(), true);
    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);

    t.__erase(1);
    t.__erase(2);
    t.__erase(-1);

    ASSERT_EQ(t.__empty(), true);
    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);

    t.__erase(1);
    t.__erase(2);
    t.__erase(-1);
    t.__erase(10);

    ASSERT_EQ(t.__empty(), true);
    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);

    t.__erase(1);
    t.__erase(2);
    t.__erase(-1);
    t.__erase(10);
    t.__erase(-10);

    ASSERT_EQ(t.__empty(), true);
    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(10);
    t.__insert(-10);
    t.__insert(5);

    t.__erase(1);
    t.__erase(2);
    t.__erase(-1);
    t.__erase(10);
    t.__erase(-10);
    t.__erase(5);

    ASSERT_EQ(t.__empty(), true);
    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(20);
    t.__insert(10);
    t.__insert(200);
    t.__insert(1);
    t.__insert(500);
    t.__insert(300);

    t.__erase(100);
    t.__erase(20);
    t.__erase(10);
    t.__erase(200);

    ft::__tree<int, int, ft::Identity<int> >::node_pointer r = t.root();
    ASSERT_EQ(r->__is_black_node(), true);
    ASSERT_EQ(r->left->__is_black_node(), true);
    ASSERT_EQ(r->right->__is_black_node(), true);
    ASSERT_EQ(r->left->left->__is_nil_node(), true);
    ASSERT_EQ(r->left->right->__is_nil_node(), true);
    ASSERT_EQ(r->right->left->__is_nil_node(), true);
    ASSERT_EQ(r->right->right->__is_nil_node(), true);

    ASSERT_EQ(r->value, 300);
    ASSERT_EQ(r->left->value, 1);
    ASSERT_EQ(r->right->value, 500);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->right->parent, r);
    ASSERT_EQ(r->left->left->parent, r->left);
    ASSERT_EQ(r->left->right->parent, r->left);
    ASSERT_EQ(r->right->left->parent, r->right);
    ASSERT_EQ(r->right->right->parent, r->right);

    ASSERT_EQ(t.__size(), 3);

    t.__erase(1);
    t.__erase(500);
    t.__erase(300);

    ASSERT_EQ(t.__empty(), true);
    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__erase(10);
    t.__insert(20);
    t.__erase(20);
    t.__insert(30);
    t.__erase(30);

    ASSERT_EQ(t.__empty(), true);
    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__insert(20);
    t.__erase(10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__insert(10);

    itr = t.__begin();
    ASSERT_EQ(*itr, 10);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__insert(20);
    t.__insert(30);
    t.__erase(10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__insert(10);

    itr = t.__begin();
    ASSERT_EQ(*itr, 10);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__insert(20);
    t.__insert(30);
    t.__insert(40);
    t.__erase(10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__insert(10);

    itr = t.__begin();
    ASSERT_EQ(*itr, 10);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__insert(20);
    t.__insert(30);
    t.__insert(40);
    t.__insert(50);
    t.__erase(10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__insert(10);

    itr = t.__begin();
    ASSERT_EQ(*itr, 10);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__insert(1);
    t.__insert(20);
    t.__insert(2);
    t.__insert(3);
    t.__erase(10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__insert(10);

    itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.__end());
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(10);
    t.__insert(1);
    t.__insert(20);
    t.__insert(2);
    t.__insert(3);
    t.__erase(10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__erase(3);

    itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__erase(2);

    itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__erase(1);

    itr = t.__begin();
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__erase(20);

    ASSERT_EQ(t.__size(), 0);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(50);
    t.__insert(1);
    t.__insert(1000);
    t.__insert(1200);
    t.__insert(500);

    t.__erase(10);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(*itr, 100);
    ++itr;
    ASSERT_EQ(*itr, 500);
    ++itr;
    ASSERT_EQ(*itr, 1000);
    ++itr;
    ASSERT_EQ(*itr, 1200);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__erase(1000);

    itr = t.__begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(*itr, 100);
    ++itr;
    ASSERT_EQ(*itr, 500);
    ++itr;
    ASSERT_EQ(*itr, 1200);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__erase(1);

    itr = t.__begin();
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(*itr, 100);
    ++itr;
    ASSERT_EQ(*itr, 500);
    ++itr;
    ASSERT_EQ(*itr, 1200);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__erase(1200);

    itr = t.__begin();
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(*itr, 100);
    ++itr;
    ASSERT_EQ(*itr, 500);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__erase(500);

    itr = t.__begin();
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(*itr, 100);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    ft::__tree<int, int, ft::Identity<int> >::node_pointer r = t.root();
    ASSERT_EQ(r->__is_black_node(), true);
    ASSERT_EQ(r->left->__is_red_node(), true);
    ASSERT_EQ(r->right->__is_nil_node(), true);
    ASSERT_EQ(r->right, t.__end_node());

    ASSERT_EQ(r->value, 100);
    ASSERT_EQ(r->left->value, 50);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->right->parent, r);

    t.__erase(100);

    r = t.root();
    ASSERT_EQ(r->__is_black_node(), true);
    ASSERT_EQ(r->left->__is_nil_node(), true);
    ASSERT_EQ(r->right->__is_nil_node(), true);
    ASSERT_EQ(r->left->__is_black_node(), true);
    ASSERT_EQ(r->right->__is_black_node(), true);
    ASSERT_EQ(r->right, t.__end_node());

    ASSERT_EQ(r->value, 50);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->right->parent, r);

    itr = t.__begin();
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(itr, t.__end());

    t.__erase(50);

    ASSERT_EQ(t.__size(), 0);
    ASSERT_EQ(t.__empty(), true);
  }

  // comp
  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    t1.__insert(2);
    t1.__insert(3);
    t1.__insert(4);
    t1.__insert(5);
    ft::__tree<int, int, ft::Identity<int> > t2;
    t2.__insert(1);
    t2.__insert(2);
    t2.__insert(3);
    t2.__insert(4);
    t2.__insert(5);

    ASSERT_EQ(t1 == t2, true);
    ASSERT_EQ(t1 != t2, false);
    ASSERT_EQ(t1 < t2, false);
    ASSERT_EQ(t1 > t2, false);
    ASSERT_EQ(t1 <= t2, true);
    ASSERT_EQ(t1 >= t2, true);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);

    ft::__tree<int, int, ft::Identity<int> > t2;
    t2.__insert(1);

    ASSERT_EQ(t1 == t2, true);
    ASSERT_EQ(t1 != t2, false);
    ASSERT_EQ(t1 < t2, false);
    ASSERT_EQ(t1 > t2, false);
    ASSERT_EQ(t1 <= t2, true);
    ASSERT_EQ(t1 >= t2, true);
  }
}

void test_vector() {
  // TODO 自作アロケーたーのテスト
  // constructor
  // vector();
  {
    ft::vector<int> myvec;
    myvec.push_back(1);
    ASSERT_EQ(myvec.size(), 1);
    ASSERT_EQ(myvec.at(0), 1);
  }

  // vector( const Allocator& alloc );
  {
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

  {
    ft::vector<int> myvec(10);

    ASSERT_EQ(myvec.size(), 10);
  }

  // vector( size_type count, const T& value = T() );
  {
    ft::vector<int> myvec(10, 42);

    ASSERT_EQ(myvec.size(), 10);
    for (std::vector<int>::size_type i = 0; i < myvec.size(); ++i) {
      ASSERT_EQ(myvec.at(i), 42);
    }
  }

  // vector( size_type count,
  //                  const T& value = T(),
  //                  const Allocator& alloc = Allocator());
  {
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
  {
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
  {
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
  {
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
  {
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
  {
    ft::vector<int> myvec;
    myvec.assign(100, 42);
    ASSERT_EQ(myvec.size(), 100);
    for (std::vector<int>::size_type i = 0; i < 100; ++i) {
      ASSERT_EQ(myvec.at(i), 42);
    }
  }

  // template< class InputIt >
  // void assign( InputIt first, InputIt last );
  {
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
  {
    ft::vector<int> myvec;
    myvec.get_allocator();
  }

  // at()
  {
    std::vector<int> test_set;
    test_set.push_back(1);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
      ASSERT_EQ(myvec.at(i), libvec.at(i));
    }
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
      ASSERT_EQ(myvec.at(i), libvec.at(i));
    }
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
      ASSERT_EQ(myvec.at(i), libvec.at(i));
    }
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
      ASSERT_EQ(myvec.at(i), libvec.at(i));
    }
  }

  // TEST(VectorTest, int_basic_at_exception) {
  // ft::vector<int> myvec;

  // EXPECT_THROW(myvec.at(42), std::out_of_range);
  // }

  // operator[]
  {
    std::vector<int> test_set;
    test_set.push_back(42);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
      ASSERT_EQ(myvec[i], libvec[i]);
    }
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
      ASSERT_EQ(myvec[i], libvec[i]);
    }
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
      ASSERT_EQ(myvec[i], libvec[i]);
    }
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    for (std::vector<int>::size_type i = 0; i < test_set.size(); ++i) {
      ASSERT_EQ(myvec[i], libvec[i]);
    }
  }

  // front()
  {
    std::vector<int> test_set;
    test_set.push_back(42);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.front(), libvec.front());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.front(), libvec.front());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.front(), libvec.front());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.front(), libvec.front());
  }

  // back()
  {
    std::vector<int> test_set;
    test_set.push_back(42);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.back(), libvec.back());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.back(), libvec.back());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.back(), libvec.back());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.back(), libvec.back());
  }

  // data()
  {
    std::vector<int> test_set;
    test_set.push_back(42);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
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

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
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

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
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

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
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
  {
    ft::vector<int> myvec;
    std::vector<int> libvec;

    ASSERT_EQ(myvec.empty(), libvec.empty());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.empty(), libvec.empty());
  }

  // size()
  {
    std::vector<int> test_set;
    test_set.push_back(42);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.size(), libvec.size());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.size(), libvec.size());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.size(), libvec.size());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(42);
    test_set.push_back(1);
    test_set.push_back(-10);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    ASSERT_EQ(myvec.size(), libvec.size());
  }

  // max_size()
  {
    ft::vector<int> myvec;
    std::vector<int> libvec;

    ASSERT_EQ(myvec.max_size(), libvec.max_size());
  }

  // reserve()
  {
    ft::vector<int> myvec;
    std::vector<int> libvec;

    std::size_t size = 100;
    myvec.reserve(size);
    libvec.reserve(size);

    ASSERT_EQ(myvec.size(), libvec.size());
  }

  {
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
  {
    ft::vector<int> myvec;
    std::vector<int> libvec;

    myvec.clear();
    libvec.clear();

    ASSERT_EQ(myvec.size(), libvec.size());
  }

  // insert()
  // iterator insert( const_iterator pos, const T& value );
  {
    // stdのセット
    std::vector<int> libvec(10, 42);
    std::vector<int>::iterator libitr = libvec.insert(libvec.begin(), 123);
    // ftのセット
    ft::vector<int> myvec(10, 42);
    ft::vector<int>::iterator myitr = myvec.insert(myvec.begin(), 123);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec;
    std::vector<int>::iterator libitr = libvec.insert(libvec.begin(), 123);
    // ftのセット
    ft::vector<int> myvec;
    ft::vector<int>::iterator myitr = myvec.insert(myvec.begin(), 123);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec;
    std::vector<int>::iterator libitr = libvec.insert(libvec.end(), 123);
    // ftのセット
    ft::vector<int> myvec;
    ft::vector<int>::iterator myitr = myvec.insert(myvec.end(), 123);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec;
    libvec.push_back(1);
    libvec.push_back(2);
    libvec.push_back(4);
    libvec.push_back(5);
    libvec.push_back(6);
    libvec.push_back(7);
    libvec.push_back(8);
    std::vector<int>::iterator itr1 = libvec.begin();
    ++itr1;
    ++itr1;
    ++itr1;
    std::vector<int>::iterator libitr = libvec.insert(itr1, 123);
    // ftのセット
    ft::vector<int> myvec;
    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(4);
    myvec.push_back(5);
    myvec.push_back(6);
    myvec.push_back(7);
    myvec.push_back(8);
    ft::vector<int>::iterator itr2 = myvec.begin();
    ++itr2;
    ++itr2;
    ++itr2;
    ft::vector<int>::iterator myitr = myvec.insert(itr2, 123);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  // iterator insert( const_iterator pos, size_type count, const T& value );
  {
    // stdのセット
    std::vector<int> libvec(10, 42);
    std::vector<int>::iterator libitr = libvec.insert(libvec.begin(), 10, 123);
    // ftのセット
    ft::vector<int> myvec(10, 42);
    ft::vector<int>::iterator myitr = myvec.insert(myvec.begin(), 10, 123);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec(10, 42);
    std::vector<int>::iterator libitr = libvec.insert(libvec.end(), 10, 123);
    // ftのセット
    ft::vector<int> myvec(10, 42);
    ft::vector<int>::iterator myitr = myvec.insert(myvec.end(), 10, 123);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec;
    std::vector<int>::iterator libitr = libvec.insert(libvec.begin(), 10, 123);
    // ftのセット
    ft::vector<int> myvec;
    ft::vector<int>::iterator myitr = myvec.insert(myvec.begin(), 10, 123);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec;
    std::vector<int>::iterator libitr = libvec.insert(libvec.end(), 10, 123);
    // ftのセット
    ft::vector<int> myvec;
    ft::vector<int>::iterator myitr = myvec.insert(myvec.end(), 10, 123);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec;
    libvec.push_back(1);
    libvec.push_back(2);
    libvec.push_back(4);
    libvec.push_back(5);
    libvec.push_back(6);
    libvec.push_back(7);
    libvec.push_back(8);
    std::vector<int>::iterator itr1 = libvec.begin();
    ++itr1;
    ++itr1;
    ++itr1;
    std::vector<int>::iterator libitr = libvec.insert(itr1, 100, 123);
    // ftのセット
    ft::vector<int> myvec;
    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(4);
    myvec.push_back(5);
    myvec.push_back(6);
    myvec.push_back(7);
    myvec.push_back(8);
    ft::vector<int>::iterator itr2 = myvec.begin();
    ++itr2;
    ++itr2;
    ++itr2;
    ft::vector<int>::iterator myitr = myvec.insert(itr2, 100, 123);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  // template< class InputIt >
  // iterator insert( const_iterator pos, InputIt first, InputIt last );
  {
    // stdのセット
    std::vector<int> libvec;
    libvec.push_back(1);
    libvec.push_back(2);
    libvec.push_back(3);
    std::vector<int> libsrc;
    libsrc.push_back(4);
    libsrc.push_back(5);
    libsrc.push_back(6);
    std::vector<int>::iterator libitr =
        libvec.insert(libvec.begin(), libsrc.begin(), libsrc.end());
    // ftのセット
    ft::vector<int> myvec;
    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(3);
    ft::vector<int> mysrc;
    mysrc.push_back(4);
    mysrc.push_back(5);
    mysrc.push_back(6);
    ft::vector<int>::iterator myitr =
        myvec.insert(myvec.begin(), mysrc.begin(), mysrc.end());

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec;
    libvec.push_back(1);
    std::vector<int> libsrc;
    libsrc.push_back(4);
    std::vector<int>::iterator libitr =
        libvec.insert(libvec.begin(), libsrc.begin(), libsrc.end());
    // ftのセット
    ft::vector<int> myvec;
    myvec.push_back(1);
    ft::vector<int> mysrc;
    mysrc.push_back(4);
    ft::vector<int>::iterator myitr =
        myvec.insert(myvec.begin(), mysrc.begin(), mysrc.end());

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec;
    std::vector<int> libsrc;
    libsrc.push_back(4);
    std::vector<int>::iterator libitr =
        libvec.insert(libvec.begin(), libsrc.begin(), libsrc.end());
    // ftのセット
    ft::vector<int> myvec;
    ft::vector<int> mysrc;
    mysrc.push_back(4);
    ft::vector<int>::iterator myitr =
        myvec.insert(myvec.begin(), mysrc.begin(), mysrc.end());

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec;
    std::vector<int> libsrc;
    std::vector<int>::iterator libitr =
        libvec.insert(libvec.begin(), libsrc.begin(), libsrc.end());
    // ftのセット
    ft::vector<int> myvec;
    ft::vector<int> mysrc;
    ft::vector<int>::iterator myitr =
        myvec.insert(myvec.begin(), mysrc.begin(), mysrc.end());

    ASSERT_EQ(libitr, libvec.begin());
    ASSERT_EQ(myitr, myvec.begin());
  }

  // erase()
  // iterator erase( iterator pos );
  {
    // stdのセット
    std::vector<int> libvec(1, 42);
    ft::vector<int> myvec(1, 42);

    std::vector<int>::iterator libitr = libvec.erase(libvec.begin());
    ft::vector<int>::iterator myitr = myvec.erase(myvec.begin());

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec(42, 4242);
    ft::vector<int> myvec(42, 4242);
    std::vector<int>::iterator libitr = libvec.erase(libvec.begin() + 10);
    ft::vector<int>::iterator myitr = myvec.erase(myvec.begin() + 10);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  // TEST(VectorTest, int_basic_erase2) {
  //   // stdのセット
  //   std::vector<int> libvec(42, 4242);
  //   ft::vector<int> myvec(42, 4242);
  //   std::vector<int>::iterator libitr = libvec.erase(libvec.begin() + 10);
  //   ft::vector<int>::iterator myitr = myvec.erase(myvec.begin() + 10);

  //   ASSERT_EQ(*libitr, *myitr);
  //   assertVector(libvec, myvec);
  // }

  {
    // stdのセット
    std::vector<int> libvec;
    libvec.push_back(1);
    libvec.push_back(2);
    libvec.push_back(3);
    libvec.push_back(4);
    libvec.push_back(5);
    ft::vector<int> myvec;
    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(3);
    myvec.push_back(4);
    myvec.push_back(5);
    std::vector<int>::iterator libitr = libvec.erase(libvec.begin() + 3);
    ft::vector<int>::iterator myitr = myvec.erase(myvec.begin() + 3);

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  {
    // stdのセット
    std::vector<int> libvec;
    libvec.push_back(1);
    libvec.push_back(2);
    libvec.push_back(3);
    libvec.push_back(4);
    libvec.push_back(5);
    libvec.push_back(6);
    libvec.push_back(7);
    libvec.push_back(8);
    libvec.push_back(9);
    libvec.push_back(10);
    ft::vector<int> myvec;
    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(3);
    myvec.push_back(4);
    myvec.push_back(5);
    myvec.push_back(6);
    myvec.push_back(7);
    myvec.push_back(8);
    myvec.push_back(9);
    myvec.push_back(10);
    std::vector<int>::iterator libitr =
        libvec.erase(libvec.begin() + 3, libvec.end());
    ft::vector<int>::iterator myitr =
        myvec.erase(myvec.begin() + 3, myvec.end());

    ASSERT_EQ(*libitr, *myitr);
    assertVector(libvec, myvec);
  }

  // push_back()
  {
    ft::vector<int> myvec;
    std::vector<int> libvec;

    myvec.push_back(1);
    libvec.push_back(1);
  }

  // pop_back()
  {
    std::vector<int> test_set;
    test_set.push_back(100);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    myvec.pop_back();
    libvec.pop_back();

    ASSERT_EQ(myvec.size(), libvec.size());
    ASSERT_EQ(myvec.empty(), libvec.empty());
  }

  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
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

  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-10);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
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
  {
    std::vector<int> test_set;
    test_set.push_back(100);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
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

  {
    std::vector<int> test_set;
    test_set.push_back(100);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
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

  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-1);
    test_set.push_back(-100);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
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

  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-1);
    test_set.push_back(-100);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    std::vector<int> libvec;

    for (std::vector<int>::iterator itr = test_set.begin();
         itr != test_set.end(); ++itr) {
      myvec.push_back(*itr);
      libvec.push_back(*itr);
    }

    myvec.resize(0);
    libvec.resize(0);

    ASSERT_EQ(myvec.size(), libvec.size());
    ASSERT_EQ(myvec.empty(), libvec.empty());
  }

  // swap()
  {
    std::vector<int> test_set1;
    test_set1.push_back(2);
    std::vector<int> test_set2;
    test_set2.push_back(2);

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
  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-1);
    test_set.push_back(-100);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    ft::vector<int> myvec_comp_target;
    std::vector<int> libvec;
    std::vector<int> libvec_comp_target;

    prepareVectorTestData(libvec, myvec, test_set);
    prepareVectorTestData(libvec_comp_target, myvec_comp_target, test_set);

    ASSERT_EQ((libvec == libvec_comp_target), (myvec == myvec_comp_target));
  }

  // operator!=
  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-1);
    test_set.push_back(-100);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    ft::vector<int> myvec_comp_target;
    std::vector<int> libvec;
    std::vector<int> libvec_comp_target;

    prepareVectorTestData(libvec, myvec, test_set);
    prepareVectorTestData(libvec_comp_target, myvec_comp_target, test_set);
    libvec_comp_target.push_back(1);
    myvec_comp_target.push_back(1);

    ASSERT_EQ((libvec != libvec_comp_target), (myvec != myvec_comp_target));
  }

  // operator<
  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-1);
    test_set.push_back(-100);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    ft::vector<int> myvec_comp_target;
    std::vector<int> libvec;
    std::vector<int> libvec_comp_target;

    prepareVectorTestData(libvec, myvec, test_set);
    prepareVectorTestData(libvec_comp_target, myvec_comp_target, test_set);
    libvec_comp_target.push_back(1);
    myvec_comp_target.push_back(1);

    ASSERT_EQ(libvec < libvec_comp_target, myvec < myvec_comp_target);
  }

  // operator<=
  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-1);
    test_set.push_back(-100);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    ft::vector<int> myvec_comp_target;
    std::vector<int> libvec;
    std::vector<int> libvec_comp_target;

    prepareVectorTestData(libvec, myvec, test_set);
    prepareVectorTestData(libvec_comp_target, myvec_comp_target, test_set);
    libvec_comp_target.push_back(1);
    myvec_comp_target.push_back(1);

    ASSERT_EQ((libvec <= libvec_comp_target), (myvec <= myvec_comp_target));
  }

  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-1);
    test_set.push_back(-100);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    ft::vector<int> myvec_comp_target;
    std::vector<int> libvec;
    std::vector<int> libvec_comp_target;

    prepareVectorTestData(libvec, myvec, test_set);
    prepareVectorTestData(libvec_comp_target, myvec_comp_target, test_set);

    ASSERT_EQ((libvec <= libvec_comp_target), (myvec <= myvec_comp_target));
  }

  // operator>
  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-1);
    test_set.push_back(-100);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    ft::vector<int> myvec_comp_target;
    std::vector<int> libvec;
    std::vector<int> libvec_comp_target;

    prepareVectorTestData(libvec, myvec, test_set);
    prepareVectorTestData(libvec_comp_target, myvec_comp_target, test_set);
    libvec_comp_target.pop_back();
    myvec_comp_target.pop_back();

    ASSERT_EQ(libvec > libvec_comp_target, myvec > myvec_comp_target);
  }

  // operator>=
  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-1);
    test_set.push_back(-100);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    ft::vector<int> myvec_comp_target;
    std::vector<int> libvec;
    std::vector<int> libvec_comp_target;

    prepareVectorTestData(libvec, myvec, test_set);
    prepareVectorTestData(libvec_comp_target, myvec_comp_target, test_set);
    libvec_comp_target.pop_back();
    myvec_comp_target.pop_back();

    ASSERT_EQ((libvec >= libvec_comp_target), (myvec >= myvec_comp_target));
  }

  {
    std::vector<int> test_set;
    test_set.push_back(100);
    test_set.push_back(42);
    test_set.push_back(-1);
    test_set.push_back(-100);
    test_set.push_back(4242);

    ft::vector<int> myvec;
    ft::vector<int> myvec_comp_target;
    std::vector<int> libvec;
    std::vector<int> libvec_comp_target;

    prepareVectorTestData(libvec, myvec, test_set);
    prepareVectorTestData(libvec_comp_target, myvec_comp_target, test_set);

    ASSERT_EQ((libvec >= libvec_comp_target), (myvec >= myvec_comp_target));
  }

  // std::swap(std::vector)
}

void test_deque() {
  // constructor
  // 1
  { ft::deque<int> mydec; }

  // 2
  {
    std::allocator<int> alloc;
    ft::deque<int> mydec(alloc);
    std::deque<int> libdec(alloc);
    ASSERT_EQ(libdec.size(), mydec.size());
  }

  // 3
  {
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

  {
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

  {
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
  {
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

  {
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
  {
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

  {
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
  {
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
  {
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

  {
    ft::deque<int> mydec;
    std::deque<int> libdec;

    mydec.assign(0, 1);
    libdec.assign(0, 1);

    ASSERT_EQ(libdec.size(), mydec.size());
  }

  {
    ft::deque<int> mydec;
    std::deque<int> libdec;

    ft::deque<int> mydec1;
    std::deque<int> libdec1;
    std::deque<int> data;
    data.push_back(0);
    data.push_back(3);
    data.push_back(10000);
    data.push_back(2);
    data.push_back(-1);
    data.push_back(-400);
    prepareDequeTestData(libdec1, mydec1, data);

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
  {
    ft::deque<int> mydec;
    mydec.push_front(1);
    std::deque<int> libdec;
    libdec.push_front(1);

    ASSERT_EQ(libdec.at(0), mydec.at(0));
  }

  // {
  //   ft::deque<int> mydec;
  //   mydec.push_front(1);
  //   std::deque<int> libdec;
  //   libdec.push_front(1);

  //   EXPECT_THROW(libdec.at(100), std::out_of_range);
  //   EXPECT_THROW(mydec.at(100), std::out_of_range);
  // }

  // operator[]
  {
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

  // front
  {
    ft::deque<int> mydec;
    mydec.push_front(1);
    std::deque<int> libdec;
    libdec.push_front(1);

    ASSERT_EQ(libdec.front(), mydec.front());
  }

  {
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

  {
    ft::deque<int> mydec;
    mydec.push_back(1);
    std::deque<int> libdec;
    libdec.push_back(1);

    ASSERT_EQ(libdec.back(), mydec.back());
  }

  {
    ft::deque<int> mydec;
    mydec.push_front(42);
    mydec.push_back(1);
    std::deque<int> libdec;
    libdec.push_front(42);
    libdec.push_back(1);

    ASSERT_EQ(libdec.back(), mydec.back());
  }

  // begin
  {
    ft::deque<int> mydec;
    mydec.push_back(1);
    std::deque<int> libdec;
    libdec.push_back(1);

    ASSERT_EQ(*(libdec.begin()), *(mydec.begin()));
  }

  // iterator
  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
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

  {
    ft::deque<int> mydec;
    std::deque<int> libdec;

    ASSERT_EQ(mydec.begin() - mydec.begin(), libdec.begin() - libdec.begin());
  }

  // end
  {
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

  {
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
  {
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

  {
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
  {
    ft::deque<int> mydec;
    std::deque<int> libdec;

    ASSERT_EQ(libdec.empty(), mydec.empty());
  }

  {
    ft::deque<int> mydec;
    mydec.push_back(1);
    std::deque<int> libdec;
    libdec.push_back(1);

    ASSERT_EQ(libdec.empty(), mydec.empty());
  }

  // size
  {
    ft::deque<int> mydec;
    std::deque<int> libdec;

    ASSERT_EQ(libdec.size(), mydec.size());
  }

  {
    ft::deque<int> mydec;
    mydec.push_back(1);
    std::deque<int> libdec;
    libdec.push_back(1);

    ASSERT_EQ(libdec.size(), mydec.size());
  }

  {
    ft::deque<int> mydec;
    mydec.push_back(1);
    mydec.push_back(42);
    std::deque<int> libdec;
    libdec.push_back(1);
    libdec.push_back(42);

    ASSERT_EQ(libdec.size(), mydec.size());
  }

  {
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
  {
    ft::deque<int> mydec;
    std::deque<int> libdec;

    ASSERT_EQ(libdec.max_size(), mydec.max_size());
  }

  // clear
  {
    ft::deque<int> mydec;
    mydec.clear();
    std::deque<int> libdec;
    libdec.clear();

    ASSERT_EQ(libdec.size(), mydec.size());
  }

  {
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
  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);

    ft::deque<int>::iterator myitr = mydec.insert(mydec.begin(), 2);
    std::deque<int>::iterator libitr = libdec.insert(libdec.begin(), 2);

    ASSERT_EQ(*libitr, *myitr);
    assertDeque(libdec, mydec);
  }

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);

    ft::deque<int>::iterator myitr = mydec.insert(mydec.begin() + 3, 2);
    std::deque<int>::iterator libitr = libdec.insert(libdec.begin() + 3, 2);

    ASSERT_EQ(*libitr, *myitr);
    assertDeque(libdec, mydec);
  }

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);

    ft::deque<int>::iterator myitr = mydec.insert(mydec.end(), 2);
    std::deque<int>::iterator libitr = libdec.insert(libdec.end(), 2);

    ASSERT_EQ(*libitr, *myitr);
    assertDeque(libdec, mydec);
  }

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);

    ft::deque<int>::iterator myitr = mydec.insert(mydec.begin(), 3, 2);
    std::deque<int>::iterator libitr = libdec.insert(libdec.begin(), 3, 2);

    ASSERT_EQ(*libitr, *myitr);
    assertDeque(libdec, mydec);
  }

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);

    ft::deque<int>::iterator myitr = mydec.insert(mydec.begin(), 1, 2);
    std::deque<int>::iterator libitr = libdec.insert(libdec.begin(), 1, 2);

    ASSERT_EQ(*libitr, *myitr);
    assertDeque(libdec, mydec);
  }

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);

    ft::deque<int>::iterator myitr = mydec.insert(mydec.begin() + 2, 2, 2);
    std::deque<int>::iterator libitr = libdec.insert(libdec.begin() + 2, 2, 2);

    ASSERT_EQ(*libitr, *myitr);
    assertDeque(libdec, mydec);
  }

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);

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

  //   prepareDequeTestData(libdec, mydec, data);

  //   ft::deque<int>::iterator myitr =
  //       mydec.insert(mydec.begin(), mydec.begin(), mydec.end());
  //   std::deque<int>::iterator libitr =
  //       libdec.insert(libdec.begin(), libdec.begin(), libdec.end());

  //   ASSERT_EQ(*libitr, *myitr);
  //   ASSERT_EQ(libdec.size(), mydec.size());
  //   ASSERT_EQ(libdec.at(0), mydec.at(0));
  //   ASSERT_EQ(libdec.at(1), mydec.at(1));
  //   ASSERT_EQ(libdec.at(2), mydec.at(2));
  //   ASSERT_EQ(libdec.at(3), mydec.at(3));
  //   ASSERT_EQ(libdec.at(4), mydec.at(4));
  // }

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);
    std::deque<int> data2;
    data2.push_back(1);
    data2.push_back(3);
    data2.push_back(42);
    data2.push_back(12);
    data2.push_back(-10);
    data2.push_back(10);
    data2.push_back(2);
    data2.push_back(-1);
    data2.push_back(-2930);
    data2.push_back(43);

    ft::deque<int> mydec2;
    std::deque<int> libdec2;

    prepareDequeTestData(libdec2, mydec2, data2);

    ft::deque<int>::iterator myitr =
        mydec.insert(mydec.begin(), mydec2.begin(), mydec2.end());
    std::deque<int>::iterator libitr =
        libdec.insert(libdec.begin(), libdec2.begin(), libdec2.end());

    ASSERT_EQ(libdec.size(), mydec.size());
    ASSERT_EQ(*libitr, *myitr);
    assertDeque(libdec, mydec);
  }

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);

    ft::deque<int>::iterator myitr = mydec.insert(mydec.begin(), 100, 2);
    std::deque<int>::iterator libitr = libdec.insert(libdec.begin(), 100, 2);

    ASSERT_EQ(*libitr, *myitr);
    assertDeque(libdec, mydec);
  }

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);

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

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    prepareDequeTestData(libdec, mydec, data);

    ft::deque<int> mydec1;
    std::deque<int> libdec1;
    std::deque<int> data1;
    data1.push_back(3);
    data1.push_back(5);
    data1.push_back(62);
    data1.push_back(67);
    data1.push_back(8);
    data1.push_back(9);

    prepareDequeTestData(libdec1, mydec1, data1);
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
  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
    ft::deque<int> mydec;
    std::deque<int> libdec;

    for (size_t i = 0; i < data.size(); ++i) {
      mydec.push_back(data.at(i));
      libdec.push_back(data.at(i));
    }

    ft::deque<int>::iterator myitr = mydec.erase(mydec.begin());
    std::deque<int>::iterator libitr = libdec.erase(libdec.begin());

    ASSERT_EQ(libdec.size(), mydec.size());
    ASSERT_EQ(*libitr, *myitr);
    for (size_t i = 0; i < libdec.size(); ++i) {
      ASSERT_EQ(libdec.at(i), mydec.at(i));
    }
  }

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
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

    ASSERT_EQ(libdec.size(), mydec.size());
    ASSERT_EQ(*libitr, *myitr);
    for (size_t i = 0; i < libdec.size(); ++i) {
      ASSERT_EQ(libdec.at(i), mydec.at(i));
    }
  }

  // push_back
  {
    ft::deque<int> mydec;
    mydec.push_back(1);
    std::deque<int> libdec;
    libdec.push_back(1);

    ASSERT_EQ(libdec.at(0), mydec.at(0));
  }

  {
    ft::deque<int> mydec;
    mydec.push_back(1);
    mydec.push_back(42);
    std::deque<int> libdec;
    libdec.push_back(1);
    libdec.push_back(42);

    ASSERT_EQ(libdec.at(0), mydec.at(0));
    ASSERT_EQ(libdec.at(1), mydec.at(1));
  }

  {
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
  {
    ft::deque<int> mydec;
    mydec.push_back(1);
    mydec.pop_back();
    std::deque<int> libdec;
    libdec.push_back(1);
    libdec.pop_back();

    ASSERT_EQ(libdec.size(), mydec.size());
  }

  {
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
  {
    ft::deque<int> mydec;
    mydec.push_back(1);
    mydec.push_front(2);
    std::deque<int> libdec;
    libdec.push_back(1);
    libdec.push_front(2);

    ASSERT_EQ(libdec.at(0), mydec.at(0));
  }

  {
    ft::deque<int> mydec;
    mydec.push_front(1);
    std::deque<int> libdec;
    libdec.push_front(1);

    ASSERT_EQ(libdec.at(0), mydec.at(0));
  }

  {
    ft::deque<int> mydec;
    mydec.push_front(1);
    mydec.push_front(2);
    std::deque<int> libdec;
    libdec.push_front(1);
    libdec.push_front(2);

    ASSERT_EQ(libdec.at(0), mydec.at(0));
    ASSERT_EQ(libdec.at(1), mydec.at(1));
  }

  {
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
  {
    ft::deque<int> mydec;
    mydec.push_back(1);
    mydec.pop_front();
    std::deque<int> libdec;
    libdec.push_back(1);
    libdec.pop_front();

    ASSERT_EQ(libdec.size(), mydec.size());
  }

  {
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

  {
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

  {
    ft::deque<int> mydec;
    mydec.push_front(1);
    mydec.push_back(3);
    std::deque<int> libdec;
    libdec.push_front(1);
    libdec.push_back(3);

    ASSERT_EQ(libdec.at(0), mydec.at(0));
    ASSERT_EQ(libdec.at(1), mydec.at(1));
  }

  {
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

  {
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
  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
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

  {
    std::deque<int> data;
    data.push_back(1);
    data.push_back(3);
    data.push_back(42);
    data.push_back(12);
    data.push_back(-10);
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
  {
    std::deque<int> data1;
    data1.push_back(1);
    data1.push_back(2);
    data1.push_back(6);
    data1.push_back(100);
    data1.push_back(2);
    data1.push_back(-1903);
    ft::deque<int> mydec1;
    std::deque<int> libdec1;
    prepareDequeTestData(libdec1, mydec1, data1);
    std::deque<int> data2;
    data2.push_back(1);
    data2.push_back(0);
    data2.push_back(-1939);
    data2.push_back(-34);
    data2.push_back(292);
    data2.push_back(193848);
    data2.push_back(2);
    ft::deque<int> mydec2;
    std::deque<int> libdec2;
    prepareDequeTestData(libdec2, mydec2, data2);

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

  {
    std::deque<int> data1;
    data1.push_back(1);
    data1.push_back(2);
    data1.push_back(6);
    data1.push_back(100);
    data1.push_back(2);
    data1.push_back(-1903);
    ft::deque<int> mydec1;
    std::deque<int> libdec1;
    prepareDequeTestData(libdec1, mydec1, data1);
    std::deque<int> data2;
    data2.push_back(1);
    data2.push_back(0);
    data2.push_back(-1939);
    data2.push_back(-34);
    data2.push_back(292);
    data2.push_back(193848);
    data2.push_back(2);
    ft::deque<int> mydec2;
    std::deque<int> libdec2;
    prepareDequeTestData(libdec2, mydec2, data2);

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
  {
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

  {
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

  {
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
}

void test_stack() {
  // constructor
  { ft::stack<int> myst; }

  {
    std::deque<int> container;
    ft::stack<int, std::deque<int> > myst(container);
  }

  {
    ft::stack<int> src;
    ft::stack<int> myst(src);
  }

  {
    ft::stack<int> src;
    ft::stack<int> myst = src;
  }

  {
    std::vector<int> test_data;
    test_data.push_back(1);
    test_data.push_back(2);
    test_data.push_back(42);
    std::stack<int> libst;
    ft::stack<int> myst;
    prepareTestData(libst, myst, test_data);

    ASSERT_EQ(libst.top(), myst.top());
  }

  {
    std::vector<int> test_data;
    test_data.push_back(1);
    test_data.push_back(2);
    test_data.push_back(42);
    std::stack<int> libst;
    ft::stack<int> myst;
    prepareTestData(libst, myst, test_data);

    ASSERT_EQ(libst.empty(), myst.empty());
  }

  {
    std::stack<int> libst;
    ft::stack<int> myst;

    ASSERT_EQ(libst.empty(), myst.empty());
  }

  {
    std::vector<int> test_data;
    test_data.push_back(1);
    test_data.push_back(2);
    test_data.push_back(42);
    std::stack<int> libst;
    ft::stack<int> myst;
    prepareTestData(libst, myst, test_data);

    ASSERT_EQ(libst.size(), myst.size());
  }

  {
    std::stack<int> libst;
    ft::stack<int> myst;

    ASSERT_EQ(libst.size(), myst.size());
  }

  {
    std::vector<int> test_data;
    test_data.push_back(1);
    test_data.push_back(2);
    test_data.push_back(42);
    std::stack<int> libst;
    ft::stack<int> myst;
    prepareTestData(libst, myst, test_data);
  }

  {
    std::vector<int> test_data;
    test_data.push_back(1);
    test_data.push_back(2);
    test_data.push_back(42);
    std::stack<int> libst;
    ft::stack<int> myst;
    prepareTestData(libst, myst, test_data);

    libst.pop();
    myst.pop();

    assertStack(libst, myst);
  }
}

void test_pair() {
  // constuctor
  {
    ft::pair<int, int> myp;
    std::pair<int, int> libp;
    ASSERT_EQ(myp.first, libp.first);
    ASSERT_EQ(myp.second, libp.second);
  }

  {
    ft::pair<int, int> myp(1, 2);
    std::pair<int, int> libp(1, 2);
    ASSERT_EQ(myp.first, libp.first);
    ASSERT_EQ(myp.second, libp.second);
  }

  {
    ft::pair<int, int> myp(1, 2);
    std::pair<int, int> libp(1, 2);
    ft::pair<int, int> myp2(myp);
    std::pair<int, int> libp2(libp);
    ASSERT_EQ(myp2.first, libp2.first);
    ASSERT_EQ(myp2.second, libp2.second);
  }

  // const
  {
    ft::pair<int, int> myp(1, 2);
    std::pair<int, int> libp(1, 2);
    std::pair<const int, int> libp2(libp);
    ft::pair<const int, int> myp2(myp);
    ASSERT_EQ(myp2.first, libp2.first);
    ASSERT_EQ(myp2.second, libp2.second);
  }

  {
    std::pair<const int, int> libp(1, 2);
    std::pair<const int, int> libp2(libp);
    ft::pair<const int, int> myp(1, 2);
    ft::pair<const int, int> myp2(myp);
    ASSERT_EQ(myp2.first, libp2.first);
    ASSERT_EQ(myp2.second, libp2.second);
  }

  // operator=
  {
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
  {
    ft::pair<int, int> myp = ft::make_pair(1, 2);
    std::pair<int, int> libp = std::make_pair(1, 2);
    ASSERT_EQ(myp.first, libp.first);
    ASSERT_EQ(myp.second, libp.second);
  }

  // compare operators
  {
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

  {
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

  {
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

  {
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

  {
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
}

int main(int ac, char** av) {
  if (ac == 1) {
    av[1] = const_cast<char*>("all");
  }
  std::string avs(av[1]);
  if (avs == "map" || avs == "all")
    test_map();
  if (avs == "set" || avs == "all")
    test_set();
  if (avs == "tree" || avs == "all")
    test_tree();
  if (avs == "vector" || avs == "all")
    test_vector();
  if (avs == "deque" || avs == "all")
    test_deque();
  if (avs == "stack" || avs == "all")
    test_stack();
  if (avs == "pair" || avs == "all")
    test_pair();
}
