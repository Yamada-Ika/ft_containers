#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include "deque.hpp"
#include "stack.hpp"
#include "pair.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"
#include <functional>
#include <limits>

namespace ft {

// 木のノードを表すクラス
template <typename T, typename Allocator>
class __node {
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::template rebind<__node>::other node_allocator;
  typedef node_allocator allocator_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef pointer iterator;
  typedef const_pointer __const_iterator;
  typedef __node Self;
  typedef __node* node_pointer;

  enum __kind { BLACK = 1, RED, NIL };

  node_pointer left;
  node_pointer right;
  node_pointer parent;
  value_type value;
  int __node_kind_;

  __node()
      : left(NULL), right(NULL), parent(NULL), value(value_type()),
        __node_kind_(0), node_alloc(node_allocator()) {}
  __node(const_reference v)
      : left(NULL), right(NULL), parent(NULL), value(v), __node_kind_(0),
        node_alloc(node_allocator()) {}
  ~__node() {}
  __node(const __node& other) { *this = other; }
  __node& operator=(const __node& other) {
    if (this == &other) {
      return *this;
    }

    // TODO コピー用の関数作る。適当
    left = other.left;
    right = other.right;
    parent = other.parent;
    // value = other.value;
    node_alloc = other.node_alloc;
    __node_kind_ = other.__node_kind_;
    return *this;
  }

  bool __is_black_node() { return __node_kind_ & (1 << BLACK); }
  bool __is_red_node() { return __node_kind_ & (1 << RED); }
  bool __is_nil_node() {
    return __is_black_node() && __node_kind_ & (1 << NIL);
  }
  void __set_black_kind() { __node_kind_ = 1 << BLACK; }
  void __set_red_kind() { __node_kind_ = 1 << RED; }
  void __set_nil_kind() { __node_kind_ = (1 << BLACK) | (1 << NIL); }
  int __get_node_kind() { return __node_kind_; }
  void __set_node_kind(int k) { __node_kind_ = k; }

private:
  allocator_type node_alloc;
};

/*
 * ノードを扱う関数群
*/
template <typename NodePtr>
static NodePtr __get_min_node(NodePtr node) {
  while (!node->__is_nil_node()) {
    node = node->left;
  }
  return node->parent;
}

template <typename NodePtr>
static NodePtr __get_max_node(NodePtr node) {
  while (!node->__is_nil_node()) {
    node = node->right;
  }
  return node->parent;
}

// - 一回だけ親を辿る時
//   - 両方子がいない
//   - 左だけ子がいる
// - 2回親を辿る時
//   - 親の右側に子がいる時

template <typename NodePtr>
static NodePtr __next_node(NodePtr node, NodePtr end_node) {
  // TODO end nodeなら親を返すだけで良い
  if (node->right == end_node) {
    return end_node;
  }

  // 　右の子がある場合
  // 　- 右の子を根とする部分木の一番左下の子を返す
  if (!node->right->__is_nil_node()) {
    return __get_min_node(node->right);
  }

  // // 左の子がいるノードまで親を辿る
  NodePtr p = node->parent;

  // 今いるノードが親の右側にあると辿る
  while (node == p->right) {
    node = node->parent;
    p = node->parent;
  }

  return node->parent;
}

template <typename NodePtr>
static NodePtr __prev_node(NodePtr node, NodePtr end_node) {
  // TODO end nodeなら親を返すだけで良い
  if (node == end_node) {
    return node->parent;
  }
  // 左の子がある場合
  // - 左の子を根とする部分木の一番右したの子を返す
  if (!node->left->__is_nil_node()) {
    return __get_max_node(node->left);
  }
  // 右の子がいるノードまで親を辿る
  NodePtr p = node->parent;

  // 今いるノードが親の右側にあると辿る
  while (node == p->left) {
    node = node->parent;
    p = node->parent;
  }

  // 以下のノードは訪れているので親を返す
  return node->parent;
}

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
    __node_pointer_ = __next_node(__node_pointer_, __end_node_);
    return *this;
  }
  Self operator++(int) {
    Self tmp = *this;
    operator++();
    return tmp;
  }
  Self& operator--() {
    __node_pointer_ = __prev_node(__node_pointer_, __end_node_);
    return *this;
  }
  Self operator--(int) {
    Self tmp = *this;
    operator--();
    return tmp;
  }

  friend bool operator==(const Self& lhs, const Self& rhs) {
    return lhs.__node_pointer_ == rhs.__node_pointer_;
  }
  friend bool operator!=(const Self& lhs, const Self& rhs) {
    return !(lhs == rhs);
  }

  __node_pointer __node_pointer_;
  __node_pointer __end_node_;
};

// const用のイテレータ
template <typename T, typename Allocator>
struct __const_tree_iterator {
  typedef T value_type;
  typedef const T& reference;
  typedef T* pointer;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
  typedef __const_tree_iterator<T, Allocator> Self;
  typedef typename __node<T, Allocator>::node_pointer __node_pointer;
  typedef __tree_iterator<T, Allocator> __non_const_iterator;

