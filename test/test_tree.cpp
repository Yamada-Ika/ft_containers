#include <gtest/gtest.h>

#include <memory>
#include "../tree.hpp"
#include "../utils.hpp"
#include "../pair.hpp"

// __begin
TEST(TreeTest, int_basic_begin) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__begin();
  ASSERT_EQ(*itr, 1);

  ++itr;
  ASSERT_EQ(itr, t.__end());
}

TEST(TreeTest, int_basic_begin1) {
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

TEST(TreeTest, int_basic_begin2) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  ft::__tree<int, ft::pair<int, int>,
             ft::Select1st<ft::pair<int, int> > >::iterator itr = t.__begin();
  ASSERT_EQ(itr->first, 1);
  ASSERT_EQ(itr->second, 1);

  ++itr;
  ASSERT_EQ(itr, t.__end());
}

TEST(TreeTest, int_basic_begin3) {
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

TEST(TreeTest, int_basic_begin4) {
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

// __end
TEST(TreeTest, int_basic_end) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__end();
  --itr;
  ASSERT_EQ(*itr, 1);

  ASSERT_EQ(itr, t.__begin());
}

TEST(TreeTest, int_basic_end1) {
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

TEST(TreeTest, int_basic_end2) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  ft::__tree<int, ft::pair<int, int>,
             ft::Select1st<ft::pair<int, int> > >::iterator itr = t.__end();
  --itr;
  ASSERT_EQ(itr->first, 1);
  ASSERT_EQ(itr->second, 1);

  ASSERT_EQ(itr, t.__begin());
}

TEST(TreeTest, int_basic_end3) {
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

// __rbegin
TEST(TreeTest, int_basic_rbegin) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  ft::__tree<int, int, ft::Identity<int> >::reverse_iterator itr = t.__rbegin();
  ASSERT_EQ(*itr, 1);
  ++itr;
  ASSERT_EQ(itr, t.__rend());
}

TEST(TreeTest, int_basic_rbegin1) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);
  ft::__tree<int, int, ft::Identity<int> >::reverse_iterator itr = t.__rbegin();
  ASSERT_EQ(*itr, 2);
  ++itr;
  ASSERT_EQ(*itr, 1);
  ++itr;
  ASSERT_EQ(itr, t.__rend());
}

TEST(TreeTest, int_basic_rbegin2) {
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

TEST(TreeTest, int_basic_rbegin3) {
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
TEST(TreeTest, int_basic_rend) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  ft::__tree<int, int, ft::Identity<int> >::reverse_iterator itr = t.__rend();
  --itr;
  ASSERT_EQ(*itr, 1);
}

TEST(TreeTest, int_basic_rend1) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);
  ft::__tree<int, int, ft::Identity<int> >::reverse_iterator itr = t.__rend();
  --itr;
  ASSERT_EQ(*itr, 1);
  --itr;
  ASSERT_EQ(*itr, 2);
}

TEST(TreeTest, int_basic_rend2) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  ft::__tree<int, ft::pair<int, int>,
             ft::Select1st<ft::pair<int, int> > >::reverse_iterator itr =
      t.__rend();
  --itr;
  ASSERT_EQ(itr->first, 1);
  ASSERT_EQ(itr->second, 1);
}

TEST(TreeTest, int_basic_rend3) {
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
TEST(TreeTest, int_basic_insert) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();
  ASSERT_EQ(root->value, 1);
  ASSERT_EQ(root->parent, root);
}

TEST(TreeTest, int_basic_insert1) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);
  ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();
  ASSERT_EQ(root->value, 1);
  ASSERT_EQ(root->right->value, 2);
  ASSERT_EQ(root->right->parent, root);
}

TEST(TreeTest, int_basic_insert2) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);
  t.__insert(-1);
  ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();
  ASSERT_EQ(root->value, 1);
  ASSERT_EQ(root->right->value, 2);
  ASSERT_EQ(root->right->parent, root);
  ASSERT_EQ(root->left->parent, root);
}

