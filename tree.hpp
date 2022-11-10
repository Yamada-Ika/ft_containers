#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include "deque.hpp"
#include "pair.hpp"
#include "utils.hpp"
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
  static node_pointer __get_min_node(node_pointer nd) {
    while (nd->left != NULL) {
      nd = nd->left;
    }
    return nd;
  }
  static node_pointer __get_max_node(node_pointer nd, node_pointer end) {
    while (nd->right != NULL && nd->right != end) {
      nd = nd->right;
    }
    return nd;
  }

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

// tree用のイテレータ
// ・イテレータをnextするアルゴリズム
// 　・なかったら
// 　　・左の子があるかチェックし、なかったらすでにそこ以下のノードは訪れているのでparentを辿る
// 　　・左の子があるノードにたどり着く。左の子以下のノードはすでに訪れているので親を返す
template <typename T, typename Allocator>
struct __tree_iterator {
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
  typedef __tree_iterator<T, Allocator> Self;
  typedef typename __node<T, Allocator>::node_pointer __node_pointer;

  // constructor
  __tree_iterator() : __node_pointer_(NULL), __end_node_(NULL) {}
  explicit __tree_iterator(const __node_pointer& bgn, const __node_pointer& end)
      : __node_pointer_(bgn), __end_node_(end) {}
  __tree_iterator(const Self& other) { *this = other; }
  Self& operator=(const Self& other) {
    if (this == &other) {
      return *this;
    }
    // TODO メモリ解放しないといけないかも？
    __node_pointer_ = other.__node_pointer_;
    __end_node_ = other.__end_node_;
    return *this;
  }

  reference operator*() const { return __node_pointer_->value; }
  pointer operator->() const { return &__node_pointer_->value; }
  Self& operator++() {
    __node_pointer_ = __next_node(__node_pointer_);
    return *this;
  }
  Self operator++(int) {
    Self tmp = *this;
    operator++();
    return tmp;
  }
  Self& operator--() {
    __node_pointer_ = __prev_node(__node_pointer_);
    return *this;
  }
  Self operator--(int) {
    Self tmp = *this;
    operator--();
    return tmp;
  }

  __node_pointer __next_node(__node_pointer nd) {
    // 　右の子がある場合
    // 　- 右の子を根とする部分木の一番左下の子を返す
    if (nd->right != NULL) {
      return __node<T, Allocator>::__get_min_node(nd->right);
    }
    // 左の子がいるノードまで親を辿る
    while (nd->left == NULL) {
      nd = nd->parent;
    }
    // 左の子以下のノードはすでに訪れているので親に移動
    return nd->parent;
  }

  __node_pointer __prev_node(__node_pointer nd) {
    // TODO end nodeなら親を返すだけで良い
    if (nd == __end_node_) {
      return nd->parent;
    }
    // 左の子がある場合
    // - 左の子を根とする部分木の一番右したの子を返す
    if (nd->left != NULL) {
      return __node<T, Allocator>::__get_max_node(nd->left, __end_node_);
    }
    // 右の子がいるノードまで親を辿る
    while (nd->right == NULL) {
      nd = nd->parent;
      LOG(ERROR) << "__prev_node/ loop";
    }
    // 以下のノードは訪れているので親を返す
    return nd->parent;
  }

  friend bool operator==(const Self& lhs, const Self& rhs) {
    return *lhs == *rhs;
  }
  friend bool operator!=(const Self& lhs, const Self& rhs) {
    return !(lhs == rhs);
  }

private:
  __node_pointer __node_pointer_;
  __node_pointer __end_node_;
};

// 二分探索木を表すクラス
template <typename Key, typename Val, typename KeyOfValue,
          class Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
class __tree {
public:
  // typedef Key value_type;
  typedef Key key_type;
  typedef Val value_type;
  // typedef ft::pair<const Key, Val> value_type;
  typedef Compare key_compare;
  typedef std::size_t size_type;
  typedef Allocator allocator_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  // typedef __node<Key, Allocator> node;
  typedef __node<value_type, Allocator> node;
  typedef typename Allocator::template rebind<node>::other node_allocator;
  typedef typename node::node_pointer node_pointer;
  typedef __tree_iterator<value_type, Allocator> iterator;
  typedef const iterator const_iterator;
  typedef typename std::reverse_iterator<iterator> reverse_iterator;
  typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

  __tree()
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(__allocate_node(Val())) {}
  explicit __tree(const Compare& comp, const Allocator& alloc = Allocator())
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(__allocate_node(Val())), __comp_(comp) {}
  // : root_(NULL), end_node_(__allocate_node(pair<Key, Val>(Key(), Val()))) {}
  // TODO メモリ解放したらクラッシュする
  ~__tree() {}