  // constructor
  __const_tree_iterator() : __node_pointer_(NULL), __end_node_(NULL) {}
  explicit __const_tree_iterator(const __node_pointer& bgn,
                                 const __node_pointer& end)
      : __node_pointer_(bgn), __end_node_(end) {}
  __const_tree_iterator(const Self& other) { *this = other; }
  Self& operator=(const Self& other) {
    if (this == &other) {
      return *this;
    }
    // TODO メモリ解放しないといけないかも？
    __node_pointer_ = other.__node_pointer_;
    __end_node_ = other.__end_node_;
    return *this;
  }
  __const_tree_iterator(__non_const_iterator itr)
      : __node_pointer_(itr.__node_pointer_), __end_node_(itr.__end_node_) {}

  reference operator*() const { return __node_pointer_->value; }
  pointer operator->() const { return &__node_pointer_->value; }
  Self& operator++() {
    __node_pointer_ = __next_node(__node_pointer_, __end_node_);
    return *this;
  }
  Self operator++(int) {
    Self tmp = *this;
    operator++();
    return tmp;
  }
  Self& operator--() {
    __node_pointer_ = __prev_node(__node_pointer_, __end_node_);
    return *this;
  }
  Self operator--(int) {
    Self tmp = *this;
    operator--();
    return tmp;
  }

  friend bool operator==(const Self& lhs, const Self& rhs) {
    return *lhs == *rhs;
  }
  friend bool operator!=(const Self& lhs, const Self& rhs) {
    return !(lhs == rhs);
  }

  __node_pointer __node_pointer_;
  __node_pointer __end_node_;
};

// 二分探索木を表すクラス
template <typename Key, typename Val, typename KeyOfValue,
          class Compare = ft::less<Key>,
          typename Allocator = std::allocator<Key> >
class __tree {
public:
  typedef Key key_type;
  typedef Val value_type;
  typedef Compare key_compare;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Allocator allocator_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef __node<value_type, Allocator> node;
  typedef typename Allocator::template rebind<node>::other node_allocator;
  typedef typename node::node_pointer node_pointer;
  typedef __tree_iterator<value_type, Allocator> iterator;
  typedef __const_tree_iterator<value_type, Allocator> __const_iterator;
  typedef typename ft::reverse_iterator<iterator> reverse_iterator;
  typedef typename ft::reverse_iterator<__const_iterator>
      __const_reverse_iterator;

  __tree()
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(__allocate_end_node()), __tree_size_(0) {}
  __tree(iterator first, iterator last)
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(__allocate_end_node()), __tree_size_(0) {
    __insert(first, last);
  }
  explicit __tree(const Compare& comp, const Allocator& alloc = Allocator())
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(__allocate_end_node()), __comp_(comp), __tree_size_(0) {}
  // : root_(NULL), end_node_(__allocate_node(pair<Key, Val>(Key(), Val()))) {}
  // TODO メモリ解放したらクラッシュする
  ~__tree() {
    destruct_tree();
    destruct_node(end_node_);
  }

  /*
   * Iterators
  */
  iterator __begin() { return iterator(__begin_node(), __end_node()); }
  __const_iterator __begin() const {
    return __const_iterator(__begin_node(), __end_node());
  }
  iterator __end() { return iterator(__end_node(), __end_node()); }
  __const_iterator __end() const {
    return __const_iterator(__end_node(), __end_node());
  }
  reverse_iterator __rbegin() {
    return reverse_iterator(iterator(__end_node(), __end_node()));
  }
  __const_reverse_iterator __rbegin() const {
    return __const_reverse_iterator(
        __const_iterator(__end_node(), __end_node()));
  }
  reverse_iterator __rend() {
    return reverse_iterator(iterator(__begin_node(), __end_node()));
  }
  __const_reverse_iterator __rend() const {
    return __const_reverse_iterator(
        __const_iterator(__begin_node(), __end_node()));
  }

  node_pointer __end_node() const { return end_node_; }

  /*
   * Capacity
  */
  size_type __size() const { return __tree_size_; }
  bool __empty() const { return __size() == 0; }
  size_type __max_size() const {
    return ft::min<size_type>(node_alloc_.max_size(),
                              std::numeric_limits<difference_type>::max());
  }

  /*
   * Modifiers
  */
  ft::pair<iterator, bool> __insert(const_reference value) {
    ft::pair<iterator, bool> p = __insert_helper(value);
    if (p.second) {
      ++__tree_size_;
    }
    return p;
  }

  iterator __insert(iterator pos, const_reference value) {
    // TODO テキトー
    // posの直前に要素を挿入
    return __insert(value).first;
  }

  void __insert(iterator first, iterator last) {
    for (iterator itr = first; itr != last; ++itr) {
      __insert(*itr);
    }
  }

  size_type __erase(const Key& key) {
    if (__erase_helper(key) == 1) {
      --__tree_size_;
      return 1;
    }
    return 0;
  }

  iterator __erase(iterator pos) {
    iterator res = pos;
    ++res;
    __erase(KeyOfValue()(*pos));
    return res;
  }

  iterator __erase(iterator first, iterator last) {
    for (; first != last;) {
      first = __erase(first);
    }
    return last;
  }

