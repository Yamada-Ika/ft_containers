#include <gtest/gtest.h>
#include <glog/logging.h>

#include <memory>
#include <set>
#include "../set.hpp"

//  (constructor)
// 1
TEST(SetTest, int_basic_constructor_1) { ft::set<int> myst; }

// 1
TEST(SetTest, int_basic_constructor_2) {
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
TEST(SetTest, int_basic_constructor_3) {
  ft::greater<int> ftcomp;
  std::allocator<int> ftalloc;
  ft::set<int, ft::greater<int> > myorigin(ftcomp, ftalloc);
  myorigin.insert(1);
  myorigin.insert(2);
  myorigin.insert(3);

  ft::set<int, ft::greater<int> > myst(myorigin.begin(), myorigin.end(), ftcomp,
                                       ftalloc);

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

TEST(SetTest, int_basic_constructor_4) {
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

//  (destructor)
// destructor
TEST(SetTest, int_basic_destructor) {
  ft::set<int> myst;
  std::set<int> libst;
}

//  operator=

//  get_allocator
TEST(SetTest, int_basic_get_allocator) {
  ft::greater<int> mycomp;
  std::allocator<int> alloc;
  ft::set<int, ft::greater<int> > mymp(mycomp, alloc);

  std::greater<int> libcomp;
  std::set<int, std::greater<int> > libmp(libcomp, alloc);

  ASSERT_EQ(mymp.get_allocator(), libmp.get_allocator());
}

TEST(SetTest, int_basic_get_allocator2) {
  ft::greater<int> mycomp;
  std::allocator<int> alloc;
  const ft::set<int, ft::greater<int> > mymp(mycomp, alloc);

  std::greater<int> libcomp;
  const std::set<int, std::greater<int> > libmp(libcomp, alloc);

  ASSERT_EQ(mymp.get_allocator(), libmp.get_allocator());
}

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

TEST(SetTest, int_basic_begin_const_1) {
  std::set<int> libdata;
  libdata.insert(1);
  ft::set<int> mydata;
  mydata.insert(1);

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

TEST(SetTest, int_basic_begin_const_2) {
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

TEST(SetTest, int_basic_begin_const_3) {
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

TEST(SetTest, int_basic_end_const_1) {
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

TEST(SetTest, int_basic_end_const_2) {
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

TEST(SetTest, int_basic_end_const_3) {
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

TEST(SetTest, int_basic_rbegin_const_1) {
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

TEST(SetTest, int_basic_rbegin_const_2) {
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

TEST(SetTest, int_basic_rbegin_const_3) {
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

TEST(SetTest, int_basic_rend_const_1) {
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

TEST(SetTest, int_basic_rend_const_2) {
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

TEST(SetTest, int_basic_rend_const_3) {
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

TEST(SetTest, int_basic_empty_const_1) {
  const std::set<int> libst;
  const ft::set<int> myst;
  ASSERT_EQ(libst.empty(), myst.empty());
}

TEST(SetTest, int_basic_empty_const_2) {
  std::set<int> libdata;
  libdata.insert(1);
  ft::set<int> mydata;
  mydata.insert(1);

  const std::set<int> libst(libdata);
  const ft::set<int> myst(mydata);
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

TEST(SetTest, int_basic_size_const_1) {
  const std::set<int> libst;
  const ft::set<int> myst;
  ASSERT_EQ(libst.size(), myst.size());
}

TEST(SetTest, int_basic_size_const_2) {
  std::set<int> libdata;
  libdata.insert(1);
  ft::set<int> mydata;
  mydata.insert(1);

  const std::set<int> libst(libdata);
  const ft::set<int> myst(mydata);
  ASSERT_EQ(libst.size(), myst.size());
}

TEST(SetTest, int_basic_size_const_3) {
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

//  max_size
TEST(SetTest, int_basic_max_size) {
  std::set<int> libst;
  ft::set<int> myst;
  ASSERT_EQ(libst.max_size(), myst.max_size());
}

TEST(SetTest, int_basic_max_size_const) {
  const std::set<int> libst;
  const ft::set<int> myst;
  ASSERT_EQ(libst.max_size(), myst.max_size());
}

//  clear
TEST(SetTest, int_basic_clear) {
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

TEST(SetTest, int_basic_insert_1_1) {
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

// void insert(InputIt first, InputIt last)
// 3
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
// 1
TEST(SetTest, int_basic_erase_1_1_1) {
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

// 2
// gnuとclangで結果違う
// TEST(SetTest, int_basic_erase_1_2_2) {
//   std::set<int> libdata;
//   libdata.insert(1);
//   libdata.insert(2);
//   libdata.insert(3);
//   libdata.insert(4);

//   ft::set<int> mydata;
//   mydata.insert(1);
//   mydata.insert(2);
//   mydata.insert(3);
//   mydata.insert(4);

//   std::set<int>::iterator libitr = libdata.begin();
//   ft::set<int>::iterator myitr = mydata.begin();

//   std::set<int>::iterator libitr2 = libdata.erase(libitr, ++libitr);
//   ft::set<int>::iterator myitr2 = mydata.erase(myitr, ++myitr);

//   ASSERT_EQ(libdata.size(), mydata.size());

//   ASSERT_EQ(*libitr2, *myitr2);
//   while (libitr2 != libdata.end() && myitr2 != mydata.end()) {
//     ASSERT_EQ(*libitr2, *myitr2);
//     libitr2++;
//     myitr2++;
//   }
//   ASSERT_EQ(libitr2, libdata.end());
//   ASSERT_EQ(myitr2, mydata.end());

//   libitr = libdata.begin();
//   myitr = mydata.begin();

//   ASSERT_EQ(*libitr, *myitr);
//   libitr++;
//   myitr++;
//   ASSERT_EQ(*libitr, *myitr);
//   libitr++;
//   myitr++;
//   ASSERT_EQ(*libitr, *myitr);
//   libitr++;
//   myitr++;
//   ASSERT_EQ(libitr, libdata.end());
//   ASSERT_EQ(myitr, mydata.end());
// }

TEST(SetTest, int_basic_erase_1_2_2) {
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

// 3
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
TEST(SetTest, int_basic_swap) {
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

TEST(SetTest, int_basic_swap_2) {
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

TEST(SetTest, int_basic_swap_3) {
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

TEST(SetTest, int_basic_swap_4) {
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

// non member swap
TEST(SetTest, int_basic_nm_swap) {
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

TEST(SetTest, int_basic_nm_swap_2) {
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

TEST(SetTest, int_basic_nm_swap_3) {
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

// TEST(SetTest, int_basic_nm_swap_4) {
//   std::set<int> libdata1;
//   libdata1.insert(1);
//   libdata1.insert(2);
//   libdata1.insert(3);
//   libdata1.insert(-110);
//   libdata1.insert(-11);
//   libdata1.insert(-1);
//   libdata1.insert(-203);
//   libdata1.insert(102);
//   libdata1.insert(10);
//   std::set<int> libdata2;
//   libdata2.insert(2);
//   libdata2.insert(-1);
//   libdata2.insert(-2);
//   libdata2.insert(-3);
//   libdata2.insert(-4);
//   libdata2.insert(10000);
//   libdata2.insert(10);
//   libdata2.insert(122323);

//   ft::set<int> mydata1;
//   mydata1.insert(1);
//   mydata1.insert(2);
//   mydata1.insert(3);
//   mydata1.insert(-110);
//   mydata1.insert(-11);
//   mydata1.insert(-1);
//   mydata1.insert(-203);
//   mydata1.insert(102);
//   mydata1.insert(10);
//   ft::set<int> mydata2;
//   mydata2.insert(2);
//   mydata2.insert(-1);
//   mydata2.insert(-2);
//   mydata2.insert(-3);
//   mydata2.insert(-4);
//   mydata2.insert(10000);
//   mydata2.insert(10);
//   mydata2.insert(122323);

//   std::swap(libdata1, libdata2);
//   ft::swap(mydata1, mydata2);

//   ASSERT_EQ(libdata1.size(), mydata1.size());
//   ASSERT_EQ(libdata2.size(), mydata2.size());

//   std::set<int>::iterator libitr1 = libdata1.begin();
//   std::set<int>::iterator libitr2 = libdata2.begin();
//   ft::set<int>::iterator myitr1 = mydata1.begin();
//   ft::set<int>::iterator myitr2 = mydata2.begin();

//   for (; libitr1 != libdata1.end(); ++libitr1, ++myitr1) {
//     ASSERT_EQ(*libitr1, *myitr1);
//   }
//   for (; libitr2 != libdata2.end(); ++libitr2, ++myitr2) {
//     ASSERT_EQ(*libitr2, *myitr2);
//   }
// }

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

TEST(SetTest, int_basic_count_const_1) {
  std::set<int> libdata;
  libdata.insert(1);
  ft::set<int> mydata;
  mydata.insert(1);

  const std::set<int> libst(libdata);
  const ft::set<int> myst(mydata);

  ASSERT_EQ(libst.count(1), myst.count(1));
}

TEST(SetTest, int_basic_count_const_2) {
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

TEST(SetTest, int_basic_count_const_3) {
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

TEST(SetTest, int_basic_find_const) {
  std::set<int> libdata;
  libdata.insert(1);
  ft::set<int> mydata;
  mydata.insert(1);

  const std::set<int> libst(libdata);
  const ft::set<int> myst(mydata);

  ASSERT_EQ(*(libst.find(1)), *(myst.find(1)));
}

TEST(SetTest, int_basic_find_const_2) {
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

TEST(SetTest, int_basic_equal_range_const) {
  std::set<int> libdata;
  libdata.insert(1);
  ft::set<int> mydata;
  mydata.insert(1);

  const std::set<int> libst(libdata);
  const ft::set<int> myst(mydata);

  std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> libp =
      libst.equal_range(1);
  ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> myp =
      myst.equal_range(1);

  ASSERT_EQ(*(libp.first), *(myp.first));
  ASSERT_EQ(libp.second == libst.end(), myp.second == myst.end());
}

TEST(SetTest, int_basic_equal_range_const_2) {
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

  std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> libp =
      libst.equal_range(1);
  ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> myp =
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

TEST(SetTest, int_basic_lower_bound_const) {
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

TEST(SetTest, int_basic_lower_bound_const_2) {
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

TEST(SetTest, int_basic_lower_bound_const_3) {
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

TEST(SetTest, int_basic_upper_bound_const_1) {
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

TEST(SetTest, int_basic_upper_bound_const_2) {
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

TEST(SetTest, int_basic_upper_bound_const_3) {
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

struct ModCmp {
  bool operator()(const int lhs, const int rhs) const {
    return (lhs % 97) < (rhs % 97);
  }
};

//  key_comp
TEST(SetTest, int_basic_key_comp_1) {
  std::set<int, ModCmp> libst;
  ft::set<int, ModCmp> myst;

  std::set<int, ModCmp>::key_compare libcomp = libst.key_comp();
  ft::set<int, ModCmp>::key_compare mycomp = myst.key_comp();

  ASSERT_EQ(libcomp(1, 2), mycomp(1, 2));
  ASSERT_EQ(libcomp(100, 2), mycomp(100, 2));
  ASSERT_EQ(libcomp(100, 200), mycomp(100, 200));
  ASSERT_EQ(libcomp(97, 98), mycomp(97, 98));
}

TEST(SetTest, int_basic_key_comp_2) {
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
TEST(SetTest, int_basic_value_comp_1) {
  std::set<int, ModCmp> libst;
  ft::set<int, ModCmp> myst;

  std::set<int, ModCmp>::value_compare libcomp = libst.value_comp();
  ft::set<int, ModCmp>::value_compare mycomp = myst.value_comp();

  ASSERT_EQ(libcomp(1, 2), mycomp(1, 2));
  ASSERT_EQ(libcomp(100, 2), mycomp(100, 2));
  ASSERT_EQ(libcomp(100, 200), mycomp(100, 200));
  ASSERT_EQ(libcomp(97, 98), mycomp(97, 98));
}

TEST(SetTest, int_basic_value_comp_2) {
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
TEST(SetTest, int_basic_comp_operator_1) {
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

TEST(SetTest, int_basic_comp_operator_2) {
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

TEST(SetTest, int_basic_comp_operator_3) {
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

TEST(SetTest, int_basic_comp_operator_4) {
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