  // TODO テキトー
  iterator __begin() { return iterator(__begin_node(), __end_node()); }
  const_iterator __begin() const {
    return iterator(__begin_node(), __end_node());
  }
  iterator __end() { return iterator(__end_node(), __end_node()); }
  const_iterator __end() const { return iterator(__end_node(), __end_node()); }
  reverse_iterator __rbegin() {
    return reverse_iterator(iterator(__end_node(), __end_node()));
  }
  const_reverse_iterator __rbegin() const {
    return reverse_iterator(__end_node(), __end_node());
  }
  reverse_iterator __rend() {
    return reverse_iterator(iterator(__begin_node(), __end_node()));
  }
  const_reverse_iterator __rend() const {
    return reverse_iterator(iterator(__begin_node(), __end_node()));
  }

  node_pointer __end_node() const { return end_node_; }

  // 要素を追加
  // deprecated
  void __insert(const_reference value) {
    // 初めて要素を追加
    if (__empty()) {
      LOG(ERROR) << "__insert/ node is root";
      // TODO とりあえず左側に
      root_ = __allocate_node(value);
      root_->parent = root_; // TODO 根の親は自分自身を指しておく
      root_->right = __end_node(); // TODO 最後のイテレータのためだけにつける
      root_->right->parent = root_;
      return;
    }
    LOG(ERROR) << "__insert/ node is not root";
    // ノードを辿って適切な場所にノードを作成
    node_pointer prev_parent = root_;
    node_pointer nd = root_;
    while (true) {
      // keyで比較
      LOG(ERROR) << "value  first " << KeyOfValue()(value);
      LOG(ERROR) << "nd val first " << KeyOfValue()(nd->value);
      if (KeyOfValue()(value) < KeyOfValue()(nd->value)) {
        nd = nd->left;
        if (nd == NULL) {
          prev_parent->left = __allocate_node(value);
          prev_parent->left->parent = prev_parent; // TODO 親をつける
          break;
        }
      } else if (KeyOfValue()(value) > KeyOfValue()(nd->value)) {
        nd = nd->right;
        // if (nd == NULL) {
        if (nd == __end_node()) {
          prev_parent->right = __allocate_node(value);
          prev_parent->right->parent = prev_parent; // TODO 親をつける
          // TODO 最後のイテレータのためだけにつける
          prev_parent->right->right = __end_node();
          prev_parent->right->right->parent = prev_parent->right;
          break;
        }
        // TODO rightがend nodeじゃない時もある
        if (nd == NULL) {
          prev_parent->right = __allocate_node(value);
          prev_parent->right->parent = prev_parent; // TODO 親をつける
          break;
        }
      } else {
        // すでに存在していたら、重複を許さないので何もしない
        // ただvalueを更新する必要がある。実はない？
        // nd->value.second = value.second;
        break;
      }
      LOG(ERROR) << "__insert/ update prev node";
      prev_parent = nd;
    }
  }

  ft::pair<iterator, bool> __insert_alt(const_reference value) {
    node_pointer inserted_node = NULL;
    bool has_inserted = false;

    // 初めて要素を追加
    if (__empty()) {
      LOG(ERROR) << "__insert/ node is root";
      // TODO とりあえず左側に
      root_ = __allocate_node(value);
      root_->parent = root_; // TODO 根の親は自分自身を指しておく
      root_->right = __end_node(); // TODO 最後のイテレータのためだけにつける
      root_->right->parent = root_;

      inserted_node = root_;
      has_inserted = true;
      return ft::make_pair(iterator(inserted_node, __end_node()), has_inserted);
    }
    // ノードを辿って適切な場所にノードを作成
    node_pointer prev_parent = root_;
    node_pointer nd = root_;
    while (true) {
      if (KeyOfValue()(value) < KeyOfValue()(nd->value)) {
        nd = nd->left;
        if (nd == NULL) {
          prev_parent->left = __allocate_node(value);
          prev_parent->left->parent = prev_parent; // TODO 親をつける

          inserted_node = prev_parent->left;
          has_inserted = true;
          break;
        }
      } else if (KeyOfValue()(value) > KeyOfValue()(nd->value)) {
        nd = nd->right;
        if (nd == __end_node()) {
          prev_parent->right = __allocate_node(value);
          prev_parent->right->parent = prev_parent; // TODO 親をつける
          // TODO 最後のイテレータのためだけにつける
          prev_parent->right->right = __end_node();
          prev_parent->right->right->parent = prev_parent->right;
          break;
        }
        // TODO rightがend nodeじゃない時もある
        if (nd == NULL) {
          prev_parent->right = __allocate_node(value);
          prev_parent->right->parent = prev_parent; // TODO 親をつける

          inserted_node = prev_parent->right;
          has_inserted = true;
          break;
        }
      } else {
        has_inserted = false;
        break;
      }
      prev_parent = nd;
    }

    return ft::make_pair(iterator(inserted_node, __end_node()), has_inserted);
  }

  // // TODO 適当
  // void __insert(key_type k, mapped_type v) {
  //   value_type val(k, v);
  //   __insert(val);
  // }

