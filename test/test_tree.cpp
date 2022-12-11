#include <gtest/gtest.h>
#include <glog/logging.h>

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

TEST(TreeTest, int_basic_begin1_1) {
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

TEST(TreeTest, int_basic_begin1_2) {
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

//               2b
//        +------+------+
//        1b            4b
//    +---+---+     +---+---+
//                  3r       5r

TEST(TreeTest, int_basic_begin1_3) {
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

TEST(TreeTest, int_basic_begin1_4) {
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

TEST(TreeTest, int_basic_begin1_5) {
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

TEST(TreeTest, int_basic_begin1_6) {
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

TEST(TreeTest, int_basic_begin1_6_1) {
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

TEST(TreeTest, int_basic_begin1_7) {
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

TEST(TreeTest, int_basic_begin1_8) {
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

TEST(TreeTest, int_basic_end_4_1) {
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
TEST(TreeTest, int_basic_insert_case1_1) {
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

TEST(TreeTest, int_basic_insert_case1_2) {
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

TEST(TreeTest, int_basic_insert_case1_3) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(-1);
  ft::__tree<int, int, ft::Identity<int> >::node_pointer root = t.root();
  ASSERT_EQ(root->__is_black_node(), true);
  ASSERT_EQ(root->left->__is_red_node(), true);

  ASSERT_EQ(root->value, 1);
  ASSERT_EQ(root->left->value, -1);
}

TEST(TreeTest, int_basic_insert_case4_1) {
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

TEST(TreeTest, int_basic_insert_case4_2) {
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

TEST(TreeTest, int_basic_insert_case4_3) {
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

TEST(TreeTest, int_basic_insert2_4) {
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

//          1b
//      +---+---+
//    -1b       2b
//  +---+---+
// -2r

TEST(TreeTest, int_basic_insert2_6) {
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

// //                1b
// //           +-----+-----+
// //          -2b         2b
// //       +---+---+  +---+---+
// //     -3r      -1r         3r

TEST(TreeTest, int_basic_insert2_7) {
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

// //                1b
// //           +-----+-----+
// //          -2r         2b
// //       +---+---+  +---+---+
// //     -3b      -1b         3r
// //  +---+---+
// // -4r

TEST(TreeTest, int_basic_insert4) {
  ft::__tree<int, ft::pair<int, int>, ft::Select1st<ft::pair<int, int> > > t;
  t.__insert(ft::make_pair(1, 1));
  t.__insert(ft::make_pair(2, 2));
  ft::__tree<int, ft::pair<int, int>,
             ft::Select1st<ft::pair<int, int> > >::node_pointer root = t.root();
  ASSERT_EQ(root->__is_black_node(), true);
  ASSERT_EQ(root->value.first, 1);
  ASSERT_EQ(root->value.second, 1);
  ASSERT_EQ(root->right->__is_red_node(), true);
  ASSERT_EQ(root->right->value.first, 2);
  ASSERT_EQ(root->right->value.second, 2);
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

// __find
TEST(TreeTest, int_basic_find_1) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);

  ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__find(1);

  ASSERT_EQ(*itr, 1);
}

TEST(TreeTest, int_basic_find_2) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);

  ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__find(1);

  ASSERT_EQ(*itr, 1);
  ++itr;
  ASSERT_EQ(*itr, 2);
}

TEST(TreeTest, int_basic_find_3) {
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

TEST(TreeTest, int_basic_find_4) {
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

TEST(TreeTest, int_basic_find_5) {
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
TEST(TreeTest, int_basic_lower_bound) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(10);
  t.__insert(20);
  t.__insert(30);
  t.__insert(40);
  t.__insert(50);

  ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__lower_bound(10);

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

//               2b
//        +------+------+
//        1b            4b
//    +---+---+     +---+---+
//                  3r       5r

TEST(TreeTest, int_basic_lower_bound_1) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(10);
  t.__insert(20);
  t.__insert(30);
  t.__insert(40);
  t.__insert(50);

  ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__lower_bound(11);

  ASSERT_EQ(*itr, 20);
  ++itr;
  ASSERT_EQ(*itr, 30);
  ++itr;
  ASSERT_EQ(*itr, 40);
  ++itr;
  ASSERT_EQ(*itr, 50);
}

TEST(TreeTest, int_basic_lower_bound_2) {
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
TEST(TreeTest, int_basic_find_node_pointer_1) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);

  ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
      t.__find_node_pointer(1);

  ASSERT_EQ(ptr->value, 1);
}

TEST(TreeTest, int_basic_find_node_pointer_2) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);

  ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
      t.__find_node_pointer(1);

  ASSERT_EQ(ptr->value, 1);
}

TEST(TreeTest, int_basic_find_node_pointer_3) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);

  ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
      t.__find_node_pointer(2);

  ASSERT_EQ(ptr->value, 2);
}

TEST(TreeTest, int_basic_find_node_pointer_4) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);
  t.__insert(3);

  ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
      t.__find_node_pointer(1);

  ASSERT_EQ(ptr->value, 1);
}

TEST(TreeTest, int_basic_find_node_pointer_5) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);
  t.__insert(3);

  ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
      t.__find_node_pointer(2);

  ASSERT_EQ(ptr->value, 2);
}

TEST(TreeTest, int_basic_find_node_pointer_6) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__insert(2);
  t.__insert(3);

  ft::__tree<int, int, ft::Identity<int> >::node_pointer ptr =
      t.__find_node_pointer(3);

  ASSERT_EQ(ptr->value, 3);
}

TEST(TreeTest, int_basic_find_node_pointer_7) {
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
TEST(TreeTest, int_basic_upper_bound) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(10);
  t.__insert(20);
  t.__insert(30);
  t.__insert(40);
  t.__insert(50);

  ft::__tree<int, int, ft::Identity<int> >::iterator itr = t.__uppper_bound(10);

  ASSERT_EQ(*itr, 20);
  ++itr;
  ASSERT_EQ(*itr, 30);
  ++itr;
  ASSERT_EQ(*itr, 40);
  ++itr;
  ASSERT_EQ(*itr, 50);
}

// count
TEST(TreeTest, int_basic_count_1) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(10);

  ASSERT_EQ(t.__count(10), 1);
}

TEST(TreeTest, int_basic_count_2) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(10);

  ASSERT_EQ(t.__count(42), 0);
}

// // max_size
// TEST(TreeTest, int_basic_max_size) {
//   ft::__tree<int, int, ft::Identity<int> > t;
// }

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

// __erase
TEST(TreeTest, int_basic_erase_1_1) {
  ft::__tree<int, int, ft::Identity<int> > t;
  t.__insert(1);
  t.__erase(1);

  ASSERT_EQ(t.__size(), 0);
}

TEST(TreeTest, int_basic_erase_1_2) {
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

TEST(TreeTest, int_basic_erase_1_3) {
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

TEST(TreeTest, int_basic_erase_1_4) {
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

TEST(TreeTest, int_basic_erase_1_5) {
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

TEST(TreeTest, int_basic_erase_1_6) {
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
