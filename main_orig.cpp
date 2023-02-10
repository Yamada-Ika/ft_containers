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

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

#include <cassert>
#include <algorithm>
#include <memory>
#include <limits>
#include <iterator>
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

#define ASSERT_EQ(exp, got) assert_eq(exp, got, __FILE__, __LINE__)

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
    (void)n;
    (void)hint;
    throw std::runtime_error("AlwaysThrowAllocator throw exception !");
  }
  void deallocate(pointer p, size_type num) {
    (void)num;
    ::operator delete(p);
  }
  void construct(pointer p, const T& value) { new ((void*)p) T(value); }
  void destroy(pointer p) { ((T*)p)->~T(); }
  pointer address(reference value) const { return &value; }
  const_pointer address(const_reference value) const { return &value; }
  size_type max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }
};

void test_map() {
  /*
  * constructor 1
  */
  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ASSERT_EQ(ftmp.size(), stdmp.size());
  }

  /*
  * constructor 2
  */
  {
    std::greater<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::map<int, int, std::greater<int> > mymp(ftcomp, ftalloc);

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

    ft::map<int, int, std::greater<int> >::iterator myitr = mymp.begin();
    std::map<int, int, std::greater<int> >::iterator libitr = libmp.begin();

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

  {
    try {
      std::greater<int> ftcomp;
      AlwaysThrowAllocator<int> myalloc;
      ft::map<int, int, std::greater<int>, AlwaysThrowAllocator<int> > mymp(
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
  }

  /*
  * constructor 3
  */
  {
    std::greater<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::map<int, int, std::greater<int> > myorigin(ftcomp, ftalloc);
    myorigin.insert(ft::make_pair(1, 1));
    myorigin.insert(ft::make_pair(2, 2));
    myorigin.insert(ft::make_pair(3, 3));

    ft::map<int, int, std::greater<int> > mymp(myorigin.begin(), myorigin.end(),
                                               ftcomp, ftalloc);

    std::greater<int> libcomp;
    std::allocator<int> stdalloc;
    std::map<int, int, std::greater<int> > liborigin(libcomp, stdalloc);
    liborigin.insert(std::make_pair(1, 1));
    liborigin.insert(std::make_pair(2, 2));
    liborigin.insert(std::make_pair(3, 3));

    std::map<int, int, std::greater<int> > libmp(
        liborigin.begin(), liborigin.end(), libcomp, stdalloc);

    ft::map<int, int, std::greater<int> >::iterator myitr = mymp.begin();
    std::map<int, int, std::greater<int> >::iterator libitr = libmp.begin();

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

  /*
  * constructor 4
  */
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

  /*
  * destructor
  */
  {
    ft::map<int, int> mymp;
    std::map<int, int> libmp;
  }

  /*
  * operator =
  */
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

  /*
  * get_allocator
  */
  {
    std::greater<int> mycomp;
    std::allocator<int> alloc;
    ft::map<int, int, std::greater<int> > mymp(mycomp, alloc);

    std::greater<int> libcomp;
    std::map<int, int, std::greater<int> > libmp(libcomp, alloc);

    ASSERT_EQ(mymp.get_allocator(), libmp.get_allocator());
  }

  /*
  * get_allocator const
  */
  {
    std::greater<int> mycomp;
    std::allocator<int> alloc;
    const ft::map<int, int, std::greater<int> > mymp(mycomp, alloc);

    std::greater<int> libcomp;
    const std::map<int, int, std::greater<int> > libmp(libcomp, alloc);

    ASSERT_EQ(mymp.get_allocator(), libmp.get_allocator());
  }

  /*
  * at
  */
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

  /*
  * at const
  */
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

  /*
  * at exception
  */
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

  /*
  * operator[]
  */
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

  /*
  * operator[] does not throw exception
  */
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

  /*
  * begin
  */
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

  /*
  * begin const (immutable instance)
  */
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

  /*
  * begin const (mutable instance)
  */
  {
    std::map<int, int> libmp;
    libmp.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp;
    mymp.insert(ft::make_pair(1, 1));
    std::map<int, int>::const_iterator libitr = libmp.begin();
    ft::map<int, int>::const_iterator myitr = mymp.begin();
    ASSERT_EQ(libitr->first, myitr->first);
    ASSERT_EQ(libitr->second, myitr->second);
    ++libitr;
    ++myitr;
    ASSERT_EQ(libitr, libmp.end());
    ASSERT_EQ(myitr, mymp.end());
  }

  /*
  * end
  */
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

  /*
  * end const
  */
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

  /*
  * rbegin
  */
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

  // TODO
  /*
  * rbegin const (mutable instance)
  */
  // {
  //   std::map<int, int> liborigin;
  //   liborigin.insert(std::make_pair(1, 1));
  //   ft::map<int, int> myorigin;
  //   myorigin.insert(ft::make_pair(1, 1));
  //   std::map<int, int> libmp(liborigin.begin(), liborigin.end());
  //   ft::map<int, int> mymp(myorigin.begin(), myorigin.end());
  //   std::map<int, int>::const_reverse_iterator libitr = libmp.rbegin();
  //   ft::map<int, int>::const_reverse_iterator myitr = mymp.rbegin();
  //   ASSERT_EQ(libitr->first, myitr->first);
  //   ASSERT_EQ(libitr->second, myitr->second);
  //   ++libitr;
  //   ++myitr;
  //   ASSERT_EQ(libitr, libmp.rend());
  //   ASSERT_EQ(myitr, mymp.rend());
  // }

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

  /*
  * rend
  */
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

  // TODO
  /*
  * rend const (mutable instance)
  */
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

  /*
  * empty
  */
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

  /*
  * empty const
  */
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

  /*
  * size && insert
  */
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

  /*
  * size const
  */
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

  /*
  * max_size
  */
  {
    std::map<int, int> libmp;
    ft::map<int, int> mymp;
    ASSERT_EQ(libmp.max_size(), mymp.max_size());
  }

  /*
  * max_size const
  */
  {
    const std::map<int, int> libmp;
    const ft::map<int, int> mymp;
    ASSERT_EQ(libmp.max_size(), mymp.max_size());
  }

  /*
  * clear
  */
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

  /*
  * insert 1
  */
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

  /*
  * insert 2
  */
  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));

    std::map<int, int>::iterator stditr = stdmp.begin();
    std::map<int, int>::iterator stdret =
        stdmp.insert(stditr, std::make_pair(2, 2));
    ft::map<int, int>::iterator ftitr = ftmp.begin();
    ft::map<int, int>::iterator ftret = ftmp.insert(ftitr, ft::make_pair(2, 2));

    ASSERT_EQ(stdret->first, ftret->first);
    ASSERT_EQ(stdret->second, ftret->second);

    stditr = stdmp.begin();
    ftitr = ftmp.begin();
    ASSERT_EQ(stdmp.size(), ftmp.size());
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
  }

  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(10, 10));
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(20, 20));
    stdmp.insert(std::make_pair(5, 5));
    stdmp.insert(std::make_pair(15, 15));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(10, 10));
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(20, 20));
    ftmp.insert(ft::make_pair(5, 5));
    ftmp.insert(ft::make_pair(15, 15));

    std::map<int, int>::iterator stditr = stdmp.begin();
    std::map<int, int>::iterator stdret =
        stdmp.insert(stditr, std::make_pair(1, 1));
    ft::map<int, int>::iterator ftitr = ftmp.begin();
    ft::map<int, int>::iterator ftret = ftmp.insert(ftitr, ft::make_pair(1, 1));

    ASSERT_EQ(stdret->first, ftret->first);
    ASSERT_EQ(stdret->second, ftret->second);

    stditr = stdmp.begin();
    ftitr = ftmp.begin();
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
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++stditr;
    ++ftitr;
  }

  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(10, 10));
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(20, 20));
    stdmp.insert(std::make_pair(5, 5));
    stdmp.insert(std::make_pair(15, 15));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(10, 10));
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(20, 20));
    ftmp.insert(ft::make_pair(5, 5));
    ftmp.insert(ft::make_pair(15, 15));

    std::map<int, int>::iterator stditr = stdmp.begin();
    std::map<int, int>::iterator stdret =
        stdmp.insert(stditr, std::make_pair(2, 2));
    ft::map<int, int>::iterator ftitr = ftmp.begin();
    ft::map<int, int>::iterator ftret = ftmp.insert(ftitr, ft::make_pair(2, 2));

    ASSERT_EQ(stdret->first, ftret->first);
    ASSERT_EQ(stdret->second, ftret->second);

    stditr = stdmp.begin();
    ftitr = ftmp.begin();
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
  }

  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(10, 10));
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(20, 20));
    stdmp.insert(std::make_pair(5, 5));
    stdmp.insert(std::make_pair(15, 15));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(10, 10));
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(20, 20));
    ftmp.insert(ft::make_pair(5, 5));
    ftmp.insert(ft::make_pair(15, 15));

    std::map<int, int>::iterator stditr = stdmp.begin();
    std::map<int, int>::iterator stdret =
        stdmp.insert(stditr, std::make_pair(11, 11));
    ft::map<int, int>::iterator ftitr = ftmp.begin();
    ft::map<int, int>::iterator ftret =
        ftmp.insert(ftitr, ft::make_pair(11, 11));

    ASSERT_EQ(stdret->first, ftret->first);
    ASSERT_EQ(stdret->second, ftret->second);

    stditr = stdmp.begin();
    ftitr = ftmp.begin();
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
  }

  /*
  * insert 3
  */
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

  /*
  * erase 1
  */
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

    libmp.erase(libitr1, libitr2);
    mymp.erase(myitr1, myitr2);

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

  /*
  * erase 2
  */
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

    (void)stdret;
    (void)ftret;
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

    stdmp.erase(stdmp.begin(), ++stdmp.begin());
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

    stdmp.erase(stditr, ++stditr);
    ftmp.erase(ftitr, ++ftitr);

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

    stdmp.erase(stditr, ++stditr);
    ftmp.erase(ftitr, ++ftitr);

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

    stdmp.erase(stditr, ++stditr);
    ftmp.erase(ftitr, ++ftitr);

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

    stdmp.erase(stditr, ++stditr);
    ftmp.erase(ftitr, ++ftitr);

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

    stdmp.erase(stditr, ++stditr);
    ftmp.erase(ftitr, ++ftitr);

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

  /*
  * erase 3
  */
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

  /*
  * swap
  */
  {
    std::map<int, int> libmp1;
    libmp1.insert(std::make_pair(1, 1));
    std::map<int, int> libmp2;
    libmp2.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp1;
    mymp1.insert(ft::make_pair(1, 1));
    ft::map<int, int> mymp2;
    mymp2.insert(ft::make_pair(1, 1));

    libmp1.swap(libmp2);
    mymp1.swap(mymp2);

    ASSERT_EQ(libmp1.size(), mymp1.size());
    ASSERT_EQ(libmp2.size(), mymp2.size());

    std::map<int, int>::iterator libitr1 = libmp1.begin();
    ft::map<int, int>::iterator myitr1 = mymp1.begin();
    for (; libitr1 != libmp1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(libitr1->first, myitr1->first);
      ASSERT_EQ(libitr1->second, myitr1->second);
    }
    ASSERT_EQ(libitr1, libmp1.end());
    ASSERT_EQ(myitr1, mymp1.end());

    std::map<int, int>::iterator libitr2 = libmp2.begin();
    ft::map<int, int>::iterator myitr2 = mymp2.begin();
    for (; libitr2 != libmp2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(libitr2->first, myitr2->first);
      ASSERT_EQ(libitr2->second, myitr2->second);
    }
    ASSERT_EQ(libitr2, libmp2.end());
    ASSERT_EQ(myitr2, mymp2.end());
  }

  {
    std::map<int, int> libmp1;
    libmp1.insert(std::make_pair(1, 1));
    libmp1.insert(std::make_pair(2, 2));
    libmp1.insert(std::make_pair(3, 3));
    libmp1.insert(std::make_pair(4, 4));
    libmp1.insert(std::make_pair(5, 5));
    std::map<int, int> libmp2;
    libmp2.insert(std::make_pair(1, 1));
    ft::map<int, int> mymp1;
    mymp1.insert(ft::make_pair(1, 1));
    mymp1.insert(ft::make_pair(2, 2));
    mymp1.insert(ft::make_pair(3, 3));
    mymp1.insert(ft::make_pair(4, 4));
    mymp1.insert(ft::make_pair(5, 5));
    ft::map<int, int> mymp2;
    mymp2.insert(ft::make_pair(1, 1));

    libmp1.swap(libmp2);
    mymp1.swap(mymp2);

    ASSERT_EQ(libmp1.size(), mymp1.size());
    ASSERT_EQ(libmp2.size(), mymp2.size());

    std::map<int, int>::iterator libitr1 = libmp1.begin();
    ft::map<int, int>::iterator myitr1 = mymp1.begin();
    for (; libitr1 != libmp1.end(); ++libitr1, ++myitr1) {
      ASSERT_EQ(libitr1->first, myitr1->first);
      ASSERT_EQ(libitr1->second, myitr1->second);
    }
    ASSERT_EQ(libitr1, libmp1.end());
    ASSERT_EQ(myitr1, mymp1.end());

    std::map<int, int>::iterator libitr2 = libmp2.begin();
    ft::map<int, int>::iterator myitr2 = mymp2.begin();
    for (; libitr2 != libmp2.end(); ++libitr2, ++myitr2) {
      ASSERT_EQ(libitr2->first, myitr2->first);
      ASSERT_EQ(libitr2->second, myitr2->second);
    }
    ASSERT_EQ(libitr2, libmp2.end());
    ASSERT_EQ(myitr2, mymp2.end());
  }

  /*
  * count
  */
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

  {
    std::map<int, int> libdata;
    libdata.insert(std::make_pair(1, 1));
    libdata.insert(std::make_pair(2, 2));
    libdata.insert(std::make_pair(3, 3));
    ft::map<int, int> mydata;
    mydata.insert(ft::make_pair(1, 1));
    mydata.insert(ft::make_pair(2, 2));
    mydata.insert(ft::make_pair(3, 3));

    const std::map<int, int> libmp(libdata.begin(), libdata.end());
    const ft::map<int, int> mymp(mydata.begin(), mydata.end());

    ASSERT_EQ(libmp.count(2), mymp.count(2));
  }

  /*
  * find
  */
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

  {
    std::map<int, int> libdata;
    libdata.insert(std::make_pair(1, 1));
    libdata.insert(std::make_pair(2, 1));
    libdata.insert(std::make_pair(3, 1));
    libdata.insert(std::make_pair(4, 1));
    libdata.insert(std::make_pair(5, 1));
    ft::map<int, int> mydata;
    mydata.insert(ft::make_pair(1, 1));
    mydata.insert(ft::make_pair(2, 1));
    mydata.insert(ft::make_pair(3, 1));
    mydata.insert(ft::make_pair(4, 1));
    mydata.insert(ft::make_pair(5, 1));

    const std::map<int, int> libmp(libdata.begin(), libdata.end());
    const ft::map<int, int> mymp(mydata.begin(), mydata.end());

    ASSERT_EQ(libmp.find(42), libmp.end());
    ASSERT_EQ(mymp.find(42), mymp.end());
  }

  /*
  * swap
  */
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

  /*
  * equal_range
  */
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

  /*
  * equal_range const
  */
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

  /*
  * lower_bound
  */
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

  /*
  * lower_bound const
  */
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

  /*
  * upper_bound
  */
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

  /*
  * upper_bound const
  */
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

  /*
  * key_comp
  */
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

  /*
  * key_comp const
  */
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

  /*
  * value_comp
  */
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

  /*
  * value_comp const
  */
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

  /*
  * compare operators
  */
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

  /*
  * compare operators const
  */
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

  /*
  * non-member swap
  */
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

  {
    std::less_equal<int> stdcomp;
    std::allocator<int> stdalloc;
    std::map<int, int, std::less_equal<int> > stdst(stdcomp, stdalloc);

    stdst.insert(std::make_pair(1, 1));
    stdst.insert(std::make_pair(1, 1));
    stdst.insert(std::make_pair(3, 1));

    std::less_equal<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::map<int, int, std::less_equal<int> > ftst(ftcomp, ftalloc);

    ftst.insert(ft::make_pair(1, 1));
    ftst.insert(ft::make_pair(1, 1));
    ftst.insert(ft::make_pair(3, 1));

    std::map<int, int, std::less_equal<int> >::iterator stditr = stdst.begin();
    ft::map<int, int, std::less_equal<int> >::iterator ftitr = ftst.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr, stdst.end());
    ASSERT_EQ(ftitr, ftst.end());
  }

  {
    std::greater_equal<int> stdcomp;
    std::allocator<int> stdalloc;
    std::map<int, int, std::greater_equal<int> > stdst(stdcomp, stdalloc);

    stdst.insert(std::make_pair(1, 1));
    stdst.insert(std::make_pair(1, 1));
    stdst.insert(std::make_pair(3, 1));

    std::greater_equal<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::map<int, int, std::greater_equal<int> > ftst(ftcomp, ftalloc);

    ftst.insert(ft::make_pair(1, 1));
    ftst.insert(ft::make_pair(1, 1));
    ftst.insert(ft::make_pair(3, 1));

    std::map<int, int, std::greater_equal<int> >::iterator stditr =
        stdst.begin();
    ft::map<int, int, std::greater_equal<int> >::iterator ftitr = ftst.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr, stdst.end());
    ASSERT_EQ(ftitr, ftst.end());
  }

  /*
  * iterator
  */
  {
    std::map<int, int> stdmp;
    stdmp.insert(std::make_pair(1, 1));
    stdmp.insert(std::make_pair(2, 1));
    ft::map<int, int> ftmp;
    ftmp.insert(ft::make_pair(1, 1));
    ftmp.insert(ft::make_pair(2, 1));

    std::map<int, int>::const_iterator stditr = stdmp.begin();
    ft::map<int, int>::const_iterator ftitr = ftmp.begin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr, stdmp.end());
    ASSERT_EQ(ftitr, ftmp.end());
  }
}

