#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include "deque.hpp"
#include "pair.hpp"
#include <glog/logging.h>
#include <functional>

namespace ft {

// 木のノードを表すクラス
template <typename T, typename Allocator>
class __node {
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  // typedef Allocator allocator_type;
  typedef typename Allocator::template rebind<__node>::other node_allocator;
  typedef node_allocator allocator_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef pointer iterator;
  typedef const_pointer const_iterator;
  typedef __node Self;
  typedef __node* node_pointer;

  node_pointer left;
  node_pointer right;
  node_pointer parent;
  value_type value;

  __node()
      : left(NULL), right(NULL), parent(NULL), value(value_type()),
        node_alloc(node_allocator()) {}
  __node(const_reference v)
      : left(NULL), right(NULL), parent(NULL), value(v),
        node_alloc(node_allocator()) {}
  ~__node();
  __node(const __node& other) { *this = other; }
  __node& operator=(const __node& other) {
    if (this == &other) {
      return *this;
    }

    // TODO コピー用の関数作る。適当
    left = other.left;
    right = other.right;
    parent = other.parent;
    value = other.value;
    node_alloc = other.node_alloc;
    return *this;
  }

  static bool __is_root(node_pointer nd);

private:
  allocator_type node_alloc;
};

/*
valueを木に追加する
public void __insert(const_reference value)

ノードの数を返す
public size_type __size()

空かチェック
public bool __empty()

値と一致するノードを削除
public void __erase(const_reference value)

値と一致するノードを検索
public node_pointer __find(const_reference value)
*/

// 二分探索木を表すクラス
template <typename Key, typename Val, class Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
class __tree {
public:
  // typedef Key value_type;
  typedef Key key_type;
  typedef Val mapped_type;
  typedef ft::pair<const Key, Val> value_type;
  typedef std::size_t size_type;
  // typedef Allocator allocator_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  // typedef __node<Key, Allocator> node;
  typedef __node<value_type, Allocator> node;
  typedef typename Allocator::template rebind<node>::other node_allocator;
  typedef typename node::node_pointer node_pointer;

  __tree() : root_(NULL) {}
  // TODO メモリ解放したらクラッシュする
  ~__tree() {}

  // 要素を追加
  void __insert(const_reference value) {
    // 初めて要素を追加
    if (__empty()) {
      LOG(ERROR) << "__insert/ node is root";
      // TODO とりあえず左側に
      root_ = __allocate_node(value);
      return;
    }
    LOG(ERROR) << "__insert/ node is not root";
    // ノードを辿って適切な場所にノードを作成
    node_pointer prev_parent = root_;
    node_pointer nd = root_;
    while (true) {
      // keyで比較
      if (value.first < nd->value.first) {
        nd = nd->left;
        if (nd == NULL) {
          prev_parent->left = __allocate_node(value);
          break;
        }
      } else if (value.first > nd->value.first) {
        nd = nd->right;
        if (nd == NULL) {
          prev_parent->right = __allocate_node(value);
          break;
        }
      } else {
        // すでに存在していたら、重複を許さないので何もしない
        // ただvalueを更新する必要がある
        nd->value.second = value.second;
        break;
      }
      LOG(ERROR) << "__insert/ update prev node";
      prev_parent = nd;
    }
  }

  // TODO 適当
  void __insert(key_type k, mapped_type v) {
    value_type val(k, v);
    __insert(val);
  }

  // ノードの要素を返す
  size_type __size() const {
    LOG(ERROR) << "__size called";
    if (root_ == NULL) {
      LOG(ERROR) << "__size returned 0";
      return 0;
    }
    ft::deque<node_pointer> q;
    size_type sz = 0;
    q.push_back(root_);
    while (!q.empty()) {
      node_pointer nd = q.at(0);
      q.pop_front();
      sz++;
      if (nd->left != NULL) {
        LOG(ERROR) << "__size push left";
        q.push_back(nd->left);
      }
      if (nd->right != NULL) {
        LOG(ERROR) << "__size push right";
        LOG(ERROR) << "__size value     " << nd->right;
        q.push_back(nd->right);
      }
      LOG(ERROR) << "__size size       " << sz;
      LOG(ERROR) << "__size queue size " << q.size();
    }
    return sz;
  }

  // TODO sizeはカウントしなくても良さそうだけど
  bool __empty() const { return root_ == NULL; }

  //  値と一致するノードを検索
  // 適当
  node_pointer __find(const key_type& k) const {
    // TODO うまくinsertと共通化したい
    if (__empty()) {
      LOG(ERROR) << "__find/ not found";
      return NULL;
    }
    // ノードを辿って適切な場所にノードを作成
    node_pointer prev_parent = root_;
    node_pointer nd = root_;
    while (true) {
      if (k < nd->value.first) {
        nd = nd->left;
      } else if (k > nd->value.first) {
        nd = nd->right;
      } else {
        LOG(ERROR) << "__find/ found";
        break;
      }
      if (nd == NULL) {
        LOG(ERROR) << "__find/ not found";
        return NULL;
      }
      prev_parent = nd;
    }
    return nd;
  }

  // rootを返す
  node_pointer root() { return root_; }

private:
  node_allocator node_alloc_;
  node_pointer root_;

  // TODO tree_baseみたいなの作ってnodeいじるメソッドはそっちに移動させたい
  // nodeをアロケーションする
  node_pointer __allocate_node(const_reference v) {
    // node_pointer n = node_alloc_.allocate(1);

    // n->value = v;
    // n->left = NULL;
    // n->right = NULL;
    // n->parent = NULL;

    node_pointer n = node_alloc_.allocate(1);
    node_alloc_.construct(n, v);
    if (n == NULL) {
      LOG(ERROR) << "__tree/__allocate_node pointer is null";
    }
    return n;
  }

  void __deallocate_node() {
    // TODO ノードを辿って全部メモリを解放する
    node_alloc_.deallocate(root_, 1);
  }
};
}; // namespace ft

#endif
