#include <gtest/gtest.h>

#include <memory>
#include "../tree.hpp"

// // __begin
// TEST(TreeTest, int_basic_begin) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   ft::__tree<int, int>::iterator itr = t.__begin();
//   ASSERT_EQ(itr->first, 1);
//   ASSERT_EQ(itr->second, 1);
// }

// TEST(TreeTest, int_basic_begin1) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 2);
//   ft::__tree<int, int>::iterator itr = t.__begin();
//   ASSERT_EQ(itr->first, 1);
//   ASSERT_EQ(itr->second, 1);
// }

// TEST(TreeTest, int_basic_begin2) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 2);
//   t.__insert(-1, -1);
//   ft::__tree<int, int>::iterator itr = t.__begin();
//   ASSERT_EQ(itr->first, -1);
//   ASSERT_EQ(itr->second, -1);
// }

// // __end
// TEST(TreeTest, int_basic_end) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   ft::__tree<int, int>::iterator itr = t.__end();
// }

// // __rbegin
// TEST(TreeTest, int_basic_rbegin) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   ft::__tree<int, int>::reverse_iterator itr = t.__rbegin();
//   ASSERT_EQ(itr->first, 1);
//   ASSERT_EQ(itr->second, 1);
// }

// TEST(TreeTest, int_basic_rbegin1) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 2);
//   ft::__tree<int, int>::reverse_iterator itr = t.__rbegin();
//   ASSERT_EQ(itr->first, 2);
//   ASSERT_EQ(itr->second, 2);
//   itr++;
//   ASSERT_EQ(itr->first, 1);
//   ASSERT_EQ(itr->second, 1);
//   itr++;
// }

// // __rend
// TEST(TreeTest, int_basic_rend) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   ft::__tree<int, int>::reverse_iterator itr = t.__rend();
//   --itr;
//   ASSERT_EQ(itr->first, 1);
//   ASSERT_EQ(itr->second, 1);
// }

// TEST(TreeTest, int_basic_rend1) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 2);
//   ft::__tree<int, int>::reverse_iterator itr = t.__rend();
//   --itr;
//   ASSERT_EQ(itr->first, 1);
//   ASSERT_EQ(itr->second, 1);
//   --itr;
//   ASSERT_EQ(itr->first, 2);
//   ASSERT_EQ(itr->second, 2);
// }

// // iterator
// TEST(TreeTest, int_basic_iterator) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 1);
//   ft::__tree<int, int>::iterator itr = t.__begin();
//   ASSERT_EQ(itr->first, 1);
//   ASSERT_EQ(itr->second, 1);
//   ++itr;
//   ASSERT_EQ(itr->first, 2);
//   ASSERT_EQ(itr->second, 1);
// }

// TEST(TreeTest, int_basic_iterator1) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 1);
//   ft::__tree<int, int>::iterator itr = t.__begin();
//   ASSERT_EQ(itr->first, 1);
//   ASSERT_EQ(itr->second, 1);
//   itr++;
//   ASSERT_EQ(itr->first, 2);
//   ASSERT_EQ(itr->second, 1);
// }

// TEST(TreeTest, int_basic_iterator2) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 1);
//   ft::__tree<int, int>::iterator itr = t.__begin();
//   ASSERT_EQ(itr->first, 1);
//   ASSERT_EQ(itr->second, 1);
//   ++itr;
//   ASSERT_EQ(itr->first, 2);
//   ASSERT_EQ(itr->second, 1);
//   ++itr;
//   ASSERT_EQ(itr, t.__end());
// }

// TEST(TreeTest, int_basic_iterator3) {
//   ft::__tree<int, int> t;
//   t.__insert(10, 1);
//   t.__insert(2, 1);
//   ft::__tree<int, int>::iterator itr = t.__begin();
//   ASSERT_EQ(itr->first, 2);
//   ASSERT_EQ(itr->second, 1);
//   ++itr;
//   --itr;
//   ASSERT_EQ(itr->first, 2);
//   ASSERT_EQ(itr->second, 1);
//   ASSERT_EQ(itr, t.__begin());
// }

// TEST(TreeTest, int_basic_iterator4) {
//   ft::__tree<int, int> t;
//   t.__insert(10, 1);
//   t.__insert(2, 1);
//   ft::__tree<int, int>::iterator itr = t.__end();
//   --itr;
//   ASSERT_EQ(itr->first, 10);
//   ASSERT_EQ(itr->second, 1);
//   --itr;
//   ASSERT_EQ(itr->first, 2);
//   ASSERT_EQ(itr->second, 1);
//   ASSERT_EQ(itr, t.__begin());
// }