void test_set() {
  /*
  * constructor 1
  */
  { ft::set<int> myst; }

  {
    std::greater<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::set<int, std::greater<int> > myst(ftcomp, ftalloc);

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

    ft::set<int, std::greater<int> >::iterator myitr = myst.begin();
    std::set<int, std::greater<int> >::iterator libitr = libst.begin();

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

  {
    try {
      std::greater<int> ftcomp;
      AlwaysThrowAllocator<int> myalloc;
      ft::set<int, std::greater<int>, AlwaysThrowAllocator<int> > myst(ftcomp,
                                                                       myalloc);
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
  }

  /*
  * constructor 2
  */
  {
    std::greater<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::set<int, std::greater<int> > myorigin(ftcomp, ftalloc);
    myorigin.insert(1);
    myorigin.insert(2);
    myorigin.insert(3);

    ft::set<int, std::greater<int> > myst(myorigin.begin(), myorigin.end(),
                                          ftcomp, ftalloc);

    std::greater<int> libcomp;
    std::allocator<int> stdalloc;
    std::set<int, std::greater<int> > liborigin(libcomp, stdalloc);
    liborigin.insert(1);
    liborigin.insert(2);
    liborigin.insert(3);

    std::set<int, std::greater<int> > libst(liborigin.begin(), liborigin.end(),
                                            libcomp, stdalloc);

    ft::set<int, std::greater<int> >::iterator myitr = myst.begin();
    std::set<int, std::greater<int> >::iterator libitr = libst.begin();

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

  /*
  * constructor 3
  */
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

  /*
  * destructor
  */
  {
    ft::set<int> myst;
    std::set<int> libst;
  }

  /*
  * operator=
  */
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
    ft::set<int> myst;

    libst = libdata;
    myst = mydata;

    ASSERT_EQ(libst.size(), myst.size());

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
    ASSERT_EQ(libitr, libst.end());
    ASSERT_EQ(myitr, myst.end());
  }

  /*
  * get_allocator
  */
  {
    std::greater<int> mycomp;
    std::allocator<int> alloc;
    ft::set<int, std::greater<int> > mymp(mycomp, alloc);

    std::greater<int> libcomp;
    std::set<int, std::greater<int> > libmp(libcomp, alloc);

    ASSERT_EQ(mymp.get_allocator(), libmp.get_allocator());
  }

  {
    std::greater<int> mycomp;
    std::allocator<int> alloc;
    const ft::set<int, std::greater<int> > mymp(mycomp, alloc);

    std::greater<int> libcomp;
    const std::set<int, std::greater<int> > libmp(libcomp, alloc);

    ASSERT_EQ(mymp.get_allocator(), libmp.get_allocator());
  }

  /*
  * begin
  */
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

  /*
  * end
  */
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

  /*
  * end const
  */
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

  /*
  * rbegin
  */
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

  /*
  * rbegin const
  */
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

  /*
  * rend
  */
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

  /*
  * rend const
  */
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

  /*
  * empty
  */
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

  /*
  * size
  */
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

  /*
  * size const
  */
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

  // TODO
  /*
  * max_size
  */
  // {
  //   std::set<int> libst;
  //   ft::set<int> myst;
  //   ASSERT_EQ(libst.max_size(), myst.max_size());
  // }

  // {
  //   const std::set<int> libst;
  //   const ft::set<int> myst;
  //   ASSERT_EQ(libst.max_size(), myst.max_size());
  // }

  /*
  * clear
  */
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

  /*
  * insert 1
  */
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

  /*
  * insert 2
  */
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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 10);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 1);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 3);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 4);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 5);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 6);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 7);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 8);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 9);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 10);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 11);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 12);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 13);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 14);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 15);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 16);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 17);

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

    ft::set<int>::iterator ftitr = ftst.begin();
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 18);

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
    ++stditr;
    std::set<int>::iterator stdret = stdst.insert(stditr, 18);

    ft::set<int>::iterator ftitr = ftst.begin();
    ++ftitr;
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 18);

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
    ++stditr;
    ++stditr;
    std::set<int>::iterator stdret = stdst.insert(stditr, 18);

    ft::set<int>::iterator ftitr = ftst.begin();
    ++ftitr;
    ++ftitr;
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 18);

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
    ++stditr;
    ++stditr;
    ++stditr;
    std::set<int>::iterator stdret = stdst.insert(stditr, 18);

    ft::set<int>::iterator ftitr = ftst.begin();
    ++ftitr;
    ++ftitr;
    ++ftitr;
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 18);

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
    ++stditr;
    ++stditr;
    ++stditr;
    ++stditr;
    std::set<int>::iterator stdret = stdst.insert(stditr, 18);

    ft::set<int>::iterator ftitr = ftst.begin();
    ++ftitr;
    ++ftitr;
    ++ftitr;
    ++ftitr;
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 18);

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
    ++stditr;
    ++stditr;
    ++stditr;
    ++stditr;
    ++stditr;
    std::set<int>::iterator stdret = stdst.insert(stditr, 18);

    ft::set<int>::iterator ftitr = ftst.begin();
    ++ftitr;
    ++ftitr;
    ++ftitr;
    ++ftitr;
    ++ftitr;
    ft::set<int>::iterator ftret = ftst.insert(ftitr, 18);

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

  /*
  * insert 3
  */
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

  /*
  * erase 1
  */
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

#ifdef __linux__
  dprintf(STDERR_FILENO,
          "[WARN] test in %d line is ignored because STL is buggy in "
          "this case\n",
          __LINE__);
#endif

#ifdef __APPLE__
  /*
  * erase 2
  */
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
#endif

  {
    ft::set<int> mydata;
    mydata.insert(1);
    mydata.insert(2);
    mydata.insert(3);
    mydata.insert(4);

    ft::set<int>::iterator myitr = mydata.begin();

    mydata.erase(myitr, ++myitr);

    ASSERT_EQ(mydata.size(), 3UL);

    myitr = mydata.begin();

    ASSERT_EQ(*myitr, 2);
    myitr++;
    ASSERT_EQ(*myitr, 3);
    myitr++;
    ASSERT_EQ(*myitr, 4);
    myitr++;
    ASSERT_EQ(myitr, mydata.end());
  }

  /*
  * erase 3
  */
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

  /*
  * swap
  */
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

  /*
  * count
  */
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

  /*
  * count const
  */
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

  /*
  * find
  */
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

  /*
  * find const
  */
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

  /*
  * equal_range
  */
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

  /*
  * equal_range const
  */
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

  /*
  * lower_bound
  */
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

  /*
  * lower_bound const
  */
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

  /*
  * upper_bound
  */
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

  /*
  * upper_bound const
  */
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

  /*
  * key_comp
  */
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

  /*
  * key_comp const
  */
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

  /*
  * value_comp
  */
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

  /*
  * value_comp const
  */
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

  /*
  * compare
  */
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

  /*
  * non member swap
  */
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

  {
    std::less_equal<int> stdcomp;
    std::allocator<int> stdalloc;
    std::set<int, std::less_equal<int> > stdst(stdcomp, stdalloc);

    stdst.insert(1);
    stdst.insert(1);
    stdst.insert(3);

    std::less_equal<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::set<int, std::less_equal<int> > ftst(ftcomp, ftalloc);

    ftst.insert(1);
    ftst.insert(1);
    ftst.insert(3);

    std::set<int, std::less_equal<int> >::iterator stditr = stdst.begin();
    ft::set<int, std::less_equal<int> >::iterator ftitr = ftst.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(*stditr, *ftitr);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(*stditr, *ftitr);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr, stdst.end());
    ASSERT_EQ(ftitr, ftst.end());
  }

  {
    std::greater_equal<int> stdcomp;
    std::allocator<int> stdalloc;
    std::set<int, std::greater_equal<int> > stdst(stdcomp, stdalloc);

    stdst.insert(1);
    stdst.insert(1);
    stdst.insert(3);

    std::greater_equal<int> ftcomp;
    std::allocator<int> ftalloc;
    ft::set<int, std::greater_equal<int> > ftst(ftcomp, ftalloc);

    ftst.insert(1);
    ftst.insert(1);
    ftst.insert(3);

    std::set<int, std::greater_equal<int> >::iterator stditr = stdst.begin();
    ft::set<int, std::greater_equal<int> >::iterator ftitr = ftst.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(*stditr, *ftitr);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(*stditr, *ftitr);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr, stdst.end());
    ASSERT_EQ(ftitr, ftst.end());
  }

  /*
  * iterator
  */
  {
    std::set<int> stdst;
    stdst.insert(1);
    stdst.insert(2);
    ft::set<int> ftst;
    ftst.insert(1);
    ftst.insert(2);

    std::set<int>::const_iterator stditr = stdst.begin();
    ft::set<int>::const_iterator ftitr = ftst.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(*stditr, *ftitr);
    ++ftitr;
    ++stditr;
    ASSERT_EQ(stditr, stdst.end());
    ASSERT_EQ(ftitr, ftst.end());
  }
}