  /*
   * Lookup
  */
  size_type __count(const Key& key) const {
    return __find(key) == __end() ? 0 : 1;
  }

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
  __const_iterator __find(const key_type& key) const {
    __const_iterator target = __lower_bound_const(key);
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

  // equal_range
  ft::pair<iterator, iterator> __equal_range(const Key& key) {
    return ft::make_pair(__lower_bound(key), __uppper_bound(key));
  }
  ft::pair<__const_iterator, __const_iterator>
  __equal_range_const(const Key& key) const {
    return ft::make_pair(__lower_bound_const(key), __upper_bound_const(key));
  }

  // lower_bound　
  iterator __lower_bound(const Key& key) {
    node_pointer ptr = __lower_bound_pointer(key);
    if (ptr == NULL) {
      return __end();
    }
    return iterator(ptr, __end_node());
  }
  __const_iterator __lower_bound_const(const Key& key) const {
    node_pointer ptr = __lower_bound_pointer(key);
    if (ptr == NULL) {
      return __end();
    }
    return __const_iterator(ptr, __end_node());
  }

  // upper bound
  iterator __uppper_bound(const Key& k) {
    iterator itr = __lower_bound(k);

    // itrがendの場合、見つかってないのでendを返す
    if (itr == __end()) {
      return __end();
    }

    // itrのkeyとkが同じの場合、インクリメントしたイテレータを返す
    if (k == KeyOfValue()(*itr)) {
      return ++itr;
    }

    // itrのkeyはkより大きいのでそのまま返す
    return itr;
  }
  __const_iterator __upper_bound_const(const Key& k) const {
    __const_iterator itr = __lower_bound_const(k);

    // itrがendの場合、見つかってないのでendを返す
    if (itr == __end()) {
      return __end();
    }

    // itrのkeyとkが同じの場合、インクリメントしたイテレータを返す
    if (k == KeyOfValue()(*itr)) {
      return ++itr;
    }

    // itrのkeyはkより大きいのでそのまま返す
    return itr;
  }

  /*
   * Lookup
  */
  key_compare __key_comp() const { return __comp_; }

  // rootを返す
  // For testable
  node_pointer root() { return root_; }

  // allocatorを返す
  allocator_type __get_allocator() const { return allocator_type(node_alloc_); }

  // TODO とりあえず木の中で使ってるfind。ノードポインターを返す
  node_pointer __find_node_pointer(const key_type& key) const {
    node_pointer target = __lower_bound_pointer(key);
    // 見つからなかった
    if (target == NULL) {
      return NULL;
    }
    // 値が一致しているか
    if (KeyOfValue()(target->value) == key) {
      return target;
    }
    // 一致していないのでNULL
    return NULL;
  }

private:
  node_allocator node_alloc_;
  node_pointer root_;
  node_pointer end_node_;
  key_compare __comp_;
  size_type __tree_size_;

  void destruct_tree() { destruct_partial_tree(root_); }
  void destruct_partial_tree(node_pointer n) {
    ft::stack<node_pointer> st;
    node_pointer nd = n;
    st.push(nd);
    while (true) {
      nd = st.top();
      st.pop();
      if (nd == end_node_) {
        continue;
      }
      if (nd == NULL) {
        if (st.empty()) {
          break;
        }
        continue;
      }
      st.push(nd->left);
      st.push(nd->right);
      destruct_node(nd);
    }
  }
  void deallocate_node(node_pointer ptr) { node_alloc_.deallocate(ptr, 1); }
  void destroy_node(node_pointer ptr) { node_alloc_.destroy(ptr); }
  void destruct_node(node_pointer ptr) {
    destroy_node(ptr);
    deallocate_node(ptr);
  }
  void destruct_erased_node(node_pointer ptr) {
    // end_node_はメモリ解放しなくて良い
    if (ptr->right != NULL && ptr->right->__is_nil_node() &&
        ptr->right != end_node_) {
      std::cerr << "destruct_erased_node/ deallocate right nil node"
                << std::endl;
      destroy_node(ptr->right);
      deallocate_node(ptr->right);
    }
    if (ptr->left != NULL && ptr->left->__is_nil_node()) {
      std::cerr << "destruct_erased_node/ deallocate left nil node"
                << std::endl;
      destroy_node(ptr->left);
      deallocate_node(ptr->left);
    }
    destroy_node(ptr);
    deallocate_node(ptr);
  }

  // rootかどうか
  bool __is_root(node_pointer nd) { return nd->parent == nd; }

  // TODO tree_baseみたいなの作ってnodeいじるメソッドはそっちに移動させたい
  node_pointer __allocate() {
    node_pointer n = node_alloc_.allocate(1);
    return n;
  }

  // nodeをアロケーションする
  node_pointer __allocate_node(const_reference v) {
    node_pointer n = __allocate();
    node_alloc_.construct(n, v);
    if (n == NULL) {
    }
    return n;
  }

  node_pointer __allocate_end_node() { return __allocate_nil_node(); }

  node_pointer __allocate_nil_node() {
    node_pointer n = __allocate();
    node_alloc_.construct(n, value_type());
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->__set_nil_kind();
    return n;
  }

  void __attach_nil_node_to_left(node_pointer nd) {
    node_pointer l = __allocate_nil_node();
    l->parent = nd;
    nd->left = l;
  }

  void __attach_nil_node_to_right(node_pointer nd) {
    node_pointer r = __allocate_nil_node();
    r->parent = nd;
    nd->right = r;
  }

  void __attach_nil_nodes(node_pointer nd) {
    __attach_nil_node_to_left(nd);
    __attach_nil_node_to_right(nd);
  }

  void __attach_end_node(node_pointer nd) {
    __attach_node_to_right(nd, end_node_);
  }

  void __attach_node_to_left(node_pointer parent, node_pointer child) {
    parent->left = child;
    child->parent = parent;
  }
  void __attach_node_to_right(node_pointer parent, node_pointer child) {
    parent->right = child;
    child->parent = parent;
  }

  void __exchange_node_color(node_pointer node1, node_pointer node2) {
    int k = node1->__get_node_kind();
    node1->__set_node_kind(node2->__get_node_kind());
    node2->__set_node_kind(k);
  }

  void __deallocate_node() {
    // TODO ノードを辿って全部メモリを解放する
    node_alloc_.deallocate(root_, 1);
  }

  node_pointer __begin_node() const {
    // TODO　何も値がないときはend nodeを返す？
    if (__empty()) {
      return __end_node();
    }
    return __get_min_node(root_);
  }

  size_type __erase_helper(const Key& key) {
    node_pointer target = __find_node_pointer(key);
    return __erase_node_pointer(target);
  }

  // 以下の条件を満たすようにする
  // 1. ノードは赤か黒である
  // 2. 根は黒である
  // 3. 全ての葉は黒である
  // 4. 赤いノードの子は黒である
  // 5. 全ての葉から根までのパスには、同じ個数の黒いノードがある

  size_type __erase_node_pointer(node_pointer n) {
    // keyがなかったら0を返す
    if (n == NULL) {
      return 0;
    }

    node_pointer cl = n->left;
    node_pointer cr = n->right;

    // TODO 要素がrootだけの時
    if (n == n->parent && cl->__is_nil_node() && cr->__is_nil_node()) {
      destruct_erased_node(root_);
      root_ = NULL;
      return 1;
    }

    if ((cl->__is_nil_node() && cr->__is_nil_node()) ||
        (!cl->__is_nil_node() && cr->__is_nil_node()) ||
        (cl->__is_nil_node() && !cr->__is_nil_node())) {
      return __erase_node_with_one_or_zero_child(n);
    }

    // 子を2つ持つ
    node_pointer partial_min = __get_min_node(n->right);
    // targetとpartial_minを入れ替える
    __exchange_node(n, partial_min);
    // 削除対象のtargetは子を一つ持つ or いないはず。
    // 再帰して削除処理を委譲する
    return __erase_node_pointer(n);
  }

  // Nの子はNULL
  size_type __erase_no_child(node_pointer n) {
    node_pointer p = n->parent;
    node_pointer nr = n->right;

    // Nがrootの場合
    if (n->parent == n) {
      root_ = NULL;
    } else {
      if (n == p->left) {
        p->left = nr;
      } else {
        p->right = nr;
      }
    }

    // nr->parent = p;
    return 1;
  }

  size_type __rebalance_when_erase(node_pointer n) {
    // あとは、targetと子供が黒の場合
    // - 黒を削除すると、条件5を満たすためにリバランスが必要
    // - 形状は以下の2ケースを考える
    //  - 最終的には一つの形状に変形していき、処理を委譲する

    // case 1
    // - Nがrootだと葉から根までの全パスから黒ノードが一つ減るだけなので条件5を破らない
    // - 子をrootに持ってくるだけで良い
    if (n->parent == n) {
      return 1;
    }

    //        P
    //  +-----+------+
    // N             S
    //           +---+---+
    //          SL      SR

    node_pointer p = n->parent;
    node_pointer s = NULL;

    if (p->left == n) {
      s = p->right;
    } else {
      s = p->left;
    }

    node_pointer sl = s->left;
    node_pointer sr = s->right;

    sl->parent = s;
    sr->parent = s;

    // (i)                      (ii)
    //        P                            P
    //  +-----+------+               +-----+-----+
    // Nb            S       or      S           N
    //           +---+---+       +---+---+
    //          SL      SR      SL       SR

    // case 2
    // - Sが赤の場合
    //  - SLとSRは黒

    //        Pb                         Sr                     Sb
    //  +-----+------+             +-----+-----+          +-----+-----+
    // Nb            Sr     ->     Pb         SRb  ->     Pr         SRb
    //           +---+---+     +---+---+              +---+---+
    //          SLb     SRb    Nb     SLb             Nb     SLb

    // 形状が(i)の場合
    if (s->__is_red_node() && sl->__is_black_node() && sr->__is_black_node() &&
        p->left == n && p->right == s) {
      // Pを中心に左回転する
      __rotate_left(p, s);
      // SとPの色を交換する
      __exchange_node_color(s, p);
      // case 4以降に委譲するためノードを再命名
      s = p->right;
      s->parent = p;
      sl = s->left;
      sl->parent = s;
      sr = s->right;
      sr->parent = s;
    }

    // 形状が(ii)の場合
    if (s->__is_red_node() && sl->__is_black_node() && sr->__is_black_node() &&
        p->left == s && p->right == n) {
      // Pを中心に右回転する
      __rotate_right(p, s);
      // SとPの色を交換する
      __exchange_node_color(s, p);
      // case 4以降に委譲するためノードを再命名
      s = p->left;
      s->parent = p;
      sl = s->left;
      sl->parent = s;
      sr = s->right;
      sr->parent = s;
    }

    // case 3
    // - 全部黒色
    //               Pb                          Pb
    //         +-----+-----+               +-----+-----+
    //        Nb           Sb      ->     Nb           Sr
    //                 +---+---+                   +---+---+
    //                SLb     SRb                 SLb     SRb
    if (n->__is_black_node() && p->__is_black_node() && s->__is_black_node() &&
        sl->__is_black_node() && sr->__is_black_node()) {
      // Sを赤に塗り替える
      // - NからP、SL or SRからPまでのパスで黒ノードの数が等しくなるので、部分的に条件5を満たす
      s->__set_red_kind();
      // Pからの深さで黒ノードを一つ減らしたため、他の部分で色の調整を行いたいため、再帰する
      return __rebalance_when_erase(p);
    }

    // case 4
    // - Pが赤、SLが黒、SRが黒
    if (n->__is_black_node() && p->__is_red_node() && s->__is_black_node() &&
        sl->__is_black_node() && sr->__is_black_node()) {
      // PとSの色を入れ替える
      __exchange_node_color(p, s);
      return 1;
    }

    // case 5
    // - Pの色はどっちでも良い

    //        P                             P
    //  +-----+------+                +-----+-----+
    // Nb            Sb       ->      Nb          SLb
    //           +---+---+                    +---+---+
    //          SLr     SRb                  (1)      Sr
    //       +---+---+                            +---+---+
    //      (1)     (2)                          (2)     SRb

    // SLが赤、SRが黒、NがPの左側の子供の場合
    if (n == p->left && n->__is_black_node() && s->__is_black_node() &&
        sl->__is_red_node() && sr->__is_black_node()) {
      // Sを中心に右回転
      __rotate_right(s, sl);
      // SLとSの色を入れ替える
      __exchange_node_color(sl, s);
      // case 6に合わせてノードを再命名する
      s = p->right;
      s->parent = p;
      sl = s->left;
      sl->parent = s;
      sr = s->right;
      sr->parent = s;
    }

    //       　   　　　　  P                              　 P
    //　　　   　　　  +-----+-----+                    +-----+-----+
    //       Sb           Nb                  SRb          Nb
    //   +---+---+              ->        +---+---+
    //  SLb     SRr                      Sr      (1)
    //       +---+---+               +---+---+
    //      (1)     (2)             SLb     (2)
    // SLが黒、SRが赤、NがPの右側の子
    if (n == p->right && n->__is_black_node() && s->__is_black_node() &&
        sl->__is_black_node() && sr->__is_red_node()) {
      // Sを中心に左回転
      __rotate_left(s, sr);
      // SRとSの色を入れ替える
      __exchange_node_color(sr, s);
      // case 6に合わせてノードを再命名する
      s = p->left;
      s->parent = p;
      sl = s->left;
      sl->parent = s;
      sr = s->right;
      sr->parent = s;
    }

    // case 6
    // - SRが赤、NがPの左側の子供

    //       　   　　　　  P                            　 S
    //　　　   　　　  +-----+-----+                  +-----+-----+
    //       Nb           Sb      ->         Pb          SRb
    //                +---+---+          +---+---+
    //               SL      SRr        Nb       SL
    if (n == p->left && n->__is_black_node() && s->__is_black_node() &&
        sr->__is_red_node()) {
      // Pを中心に左回転
      __rotate_left(p, s);
      // PとSの色を交換
      __exchange_node_color(p, s);
      // SRを黒に
      sr->__set_black_kind();
      return 1;
    }

    // - SLが赤、NがPの右側の子供
    if (n == p->right && n->__is_black_node() && s->__is_black_node() &&
        sl->__is_red_node()) {
      // Pを中心に右回転
      __rotate_right(p, s);
      // PとSの色を交換する
      __exchange_node_color(p, s);
      // SLを黒に
      sl->__set_black_kind();
      return 1;
    }
    return 1;
  }

  size_type __erase_node_with_one_or_zero_child(node_pointer target) {
    // case 0
    // - targetが赤
    //  - 条件4、5を破らないのでリバランスは不要
    if (target->__is_red_node()) {
      return __erase_own_and_replace_child(target);
    }

    // - targetが黒で子が赤
    //  - targetを子に置き換えて、黒に塗り替えるだけ
    node_pointer tl = target->left, tr = target->right;
    if (target->__is_black_node() &&
        ((tl->__is_nil_node() && tr->__is_red_node()) ||
         (tl->__is_red_node() && tr->__is_nil_node()))) {
      return __erase_own_and_repaint_after_replace_child(target);
    }

    //           P
    //       +---+---+
    //    target
    //  +---+---+
    //  N

    // replace
    node_pointer p = target->parent;
    node_pointer n = NULL;
    // Nはtargetの場所にくるノード
    if (!target->left->__is_nil_node()) {
      n = target->left;
    } else {
      n = target->right;
    }

    if (target == p->left) {
      p->left = n; // Nをtargetの場所に持ってくる
    } else {
      p->right = n;
    }
    n->parent = p;

    if (target->left == n) {
      if (target->right != end_node_) {
        destruct_node(target->right);
      }
    } else {
      destruct_node(target->left);
    }
    destruct_node(target);

    return __rebalance_when_erase(n);
  }

  //             P1
  //      +------+------+
  //      N1           (1)
  //  +---+---+     +---+---+
  // NL1     NR1   (2)      P2
  //                    +---+---+
  //                            N2
  //                        +---+---+
  //                       NL2     NR2
  void __exchange_node(node_pointer n1, node_pointer n2) {
    node_pointer p1 = n1->parent, nl1 = n1->left, nr1 = n1->right;
    node_pointer p2 = n2->parent, nl2 = n2->left, nr2 = n2->right;

    //              N1
    //       +------+------+
    //      N2            NR1
    //  +---+---+
    // NL2     NR2
    // TODO N1とN2が親子
    if (p2 == n1) {
      if (nl1 == n2) {
        if (n1 == root_) {
          root_ = n2;
          root_->parent = root_;
        } else {
          if (n1 == p1->left) {
            p1->left = n2;
          } else {
            p1->right = n2;
          }
          n2->parent = p1;
        }

        n2->right = nr1;
        nr1->parent = n2;
        n2->left = n1;
        n1->parent = n2;

        n1->left = nl2;
        nl2->parent = n1;
        n1->right = nr2;
        nr2->parent = n1;
      } else if (nr1 == n2) {
        //             N1
        //      +------+------+
        //     NL1            N2
        //                +---+---+
        //               NL2      NR2
        if (n1 == root_) {
          root_ = n2;
          root_->parent = root_;
        } else {
          if (n1 == p1->left) {
            p1->left = n2;
          } else {
            p1->right = n2;
          }
          n2->parent = p1;
        }

        n2->left = nl1;
        nl1->parent = n2;
        n2->right = n1;
        n1->parent = n2;

        n1->left = nl2;
        nl2->parent = n1;
        n1->right = nr2;
        nr2->parent = n1;
      }

      // TODO 色も交換する？
      __exchange_node_color(n1, n2);
      return;
    }

    // N2をN1の場所に持ってくる
    // N1がrootだった時
    if (n1 == root_) {
      root_ = n2;
      root_->parent = root_;
    } else {
      if (n1 == p1->left) {
        p1->left = n2;
      } else {
        p1->right = n2;
      }
      n2->parent = p1;
    }
    n2->left = nl1;
    nl1->parent = n2;
    n2->right = nr1;
    nr1->parent = n2;

    // N1をN2の場所に持ってくる
    if (n2 == p2->left) {
      p2->left = n1;
    } else {
      p2->right = n1;
    }
    n1->parent = p2;
    n1->left = nl2;
    nl2->parent = n1;
    n1->right = nr2;
    nr2->parent = n1;

    // TODO 色も交換する？
    __exchange_node_color(n1, n2);
  }

  //     n
  // +---+---+
  //         c
  size_type __erase_own_and_repaint_after_replace_child(node_pointer n) {
    // nのchildがnの場所に来る
    // あらかじめchildを覚えておき、削除した後に黒に塗り替える
    node_pointer c = NULL;
    if (!n->left->__is_nil_node()) {
      c = n->left;
    } else {
      c = n->right;
    }

    size_type ret = __erase_own_and_replace_child(n);

    // 黒に塗り替える
    c->__set_black_kind();

    return ret;
  }

  size_type __erase_own_and_replace_child(node_pointer target) {

    // - 形状の例
    //         P
    //     +---+
    //     N
    // +---+
    // C

    node_pointer p = target->parent;
    node_pointer n = target;
    node_pointer c = NULL;

    if (n->left->__is_nil_node() && n->right == __end_node()) {
      c = n->right;
    } else {
      if (!n->left->__is_nil_node()) {
        c = n->left;
      } else {
        c = n->right;
      }
    }

    // Nがroot
    if (n->parent == n) {
      //          N                     C
      //      +---+---+     ->      +---+---+
      //      C      nil           nil     nil
      //  +---+---+
      // nil     nil
      if (n->right == __end_node()) {
        destruct_node(c->right);
        c->right = __end_node();
        c->right->parent = c;
      } else {
        //      N                    C
        //  +---+---+     ->     +---+---+
        // nil      C           nil     nil
        //      +---+---+
        //     nil     nil
        destruct_node(n->left);
      }
      root_ = c;
      root_->parent = root_;
      destruct_node(n);
      return 1;
    }

    // NがPの左側にある場合
    if (n == p->left) {
      //              P                      P
      //          +---+---+              +---+---+
      //          N      nil    ->       C      nil
      //      +---+---+              +---+---+
      //      C      nil            nil     nil
      p->left = c;
    } else {
      // NがPの右側にある場合
      //       P                       P
      //   +---+---+               +---+---+
      //  nil      N      ->       C      nil
      //       +---+---+       +---+---+
      //       C      nil     nil     nil
      p->right = c;
    }
    c->parent = p;

    if (c == n->left) {
      if (n->right != end_node_) {
        destruct_node(n->right);
      }
    } else {
      destruct_node(n->left);
    }
    destruct_node(n);
    return 1;
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
      if (__comp_(k, KeyOfValue()(nd->value))) {
        nd = nd->left;
      } else if (__comp_(KeyOfValue()(nd->value), k)) {
        nd = nd->right;
      } else {
        break;
      }

      // TODO end nodeまで到達するとこれ以上のノードは存在しないので、見つからなかったとする
      if (nd == end_node_) {
        return NULL;
      }
      if (nd->__is_nil_node()) {
        // ここで一個前のノードの値をチェック
        // k > nd->valueならそのノードを返す
        if (__comp_(KeyOfValue()(nd->parent->value), k)) {
          return nd->parent->parent;
        }
        return nd->parent;
      }
      prev_parent = nd;
    }
    return nd;
  }