// TEST(TreeTest, int_basic_iterator5) {
//   ft::__tree<int, int> t;
//   t.__insert(10, 1);
//   t.__insert(2, 1);
//   ft::__tree<int, int>::iterator itr = t.__end();
//   itr--;
//   ASSERT_EQ(itr->first, 10);
//   ASSERT_EQ(itr->second, 1);
//   itr--;
//   ASSERT_EQ(itr->first, 2);
//   ASSERT_EQ(itr->second, 1);
//   ASSERT_EQ(itr, t.__begin());
// }

// // __insert
// TEST(TreeTest, int_basic_insert) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   ft::__tree<int, int>::node_pointer root = t.root();
//   ASSERT_EQ(root->value.first, 1);
//   ASSERT_EQ(root->value.second, 1);
//   ASSERT_EQ(root->parent, root);
// }

// TEST(TreeTest, int_basic_insert1) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(-1, 1);
//   ft::__tree<int, int>::node_pointer root = t.root();
//   ASSERT_EQ(root->value.first, 1);
//   ASSERT_EQ(root->value.second, 1);
//   ASSERT_EQ(root->left->value.first, -1);
//   ASSERT_EQ(root->left->value.second, 1);

//   ASSERT_EQ(root->left->parent->value.first, 1);
//   ASSERT_EQ(root->left->parent->value.second, 1);
// }

// TEST(TreeTest, int_basic_insert2) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 1);
//   ft::__tree<int, int>::node_pointer root = t.root();
//   ASSERT_EQ(root->value.first, 1);
//   ASSERT_EQ(root->value.second, 1);
//   ASSERT_EQ(root->right->value.first, 2);
//   ASSERT_EQ(root->right->value.second, 1);

//   ASSERT_EQ(root->right->parent->value.first, 1);
//   ASSERT_EQ(root->right->parent->value.second, 1);
// }

// TEST(TreeTest, int_basic_insert3) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(-1, 1);
//   t.__insert(2, 1);
//   ft::__tree<int, int>::node_pointer root = t.root();
//   ASSERT_EQ(root->value.first, 1);
//   ASSERT_EQ(root->value.second, 1);
//   ASSERT_EQ(root->left->value.first, -1);
//   ASSERT_EQ(root->left->value.second, 1);
//   ASSERT_EQ(root->right->value.first, 2);
//   ASSERT_EQ(root->right->value.second, 1);

//   ASSERT_EQ(root->left->parent->value.first, 1);
//   ASSERT_EQ(root->left->parent->value.second, 1);
//   ASSERT_EQ(root->right->parent->value.first, 1);
//   ASSERT_EQ(root->right->parent->value.second, 1);
// }

// TEST(TreeTest, int_basic_insert4) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(-1, 1);
//   t.__insert(2, 1);
//   t.__insert(-10, 2);
//   ft::__tree<int, int>::node_pointer root = t.root();
//   ASSERT_EQ(root->value.first, 1);
//   ASSERT_EQ(root->value.second, 1);
//   ASSERT_EQ(root->left->value.first, -1);
//   ASSERT_EQ(root->left->value.second, 1);
//   ASSERT_EQ(root->left->left->value.first, -10);
//   ASSERT_EQ(root->left->left->value.second, 2);
//   ASSERT_EQ(root->right->value.first, 2);
//   ASSERT_EQ(root->right->value.second, 1);
// }

// TEST(TreeTest, int_basic_insert5) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(-1, -1);
//   t.__insert(2, 2);
//   t.__insert(-10, -10);
//   t.__insert(10, 10);
//   ft::__tree<int, int>::node_pointer root = t.root();
//   ASSERT_EQ(root->value.first, 1);
//   ASSERT_EQ(root->value.second, 1);
//   ASSERT_EQ(root->left->value.first, -1);
//   ASSERT_EQ(root->left->value.second, -1);
//   ASSERT_EQ(root->left->left->value.first, -10);
//   ASSERT_EQ(root->left->left->value.second, -10);
//   ASSERT_EQ(root->right->value.first, 2);
//   ASSERT_EQ(root->right->value.second, 2);
//   ASSERT_EQ(root->right->right->value.first, 10);
//   ASSERT_EQ(root->right->right->value.second, 10);
// }