void test_tree() {
  // detail::__tree_iterator
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr1 =
        t.begin();
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr2 =
        t.begin();

    ASSERT_EQ(itr1 == itr2, true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr1 =
        t.begin();
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr2 =
        t.begin();
    ++itr2;

    ASSERT_EQ(itr1 == itr2, false);
    ASSERT_EQ(itr1 != itr2, true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr1 =
        t.begin();
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr2 =
        t.end();

    ASSERT_EQ(itr1 == itr2, false);
    ASSERT_EQ(itr1 != itr2, true);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >::iterator
        itr1 = t.begin();
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >::iterator
        itr2 = t.begin();

    ASSERT_EQ(itr1 == itr2, true);
    ASSERT_EQ(itr1 != itr2, false);
  }

  // begin
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 1);

    ++itr;
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);

    ++itr;
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 4);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.insert(6);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(-1);
    t.insert(2);
    t.insert(-2);
    t.insert(3);
    t.insert(-4);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(-1);
    t.insert(2);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(-1);
    t.insert(2);
    t.insert(-2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -2);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(-1);
    t.insert(2);
    t.insert(-2);
    t.insert(3);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(-1);
    t.insert(2);
    t.insert(-2);
    t.insert(3);
    t.insert(-10);
    t.insert(-5);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();

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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(204);
    t.insert(205);
    t.insert(206);
    t.insert(93);
    t.insert(192);
    t.insert(202);
    t.insert(0);
    t.insert(305);
    t.insert(213);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(200);
    t.insert(196);
    t.insert(193);
    t.insert(187);
    t.insert(175);
    t.insert(150);
    t.insert(125);
    t.insert(112);
    t.insert(106);
    t.insert(103);
    t.insert(100);
    t.insert(96);
    t.insert(93);
    t.insert(87);
    t.insert(75);
    t.insert(50);
    t.insert(25);
    t.insert(12);
    t.insert(6);
    t.insert(3);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(6);
    t.insert(175);
    t.insert(125);
    t.insert(100);
    t.insert(150);
    t.insert(196);
    t.insert(103);
    t.insert(87);
    t.insert(187);
    t.insert(200);
    t.insert(93);
    t.insert(96);
    t.insert(3);
    t.insert(106);
    t.insert(12);
    t.insert(193);
    t.insert(50);
    t.insert(75);
    t.insert(25);
    t.insert(112);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(204);
    t.insert(205);
    t.insert(206);
    t.insert(93);
    t.insert(192);
    t.insert(202);
    t.insert(0);
    t.insert(305);
    t.insert(213);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.end();
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
    ASSERT_EQ(itr, t.begin());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(200);
    t.insert(196);
    t.insert(193);
    t.insert(187);
    t.insert(175);
    t.insert(150);
    t.insert(125);
    t.insert(112);
    t.insert(106);
    t.insert(103);
    t.insert(100);
    t.insert(96);
    t.insert(93);
    t.insert(87);
    t.insert(75);
    t.insert(50);
    t.insert(25);
    t.insert(12);
    t.insert(6);
    t.insert(3);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.end();

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

    ASSERT_EQ(itr, t.begin());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(6);
    t.insert(175);
    t.insert(125);
    t.insert(100);
    t.insert(150);
    t.insert(196);
    t.insert(103);
    t.insert(87);
    t.insert(187);
    t.insert(200);
    t.insert(93);
    t.insert(96);
    t.insert(3);
    t.insert(106);
    t.insert(12);
    t.insert(193);
    t.insert(50);
    t.insert(75);
    t.insert(25);
    t.insert(112);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.end();

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

    ASSERT_EQ(itr, t.begin());
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >::iterator
        itr = t.begin();
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);

    ++itr;
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(2, 2));
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >::iterator
        itr = t.begin();
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
    ++itr;
    ASSERT_EQ(itr->first, 2);
    ASSERT_EQ(itr->second, 2);

    ++itr;
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(2, 2));
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >::iterator
        itr = t.begin();
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
    ++itr;
    ASSERT_EQ(itr->first, 2);
    ASSERT_EQ(itr->second, 2);

    ++itr;
    ASSERT_EQ(itr, t.end());
  }

  // begin const
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > data;
    data.insert(1);
    const ft::detail::__tree<int, int, ft::detail::__Identity<int> > t(
        data.begin(), data.end());
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::const_iterator
        itr = t.begin();
    ASSERT_EQ(*itr, 1);

    ++itr;
    ASSERT_EQ(itr, t.end());
  }

  // end
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.end();
    --itr;
    ASSERT_EQ(*itr, 1);

    ASSERT_EQ(itr, t.begin());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.end();
    --itr;
    ASSERT_EQ(*itr, 2);
    --itr;
    ASSERT_EQ(*itr, 1);

    ASSERT_EQ(itr, t.begin());
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >::iterator
        itr = t.end();
    --itr;
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);

    ASSERT_EQ(itr, t.begin());
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(2, 2));
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >::iterator
        itr = t.end();
    --itr;
    ASSERT_EQ(itr->first, 2);
    ASSERT_EQ(itr->second, 2);
    --itr;
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);

    ASSERT_EQ(itr, t.begin());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(-1);
    t.insert(2);
    t.insert(-2);
    t.insert(3);
    t.insert(-10);
    t.insert(-5);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.end();

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

    ASSERT_EQ(itr, t.begin());
  }

  // rbegin
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::reverse_iterator
        itr = t.rbegin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(itr, t.rend());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::reverse_iterator
        itr = t.rbegin();
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(itr, t.rend());
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    ft::detail::__tree<
        int, ft::pair<int, int>,
        ft::detail::__Select1st<ft::pair<int, int> > >::reverse_iterator itr =
        t.rbegin();
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
    ++itr;
    ASSERT_EQ(itr, t.rend());
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(2, 2));
    ft::detail::__tree<
        int, ft::pair<int, int>,
        ft::detail::__Select1st<ft::pair<int, int> > >::reverse_iterator itr =
        t.rbegin();
    ASSERT_EQ(itr->first, 2);
    ASSERT_EQ(itr->second, 2);
    ++itr;
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
    ++itr;
    ASSERT_EQ(itr, t.rend());
  }

  // rend
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::reverse_iterator
        itr = t.rend();
    --itr;
    ASSERT_EQ(*itr, 1);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::reverse_iterator
        itr = t.rend();
    --itr;
    ASSERT_EQ(*itr, 1);
    --itr;
    ASSERT_EQ(*itr, 2);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    ft::detail::__tree<
        int, ft::pair<int, int>,
        ft::detail::__Select1st<ft::pair<int, int> > >::reverse_iterator itr =
        t.rend();
    --itr;
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(2, 2));
    ft::detail::__tree<
        int, ft::pair<int, int>,
        ft::detail::__Select1st<ft::pair<int, int> > >::reverse_iterator itr =
        t.rend();
    --itr;
    ASSERT_EQ(itr->first, 1);
    ASSERT_EQ(itr->second, 1);
    --itr;
    ASSERT_EQ(itr->first, 2);
    ASSERT_EQ(itr->second, 2);
  }

  // insert
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();

    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->left->is_nil_node(), true);
    ASSERT_EQ(root->right->is_nil_node(), true);

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->left->parent, root);

    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->parent, root);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();
    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->left->is_nil_node(), true);
    ASSERT_EQ(root->right->is_red_node(), true);
    ASSERT_EQ(root->right->right->is_nil_node(), true);
    ASSERT_EQ(root->right->left->is_nil_node(), true);

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->right->right->parent, root->right);
    ASSERT_EQ(root->right->left->parent, root->right);

    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->right->value, 2);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(-1);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();
    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->left->is_red_node(), true);

    ASSERT_EQ(root->value, 1);
    ASSERT_EQ(root->left->value, -1);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();

    ASSERT_EQ(root->parent, root);
    ASSERT_EQ(root->left->parent, root);
    ASSERT_EQ(root->right->parent, root);
    ASSERT_EQ(root->left->left->parent, root->left);
    ASSERT_EQ(root->left->right->parent, root->left);
    ASSERT_EQ(root->right->left->parent, root->right);
    ASSERT_EQ(root->right->right->parent, root->right);

    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->left->is_red_node(), true);
    ASSERT_EQ(root->left->left->is_nil_node(), true);
    ASSERT_EQ(root->left->right->is_nil_node(), true);

    ASSERT_EQ(root->right->is_red_node(), true);
    ASSERT_EQ(root->right->left->is_nil_node(), true);
    ASSERT_EQ(root->right->right->is_nil_node(), true);

    ASSERT_EQ(root->value, 2);
    ASSERT_EQ(root->right->value, 3);
    ASSERT_EQ(root->left->value, 1);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(-1);
    t.insert(-2);
    t.insert(-3);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();
    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->left->is_red_node(), true);
    ASSERT_EQ(root->left->left->is_nil_node(), true);
    ASSERT_EQ(root->left->right->is_nil_node(), true);
    ASSERT_EQ(root->right->is_red_node(), true);
    ASSERT_EQ(root->right->left->is_nil_node(), true);
    ASSERT_EQ(root->right->right->is_nil_node(), true);

    ASSERT_EQ(root->value, -2);
    ASSERT_EQ(root->right->value, -1);
    ASSERT_EQ(root->left->value, -3);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();
    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->left->is_black_node(), true);
    ASSERT_EQ(root->right->is_black_node(), true);
    ASSERT_EQ(root->right->right->is_red_node(), true);

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
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();

    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->left->is_black_node(), true);
    ASSERT_EQ(root->right->is_black_node(), true);
    ASSERT_EQ(root->right->left->is_red_node(), true);
    ASSERT_EQ(root->right->right->is_red_node(), true);

    ASSERT_EQ(root->left->left->is_nil_node(), true);
    ASSERT_EQ(root->left->right->is_nil_node(), true);
    ASSERT_EQ(root->right->left->left->is_nil_node(), true);
    ASSERT_EQ(root->right->left->right->is_nil_node(), true);
    ASSERT_EQ(root->right->right->left->is_nil_node(), true);
    ASSERT_EQ(root->right->right->right->is_nil_node(), true);

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
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(-1);
    t.insert(2);
    t.insert(-2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();

    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->left->is_black_node(), true);
    ASSERT_EQ(root->left->left->is_red_node(), true);
    ASSERT_EQ(root->left->right->is_nil_node(), true);
    ASSERT_EQ(root->left->left->left->is_nil_node(), true);
    ASSERT_EQ(root->left->left->right->is_nil_node(), true);
    ASSERT_EQ(root->right->is_black_node(), true);
    ASSERT_EQ(root->right->left->is_nil_node(), true);
    ASSERT_EQ(root->right->right->is_nil_node(), true);

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
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(-1);
    t.insert(2);
    t.insert(-2);
    t.insert(3);
    t.insert(-3);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();

    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->left->is_black_node(), true);
    ASSERT_EQ(root->left->left->is_red_node(), true);
    ASSERT_EQ(root->left->left->left->is_nil_node(), true);
    ASSERT_EQ(root->left->left->right->is_nil_node(), true);
    ASSERT_EQ(root->left->right->is_red_node(), true);
    ASSERT_EQ(root->left->right->left->is_nil_node(), true);
    ASSERT_EQ(root->left->right->right->is_nil_node(), true);
    ASSERT_EQ(root->right->is_black_node(), true);
    ASSERT_EQ(root->right->right->is_red_node(), true);
    ASSERT_EQ(root->right->right->left->is_nil_node(), true);
    ASSERT_EQ(root->right->right->right->is_nil_node(), true);
    ASSERT_EQ(root->right->left->is_nil_node(), true);

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
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(-10);
    t.insert(10);
    t.insert(-5);
    t.insert(15);
    t.insert(20);
    t.insert(-12);
    t.insert(100);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();

    ASSERT_EQ(root->is_black_node(), true);

    ASSERT_EQ(root->left->is_black_node(), true);
    ASSERT_EQ(root->left->left->is_red_node(), true);
    ASSERT_EQ(root->left->right->is_red_node(), true);

    ASSERT_EQ(root->left->left->left->is_nil_node(), true);
    ASSERT_EQ(root->left->left->right->is_nil_node(), true);

    ASSERT_EQ(root->left->right->left->is_nil_node(), true);
    ASSERT_EQ(root->left->right->right->is_nil_node(), true);

    ASSERT_EQ(root->right->is_red_node(), true);
    ASSERT_EQ(root->right->left->is_black_node(), true);
    ASSERT_EQ(root->right->right->is_black_node(), true);

    ASSERT_EQ(root->right->left->left->is_nil_node(), true);
    ASSERT_EQ(root->right->left->right->is_nil_node(), true);

    ASSERT_EQ(root->right->right->right->is_red_node(), true);
    ASSERT_EQ(root->right->right->right->left->is_nil_node(), true);
    ASSERT_EQ(root->right->right->right->right->is_nil_node(), true);

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
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(204);
    t.insert(205);
    t.insert(206);
    t.insert(93);
    t.insert(192);
    t.insert(202);
    t.insert(0);
    t.insert(305);
    t.insert(213);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        root = t.root();

    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->left->is_red_node(), true);
    ASSERT_EQ(root->left->left->is_black_node(), true);
    ASSERT_EQ(root->left->left->right->is_nil_node(), true);
    ASSERT_EQ(root->left->left->left->is_red_node(), true);
    ASSERT_EQ(root->left->left->left->left->is_nil_node(), true);
    ASSERT_EQ(root->left->left->left->right->is_nil_node(), true);
    ASSERT_EQ(root->left->right->is_black_node(), true);
    ASSERT_EQ(root->left->right->right->is_nil_node(), true);
    ASSERT_EQ(root->left->right->left->is_red_node(), true);
    ASSERT_EQ(root->left->right->left->left->is_nil_node(), true);
    ASSERT_EQ(root->left->right->left->right->is_nil_node(), true);
    ASSERT_EQ(root->right->is_black_node(), true);
    ASSERT_EQ(root->right->left->is_red_node(), true);
    ASSERT_EQ(root->right->left->left->is_nil_node(), true);
    ASSERT_EQ(root->right->left->right->is_nil_node(), true);
    ASSERT_EQ(root->right->right->is_red_node(), true);
    ASSERT_EQ(root->right->right->left->is_nil_node(), true);
    ASSERT_EQ(root->right->right->right->is_nil_node(), true);

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
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(2, 2));
    ft::detail::__tree<
        int, ft::pair<int, int>,
        ft::detail::__Select1st<ft::pair<int, int> > >::node_pointer root =
        t.root();
    ASSERT_EQ(root->is_black_node(), true);
    ASSERT_EQ(root->value.first, 1);
    ASSERT_EQ(root->value.second, 1);
    ASSERT_EQ(root->right->is_red_node(), true);
    ASSERT_EQ(root->right->value.first, 2);
    ASSERT_EQ(root->right->value.second, 2);
    ASSERT_EQ(root->right->parent, root);
  }

  // size
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    ASSERT_EQ(t.size(), 1UL);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    ASSERT_EQ(t.size(), 1UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    ASSERT_EQ(t.size(), 2UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    ASSERT_EQ(t.size(), 3UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(1);
    t.insert(1);
    ASSERT_EQ(t.size(), 1UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(1);
    ASSERT_EQ(t.size(), 2UL);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(2, 2));
    ASSERT_EQ(t.size(), 2UL);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(2, 2));
    t.insert(ft::make_pair(3, 3));
    ASSERT_EQ(t.size(), 3UL);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(1, 1));
    ASSERT_EQ(t.size(), 1UL);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(1, 2));
    t.insert(ft::make_pair(1, 3));
    ASSERT_EQ(t.size(), 1UL);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    t.insert(ft::make_pair(2, 2));
    t.insert(ft::make_pair(1, 3));
    ASSERT_EQ(t.size(), 2UL);
  }

  // empty
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    ASSERT_EQ(t.empty(), true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    ASSERT_EQ(t.empty(), false);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    ASSERT_EQ(t.empty(), true);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));
    ASSERT_EQ(t.empty(), false);
  }

  // find
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.find(1);

    ASSERT_EQ(*itr, 1);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.find(1);

    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.find(1);

    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.find(1);

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
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.find(3);

    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 4);
    ++itr;
    ASSERT_EQ(*itr, 5);
  }

  // lower_bound
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.insert(20);
    t.insert(30);
    t.insert(40);
    t.insert(50);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.lower_bound(10);

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
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.insert(20);
    t.insert(30);
    t.insert(40);
    t.insert(50);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.lower_bound(11);

    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(*itr, 50);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(-10);
    t.insert(20);

    ASSERT_EQ(*(t.lower_bound(-10)), -10);
    ASSERT_EQ(*(t.lower_bound(5)), 5);
    ASSERT_EQ(*(t.lower_bound(10)), 10);
    ASSERT_EQ(*(t.lower_bound(15)), 15);
    ASSERT_EQ(*(t.lower_bound(20)), 20);
    ASSERT_EQ(*(t.lower_bound(-100)), -10);
    ASSERT_EQ(*(t.lower_bound(1)), 5);
    ASSERT_EQ(*(t.lower_bound(6)), 10);
    ASSERT_EQ(*(t.lower_bound(11)), 15);
    ASSERT_EQ(*(t.lower_bound(16)), 20);
    ASSERT_EQ(t.lower_bound(100), t.end());
  }

  // find_node_pointer
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        ptr = t.find_node_pointer(1);

    ASSERT_EQ(ptr->value, 1);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        ptr = t.find_node_pointer(1);

    ASSERT_EQ(ptr->value, 1);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        ptr = t.find_node_pointer(2);

    ASSERT_EQ(ptr->value, 2);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        ptr = t.find_node_pointer(1);

    ASSERT_EQ(ptr->value, 1);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        ptr = t.find_node_pointer(2);

    ASSERT_EQ(ptr->value, 2);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        ptr = t.find_node_pointer(3);

    ASSERT_EQ(ptr->value, 3);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer
        ptr = t.find_node_pointer(4);

    ASSERT_EQ(ptr->value, 4);
  }

  // upper_bound
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.insert(20);
    t.insert(30);
    t.insert(40);
    t.insert(50);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.upper_bound(10);

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
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);

    ASSERT_EQ(t.count(10), 1UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);

    ASSERT_EQ(t.count(42), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);

    ASSERT_EQ(t.count(42), 0UL);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));

    ASSERT_EQ(t.count(1), 1UL);
  }

  {
    ft::detail::__tree<int, ft::pair<int, int>,
                       ft::detail::__Select1st<ft::pair<int, int> > >
        t;
    t.insert(ft::make_pair(1, 1));

    ASSERT_EQ(t.count(42), 0UL);
  }

  // operator==
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t1;
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t2;
    ASSERT_EQ(t1 == t2, true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t1;
    t1.insert(1);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t2;
    ASSERT_EQ(t1 != t2, true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t1;
    t1.insert(1);
    t1.insert(2);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t2;
    t2.insert(1);
    t2.insert(3);
    ASSERT_EQ(t1 < t2, true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t1;
    t1.insert(1);
    t1.insert(2);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t2;
    t2.insert(1);
    t2.insert(2);
    ASSERT_EQ(t1 >= t2, true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t1;
    t1.insert(1);
    t1.insert(3);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t2;
    t2.insert(1);
    t2.insert(2);
    ASSERT_EQ(t1 >= t2, true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t1;
    t1.insert(1);
    t1.insert(3);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t2;
    t2.insert(1);
    t2.insert(2);
    ASSERT_EQ(t1 > t2, true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t1;
    t1.insert(1);
    t1.insert(2);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t2;
    t2.insert(1);
    t2.insert(2);
    ASSERT_EQ(t1 <= t2, true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t1;
    t1.insert(1);
    t1.insert(2);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t2;
    t2.insert(1);
    t2.insert(3);
    ASSERT_EQ(t1 <= t2, true);
  }

  // erase
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.erase(1);

    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.erase(2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer r =
        t.root();

    ASSERT_EQ(t.size(), 1UL);

    ASSERT_EQ(r->is_black_node(), true);
    ASSERT_EQ(r->left->is_nil_node(), true);
    ASSERT_EQ(r->right->is_nil_node(), true);

    ASSERT_EQ(r->parent, r);

    ASSERT_EQ(r->value, 1);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);

    t.erase(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer r =
        t.root();

    ASSERT_EQ(t.size(), 1UL);

    ASSERT_EQ(r->is_black_node(), true);
    ASSERT_EQ(r->left->is_nil_node(), true);
    ASSERT_EQ(r->right->is_black_node(), true);
    ASSERT_EQ(r->right->is_nil_node(), true);

    ASSERT_EQ(r->parent, r);

    ASSERT_EQ(r->value, 2);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);

    t.erase(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer r =
        t.root();

    ASSERT_EQ(t.size(), 2UL);

    ASSERT_EQ(r->is_black_node(), true);
    ASSERT_EQ(r->left->is_nil_node(), true);
    ASSERT_EQ(r->right->is_red_node(), true);
    ASSERT_EQ(r->right->right->is_nil_node(), true);
    ASSERT_EQ(r->right->left->is_nil_node(), true);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->right->parent, r);
    ASSERT_EQ(r->right->left->parent, r->right);
    ASSERT_EQ(r->right->right->parent, r->right);

    ASSERT_EQ(r->value, 2);
    ASSERT_EQ(r->right->value, 3);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);

    t.erase(2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer r =
        t.root();

    ASSERT_EQ(t.size(), 2UL);

    ASSERT_EQ(r->is_black_node(), true);
    ASSERT_EQ(r->left->is_black_node(), false);
    ASSERT_EQ(r->left->is_red_node(), true);
    ASSERT_EQ(r->left->left->is_nil_node(), true);
    ASSERT_EQ(r->left->right->is_nil_node(), true);
    ASSERT_EQ(r->right->is_nil_node(), true);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->left->left->parent, r->left);
    ASSERT_EQ(r->left->right->parent, r->left);
    ASSERT_EQ(r->right->parent, r);

    ASSERT_EQ(r->value, 3);
    ASSERT_EQ(r->left->value, 1);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);

    t.erase(3);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer r =
        t.root();

    ASSERT_EQ(t.size(), 2UL);

    ASSERT_EQ(r->is_black_node(), true);
    ASSERT_EQ(r->left->is_red_node(), true);
    ASSERT_EQ(r->left->left->is_nil_node(), true);
    ASSERT_EQ(r->left->right->is_nil_node(), true);
    ASSERT_EQ(r->right->is_nil_node(), true);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->left->left->parent, r->left);
    ASSERT_EQ(r->left->right->parent, r->left);
    ASSERT_EQ(r->right->parent, r);

    ASSERT_EQ(r->value, 2);
    ASSERT_EQ(r->left->value, 1);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);

    t.erase(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer r =
        t.root();

    ASSERT_EQ(t.size(), 3UL);

    ASSERT_EQ(r->is_black_node(), true);
    ASSERT_EQ(r->left->is_black_node(), true);
    ASSERT_EQ(r->left->left->is_nil_node(), true);
    ASSERT_EQ(r->left->right->is_nil_node(), true);
    ASSERT_EQ(r->right->is_black_node(), true);
    ASSERT_EQ(r->right->left->is_nil_node(), true);
    ASSERT_EQ(r->right->right->is_nil_node(), true);

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
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);

    t.erase(2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 1);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);

    t.erase(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);

    t.erase(-1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);

    t.erase(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);

    t.erase(2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);

    t.erase(-1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);

    t.erase(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);

    t.erase(2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);

    t.erase(10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);

    t.erase(-1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);

    t.erase(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);

    t.erase(2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 10);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);

    t.erase(10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, -10);
    ++itr;
    ASSERT_EQ(*itr, -1);
    ++itr;
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);
    t.insert(5);

    t.erase(-10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);
    t.insert(5);

    t.erase(-1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);
    t.insert(5);

    t.erase(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);
    t.insert(5);

    t.erase(2);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);
    t.insert(5);

    t.erase(5);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);
    t.insert(5);

    t.erase(10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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

    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);

    t.erase(1);
    t.erase(2);

    ASSERT_EQ(t.empty(), true);
    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);

    t.erase(1);
    t.erase(2);
    t.erase(-1);

    ASSERT_EQ(t.empty(), true);
    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);

    t.erase(1);
    t.erase(2);
    t.erase(-1);
    t.erase(10);

    ASSERT_EQ(t.empty(), true);
    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);

    t.erase(1);
    t.erase(2);
    t.erase(-1);
    t.erase(10);
    t.erase(-10);

    ASSERT_EQ(t.empty(), true);
    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(1);
    t.insert(2);
    t.insert(-1);
    t.insert(10);
    t.insert(-10);
    t.insert(5);

    t.erase(1);
    t.erase(2);
    t.erase(-1);
    t.erase(10);
    t.erase(-10);
    t.erase(5);

    ASSERT_EQ(t.empty(), true);
    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(100);
    t.insert(20);
    t.insert(10);
    t.insert(200);
    t.insert(1);
    t.insert(500);
    t.insert(300);

    t.erase(100);
    t.erase(20);
    t.erase(10);
    t.erase(200);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer r =
        t.root();
    ASSERT_EQ(r->is_black_node(), true);
    ASSERT_EQ(r->left->is_black_node(), true);
    ASSERT_EQ(r->right->is_black_node(), true);
    ASSERT_EQ(r->left->left->is_nil_node(), true);
    ASSERT_EQ(r->left->right->is_nil_node(), true);
    ASSERT_EQ(r->right->left->is_nil_node(), true);
    ASSERT_EQ(r->right->right->is_nil_node(), true);

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

    ASSERT_EQ(t.size(), 3UL);

    t.erase(1);
    t.erase(500);
    t.erase(300);

    ASSERT_EQ(t.empty(), true);
    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.erase(10);
    t.insert(20);
    t.erase(20);
    t.insert(30);
    t.erase(30);

    ASSERT_EQ(t.empty(), true);
    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.insert(20);
    t.erase(10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.insert(10);

    itr = t.begin();
    ASSERT_EQ(*itr, 10);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.insert(20);
    t.insert(30);
    t.erase(10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.insert(10);

    itr = t.begin();
    ASSERT_EQ(*itr, 10);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.insert(20);
    t.insert(30);
    t.insert(40);
    t.erase(10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.insert(10);

    itr = t.begin();
    ASSERT_EQ(*itr, 10);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.insert(20);
    t.insert(30);
    t.insert(40);
    t.insert(50);
    t.erase(10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(*itr, 30);
    ++itr;
    ASSERT_EQ(*itr, 40);
    ++itr;
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.insert(10);

    itr = t.begin();
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
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.insert(1);
    t.insert(20);
    t.insert(2);
    t.insert(3);
    t.erase(10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.insert(10);

    itr = t.begin();
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
    ASSERT_EQ(itr, t.end());
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(10);
    t.insert(1);
    t.insert(20);
    t.insert(2);
    t.insert(3);
    t.erase(10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 3);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.erase(3);

    itr = t.begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 2);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.erase(2);

    itr = t.begin();
    ASSERT_EQ(*itr, 1);
    ++itr;
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.erase(1);

    itr = t.begin();
    ASSERT_EQ(*itr, 20);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.erase(20);

    ASSERT_EQ(t.size(), 0UL);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t;
    t.insert(100);
    t.insert(10);
    t.insert(50);
    t.insert(1);
    t.insert(1000);
    t.insert(1200);
    t.insert(500);

    t.erase(10);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::iterator itr =
        t.begin();
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
    ASSERT_EQ(itr, t.end());

    t.erase(1000);

    itr = t.begin();
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
    ASSERT_EQ(itr, t.end());

    t.erase(1);

    itr = t.begin();
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(*itr, 100);
    ++itr;
    ASSERT_EQ(*itr, 500);
    ++itr;
    ASSERT_EQ(*itr, 1200);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.erase(1200);

    itr = t.begin();
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(*itr, 100);
    ++itr;
    ASSERT_EQ(*itr, 500);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.erase(500);

    itr = t.begin();
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(*itr, 100);
    ++itr;
    ASSERT_EQ(itr, t.end());

    ft::detail::__tree<int, int, ft::detail::__Identity<int> >::node_pointer r =
        t.root();
    ASSERT_EQ(r->is_black_node(), true);
    ASSERT_EQ(r->left->is_red_node(), true);
    ASSERT_EQ(r->right->is_nil_node(), true);
    ASSERT_EQ(r->right, t.end_node());

    ASSERT_EQ(r->value, 100);
    ASSERT_EQ(r->left->value, 50);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->right->parent, r);

    t.erase(100);

    r = t.root();
    ASSERT_EQ(r->is_black_node(), true);
    ASSERT_EQ(r->left->is_nil_node(), true);
    ASSERT_EQ(r->right->is_nil_node(), true);
    ASSERT_EQ(r->left->is_black_node(), true);
    ASSERT_EQ(r->right->is_black_node(), true);
    ASSERT_EQ(r->right, t.end_node());

    ASSERT_EQ(r->value, 50);

    ASSERT_EQ(r->parent, r);
    ASSERT_EQ(r->left->parent, r);
    ASSERT_EQ(r->right->parent, r);

    itr = t.begin();
    ASSERT_EQ(*itr, 50);
    ++itr;
    ASSERT_EQ(itr, t.end());

    t.erase(50);

    ASSERT_EQ(t.size(), 0UL);
    ASSERT_EQ(t.empty(), true);
  }

  // comp
  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t1;
    t1.insert(1);
    t1.insert(2);
    t1.insert(3);
    t1.insert(4);
    t1.insert(5);
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t2;
    t2.insert(1);
    t2.insert(2);
    t2.insert(3);
    t2.insert(4);
    t2.insert(5);

    ASSERT_EQ(t1 == t2, true);
    ASSERT_EQ(t1 != t2, false);
    ASSERT_EQ(t1 < t2, false);
    ASSERT_EQ(t1 > t2, false);
    ASSERT_EQ(t1 <= t2, true);
    ASSERT_EQ(t1 >= t2, true);
  }

  {
    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t1;
    t1.insert(1);

    ft::detail::__tree<int, int, ft::detail::__Identity<int> > t2;
    t2.insert(1);

    ASSERT_EQ(t1 == t2, true);
    ASSERT_EQ(t1 != t2, false);
    ASSERT_EQ(t1 < t2, false);
    ASSERT_EQ(t1 > t2, false);
    ASSERT_EQ(t1 <= t2, true);
    ASSERT_EQ(t1 >= t2, true);
  }
}