TEST(TreeTest, int_basic_insert3) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  ft::__tree<int, ft::pair<int, int>,
             ft::Select1st<ft::pair<int, int> > >::node_pointer root = t.root();
  ASSERT_EQ(root->value.first, 1);
  ASSERT_EQ(root->value.second, 1);
  ASSERT_EQ(root->parent, root);
}

TEST(TreeTest, int_basic_insert4) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  t.__insert(ft::make_pair(2, 2));
  ft::__tree<int, ft::pair<int, int>,
             ft::Select1st<ft::pair<int, int> > >::node_pointer root = t.root();
  ASSERT_EQ(root->value.first, 1);
  ASSERT_EQ(root->value.second, 1);
  ASSERT_EQ(root->right->value.first, 2);
  ASSERT_EQ(root->right->value.second, 2);
  ASSERT_EQ(root->right->parent, root);
}

TEST(TreeTest, int_basic_insert5) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  t.__insert(ft::make_pair(2, 2));
  t.__insert(ft::make_pair(-1, -1));
  ft::__tree<int, ft::pair<int, int>,
             ft::Select1st<ft::pair<int, int> > >::node_pointer root = t.root();
  ASSERT_EQ(root->value.first, 1);
  ASSERT_EQ(root->value.second, 1);
  ASSERT_EQ(root->right->value.first, 2);
  ASSERT_EQ(root->right->value.second, 2);
  ASSERT_EQ(root->left->parent, root);
  ASSERT_EQ(root->left->value.first, -1);
  ASSERT_EQ(root->left->value.second, -1);
  ASSERT_EQ(root->right->parent, root);
}

// __size
TEST(TreeTest, int_basic_size) {
  ft::__tree<int, int, ft::Identity<int> > t;
  ASSERT_EQ(t.__size(), 0);
}

TEST(TreeTest, int_basic_size1) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  ASSERT_EQ(t.__size(), 1);
}

TEST(TreeTest, int_basic_size2) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  ASSERT_EQ(t.__size(), 0);
}

TEST(TreeTest, int_basic_size3) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  ASSERT_EQ(t.__size(), 1);
}

TEST(TreeTest, int_basic_size4) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);
  ASSERT_EQ(t.__size(), 2);
}

TEST(TreeTest, int_basic_size5) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);
  t.__insert(3);
  ASSERT_EQ(t.__size(), 3);
}

TEST(TreeTest, int_basic_size6) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(1);
  t.__insert(1);
  ASSERT_EQ(t.__size(), 1);
}

TEST(TreeTest, int_basic_size7) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);
  t.__insert(1);
  ASSERT_EQ(t.__size(), 2);
}

TEST(TreeTest, int_basic_size8) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  t.__insert(ft::make_pair(2, 2));
  ASSERT_EQ(t.__size(), 2);
}

TEST(TreeTest, int_basic_size9) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  t.__insert(ft::make_pair(2, 2));
  t.__insert(ft::make_pair(3, 3));
  ASSERT_EQ(t.__size(), 3);
}

TEST(TreeTest, int_basic_size10) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  t.__insert(ft::make_pair(1, 1));
  t.__insert(ft::make_pair(1, 1));
  ASSERT_EQ(t.__size(), 1);
}

TEST(TreeTest, int_basic_size11) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  t.__insert(ft::make_pair(1, 2));
  t.__insert(ft::make_pair(1, 3));
  ASSERT_EQ(t.__size(), 1);
}

TEST(TreeTest, int_basic_size12) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  t.__insert(ft::make_pair(2, 2));
  t.__insert(ft::make_pair(1, 3));
  ASSERT_EQ(t.__size(), 2);
}

// __empty
TEST(TreeTest, int_basic_empty) {
  ft::__tree<int, int, ft::Identity<int> > t;
  ASSERT_EQ(t.__empty(), true);
}

TEST(TreeTest, int_basic_empty1) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  ASSERT_EQ(t.__empty(), false);
}