  // 以下の条件を満たすようにする
  // 1. ノードは赤か黒である
  // 2. 根は黒である
  // 3. 全ての葉は黒である
  // 4. 赤いノードの子は黒である
  // 5. 全ての葉から根までのパスには、同じ個数の黒いノードがある

  // insertした後のtreeのトポロジをリバランスする関数
  void __rebalance_tree(node_pointer n, node_pointer p) {
    node_pointer g;
    node_pointer u;

    // p : nの親
    // g : pの親
    // u : gの子
    //              g
    //       +------+------+
    //       p             u
    //   +---+---+
    //   n

    // case 1
    // - Nがroot
    if (__is_root(n)) {
      // 条件2より黒にする
      n->__set_black_kind();
      // ノードがrootしか存在しないので、全ての葉から根までのパスに黒いノードは1個のため条件5もクリア
      // TODO rootのparentをつける？
      return;
    }

    // - Pが黒
    if (p->__is_black_node()) {
      // Nは赤なので条件4はクリア。Nが挿入された場所は元々nilであるため、nilからrootまでのパスの黒ノードの数は変わらない
      // 従って条件5もクリア
      return;
    }

    // case 2
    // - Pが赤
    // Pが赤の場合、rootではないため、Gが存在する
    // 条件4よりGは黒である
    g = p->parent;
    // Uが赤か黒の場合が残っている
    // UとPはGの子
    if (p == g->left) {
      u = g->right;
    } else {
      u = g->left;
    }

    // - Uが赤
    if (u->__is_red_node()) {
      // Gは黒、その下層のPとUは赤である。色を交換して、Gを赤、PとUを黒にしても条件5を満たしたままのはず
      // Nを黒にすると条件5を満たさないのでだめ
      g->__set_red_kind();
      p->__set_black_kind();
      u->__set_black_kind();
      // Gを赤にしたことで、Gより上層の色を変更しないといけない
      // NをGにして根まで再帰的に辿る
      __rebalance_tree(g, g->parent);
      return;
    }

    // 残りは以下のパターン
    // (i)　　　　　　　　　　　　　　　　　　　　　　(ii)              (iii)             (iv)
    //        Gb　　　　　　　　　　　　　　　　　　　      Gb              Gb                Gb
    //    +---+---+　　　　　　　　　　　　　　　　　　+---+---+       +---+---+         +---+---+
    //    Pr      Ub       Pr      Ub      Ub      Pr        Ub      Pr
    // +--+--+          +--+--+                 +--+--+           +--+--+
    //       Nr        Nr                      Nr                       Nr

    // case 3
    // - Uが黒の場合
    //   - 上記のパターンの(i)を(ii)に、(iii)を(iv)に変形し、case 4に委譲する

    // - (i)を(ii)に変形
    if (p == g->left && u == g->right && n == p->right) {
      __rotate_left(p, n);
      // PとNの名称を入れ替える　
      node_pointer tmp = n;
      n = p;
      p = tmp;
    }

    // - (iii)を(iv)に変形
    if (p == g->right && u == g->left && n == p->left) {
      __rotate_right(p, n);
      // PとNの名称を入れ替える　
      node_pointer tmp = n;
      n = p;
      p = tmp;
    }

    // case 4
    // - (ii)の場合
    if (p == g->left && u == g->right && n == p->left) {
      __rotate_right(g, p);
    }

    // - (iv)の場合
    //         Gb
    //     +---+---+
    //    Ub      Pr
    //         +--+--+
    //               Nr
    if (p == g->right && u == g->left && n == p->right) {
      __rotate_left(g, p);
    }

    // PとGの色を入れ替える
    __exchange_node_color(p, g);
  }