  // ノードの要素を返す
  size_type __size() const {
    LOG(ERROR) << "__size called";
    if (root_ == NULL) {
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
        q.push_back(nd->left);
      }
      if (nd->right != __end_node() && nd->right != NULL) {
        q.push_back(nd->right);
      }
    }
    return sz;
  }

  // TODO sizeはカウントしなくても良さそうだけど
  bool __empty() const { return root_ == NULL; }

  // iterator返すfind
  iterator __find(const key_type& key) {
    iterator target = __lower_bound(key);
    // 見つからなかったか
    if (target == __end()) {
      return __end();
    }
    // keyと一致しているか
    if (KeyOfValue()(*target) == key) {
      return target;
    }
    // 一致してない == 見つからなかった
    return __end();
  }
  const_iterator __find(const key_type& key) const {
    const_iterator target = __lower_bound(key);
    // 見つからなかったか
    if (target == __end()) {
      return __end();
    }
    // keyと一致しているか
    if (KeyOfValue()(*target) == key) {
      return target;
    }
    // 一致してない == 見つからなかった
    return __end();
  }

  // lower_bound　
  // keyと一緒か大きい最初？一番近いイテレータを返す
  iterator __lower_bound(const Key& key) {
    node_pointer ptr = __lower_bound_pointer(key);
    if (ptr == NULL) {
      return __end();
    }
    return iterator(ptr, __end_node());
  }
  const_iterator __lower_bound(const Key& key) const {
    node_pointer ptr = __lower_bound_pointer(key);
    if (ptr == NULL) {
      return __end();
    }
    return const_iterator(ptr, __end_node());
  }

  node_pointer __lower_bound_pointer(const Key& k) const {
    // TODO うまくinsertと共通化したい
    if (__empty()) {
      return NULL;
    }
    // ノードを辿って適切な場所にノードを作成
    node_pointer prev_parent = root_;
    node_pointer nd = root_;
    while (true) {
      if (k < KeyOfValue()(nd->value)) {
        nd = nd->left;
      } else if (k > KeyOfValue()(nd->value)) {
        nd = nd->right;
      } else {
        LOG(ERROR) << "__find/ found";
        break;
      }
      if (nd == NULL || nd == end_node_) {
        LOG(ERROR) << "__find/ not found";
        // ここで一個前のノードの値をチェック
        // k > nd->valueならそのノードを返す
        if (k < KeyOfValue()(prev_parent->value)) {
          return prev_parent;
        }
        return NULL;
      }
      prev_parent = nd;
    }
    return nd;
  }

  // upper bound
  // lower boundの不等号変わったやつ
  iterator __uppper_bound(const Key& k) {
    node_pointer ptr = __upper_bound_pointer(k);
    if (ptr == NULL) {
      return __end();
    }
    return iterator(ptr, __end_node());
  }
  const_iterator __upper_bound(const Key& k) {
    node_pointer ptr = __upper_bound_pointer(k);
    if (ptr == NULL) {
      return __end();
    }
    return const_iterator(ptr, __end_node());
  }

  node_pointer __upper_bound_pointer(const Key& k) {
    // TODO うまくinsertと共通化したい
    if (__empty()) {
      return NULL;
    }
    // ノードを辿って適切な場所にノードを作成
    node_pointer prev_parent = root_;
    node_pointer nd = root_;
    while (true) {
      if (k < KeyOfValue()(nd->value)) {
        nd = nd->left;
      } else if (k > KeyOfValue()(nd->value)) {
        nd = nd->right;
      } else {
        // upper boundはkeyが一致するノードを検索対象に含まない
        // より大きい値を持つノードを訪ねるために右の子に移動
        nd = nd->right;
      }
      if (nd == NULL || nd == end_node_) {
        LOG(ERROR) << "__find/ not found";
        // ここで一個前のノードの値をチェック
        if (k < KeyOfValue()(prev_parent->value)) {
          return prev_parent;
        }
        return NULL;
      }
      prev_parent = nd;
    }
    return nd;
  }

  // count
  size_type __count(const Key& key) const {
    return __find(key) == __end() ? 0 : 1;
  }

  // max_size
  size_type __max_size() const { return node_alloc_.max_size(); }

  // rootを返す
  node_pointer root() { return root_; }

  // allocatorを返す
  allocator_type __get_allocator() const { return allocator_type(node_alloc_); }
  // key_compareを返す
  key_compare __key_comp() const { return __comp_; }

private:
  node_allocator node_alloc_;
  node_pointer root_;
  node_pointer end_node_;
  key_compare __comp_;

  // TODO tree_baseみたいなの作ってnodeいじるメソッドはそっちに移動させたい
  // nodeをアロケーションする
  node_pointer __allocate_node(const_reference v) {
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

  node_pointer __begin_node() const { return node::__get_min_node(root_); }
};
}; // namespace ft

#endif