TEST(TreeTest, int_basic_empty2) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  ASSERT_EQ(t.__empty(), true);
}

TEST(TreeTest, int_basic_empty3) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  ASSERT_EQ(t.__empty(), false);
}

// __erase
TEST(TreeTest, int_basic_erase_3_1) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(2);
  t1.__erase(2);

  ft::__tree<int, int, ft::Identity<int> > t_exp;
  t_exp.__insert(1);

  ASSERT_EQ(t1.__size(), t_exp.__size());
  ft::__tree<int, int, ft::Identity<int> >::iterator t1itr = t1.__begin();
  ft::__tree<int, int, ft::Identity<int> >::iterator t_expitr = t_exp.__begin();

  while (t_expitr != t_exp.__end()) {
    ASSERT_EQ(*t1itr, *t_expitr);
    ++t1itr;
    ++t_expitr;
  }
}

TEST(TreeTest, int_basic_erase_3_2) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(4);
  t1.__insert(2);
  t1.__erase(4);

  ft::__tree<int, int, ft::Identity<int> > t_exp;
  t_exp.__insert(1);
  t_exp.__insert(2);

  ASSERT_EQ(t1.__size(), t_exp.__size());
  ft::__tree<int, int, ft::Identity<int> >::iterator t1itr = t1.__begin();
  ft::__tree<int, int, ft::Identity<int> >::iterator t_expitr = t_exp.__begin();

  while (t_expitr != t_exp.__end()) {
    ASSERT_EQ(*t1itr, *t_expitr);
    ++t1itr;
    ++t_expitr;
  }
}

TEST(TreeTest, int_basic_erase_3_3) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(-4);
  t1.__insert(-6);

  ASSERT_EQ(t1.__erase(-4), 1);

  ft::__tree<int, int, ft::Identity<int> > t_exp;
  t_exp.__insert(1);
  t_exp.__insert(-6);

  ASSERT_EQ(t1.__size(), t_exp.__size());
  ft::__tree<int, int, ft::Identity<int> >::iterator t1itr = t1.__begin();
  ft::__tree<int, int, ft::Identity<int> >::iterator t_expitr = t_exp.__begin();

  while (t_expitr != t_exp.__end()) {
    ASSERT_EQ(*t1itr, *t_expitr);
    ++t1itr;
    ++t_expitr;
  }
}

TEST(TreeTest, int_basic_erase_3_4) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(4);
  t1.__insert(6);
  t1.__erase(4);

  ft::__tree<int, int, ft::Identity<int> > t_exp;
  t_exp.__insert(1);
  t_exp.__insert(6);

  ASSERT_EQ(t1.__size(), t_exp.__size());
  ft::__tree<int, int, ft::Identity<int> >::iterator t1itr = t1.__begin();
  ft::__tree<int, int, ft::Identity<int> >::iterator t_expitr = t_exp.__begin();

  while (t_expitr != t_exp.__end()) {
    ASSERT_EQ(*t1itr, *t_expitr);
    ++t1itr;
    ++t_expitr;
  }
}

TEST(TreeTest, int_basic_erase_3_5) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(-4);
  t1.__insert(-1);
  t1.__erase(-4);

  ft::__tree<int, int, ft::Identity<int> > t_exp;
  t_exp.__insert(1);
  t_exp.__insert(-1);

  ASSERT_EQ(t1.__size(), t_exp.__size());
  ft::__tree<int, int, ft::Identity<int> >::iterator t1itr = t1.__begin();
  ft::__tree<int, int, ft::Identity<int> >::iterator t_expitr = t_exp.__begin();

  while (t_expitr != t_exp.__end()) {
    ASSERT_EQ(*t1itr, *t_expitr);
    ++t1itr;
    ++t_expitr;
  }
}