  // 要素を追加
  ft::pair<iterator, bool> __insert_helper(const_reference value) {
    node_pointer inserted_node = NULL;
    bool has_inserted = false;

    // 初めて要素を追加
    if (__empty()) {
      inserted_node = __allocate_node(value);
      // rootにつける
      root_ = inserted_node;
      root_->parent = root_;
      // TODO 最後のイテレータのためだけにつける
      __attach_end_node(inserted_node);
      __attach_nil_node_to_left(inserted_node);
      has_inserted = true;
      // リバランス
      inserted_node->__set_red_kind();
      __rebalance_tree(inserted_node, inserted_node);
      return ft::make_pair(iterator(inserted_node, __end_node()), has_inserted);
    }

    // ノードを辿って適切な場所にノードを作成
    node_pointer nd = root_;

    while (true) {
      if (__comp_(KeyOfValue()(value), KeyOfValue()(nd->value))) {
        nd = nd->left;
        if (nd->__is_nil_node()) {
          inserted_node = __allocate_node(value);
          // leftにノードをつける
          __attach_node_to_left(nd->parent, inserted_node);
          destruct_node(nd);
          // nil nodeをつける
          __attach_nil_nodes(inserted_node);
          has_inserted = true;
          // リバランス
          inserted_node->__set_red_kind();
          __rebalance_tree(inserted_node, inserted_node->parent);
          break;
        }
      } else if (__comp_(KeyOfValue()(nd->value), KeyOfValue()(value))) {
        nd = nd->right;
        if (nd == __end_node()) {
          inserted_node = __allocate_node(value);
          // rightにノードをつける
          __attach_node_to_right(nd->parent, inserted_node);
          // TODO 最後のイテレータのためだけにつける
          __attach_end_node(inserted_node);
          // nil nodeをつける
          __attach_nil_node_to_left(inserted_node);
          // prev_parent->right->right->parent = prev_parent->right;
          has_inserted = true;
          // リバランス
          inserted_node->__set_red_kind();
          __rebalance_tree(inserted_node, inserted_node->parent);
          break;
        }

        // TODO rightがend nodeじゃない時もある
        if (nd->__is_nil_node()) {
          inserted_node = __allocate_node(value);
          // rightにノードをつける　
          __attach_node_to_right(nd->parent, inserted_node);
          destruct_node(nd);
          // nil nodeをつける
          __attach_nil_nodes(inserted_node);
          has_inserted = true;
          // リバランス
          inserted_node->__set_red_kind();
          __rebalance_tree(inserted_node, inserted_node->parent);
          break;
        }
      } else {
        has_inserted = false;
        // 同じ要素がすでに存在していたら、その要素を指すイテレータを返したいので、ノードをセット
        inserted_node = nd;
        break;
      }
    }

    return ft::make_pair(iterator(inserted_node, __end_node()), has_inserted);
  }