// TEST(TreeTest, int_basic_insert6) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(-1, -1);
//   t.__insert(2, 2);
//   t.__insert(-10, -10);
//   t.__insert(10, 10);
//   t.__insert(5, 5);
//   ft::__tree<int, int>::node_pointer root = t.root();
//   ASSERT_EQ(root->value.first, 1);
//   ASSERT_EQ(root->value.second, 1);
//   ASSERT_EQ(root->left->value.first, -1);
//   ASSERT_EQ(root->left->value.second, -1);
//   ASSERT_EQ(root->left->left->value.first, -10);
//   ASSERT_EQ(root->left->left->value.second, -10);
//   ASSERT_EQ(root->right->value.first, 2);
//   ASSERT_EQ(root->right->value.second, 2);
//   ASSERT_EQ(root->right->right->value.first, 10);
//   ASSERT_EQ(root->right->right->value.second, 10);
//   ASSERT_EQ(root->right->right->left->value.first, 5);
//   ASSERT_EQ(root->right->right->left->value.second, 5);
// }

// __size
TEST(TreeTest, int_basic_size) {
  ft::__tree<int, int> t;
  ASSERT_EQ(t.__size(), 0);
}

// TEST(TreeTest, int_basic_size1) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   ASSERT_EQ(t.__size(), 1);
// }

// TEST(TreeTest, int_basic_size2) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 2);
//   ASSERT_EQ(t.__size(), 2);
// }

// TEST(TreeTest, int_basic_size3) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 2);
//   t.__insert(3, 3);
//   ASSERT_EQ(t.__size(), 3);
// }

// TEST(TreeTest, int_basic_size4) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 2);
//   t.__insert(3, 3);
//   t.__insert(4, 4);
//   ASSERT_EQ(t.__size(), 4);
// }

// TEST(TreeTest, int_basic_size5) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(2, 2);
//   t.__insert(3, 3);
//   t.__insert(4, 4);
//   t.__insert(-1, -1);
//   t.__insert(-2, -2);
//   t.__insert(-10, -10);
//   t.__insert(-5, -5);
//   ASSERT_EQ(t.__size(), 8);
// }

// TEST(TreeTest, int_basic_size6) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 1);
//   t.__insert(1, 1);
//   t.__insert(1, 1);
//   ASSERT_EQ(t.__size(), 1);
// }

// // __empty
// TEST(TreeTest, int_basic_empty) {
//   ft::__tree<int, int> t;
//   ASSERT_EQ(t.__empty(), true);
// }

// TEST(TreeTest, int_basic_empty1) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 2);
//   ASSERT_EQ(t.__empty(), false);
// }

// // __erase
// // __find
// TEST(TreeTest, int_basic_find) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 2);
//   ft::__tree<int, int>::node_pointer ndp = t.__find(1);
//   ASSERT_EQ(ndp->value.first, 1);
//   ASSERT_EQ(ndp->value.second, 2);
// }

// TEST(TreeTest, int_basic_find1) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 2);
//   t.__insert(2, 4);
//   ft::__tree<int, int>::node_pointer ndp = t.__find(1);
//   ft::__tree<int, int>::node_pointer ndp1 = t.__find(2);
//   ASSERT_EQ(ndp->value.first, 1);
//   ASSERT_EQ(ndp->value.second, 2);
//   ASSERT_EQ(ndp1->value.first, 2);
//   ASSERT_EQ(ndp1->value.second, 4);
// }

// TEST(TreeTest, int_basic_find2) {
//   ft::__tree<int, int> t;
//   t.__insert(1, 2);
//   t.__insert(2, 4);
//   t.__insert(-1, 2);
//   ft::__tree<int, int>::node_pointer ndp = t.__find(1);
//   ft::__tree<int, int>::node_pointer ndp1 = t.__find(2);
//   ft::__tree<int, int>::node_pointer ndp2 = t.__find(-1);
//   ASSERT_EQ(ndp->value.first, 1);
//   ASSERT_EQ(ndp->value.second, 2);
//   ASSERT_EQ(ndp1->value.first, 2);
//   ASSERT_EQ(ndp1->value.second, 4);
//   ASSERT_EQ(ndp2->value.first, -1);
//   ASSERT_EQ(ndp2->value.second, 2);
// }