TEST(TreeTest, int_basic_erase_3_6) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(10);
  t1.__insert(5);
  t1.__insert(15);
  t1.__erase(10);

  ft::__tree<int, int, ft::Identity<int> > t_exp;
  t_exp.__insert(1);
  t_exp.__insert(5);
  t_exp.__insert(15);

  ASSERT_EQ(t1.__size(), t_exp.__size());
  ft::__tree<int, int, ft::Identity<int> >::iterator t1itr = t1.__begin();
  ft::__tree<int, int, ft::Identity<int> >::iterator t_expitr = t_exp.__begin();

  ASSERT_EQ(*t1itr, *t_expitr);
  ++t1itr;
  ++t_expitr;
  ASSERT_EQ(*t1itr, *t_expitr);
  ++t1itr;
  ++t_expitr;
  ASSERT_EQ(*t1itr, *t_expitr);
  ++t1itr;
  ++t_expitr;
}

TEST(TreeTest, int_basic_erase_3_7) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(10);
  t1.__insert(5);
  t1.__insert(15);
  t1.__insert(6);
  t1.__insert(7);
  t1.__insert(8);
  t1.__insert(9);
  t1.__insert(11);
  t1.__insert(12);
  t1.__insert(13);
  t1.__insert(14);

  t1.__erase(10);

  ft::__tree<int, int, ft::Identity<int> > t_exp;
  t_exp.__insert(1);
  t_exp.__insert(5);
  t_exp.__insert(15);
  t_exp.__insert(6);
  t_exp.__insert(7);
  t_exp.__insert(8);
  t_exp.__insert(9);
  t_exp.__insert(11);
  t_exp.__insert(12);
  t_exp.__insert(13);
  t_exp.__insert(14);

  ASSERT_EQ(t1.__size(), t_exp.__size());
  ft::__tree<int, int, ft::Identity<int> >::iterator t1itr = t1.__begin();
  ft::__tree<int, int, ft::Identity<int> >::iterator t_expitr = t_exp.__begin();

  while (t1itr != t1.__end()) {
    ASSERT_EQ(*t1itr, *t_expitr);
    ++t1itr;
    ++t_expitr;
  }
}

// operator==
TEST(TreeTest, int_basic_operator_equal) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  ft::__tree<int, int, ft::Identity<int> > t2;
  ASSERT_EQ(t1 == t2, true);
}

TEST(TreeTest, int_basic_operator_not_equal) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  ft::__tree<int, int, ft::Identity<int> > t2;
  ASSERT_EQ(t1 != t2, true);
}

TEST(TreeTest, int_basic_operator_less_than) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(2);
  ft::__tree<int, int, ft::Identity<int> > t2;
  t2.__insert(1);
  t2.__insert(3);
  ASSERT_EQ(t1 < t2, true);
}

TEST(TreeTest, int_basic_operator_greater_equal_than) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(2);
  ft::__tree<int, int, ft::Identity<int> > t2;
  t2.__insert(1);
  t2.__insert(2);
  ASSERT_EQ(t1 >= t2, true);
}

TEST(TreeTest, int_basic_operator_greater_equal_than1) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(3);
  ft::__tree<int, int, ft::Identity<int> > t2;
  t2.__insert(1);
  t2.__insert(2);
  ASSERT_EQ(t1 >= t2, true);
}

TEST(TreeTest, int_basic_operator_greater_than) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(3);
  ft::__tree<int, int, ft::Identity<int> > t2;
  t2.__insert(1);
  t2.__insert(2);
  ASSERT_EQ(t1 > t2, true);
}

TEST(TreeTest, int_basic_operator_less_equal_than) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(2);
  ft::__tree<int, int, ft::Identity<int> > t2;
  t2.__insert(1);
  t2.__insert(2);
  ASSERT_EQ(t1 <= t2, true);
}

TEST(TreeTest, int_basic_operator_less_equal_than1) {
  ft::__tree<int, int, ft::Identity<int> > t1;
  t1.__insert(1);
  t1.__insert(2);
  ft::__tree<int, int, ft::Identity<int> > t2;
  t2.__insert(1);
  t2.__insert(3);
  ASSERT_EQ(t1 <= t2, true);
}