void test_vector() {
  {
    ft::vector<int> ftvec1(3, 42);
    const ft::vector<int> ftvec2(3, 42);

    (void)(ftvec1.begin() == ftvec2.begin());
  }

  /*
  * constructor 1
  */
  {
    std::vector<int> stdvec;
    stdvec.push_back(1);
    ft::vector<int> ftvec;
    ftvec.push_back(1);
    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
  }

  /*
  * constructor 2
  */
  {
    try {
      AlwaysThrowAllocator<int> myalloc;
      std::vector<int, AlwaysThrowAllocator<int> > stdvec(myalloc);
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
  }

  /*
  * constructor 3
  */
  {
    std::vector<int> stdvec(3);
    ft::vector<int> ftvec(3);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));
  }

  /*
  * constructor 5
  */
  {
    std::vector<int> stddata(3, 42);
    ft::vector<int> ftdata(3, 42);

    std::vector<int> stdvec(stddata.begin(), stddata.end());
    ft::vector<int> ftvec(ftdata.begin(), ftdata.end());

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));
  }

  /*
  * constructor 6
  */
  {
    std::vector<int> stddata(3, 42);
    ft::vector<int> ftdata(3, 42);

    std::vector<int> stdvec(stddata);
    ft::vector<int> ftvec(ftdata);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));
  }

  /*
  * operator=
  */
  {
    std::vector<int> stddata(3, 42);
    ft::vector<int> ftdata(3, 42);

    std::vector<int> stdvec;
    ft::vector<int> ftvec;

    stdvec = stddata;
    ftvec = ftdata;

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));
  }

  /*
  * assign 1
  */
  {
    std::vector<int> stdvec;
    ft::vector<int> ftvec;

    stdvec.assign(3, 42);
    ftvec.assign(3, 42);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));
  }

  /*
  * assign 2
  */
  {
    std::vector<int> stddata(3, 42);
    ft::vector<int> ftdata(3, 42);
    std::vector<int> stdvec;
    ft::vector<int> ftvec;

    stdvec.assign(stddata.begin(), stddata.end());
    ftvec.assign(ftdata.begin(), ftdata.end());

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));
  }

  /*
  * get_allocator
  */
  {
    std::allocator<int> alloc;
    std::vector<int> stdvec(alloc);
    ft::vector<int> ftvec(alloc);

    ASSERT_EQ(stdvec.get_allocator(), ftvec.get_allocator());
  }

  /*
  * at
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));

    stdvec.at(0) = 4242;
    ftvec.at(0) = 4242;
    stdvec.at(1) = 4242;
    ftvec.at(1) = 4242;
    stdvec.at(2) = 4242;
    ftvec.at(2) = 4242;

    ASSERT_EQ(stdvec[0], ftvec[0]);
    ASSERT_EQ(stdvec[1], ftvec[1]);
    ASSERT_EQ(stdvec[2], ftvec[2]);
  }

  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));
  }

  /*
  * at exception
  */
  {
    bool has_exception_occured = false;
    try {
      ft::vector<int> myvec;
      myvec.at(100);
    } catch (const std::out_of_range& e) {
      // do nothing
      has_exception_occured = true;
    } catch (const std::exception& e) {
      std::exit(1);
    }
    ASSERT_EQ(has_exception_occured, true);
    has_exception_occured = false;
    try {
      std::vector<int> libvec;
      libvec.at(100);
    } catch (const std::out_of_range& e) {
      // do nothing
      has_exception_occured = true;
    } catch (const std::exception& e) {
      std::exit(1);
    }
    ASSERT_EQ(has_exception_occured, true);
  }

  /*
  * operator[]
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec[0], ftvec[0]);
    ASSERT_EQ(stdvec[1], ftvec[1]);
    ASSERT_EQ(stdvec[2], ftvec[2]);
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec[0], ftvec[0]);
    ASSERT_EQ(stdvec[1], ftvec[1]);
    ASSERT_EQ(stdvec[2], ftvec[2]);

    stdvec[0] = 4242;
    ftvec[0] = 4242;
    stdvec[1] = 4242;
    ftvec[1] = 4242;
    stdvec[2] = 4242;
    ftvec[2] = 4242;

    ASSERT_EQ(stdvec[0], ftvec[0]);
    ASSERT_EQ(stdvec[1], ftvec[1]);
    ASSERT_EQ(stdvec[2], ftvec[2]);
  }

  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec[0], ftvec[0]);
    ASSERT_EQ(stdvec[1], ftvec[1]);
    ASSERT_EQ(stdvec[2], ftvec[2]);
  }

  /*
  * front
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.front(), ftvec.front());
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.front(), ftvec.front());

    stdvec.front() = 4242;
    ftvec.front() = 4242;

    ASSERT_EQ(stdvec.front(), ftvec.front());
  }

  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.front(), ftvec.front());
  }

  /*
  * back
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.back(), ftvec.back());
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.back(), ftvec.back());

    stdvec.back() = 4242;
    ftvec.back() = 4242;

    ASSERT_EQ(stdvec.back(), ftvec.back());
  }

  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.back(), ftvec.back());
  }

  /*
  * data
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    int* stddata = stdvec.data();
    int* ftdata = ftvec.data();

    ASSERT_EQ(stddata[0], ftdata[0]);
    ASSERT_EQ(stddata[1], ftdata[1]);
    ASSERT_EQ(stddata[2], ftdata[2]);
  }

  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    const int* stddata = stdvec.data();
    const int* ftdata = ftvec.data();

    ASSERT_EQ(stddata[0], ftdata[0]);
    ASSERT_EQ(stddata[1], ftdata[1]);
    ASSERT_EQ(stddata[2], ftdata[2]);
  }

  /*
  * begin
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  /*
  * begin const
  */
  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    std::vector<int>::const_iterator stditr = stdvec.begin();
    ft::vector<int>::const_iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  /*
  * end
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stditr = stdvec.end();
    ft::vector<int>::iterator ftitr = ftvec.end();

    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stdvec.begin());
    ASSERT_EQ(ftitr, ftvec.begin());
  }

  /*
  * end const
  */
  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    std::vector<int>::const_iterator stditr = stdvec.end();
    ft::vector<int>::const_iterator ftitr = ftvec.end();

    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stdvec.begin());
    ASSERT_EQ(ftitr, ftvec.begin());
  }

  /*
  * rbegin
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::reverse_iterator stditr = stdvec.rbegin();
    ft::vector<int>::reverse_iterator ftitr = ftvec.rbegin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdvec.rend());
    ASSERT_EQ(ftitr, ftvec.rend());
  }

  /*
  * rbegin const
  */
  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    std::vector<int>::const_reverse_iterator stditr = stdvec.rbegin();
    ft::vector<int>::const_reverse_iterator ftitr = ftvec.rbegin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdvec.rend());
    ASSERT_EQ(ftitr, ftvec.rend());
  }

  {
    std::vector<std::pair<int, int> > stdvec;
    ft::vector<std::pair<int, int> > ftvec;

    stdvec.push_back(std::make_pair(1, 32));
    ftvec.push_back(std::make_pair(1, 32));

    std::vector<std::pair<int, int> >::const_reverse_iterator stditr =
        stdvec.rbegin();
    ft::vector<std::pair<int, int> >::const_reverse_iterator ftitr =
        ftvec.rbegin();

    ASSERT_EQ(stditr->first, ftitr->first);
    ASSERT_EQ(stditr->second, ftitr->second);
  }

  /*
  * rend
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::const_reverse_iterator stditr = stdvec.rend();
    ft::vector<int>::const_reverse_iterator ftitr = ftvec.rend();

    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stdvec.rbegin());
    ASSERT_EQ(ftitr, ftvec.rbegin());
  }

  /*
  * rend const
  */
  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    std::vector<int>::const_reverse_iterator stditr = stdvec.rend();
    ft::vector<int>::const_reverse_iterator ftitr = ftvec.rend();

    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    --stditr;
    --ftitr;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stdvec.rbegin());
    ASSERT_EQ(ftitr, ftvec.rbegin());
  }

  /*
  * empty
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.empty(), ftvec.empty());
  }

  {
    std::vector<int> stdvec;
    ft::vector<int> ftvec;

    ASSERT_EQ(stdvec.empty(), ftvec.empty());
  }

  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.empty(), ftvec.empty());
  }

  {
    const std::vector<int> stdvec;
    const ft::vector<int> ftvec;

    ASSERT_EQ(stdvec.empty(), ftvec.empty());
  }

  /*
  * size
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.size(), ftvec.size());
  }

  {
    std::vector<int> stdvec;
    ft::vector<int> ftvec;

    ASSERT_EQ(stdvec.size(), ftvec.size());
  }

  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.size(), ftvec.size());
  }

  {
    const std::vector<int> stdvec;
    const ft::vector<int> ftvec;

    ASSERT_EQ(stdvec.size(), ftvec.size());
  }

  /*
  * max_size
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.max_size(), ftvec.max_size());
  }

  {
    const std::vector<int> stdvec(3, 42);
    const ft::vector<int> ftvec(3, 42);

    ASSERT_EQ(stdvec.max_size(), ftvec.max_size());
  }

  /*
  * reserve
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    stdvec.reserve(1000);
    ftvec.reserve(1000);

    ASSERT_EQ(stdvec.capacity(), ftvec.capacity());
    ASSERT_EQ(stdvec.at(0), ftvec.at(0));
    ASSERT_EQ(stdvec.at(1), ftvec.at(1));
    ASSERT_EQ(stdvec.at(2), ftvec.at(2));
  }

  /*
  * capacity const
  */
  {
    const ft::vector<int> ftvec(3, 42);

    ftvec.capacity();
  }

  /*
  * clear
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::size_type stdcap = stdvec.capacity();
    ft::vector<int>::size_type ftcap = ftvec.capacity();

    stdvec.clear();
    ftvec.clear();

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.capacity(), stdcap);
    ASSERT_EQ(ftvec.capacity(), ftcap);
  }

  /*
  * insert 1
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    std::vector<int>::iterator stdret = stdvec.insert(stdpos, 4242);
    ft::vector<int>::iterator ftret = ftvec.insert(ftpos, 4242);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    ++stdpos;
    ++ftpos;

    std::vector<int>::iterator stdret = stdvec.insert(stdpos, 4242);
    ft::vector<int>::iterator ftret = ftvec.insert(ftpos, 4242);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    stdpos += 2;
    ftpos += 2;

    std::vector<int>::iterator stdret = stdvec.insert(stdpos, 4242);
    ft::vector<int>::iterator ftret = ftvec.insert(ftpos, 4242);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  /*
  * insert 3
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    std::vector<int>::iterator stdret = stdvec.insert(stdpos, 3, 4242);
    ft::vector<int>::iterator ftret = ftvec.insert(ftpos, 3, 4242);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    stdpos++;
    ftpos++;

    std::vector<int>::iterator stdret = stdvec.insert(stdpos, 3, 4242);
    ft::vector<int>::iterator ftret = ftvec.insert(ftpos, 3, 4242);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    stdpos += 2;
    ftpos += 2;

    std::vector<int>::iterator stdret = stdvec.insert(stdpos, 3, 4242);
    ft::vector<int>::iterator ftret = ftvec.insert(ftpos, 3, 4242);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  /*
  * insert 4
  */
  {
    std::vector<int> stddata(3, 4242);
    ft::vector<int> ftdata(3, 4242);

    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    std::vector<int>::iterator stdret =
        stdvec.insert(stdpos, stddata.begin(), stddata.end());
    ft::vector<int>::iterator ftret =
        ftvec.insert(ftpos, ftdata.begin(), ftdata.end());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stddata(3, 4242);
    ft::vector<int> ftdata(3, 4242);

    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    stdpos += 1;
    ftpos += 1;

    std::vector<int>::iterator stdret =
        stdvec.insert(stdpos, stddata.begin(), stddata.end());
    ft::vector<int>::iterator ftret =
        ftvec.insert(ftpos, ftdata.begin(), ftdata.end());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stddata(3, 4242);
    ft::vector<int> ftdata(3, 4242);

    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    stdpos += 2;
    ftpos += 2;

    std::vector<int>::iterator stdret =
        stdvec.insert(stdpos, stddata.begin(), stddata.end());
    ft::vector<int>::iterator ftret =
        ftvec.insert(ftpos, ftdata.begin(), ftdata.end());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::set<int> stddata;
    stddata.insert(1);
    stddata.insert(2);
    stddata.insert(3);

    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    std::vector<int>::iterator stdret =
        stdvec.insert(stdpos, stddata.begin(), stddata.end());
    ft::vector<int>::iterator ftret =
        ftvec.insert(ftpos, stddata.begin(), stddata.end());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  /*
  * erase 1
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    std::vector<int>::iterator stdret = stdvec.erase(stdpos);
    ft::vector<int>::iterator ftret = ftvec.erase(ftpos);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;

    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdpos = stdvec.begin();
    ft::vector<int>::iterator ftpos = ftvec.begin();

    stdpos += 2;
    ftpos += 2;

    std::vector<int>::iterator stdret = stdvec.erase(stdpos);
    ft::vector<int>::iterator ftret = ftvec.erase(ftpos);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stdvec.size(), ftvec.size());

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;

    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  /*
  * erase 2
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdfirst = stdvec.begin();
    ft::vector<int>::iterator ftfirst = ftvec.begin();

    std::vector<int>::iterator stdend = stdvec.end();
    ft::vector<int>::iterator ftend = ftvec.end();

    stdvec.erase(stdfirst, stdend);
    ftvec.erase(ftfirst, ftend);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdvec.empty(), ftvec.empty());
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdfirst = stdvec.begin();
    ft::vector<int>::iterator ftfirst = ftvec.begin();

    std::vector<int>::iterator stdret = stdvec.erase(stdfirst, stdfirst + 1);
    ft::vector<int>::iterator ftret = ftvec.erase(ftfirst, ftfirst + 1);

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(*stdret, *ftret);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;

    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdfirst = stdvec.begin();
    ft::vector<int>::iterator ftfirst = ftvec.begin();

    std::vector<int>::iterator stdret = stdvec.erase(++stdfirst, stdvec.end());
    ft::vector<int>::iterator ftret = ftvec.erase(++ftfirst, ftvec.end());

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(stdret, stdvec.end());
    ASSERT_EQ(ftret, ftvec.end());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;

    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::iterator stdfirst = stdvec.begin();
    ft::vector<int>::iterator ftfirst = ftvec.begin();

    std::vector<int>::iterator stdret = stdvec.erase(stdfirst, stdvec.begin());
    ft::vector<int>::iterator ftret = ftvec.erase(ftfirst, ftvec.begin());

    ASSERT_EQ(stdvec.size(), ftvec.size());
    ASSERT_EQ(*stdret, *ftret);

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;

    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  /*
  * push_back
  */
  {
    std::vector<int> stdvec;
    stdvec.push_back(1);
    stdvec.push_back(2);
    stdvec.push_back(3);
    ft::vector<int> ftvec;
    ftvec.push_back(1);
    ftvec.push_back(2);
    ftvec.push_back(3);

    ASSERT_EQ(stdvec.size(), ftvec.size());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  /*
  * pop_back
  */
  {
    std::vector<int> stdvec(3, 42);
    stdvec.pop_back();
    ft::vector<int> ftvec(3, 42);
    ftvec.pop_back();

    ASSERT_EQ(stdvec.size(), ftvec.size());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  /*
  * resize
  */
  {
    std::vector<int> stdvec(3, 42);
    stdvec.resize(5);
    ft::vector<int> ftvec(3, 42);
    ftvec.resize(5);

    ASSERT_EQ(stdvec.size(), ftvec.size());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stdvec(3, 42);
    stdvec.resize(2);
    ft::vector<int> ftvec(3, 42);
    ftvec.resize(2);

    ASSERT_EQ(stdvec.size(), ftvec.size());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stdvec(3, 42);
    stdvec.resize(5, 4242);
    ft::vector<int> ftvec(3, 42);
    ftvec.resize(5, 4242);

    ASSERT_EQ(stdvec.size(), ftvec.size());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

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
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  {
    std::vector<int> stdvec(3, 42);
    stdvec.resize(2, 4242);
    ft::vector<int> ftvec(3, 42);
    ftvec.resize(2, 4242);

    ASSERT_EQ(stdvec.size(), ftvec.size());

    std::vector<int>::iterator stditr = stdvec.begin();
    ft::vector<int>::iterator ftitr = ftvec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }

  /*
  * swap
  */
  {
    std::vector<int> stdvec1(3, 42);
    std::vector<int> stdvec2(10, 4242);
    ft::vector<int> ftvec1(3, 42);
    ft::vector<int> ftvec2(10, 4242);

    stdvec1.swap(stdvec2);
    ftvec1.swap(ftvec2);

    ASSERT_EQ(stdvec1.size(), ftvec1.size());
    ASSERT_EQ(stdvec2.size(), ftvec2.size());

    std::vector<int>::iterator stditr1 = stdvec1.begin();
    ft::vector<int>::iterator ftitr1 = ftvec1.begin();
    for (; stditr1 != stdvec1.end(); ++stditr1, ++ftitr1) {
      ASSERT_EQ(*stditr1, *ftitr1);
    }
    ASSERT_EQ(stditr1, stdvec1.end());
    ASSERT_EQ(ftitr1, ftvec1.end());

    std::vector<int>::iterator stditr2 = stdvec2.begin();
    ft::vector<int>::iterator ftitr2 = ftvec2.begin();
    for (; stditr2 != stdvec2.end(); ++stditr2, ++ftitr2) {
      ASSERT_EQ(*stditr2, *ftitr2);
    }
    ASSERT_EQ(stditr2, stdvec2.end());
    ASSERT_EQ(ftitr2, ftvec2.end());
  }

  /*
  * operator
  */
  {
    std::vector<int> stdvec1;
    stdvec1.push_back(1);
    stdvec1.push_back(2);
    stdvec1.push_back(3);
    std::vector<int> stdvec2;
    stdvec2.push_back(1);
    stdvec2.push_back(2);
    stdvec2.push_back(3);
    ft::vector<int> ftvec1;
    ftvec1.push_back(1);
    ftvec1.push_back(2);
    ftvec1.push_back(3);
    ft::vector<int> ftvec2;
    ftvec2.push_back(1);
    ftvec2.push_back(2);
    ftvec2.push_back(3);

    ASSERT_EQ(stdvec1 == stdvec2, ftvec1 == ftvec2);
    ASSERT_EQ(stdvec1 != stdvec2, ftvec1 != ftvec2);
    ASSERT_EQ(stdvec1 < stdvec2, ftvec1 < ftvec2);
    ASSERT_EQ(stdvec1 <= stdvec2, ftvec1 <= ftvec2);
    ASSERT_EQ(stdvec1 > stdvec2, ftvec1 > ftvec2);
    ASSERT_EQ(stdvec1 >= stdvec2, ftvec1 >= ftvec2);
  }

  {
    std::vector<int> stdvec1;
    stdvec1.push_back(1);
    std::vector<int> stdvec2;
    stdvec2.push_back(1);
    stdvec2.push_back(2);
    stdvec2.push_back(3);
    ft::vector<int> ftvec1;
    ftvec1.push_back(1);
    ft::vector<int> ftvec2;
    ftvec2.push_back(1);
    ftvec2.push_back(2);
    ftvec2.push_back(3);

    ASSERT_EQ(stdvec1 == stdvec2, ftvec1 == ftvec2);
    ASSERT_EQ(stdvec1 != stdvec2, ftvec1 != ftvec2);
    ASSERT_EQ(stdvec1 < stdvec2, ftvec1 < ftvec2);
    ASSERT_EQ(stdvec1 <= stdvec2, ftvec1 <= ftvec2);
    ASSERT_EQ(stdvec1 > stdvec2, ftvec1 > ftvec2);
    ASSERT_EQ(stdvec1 >= stdvec2, ftvec1 >= ftvec2);
  }

  {
    std::vector<int> stdvec1;
    stdvec1.push_back(1);
    stdvec1.push_back(2);
    stdvec1.push_back(3);
    std::vector<int> stdvec2;
    stdvec2.push_back(1);
    ft::vector<int> ftvec1;
    ftvec1.push_back(1);
    ftvec1.push_back(2);
    ftvec1.push_back(3);
    ft::vector<int> ftvec2;
    ftvec2.push_back(1);

    ASSERT_EQ(stdvec1 == stdvec2, ftvec1 == ftvec2);
    ASSERT_EQ(stdvec1 != stdvec2, ftvec1 != ftvec2);
    ASSERT_EQ(stdvec1 < stdvec2, ftvec1 < ftvec2);
    ASSERT_EQ(stdvec1 <= stdvec2, ftvec1 <= ftvec2);
    ASSERT_EQ(stdvec1 > stdvec2, ftvec1 > ftvec2);
    ASSERT_EQ(stdvec1 >= stdvec2, ftvec1 >= ftvec2);
  }

  /*
  * non member swap
  */
  {
    std::vector<int> stdvec1(3, 42);
    std::vector<int> stdvec2(10, 4242);
    ft::vector<int> ftvec1(3, 42);
    ft::vector<int> ftvec2(10, 4242);

    std::swap(stdvec1, stdvec2);
    ft::swap(ftvec1, ftvec2);

    ASSERT_EQ(stdvec1.size(), ftvec1.size());
    ASSERT_EQ(stdvec2.size(), ftvec2.size());

    std::vector<int>::iterator stditr1 = stdvec1.begin();
    ft::vector<int>::iterator ftitr1 = ftvec1.begin();
    for (; stditr1 != stdvec1.end(); ++stditr1, ++ftitr1) {
      ASSERT_EQ(*stditr1, *ftitr1);
    }
    ASSERT_EQ(stditr1, stdvec1.end());
    ASSERT_EQ(ftitr1, ftvec1.end());

    std::vector<int>::iterator stditr2 = stdvec2.begin();
    ft::vector<int>::iterator ftitr2 = ftvec2.begin();
    for (; stditr2 != stdvec2.end(); ++stditr2, ++ftitr2) {
      ASSERT_EQ(*stditr2, *ftitr2);
    }
    ASSERT_EQ(stditr2, stdvec2.end());
    ASSERT_EQ(ftitr2, ftvec2.end());
  }

  /*
  * iterator
  */
  {
    std::vector<int> stdvec(3, 42);
    ft::vector<int> ftvec(3, 42);

    std::vector<int>::const_iterator stditr = stdvec.begin();
    ft::vector<int>::const_iterator ftitr = ftvec.begin();

    for (; stditr != stdvec.end(); ++stditr, ++ftitr) {
      ASSERT_EQ(*stditr, *ftitr);
    }
    ASSERT_EQ(stditr, stdvec.end());
    ASSERT_EQ(ftitr, ftvec.end());
  }
}

void test_deque() {
  // iterator
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(2);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(2);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();

    ++stditr2;
    ++ftitr2;
    ASSERT_EQ(stditr2 - stditr1, ftitr2 - ftitr1);
    ASSERT_EQ(stditr1 - stditr2, ftitr1 - ftitr2);
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(2);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(2);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();

    ++stditr2;
    ++ftitr2;
    ASSERT_EQ(stditr2 - stditr1, ftitr2 - ftitr1);
    ASSERT_EQ(stditr1 - stditr2, ftitr1 - ftitr2);
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(2);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(2);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();

    ++stditr2;
    ++ftitr2;
    ASSERT_EQ(stditr2 - stditr1, ftitr2 - ftitr1);
    ASSERT_EQ(stditr1 - stditr2, ftitr1 - ftitr2);
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(2);
    stddec.push_front(3);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(2);
    ftdec.push_front(3);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();

    ++stditr2;
    ++ftitr2;
    ASSERT_EQ(stditr2 - stditr1, ftitr2 - ftitr1);
    ASSERT_EQ(stditr1 - stditr2, ftitr1 - ftitr2);
    ++stditr2;
    ++ftitr2;
    ASSERT_EQ(stditr2 - stditr1, ftitr2 - ftitr1);
    ASSERT_EQ(stditr1 - stditr2, ftitr1 - ftitr2);
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(2);
    stddec.push_front(3);
    stddec.push_back(4);
    stddec.push_front(5);
    stddec.push_back(6);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(2);
    ftdec.push_front(3);
    ftdec.push_back(4);
    ftdec.push_front(5);
    ftdec.push_back(6);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();

    ++stditr2;
    ++ftitr2;
    ASSERT_EQ(stditr2 - stditr1, ftitr2 - ftitr1);
    ASSERT_EQ(stditr1 - stditr2, ftitr1 - ftitr2);
    ++stditr2;
    ++ftitr2;
    ASSERT_EQ(stditr2 - stditr1, ftitr2 - ftitr1);
    ASSERT_EQ(stditr1 - stditr2, ftitr1 - ftitr2);
    ++stditr2;
    ++ftitr2;
    ASSERT_EQ(stditr2 - stditr1, ftitr2 - ftitr1);
    ASSERT_EQ(stditr1 - stditr2, ftitr1 - ftitr2);
    ++stditr2;
    ++ftitr2;
    ASSERT_EQ(stditr2 - stditr1, ftitr2 - ftitr1);
    ASSERT_EQ(stditr1 - stditr2, ftitr1 - ftitr2);
    ++stditr2;
    ++ftitr2;
    ASSERT_EQ(stditr2 - stditr1, ftitr2 - ftitr1);
    ASSERT_EQ(stditr1 - stditr2, ftitr1 - ftitr2);
  }

  {
    std::deque<int> stddec;
    for (int i = 0; i < 10240; ++i) {
      stddec.push_back(i);
    }
    ft::deque<int> ftdec;
    for (int i = 0; i < 10240; ++i) {
      ftdec.push_back(i);
    }
    ASSERT_EQ(stddec.size(), ftdec.size());
    for (int i = 0; i < 10240; ++i) {
      ASSERT_EQ(stddec[i], ftdec[i]);
    }
  }

  /*
  * constructor 1
  */
  { ft::deque<int> mydec; }

  /*
  * constructor 2
  */
  {
    std::allocator<int> alloc;
    ft::deque<int> mydec(alloc);
    std::deque<int> libdec(alloc);
    ASSERT_EQ(libdec.size(), mydec.size());
  }

  /*
  * constructor 3
  */
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

  /*
  * constructor 5
  */
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

  /*
  * constructor 6
  */
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

  /*
  * operator=
  */
  {
    ft::deque<int> mydec2;
    mydec2.push_back(1);
    mydec2.push_back(42);
    mydec2.push_back(5);
    std::deque<int> libdec2;
    libdec2.push_back(1);
    libdec2.push_back(42);
    libdec2.push_back(5);

    ft::deque<int> mydec;
    mydec = mydec2;
    std::deque<int> libdec;
    libdec = libdec2;

    ASSERT_EQ(libdec.size(), mydec.size());
    ASSERT_EQ(libdec.at(0), mydec.at(0));
    ASSERT_EQ(libdec.at(1), mydec.at(1));
    ASSERT_EQ(libdec.at(2), mydec.at(2));
  }

  /*
  * assign
  */
  {
    std::deque<int> stddec;
    stddec.assign(5, 42);
    ft::deque<int> ftdec;
    ftdec.assign(5, 42);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddata;
    stddata.assign(5, 42);
    ft::deque<int> ftdata;
    ftdata.assign(5, 42);

    std::deque<int> stddec;
    stddec.assign(stddata.begin(), stddata.end());
    ft::deque<int> ftdec;
    ftdec.assign(ftdata.begin(), ftdata.end());

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  /*
  * get_allocator
  */
  {
    std::allocator<int> alloc;
    std::deque<int> stddec(alloc);
    ft::deque<int> ftdec(alloc);

    ASSERT_EQ(stddec.get_allocator(), ftdec.get_allocator());
  }

  {
    std::allocator<int> alloc;
    const std::deque<int> stddec(alloc);
    const ft::deque<int> ftdec(alloc);

    ASSERT_EQ(stddec.get_allocator(), ftdec.get_allocator());
  }

  /*
  * at
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));

    stddec.at(0) = 100;
    ftdec.at(0) = 100;
    stddec.at(1) = 100;
    ftdec.at(1) = 100;
    stddec.at(2) = 100;
    ftdec.at(2) = 100;

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
  }

  {
    std::deque<int> stddata;
    stddata.assign(5, 42);
    ft::deque<int> ftdata;
    ftdata.assign(5, 42);

    const std::deque<int> stddec(stddata.begin(), stddata.end());
    const ft::deque<int> ftdec(ftdata.begin(), ftdata.end());

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  /*
  * operator[]
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec[0], ftdec[0]);
    ASSERT_EQ(stddec[1], ftdec[1]);
    ASSERT_EQ(stddec[2], ftdec[2]);

    stddec[0] = 100;
    ftdec[0] = 100;
    stddec[1] = 100;
    ftdec[1] = 100;
    stddec[2] = 100;
    ftdec[2] = 100;

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec[0], ftdec[0]);
    ASSERT_EQ(stddec[1], ftdec[1]);
    ASSERT_EQ(stddec[2], ftdec[2]);
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec[0], ftdec[0]);
    ASSERT_EQ(stddec[1], ftdec[1]);
    ASSERT_EQ(stddec[2], ftdec[2]);

    stddec[0] = 100;
    ftdec[0] = 100;
    stddec[1] = 100;
    ftdec[1] = 100;
    stddec[2] = 100;
    ftdec[2] = 100;

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec[0], ftdec[0]);
    ASSERT_EQ(stddec[1], ftdec[1]);
    ASSERT_EQ(stddec[2], ftdec[2]);
  }

  {
    std::deque<int> stddata;
    stddata.assign(5, 42);
    ft::deque<int> ftdata;
    ftdata.assign(5, 42);

    const std::deque<int> stddec(stddata.begin(), stddata.end());
    const ft::deque<int> ftdec(ftdata.begin(), ftdata.end());

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec[0], ftdec[0]);
    ASSERT_EQ(stddec[1], ftdec[1]);
    ASSERT_EQ(stddec[2], ftdec[2]);
    ASSERT_EQ(stddec[3], ftdec[3]);
    ASSERT_EQ(stddec[4], ftdec[4]);
  }

  /*
  * front
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    ASSERT_EQ(stddec.front(), ftdec.front());

    stddec.front() = 100;
    ftdec.front() = 100;

    ASSERT_EQ(stddec.front(), ftdec.front());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    ASSERT_EQ(stddec.front(), ftdec.front());

    stddec.front() = 100;
    ftdec.front() = 100;

    ASSERT_EQ(stddec.front(), ftdec.front());
  }

  {
    std::deque<int> stddata;
    stddata.assign(5, 42);
    ft::deque<int> ftdata;
    ftdata.assign(5, 42);

    const std::deque<int> stddec(stddata.begin(), stddata.end());
    const ft::deque<int> ftdec(ftdata.begin(), ftdata.end());

    ASSERT_EQ(stddec.front(), ftdec.front());
  }

  /*
  * back
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    ASSERT_EQ(stddec.back(), ftdec.back());

    stddec.back() = 100;
    ftdec.back() = 100;

    ASSERT_EQ(stddec.back(), ftdec.back());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    ASSERT_EQ(stddec.back(), ftdec.back());

    stddec.back() = 100;
    ftdec.back() = 100;

    ASSERT_EQ(stddec.back(), ftdec.back());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    ASSERT_EQ(stddec.back(), ftdec.back());

    stddec.back() = 100;
    ftdec.back() = 100;

    ASSERT_EQ(stddec.back(), ftdec.back());
  }

  {
    std::deque<int> stddata;
    stddata.assign(5, 42);
    ft::deque<int> ftdata;
    ftdata.assign(5, 42);

    const std::deque<int> stddec(stddata.begin(), stddata.end());
    const ft::deque<int> ftdec(ftdata.begin(), ftdata.end());

    ASSERT_EQ(stddec.back(), ftdec.back());
  }

  /*
  * begin
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(stditr, stddec.end());
    ASSERT_EQ(ftitr, ftdec.end());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(stditr, stddec.end());
    ASSERT_EQ(ftitr, ftdec.end());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(stditr, stddec.end());
    ASSERT_EQ(ftitr, ftdec.end());
  }

  /*
  * begin const
  */
  {
    std::deque<int> stddata;
    stddata.assign(5, 42);
    ft::deque<int> ftdata;
    ftdata.assign(5, 42);

    const std::deque<int> stddec(stddata.begin(), stddata.end());
    const ft::deque<int> ftdec(ftdata.begin(), ftdata.end());

    std::deque<int>::const_iterator stditr = stddec.begin();
    ft::deque<int>::const_iterator ftitr = ftdec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(stditr, stddec.end());
    ASSERT_EQ(ftitr, ftdec.end());
  }

  /*
  * end
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.end();
    ft::deque<int>::iterator ftitr = ftdec.end();

    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stddec.begin());
    ASSERT_EQ(ftitr, ftdec.begin());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.end();
    ft::deque<int>::iterator ftitr = ftdec.end();

    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stddec.begin());
    ASSERT_EQ(ftitr, ftdec.begin());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::iterator stditr = stddec.end();
    ft::deque<int>::iterator ftitr = ftdec.end();

    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stddec.begin());
    ASSERT_EQ(ftitr, ftdec.begin());
  }

  /*
  * end const
  */
  {
    std::deque<int> stddata;
    stddata.assign(5, 42);
    ft::deque<int> ftdata;
    ftdata.assign(5, 42);

    const std::deque<int> stddec(stddata.begin(), stddata.end());
    const ft::deque<int> ftdec(ftdata.begin(), ftdata.end());

    std::deque<int>::const_iterator stditr = stddec.end();
    ft::deque<int>::const_iterator ftitr = ftdec.end();

    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stddec.begin());
    ASSERT_EQ(ftitr, ftdec.begin());
  }

  /*
  * rbegin
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::reverse_iterator stditr = stddec.rbegin();
    ft::deque<int>::reverse_iterator ftitr = ftdec.rbegin();

    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;

    ASSERT_EQ(stditr, stddec.rend());
    ASSERT_EQ(ftitr, ftdec.rend());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::reverse_iterator stditr = stddec.rbegin();
    ft::deque<int>::reverse_iterator ftitr = ftdec.rbegin();

    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;

    ASSERT_EQ(stditr, stddec.rend());
    ASSERT_EQ(ftitr, ftdec.rend());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::reverse_iterator stditr = stddec.rbegin();
    ft::deque<int>::reverse_iterator ftitr = ftdec.rbegin();

    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;

    ASSERT_EQ(stditr, stddec.rend());
    ASSERT_EQ(ftitr, ftdec.rend());
  }

  /*
  * rbegin const
  */
  {
    std::deque<int> stddata;
    stddata.assign(5, 42);
    ft::deque<int> ftdata;
    ftdata.assign(5, 42);

    const std::deque<int> stddec(stddata.begin(), stddata.end());
    const ft::deque<int> ftdec(ftdata.begin(), ftdata.end());

    std::deque<int>::const_reverse_iterator stditr = stddec.rbegin();
    ft::deque<int>::const_reverse_iterator ftitr = ftdec.rbegin();

    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;
    ASSERT_EQ(*stditr, *ftitr);
    stditr++;
    ftitr++;

    ASSERT_EQ(stditr, stddec.rend());
    ASSERT_EQ(ftitr, ftdec.rend());
  }

  /*
  * rend
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::reverse_iterator stditr = stddec.rend();
    ft::deque<int>::reverse_iterator ftitr = ftdec.rend();

    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stddec.rbegin());
    ASSERT_EQ(ftitr, ftdec.rbegin());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::reverse_iterator stditr = stddec.rend();
    ft::deque<int>::reverse_iterator ftitr = ftdec.rend();

    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stddec.rbegin());
    ASSERT_EQ(ftitr, ftdec.rbegin());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::reverse_iterator stditr = stddec.rend();
    ft::deque<int>::reverse_iterator ftitr = ftdec.rend();

    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stddec.rbegin());
    ASSERT_EQ(ftitr, ftdec.rbegin());
  }

  /*
  * rend const
  */
  {
    std::deque<int> stddata;
    stddata.assign(5, 42);
    ft::deque<int> ftdata;
    ftdata.assign(5, 42);

    const std::deque<int> stddec(stddata.begin(), stddata.end());
    const ft::deque<int> ftdec(ftdata.begin(), ftdata.end());

    std::deque<int>::const_reverse_iterator stditr = stddec.rend();
    ft::deque<int>::const_reverse_iterator ftitr = ftdec.rend();

    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);
    stditr--;
    ftitr--;
    ASSERT_EQ(*stditr, *ftitr);

    ASSERT_EQ(stditr, stddec.rbegin());
    ASSERT_EQ(ftitr, ftdec.rbegin());
  }

  /*
  * empty
  */
  {
    std::deque<int> stddec;
    ft::deque<int> ftdec;

    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    const std::deque<int> stddec;
    const ft::deque<int> ftdec;

    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  /*
  * size
  */
  {
    std::deque<int> stddec;
    ft::deque<int> ftdec;

    ASSERT_EQ(stddec.size(), ftdec.size());
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    ASSERT_EQ(stddec.size(), ftdec.size());
  }

  {
    const std::deque<int> stddec;
    const ft::deque<int> ftdec;

    ASSERT_EQ(stddec.size(), ftdec.size());
  }

  /*
  * max_size
  */
  {
    std::deque<int> stddec;
    ft::deque<int> ftdec;

    ASSERT_EQ(stddec.max_size(), ftdec.max_size());
  }

  {
    const std::deque<int> stddec;
    const ft::deque<int> ftdec;

    ASSERT_EQ(stddec.max_size(), ftdec.max_size());
  }

  /*
  * clear
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    stddec.clear();
    ftdec.clear();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  /*
  * insert 1
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret = stddec.insert(stditr, 4242);
    ft::deque<int>::iterator ftret = ftdec.insert(ftitr, 4242);

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret = stddec.insert(stditr, 4242);
    ft::deque<int>::iterator ftret = ftdec.insert(ftitr, 4242);

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret = stddec.insert(stditr, 4242);
    ft::deque<int>::iterator ftret = ftdec.insert(ftitr, 4242);

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
  }

  /*
  * insert 2
  */
  {
    std::deque<int> stddec;
    stddec.insert(stddec.begin(), 100, 1);
    ft::deque<int> ftdec;
    ftdec.insert(ftdec.begin(), 100, 1);

    ASSERT_EQ(stddec.size(), ftdec.size());
    for (std::size_t i = 0; i < stddec.size(); ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  {
    std::deque<int> stddec;
    stddec.insert(stddec.begin(), 10000, 42);
    ft::deque<int> ftdec;
    ftdec.insert(ftdec.begin(), 10000, 42);

    ASSERT_EQ(stddec.size(), ftdec.size());
    for (std::size_t i = 0; i < stddec.size(); ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret = stddec.insert(stditr, 2, 4242);
    ft::deque<int>::iterator ftret = ftdec.insert(ftitr, 2, 4242);

    ASSERT_EQ(*stdret, *ftret);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret = stddec.insert(stditr, 2, 4242);
    ft::deque<int>::iterator ftret = ftdec.insert(ftitr, 2, 4242);

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret = stddec.insert(stditr, 2, 4242);
    ft::deque<int>::iterator ftret = ftdec.insert(ftitr, 2, 4242);

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  /*
  * insert 3
  */
  {
    std::deque<int> stddata(2, 4242);
    ft::deque<int> ftdata(2, 4242);

    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret =
        stddec.insert(stditr, stddata.begin(), stddata.end());
    ft::deque<int>::iterator ftret =
        ftdec.insert(ftitr, ftdata.begin(), ftdata.end());

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddata(2, 4242);
    ft::deque<int> ftdata(2, 4242);

    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret =
        stddec.insert(stditr, stddata.begin(), stddata.end());
    ft::deque<int>::iterator ftret =
        ftdec.insert(ftitr, ftdata.begin(), ftdata.end());

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddata(2, 4242);
    ft::deque<int> ftdata(2, 4242);

    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret =
        stddec.insert(stditr, stddata.begin(), stddata.end());
    ft::deque<int>::iterator ftret =
        ftdec.insert(ftitr, ftdata.begin(), ftdata.end());

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::vector<int> stddata(2, 4242);
    ft::vector<int> ftdata(2, 4242);

    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret =
        stddec.insert(stditr, stddata.begin(), stddata.end());
    ft::deque<int>::iterator ftret =
        ftdec.insert(ftitr, ftdata.begin(), ftdata.end());

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  /*
  * erase 1
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret = stddec.erase(stditr);
    ft::deque<int>::iterator ftret = ftdec.erase(ftitr);

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret = stddec.erase(stditr);
    ft::deque<int>::iterator ftret = ftdec.erase(ftitr);

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret = stddec.erase(stditr);
    ft::deque<int>::iterator ftret = ftdec.erase(ftitr);

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::iterator stditr = stddec.begin();
    ft::deque<int>::iterator ftitr = ftdec.begin();

    std::deque<int>::iterator stdret = stddec.erase(stditr);
    ft::deque<int>::iterator ftret = ftdec.erase(ftitr);

    ASSERT_EQ(*stdret, *ftret);
    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  /*
  * erase 2
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    std::deque<int>::iterator stditr1 = stddec.begin();
    std::deque<int>::iterator stditr2 = stddec.begin();
    ft::deque<int>::iterator ftitr1 = ftdec.begin();
    ft::deque<int>::iterator ftitr2 = ftdec.begin();

    ++stditr1;
    ++ftitr1;
    ++stditr2;
    ++ftitr2;
    ++stditr2;
    ++ftitr2;

    stddec.erase(stditr1, stditr2);
    ftdec.erase(ftitr1, ftitr2);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  /*
  * push_back
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
  }

  {
    std::deque<int> stddec;
    for (std::size_t i = 0; i < 1024; ++i) {
      stddec.push_back(i);
    }
    ft::deque<int> ftdec;
    for (std::size_t i = 0; i < 1024; ++i) {
      ftdec.push_back(i);
    }

    ASSERT_EQ(stddec.size(), ftdec.size());

    for (std::size_t i = 0; i < 1024; ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  {
    std::deque<int> stddec;
    for (std::size_t i = 0; i < 5128; ++i) {
      stddec.push_back(i);
    }
    ft::deque<int> ftdec;
    for (std::size_t i = 0; i < 5128; ++i) {
      ftdec.push_back(i);
    }

    ASSERT_EQ(stddec.size(), ftdec.size());

    for (std::size_t i = 0; i < 5128; ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  {
    std::deque<int> stddec;
    for (std::size_t i = 0; i < 1000000; ++i) {
      stddec.push_back(i);
    }
    ft::deque<int> ftdec;
    for (std::size_t i = 0; i < 1000000; ++i) {
      ftdec.push_back(i);
    }

    ASSERT_EQ(stddec.size(), ftdec.size());

    for (std::size_t i = 0; i < 1000000; ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  /*
  * pop_back
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_back();
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_back();
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_back();
    stddec.pop_back();
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_back();
    ftdec.pop_back();
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_back();
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_back();
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_back();
    stddec.pop_back();
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_back();
    ftdec.pop_back();
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    stddec.pop_back();
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);
    ftdec.pop_back();
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    stddec.pop_back();
    stddec.pop_back();
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);
    ftdec.pop_back();
    ftdec.pop_back();
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    stddec.pop_back();
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);
    ftdec.pop_back();
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    stddec.pop_back();
    stddec.pop_back();
    stddec.pop_back();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);
    ftdec.pop_back();
    ftdec.pop_back();
    ftdec.pop_back();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  /*
  * push_front
  */
  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
  }

  {
    std::deque<int> stddec;
    for (std::size_t i = 0; i < 512; ++i) {
      stddec.push_front(i);
    }
    stddec.push_front(4242);

    ft::deque<int> ftdec;
    for (std::size_t i = 0; i < 512; ++i) {
      ftdec.push_front(i);
    }
    ftdec.push_front(4242);

    ASSERT_EQ(stddec.size(), ftdec.size());

    for (std::size_t i = 0; i < 512; ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  {
    std::deque<int> stddec;
    for (std::size_t i = 0; i < 1024; ++i) {
      stddec.push_front(i);
    }
    ft::deque<int> ftdec;
    for (std::size_t i = 0; i < 1024; ++i) {
      ftdec.push_front(i);
    }

    ASSERT_EQ(stddec.size(), ftdec.size());

    for (std::size_t i = 0; i < 1024; ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  {
    std::deque<int> stddec;
    for (std::size_t i = 0; i < 5128; ++i) {
      stddec.push_front(i);
    }
    ft::deque<int> ftdec;
    for (std::size_t i = 0; i < 5128; ++i) {
      ftdec.push_front(i);
    }

    ASSERT_EQ(stddec.size(), ftdec.size());

    for (std::size_t i = 0; i < 5128; ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  {
    std::deque<int> stddec;
    for (std::size_t i = 0; i < 1000000; ++i) {
      stddec.push_front(i);
    }
    ft::deque<int> ftdec;
    for (std::size_t i = 0; i < 1000000; ++i) {
      ftdec.push_front(i);
    }

    ASSERT_EQ(stddec.size(), ftdec.size());

    for (std::size_t i = 0; i < 1000000; ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  {
    std::deque<int> stddec;
    for (std::size_t i = 0; i < 1000000; ++i) {
      if (i % 2 == 0) {
        stddec.push_front(i);
      } else {
        stddec.push_back(i);
      }
    }
    ft::deque<int> ftdec;
    for (std::size_t i = 0; i < 1000000; ++i) {
      if (i % 2 == 0) {
        ftdec.push_front(i);
      } else {
        ftdec.push_back(i);
      }
    }

    ASSERT_EQ(stddec.size(), ftdec.size());

    for (std::size_t i = 0; i < 1000000; ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  /*
  * pop_front
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_front();
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_front();
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_front();
    stddec.pop_front();
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_front();
    ftdec.pop_front();
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_front();
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_front();
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    stddec.pop_front();
    stddec.pop_front();
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);
    ftdec.pop_front();
    ftdec.pop_front();
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    stddec.pop_front();
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);
    ftdec.pop_front();
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    stddec.pop_front();
    stddec.pop_front();
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);
    ftdec.pop_front();
    ftdec.pop_front();
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    stddec.pop_front();
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);
    ftdec.pop_front();
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    stddec.pop_front();
    stddec.pop_front();
    stddec.pop_front();
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);
    ftdec.pop_front();
    ftdec.pop_front();
    ftdec.pop_front();

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.empty(), ftdec.empty());
  }

  /*
  * resize
  */
  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    stddec.resize(5);
    ftdec.resize(5);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    stddec.resize(5);
    ftdec.resize(5);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);

    stddec.resize(5);
    ftdec.resize(5);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    stddec.resize(5);
    ftdec.resize(5);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddec;
    stddec.push_back(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_back(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    stddec.resize(5, 4242);
    ftdec.resize(5, 4242);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_back(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_back(42);
    ftdec.push_back(5);

    stddec.resize(5, 4242);
    ftdec.resize(5, 4242);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_back(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_back(5);

    stddec.resize(5, 4242);
    ftdec.resize(5, 4242);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddec;
    stddec.push_front(1);
    stddec.push_front(42);
    stddec.push_front(5);
    ft::deque<int> ftdec;
    ftdec.push_front(1);
    ftdec.push_front(42);
    ftdec.push_front(5);

    stddec.resize(5, 4242);
    ftdec.resize(5, 4242);

    ASSERT_EQ(stddec.size(), ftdec.size());
    ASSERT_EQ(stddec.at(0), ftdec.at(0));
    ASSERT_EQ(stddec.at(1), ftdec.at(1));
    ASSERT_EQ(stddec.at(2), ftdec.at(2));
    ASSERT_EQ(stddec.at(3), ftdec.at(3));
    ASSERT_EQ(stddec.at(4), ftdec.at(4));
  }

  {
    std::deque<int> stddec;
    ft::deque<int> ftdec;

    stddec.resize(1024, 4242);
    ftdec.resize(1024, 4242);

    ASSERT_EQ(stddec.size(), ftdec.size());
    for (std::size_t i = 0; i < 1024; ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  {
    std::deque<int> stddec(200, 42);
    ft::deque<int> ftdec(200, 42);

    stddec.resize(1024, 4242);
    ftdec.resize(1024, 4242);

    ASSERT_EQ(stddec.size(), ftdec.size());
    for (std::size_t i = 0; i < 1024; ++i) {
      ASSERT_EQ(stddec.at(i), ftdec.at(i));
    }
  }

  /*
  * swap
  */
  {
    std::deque<int> stddec1(3, 42);
    ft::deque<int> ftdec1(3, 42);
    std::deque<int> stddec2(5, 42);
    ft::deque<int> ftdec2(5, 42);

    stddec1.swap(stddec2);
    ftdec1.swap(ftdec2);

    ASSERT_EQ(stddec1.size(), ftdec1.size());
    ASSERT_EQ(stddec1.at(0), ftdec1.at(0));
    ASSERT_EQ(stddec1.at(1), ftdec1.at(1));
    ASSERT_EQ(stddec1.at(2), ftdec1.at(2));
    ASSERT_EQ(stddec1.at(3), ftdec1.at(3));
    ASSERT_EQ(stddec1.at(4), ftdec1.at(4));

    ASSERT_EQ(stddec2.size(), ftdec2.size());
    ASSERT_EQ(stddec2.at(0), ftdec2.at(0));
    ASSERT_EQ(stddec2.at(1), ftdec2.at(1));
    ASSERT_EQ(stddec2.at(2), ftdec2.at(2));
  }

  /*
  * comp
  */
  {
    std::deque<int> stddec1;
    stddec1.push_front(1);
    stddec1.push_front(42);
    stddec1.push_front(5);
    ft::deque<int> ftdec1;
    ftdec1.push_front(1);
    ftdec1.push_front(42);
    ftdec1.push_front(5);

    std::deque<int> stddec2;
    stddec2.push_front(1);
    stddec2.push_front(42);
    stddec2.push_front(5);
    ft::deque<int> ftdec2;
    ftdec2.push_front(1);
    ftdec2.push_front(42);
    ftdec2.push_front(5);

    ASSERT_EQ(stddec1 == stddec2, ftdec1 == ftdec2);
    ASSERT_EQ(stddec1 != stddec2, ftdec1 != ftdec2);
    ASSERT_EQ(stddec1 < stddec2, ftdec1 < ftdec2);
    ASSERT_EQ(stddec1 <= stddec2, ftdec1 <= ftdec2);
    ASSERT_EQ(stddec1 > stddec2, ftdec1 > ftdec2);
    ASSERT_EQ(stddec1 >= stddec2, ftdec1 >= ftdec2);
  }

  {
    std::deque<int> stddec1;
    stddec1.push_front(1);
    stddec1.push_front(42);
    stddec1.push_front(5);
    stddec1.push_front(5);
    ft::deque<int> ftdec1;
    ftdec1.push_front(1);
    ftdec1.push_front(42);
    ftdec1.push_front(5);

    std::deque<int> stddec2;
    stddec2.push_front(1);
    stddec2.push_front(42);
    stddec2.push_front(5);
    stddec2.push_front(5);
    ft::deque<int> ftdec2;
    ftdec2.push_front(1);
    ftdec2.push_front(42);
    ftdec2.push_front(5);

    ASSERT_EQ(stddec1 == stddec2, ftdec1 == ftdec2);
    ASSERT_EQ(stddec1 != stddec2, ftdec1 != ftdec2);
    ASSERT_EQ(stddec1 < stddec2, ftdec1 < ftdec2);
    ASSERT_EQ(stddec1 <= stddec2, ftdec1 <= ftdec2);
    ASSERT_EQ(stddec1 > stddec2, ftdec1 > ftdec2);
    ASSERT_EQ(stddec1 >= stddec2, ftdec1 >= ftdec2);
  }

  {
    std::deque<int> stddec1;
    stddec1.push_front(1);
    stddec1.push_front(42);
    stddec1.push_front(5);
    stddec1.push_front(5);
    ft::deque<int> ftdec1;
    ftdec1.push_front(1);
    ftdec1.push_front(42);
    ftdec1.push_front(5);
    ftdec1.push_front(5);
    ftdec1.push_front(5);

    std::deque<int> stddec2;
    stddec2.push_front(1);
    stddec2.push_front(42);
    stddec2.push_front(5);
    stddec2.push_front(5);
    ft::deque<int> ftdec2;
    ftdec2.push_front(1);
    ftdec2.push_front(42);
    ftdec2.push_front(5);
    ftdec2.push_front(5);
    ftdec2.push_front(5);

    ASSERT_EQ(stddec1 == stddec2, ftdec1 == ftdec2);
    ASSERT_EQ(stddec1 != stddec2, ftdec1 != ftdec2);
    ASSERT_EQ(stddec1 < stddec2, ftdec1 < ftdec2);
    ASSERT_EQ(stddec1 <= stddec2, ftdec1 <= ftdec2);
    ASSERT_EQ(stddec1 > stddec2, ftdec1 > ftdec2);
    ASSERT_EQ(stddec1 >= stddec2, ftdec1 >= ftdec2);
  }

  /*
  * non member swap
  */
  {
    std::deque<int> stddec1(3, 42);
    ft::deque<int> ftdec1(3, 42);
    std::deque<int> stddec2(5, 42);
    ft::deque<int> ftdec2(5, 42);

    std::swap(stddec1, stddec2);
    ft::swap(ftdec1, ftdec2);

    ASSERT_EQ(stddec1.size(), ftdec1.size());
    ASSERT_EQ(stddec1.at(0), ftdec1.at(0));
    ASSERT_EQ(stddec1.at(1), ftdec1.at(1));
    ASSERT_EQ(stddec1.at(2), ftdec1.at(2));
    ASSERT_EQ(stddec1.at(3), ftdec1.at(3));
    ASSERT_EQ(stddec1.at(4), ftdec1.at(4));

    ASSERT_EQ(stddec2.size(), ftdec2.size());
    ASSERT_EQ(stddec2.at(0), ftdec2.at(0));
    ASSERT_EQ(stddec2.at(1), ftdec2.at(1));
    ASSERT_EQ(stddec2.at(2), ftdec2.at(2));
  }

  /*
  * iterator
  */
  {
    std::deque<int> stddec(3, 42);
    ft::deque<int> ftdec(3, 42);

    std::deque<int>::const_iterator stditr = stddec.begin();
    ft::deque<int>::const_iterator ftitr = ftdec.begin();

    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(*stditr, *ftitr);
    ++stditr;
    ++ftitr;
    ASSERT_EQ(stditr, stddec.end());
    ASSERT_EQ(ftitr, ftdec.end());
  }
}

void test_stack() {
  /*
  * constructor 1
  */
  {
    std::stack<int> stdst;
    stdst.push(1);
    ft::stack<int> ftst;
    ftst.push(1);

    ASSERT_EQ(stdst.size(), ftst.size());
  }

  {
    std::deque<int> container;
    ft::stack<int, std::deque<int> > ftst(container);
    ftst.push(1);

    ASSERT_EQ(ftst.size(), 1UL);
  }

  /*
  * constructor 2
  */
  {
    std::stack<int> stddata;
    stddata.push(1);
    std::stack<int> stdst(stddata);
    ft::stack<int> ftdata;
    ftdata.push(1);
    ft::stack<int> ftst(ftdata);

    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(stdst.top(), ftst.top());
  }

  /*
  * operator=
  */
  {
    std::stack<int> stddata;
    stddata.push(1);
    std::stack<int> stdst;
    stdst = stddata;
    ft::stack<int> ftdata;
    ftdata.push(1);
    ft::stack<int> ftst;
    ftst = ftdata;

    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(stdst.top(), ftst.top());
  }

  /*
  * top
  */
  {
    std::stack<int> stdst;
    stdst.push(1);
    ft::stack<int> ftst;
    ftst.push(1);

    ASSERT_EQ(stdst.top(), ftst.top());
  }

  {
    std::stack<int> stdst;
    stdst.push(1);
    ft::stack<int> ftst;
    ftst.push(1);

    stdst.top() = 42;
    ftst.top() = 42;

    ASSERT_EQ(stdst.top(), ftst.top());
  }

  {
    std::stack<int> stddata;
    stddata.push(1);
    ft::stack<int> ftdata;
    ftdata.push(1);

    const std::stack<int> stdst(stddata);
    const ft::stack<int> ftst(ftdata);

    ASSERT_EQ(stdst.top(), ftst.top());
  }

  /*
  * empty
  */
  {
    std::stack<int> stdst;
    ft::stack<int> ftst;

    ASSERT_EQ(stdst.empty(), ftst.empty());
  }

  {
    std::stack<int> stdst;
    stdst.push(1);
    ft::stack<int> ftst;
    ftst.push(1);

    ASSERT_EQ(stdst.empty(), ftst.empty());
  }

  {
    const std::stack<int> stdst;
    const ft::stack<int> ftst;

    ASSERT_EQ(stdst.empty(), ftst.empty());
  }

  {
    std::stack<int> stddata;
    stddata.push(1);
    ft::stack<int> ftdata;
    ftdata.push(1);

    const std::stack<int> stdst(stddata);
    const ft::stack<int> ftst(ftdata);

    ASSERT_EQ(stdst.empty(), ftst.empty());
  }

  /*
  * size
  */
  {
    std::stack<int> stdst;
    ft::stack<int> ftst;

    ASSERT_EQ(stdst.size(), ftst.size());
  }

  {
    std::stack<int> stdst;
    stdst.push(1);
    ft::stack<int> ftst;
    ftst.push(1);

    ASSERT_EQ(stdst.size(), ftst.size());
  }

  {
    const std::stack<int> stdst;
    const ft::stack<int> ftst;

    ASSERT_EQ(stdst.size(), ftst.size());
  }

  {
    std::stack<int> stddata;
    stddata.push(1);
    ft::stack<int> ftdata;
    ftdata.push(1);

    const std::stack<int> stdst(stddata);
    const ft::stack<int> ftst(ftdata);

    ASSERT_EQ(stdst.size(), ftst.size());
  }

  /*
  * pop
  */
  {
    std::stack<int> stdst;
    stdst.push(1);
    stdst.pop();
    ft::stack<int> ftst;
    ftst.push(1);
    ftst.pop();

    ASSERT_EQ(stdst.size(), ftst.size());
    ASSERT_EQ(stdst.empty(), ftst.empty());
  }

  /*
  * compare
  */
  {
    std::stack<int> stdst1;
    stdst1.push(1);
    std::stack<int> stdst2;
    stdst2.push(1);
    ft::stack<int> ftst1;
    ftst1.push(1);
    ft::stack<int> ftst2;
    ftst2.push(1);

    ASSERT_EQ(stdst1 == stdst2, ftst1 == ftst2);
    ASSERT_EQ(stdst1 != stdst2, ftst1 != ftst2);
    ASSERT_EQ(stdst1 <= stdst2, ftst1 <= ftst2);
    ASSERT_EQ(stdst1 < stdst2, ftst1 < ftst2);
    ASSERT_EQ(stdst1 >= stdst2, ftst1 >= ftst2);
    ASSERT_EQ(stdst1 > stdst2, ftst1 > ftst2);
  }

  {
    std::stack<int> stdst1;
    stdst1.push(1);
    stdst1.push(2);
    stdst1.push(3);
    std::stack<int> stdst2;
    stdst2.push(1);
    ft::stack<int> ftst1;
    ftst1.push(1);
    ftst1.push(2);
    ftst1.push(3);
    ft::stack<int> ftst2;
    ftst2.push(1);

    ASSERT_EQ(stdst1 == stdst2, ftst1 == ftst2);
    ASSERT_EQ(stdst1 != stdst2, ftst1 != ftst2);
    ASSERT_EQ(stdst1 <= stdst2, ftst1 <= ftst2);
    ASSERT_EQ(stdst1 < stdst2, ftst1 < ftst2);
    ASSERT_EQ(stdst1 >= stdst2, ftst1 >= ftst2);
    ASSERT_EQ(stdst1 > stdst2, ftst1 > ftst2);
  }

  {
    std::stack<int> stdst1;
    stdst1.push(1);
    std::stack<int> stdst2;
    stdst2.push(1);
    stdst2.push(2);
    stdst2.push(3);
    ft::stack<int> ftst1;
    ftst1.push(1);
    ft::stack<int> ftst2;
    ftst2.push(1);
    ftst2.push(2);
    ftst2.push(3);

    ASSERT_EQ(stdst1 == stdst2, ftst1 == ftst2);
    ASSERT_EQ(stdst1 != stdst2, ftst1 != ftst2);
    ASSERT_EQ(stdst1 <= stdst2, ftst1 <= ftst2);
    ASSERT_EQ(stdst1 < stdst2, ftst1 < ftst2);
    ASSERT_EQ(stdst1 >= stdst2, ftst1 >= ftst2);
    ASSERT_EQ(stdst1 > stdst2, ftst1 > ftst2);
  }

  {
    std::stack<int> stdst;
    for (int i = 0; i < 1024; ++i) {
      stdst.push(i);
    }
    ft::stack<int> ftst;
    for (int i = 0; i < 1024; ++i) {
      ftst.push(i);
    }
    ASSERT_EQ(stdst.size(), ftst.size());
    for (int i = 0; i < 1024; ++i) {
      ASSERT_EQ(stdst.top(), ftst.top());
      stdst.pop();
      ftst.pop();
    }
  }

  {
    std::stack<int> stdst;
    for (int i = 0; i < 5128; ++i) {
      stdst.push(i);
    }
    ft::stack<int> ftst;
    for (int i = 0; i < 5128; ++i) {
      ftst.push(i);
    }
    ASSERT_EQ(stdst.size(), ftst.size());
    for (int i = 0; i < 5128; ++i) {
      ASSERT_EQ(stdst.top(), ftst.top());
      stdst.pop();
      ftst.pop();
    }
  }

  {
    std::stack<int> stdst;
    for (int i = 0; i < 10000000; ++i) {
      stdst.push(i);
    }
    ft::stack<int> ftst;
    for (int i = 0; i < 10000000; ++i) {
      ftst.push(i);
    }
    ASSERT_EQ(stdst.size(), ftst.size());
    for (int i = 0; i < 10000000; ++i) {
      ASSERT_EQ(stdst.top(), ftst.top());
      stdst.pop();
      ftst.pop();
    }
  }
}

void test_pair() {
  /*
  * constuctor
  */
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
    ft::pair<long, long> myp(std::numeric_limits<long>::max(),
                             std::numeric_limits<long>::min());
    std::pair<long, long> libp(std::numeric_limits<long>::max(),
                               std::numeric_limits<long>::min());
    ft::pair<int, int> myp2(myp);
    std::pair<int, int> libp2(libp);
    ASSERT_EQ(myp2.first, libp2.first);
    ASSERT_EQ(myp2.second, libp2.second);
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

void test_other() {
  /*
  * iterator_traits
  */
  {
    // int *
    if (std::is_same<ft::iterator_traits<int*>::difference_type,
                     std::iterator_traits<int*>::difference_type>::value ==
        false)
      assert(false);
    if (std::is_same<ft::iterator_traits<int*>::value_type,
                     std::iterator_traits<int*>::value_type>::value == false)
      assert(false);
    if (std::is_same<ft::iterator_traits<int*>::pointer,
                     std::iterator_traits<int*>::pointer>::value == false)
      assert(false);
    if (std::is_same<ft::iterator_traits<int*>::reference,
                     std::iterator_traits<int*>::reference>::value == false)
      assert(false);
    if (std::is_same<ft::iterator_traits<int*>::iterator_category,
                     std::iterator_traits<int*>::iterator_category>::value ==
        false)
      assert(false);

    // const int *
    if (std::is_same<
            ft::iterator_traits<const int*>::difference_type,
            std::iterator_traits<const int*>::difference_type>::value == false)
      assert(false);
    if (std::is_same<ft::iterator_traits<const int*>::value_type,
                     std::iterator_traits<const int*>::value_type>::value ==
        false)
      assert(false);
    if (std::is_same<ft::iterator_traits<const int*>::pointer,
                     std::iterator_traits<const int*>::pointer>::value == false)
      assert(false);
    if (std::is_same<ft::iterator_traits<const int*>::reference,
                     std::iterator_traits<const int*>::reference>::value ==
        false)
      assert(false);
    if (std::is_same<
            ft::iterator_traits<const int*>::iterator_category,
            std::iterator_traits<const int*>::iterator_category>::value ==
        false)
      assert(false);

    // vector iterator
    if (std::is_same<
            ft::iterator_traits<std::vector<int>::iterator>::difference_type,
            std::iterator_traits<std::vector<int>::iterator>::difference_type>::
            value == false)
      assert(false);
    if (std::is_same<
            ft::iterator_traits<std::vector<int>::iterator>::value_type,
            std::iterator_traits<std::vector<int>::iterator>::value_type>::
            value == false)
      assert(false);
    if (std::is_same<
            ft::iterator_traits<std::vector<int>::iterator>::pointer,
            std::iterator_traits<std::vector<int>::iterator>::pointer>::value ==
        false)
      assert(false);
    if (std::is_same<ft::iterator_traits<std::vector<int>::iterator>::reference,
                     std::iterator_traits<
                         std::vector<int>::iterator>::reference>::value ==
        false)
      assert(false);
    if (std::is_same<
            ft::iterator_traits<std::vector<int>::iterator>::iterator_category,
            std::iterator_traits<
                std::vector<int>::iterator>::iterator_category>::value == false)
      assert(false);

    // set iterator
    if (std::is_same<
            ft::iterator_traits<std::set<int>::iterator>::difference_type,
            std::iterator_traits<std::set<int>::iterator>::difference_type>::
            value == false)
      assert(false);
    if (std::is_same<
            ft::iterator_traits<std::set<int>::iterator>::value_type,
            std::iterator_traits<std::set<int>::iterator>::value_type>::value ==
        false)
      assert(false);
    if (std::is_same<
            ft::iterator_traits<std::set<int>::iterator>::pointer,
            std::iterator_traits<std::set<int>::iterator>::pointer>::value ==
        false)
      assert(false);
    if (std::is_same<
            ft::iterator_traits<std::set<int>::iterator>::reference,
            std::iterator_traits<std::set<int>::iterator>::reference>::value ==
        false)
      assert(false);
    if (std::is_same<
            ft::iterator_traits<std::set<int>::iterator>::iterator_category,
            std::iterator_traits<std::set<int>::iterator>::iterator_category>::
            value == false)
      assert(false);
  }

  /*
  * reverse_iterator
  */
  {
    std::vector<int> stdvec1;
    stdvec1.push_back(1);
    stdvec1.push_back(2);
    stdvec1.push_back(3);
    std::vector<int> stdvec2;
    stdvec2.push_back(1);
    stdvec2.push_back(2);
    stdvec2.push_back(3);

    std::reverse_iterator<std::vector<int>::iterator> stditr =
        std::reverse_iterator<std::vector<int>::iterator>(stdvec1.end());
    ft::reverse_iterator<std::vector<int>::iterator> ftitr =
        ft::reverse_iterator<std::vector<int>::iterator>(stdvec2.end());

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
    std::set<int> stdst1;
    stdst1.insert(1);
    stdst1.insert(2);
    stdst1.insert(3);
    std::set<int> stdst2;
    stdst2.insert(1);
    stdst2.insert(2);
    stdst2.insert(3);

    std::reverse_iterator<std::set<int>::iterator> stditr =
        std::reverse_iterator<std::set<int>::iterator>(stdst1.end());
    ft::reverse_iterator<std::set<int>::iterator> ftitr =
        ft::reverse_iterator<std::set<int>::iterator>(stdst2.end());

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

  /*
  * enable_if
  */
  {
    if (std::is_same<std::enable_if<true, int>::type,
                     ft::enable_if<true, int>::type>::value == false)
      assert(false);
    if (std::is_same<
            std::enable_if<true, std::vector<int>::iterator>::type,
            ft::enable_if<true, std::vector<int>::iterator>::type>::value ==
        false)
      assert(false);
  }

  /*
  * is_integral
  */
  {
    std::true_type stdtrue_type = std::is_integral<int>();
    ft::true_type fttrue_type = ft::is_integral<int>();
    ASSERT_EQ(stdtrue_type.value, fttrue_type.value);
  }

  {
    std::false_type stdtrue_type = std::is_integral<double>();
    ft::false_type fttrue_type = ft::is_integral<double>();
    ASSERT_EQ(stdtrue_type.value, fttrue_type.value);
  }

  /*
  * lexicographical_compare
  */
  {
    std::vector<int> vec1(10, 42);
    std::vector<int> vec2(10, 42);
    ASSERT_EQ(std::lexicographical_compare(vec1.begin(), vec1.end(),
                                           vec2.begin(), vec2.end()),
              ft::lexicographical_compare(vec1.begin(), vec1.end(),
                                          vec2.begin(), vec2.end()));
  }

  {
    std::vector<int> vec1(10, 42);
    std::vector<int> vec2(9, 42);
    ASSERT_EQ(std::lexicographical_compare(vec1.begin(), vec1.end(),
                                           vec2.begin(), vec2.end()),
              ft::lexicographical_compare(vec1.begin(), vec1.end(),
                                          vec2.begin(), vec2.end()));
  }

  {
    std::vector<int> vec1(9, 42);
    std::vector<int> vec2(10, 42);
    ASSERT_EQ(std::lexicographical_compare(vec1.begin(), vec1.end(),
                                           vec2.begin(), vec2.end()),
              ft::lexicographical_compare(vec1.begin(), vec1.end(),
                                          vec2.begin(), vec2.end()));
  }

  {
    std::set<int> vec1;
    vec1.insert(1);
    std::set<int> vec2;
    vec2.insert(1);
    ASSERT_EQ(std::lexicographical_compare(vec1.begin(), vec1.end(),
                                           vec2.begin(), vec2.end()),
              ft::lexicographical_compare(vec1.begin(), vec1.end(),
                                          vec2.begin(), vec2.end()));
  }

  {
    std::set<int> vec1;
    vec1.insert(1);
    std::set<int> vec2;
    ASSERT_EQ(std::lexicographical_compare(vec1.begin(), vec1.end(),
                                           vec2.begin(), vec2.end()),
              ft::lexicographical_compare(vec1.begin(), vec1.end(),
                                          vec2.begin(), vec2.end()));
  }

  {
    std::set<int> vec1;
    std::set<int> vec2;
    vec2.insert(1);
    ASSERT_EQ(std::lexicographical_compare(vec1.begin(), vec1.end(),
                                           vec2.begin(), vec2.end()),
              ft::lexicographical_compare(vec1.begin(), vec1.end(),
                                          vec2.begin(), vec2.end()));
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
  if (avs == "other" || avs == "all")
    test_other();

  std::cerr << "RESULT: \033[32mOK\033[0m" << std::endl;
}