  //  * PはGの左にある場合もある
  //      G                         G
  //  +---+---+                 +---+---+
  //          P                         N
  //      +---+---+                 +---+---+
  //      S       N                 P       NR
  //          +---+---+         +---+---+
  //         NL       NR        S       NL
  //

  //          P                         N
  //      +---+---+                 +---+---+
  //      S       N                 P       NR
  //          +---+---+         +---+---+
  //         NL       NR        S       NL
  void __rotate_left(node_pointer p, node_pointer n) {
    node_pointer g = p->parent;
    node_pointer s = p->left;
    node_pointer nl = n->left;
    node_pointer nr = n->right;

    p->right = nl;
    nl->parent = p;

    // Pがrootの場合
    if (__is_root(p)) {
      root_ = n;
      root_->parent = n;
    } else {
      if (p == g->left) {
        g->left = n;
      } else {
        g->right = n;
      }
      n->parent = g;
    }

    n->left = p;
    p->parent = n;
  }

  //
  //               G                     G
  //           +---+---+             +---+---+
  //           P                     N
  //       +---+---+             +---+---+
  //       N       S            NL       P
  //   +---+---+                     +---+---+
  //   NL     NR                    NR       S
  //
  //
  //           P                     N
  //       +---+---+             +---+---+
  //       N       S            NL       P
  //   +---+---+                     +---+---+
  //   NL     NR                    NR       S
  //
  void __rotate_right(node_pointer p, node_pointer n) {
    node_pointer g = p->parent;
    node_pointer s = p->right;
    node_pointer nl = n->left;
    node_pointer nr = n->right;

    p->left = nr;
    nr->parent = p;

    // Pがrootの場合
    if (__is_root(p)) {
      root_ = n;
      root_->parent = n;
    } else {
      if (p == g->left) {
        g->left = n;
      } else {
        g->right = n;
      }
      n->parent = g;
    }

    n->right = p;
    p->parent = n;
  }
};

// compare operators
template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator==(
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return lhs.__size() == rhs.__size() &&
         ft::equal(lhs.__begin(), lhs.__end(), rhs.__begin(), rhs.__end());
}

template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator!=(
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return !(lhs == rhs);
}

template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator<(
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return ft::lexicographical_compare(lhs.__begin(), lhs.__end(), rhs.__begin(),
                                     rhs.__end());
}

template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator>=(
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return !(lhs < rhs);
}

template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator>(
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return rhs < lhs;
}

template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator<=(
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return !(lhs > rhs);
}
}; // namespace ft

#endif
