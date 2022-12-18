#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef>
#include <iostream>
#include <memory>
#include "deque.hpp"
#include "stack.hpp"
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
    __node_kind_ = other.__node_kind_;
    return *this;
  }

  static node_pointer __get_min_node(node_pointer nd) {
    while (!nd->__is_nil_node()) {
      nd = nd->left;
    }
    return nd->parent;
  }
  static node_pointer __get_max_node(node_pointer nd, node_pointer end) {
    while (!nd->__is_nil_node()) {
      nd = nd->right;
    }
    return nd->parent;
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

  friend bool operator==(const Self& lhs, const Self& rhs) {
    return *lhs == *rhs;
  }
  friend bool operator!=(const Self& lhs, const Self& rhs) {
    return !(lhs == rhs);
  }

private:
  __node_pointer __node_pointer_;
  __node_pointer __end_node_;

  __node_pointer __next_node(__node_pointer nd) {
    // TODO end nodeなら親を返すだけで良い
    if (nd->right == __end_node_) {
      return __end_node_;
    }

    // 　右の子がある場合
    // 　- 右の子を根とする部分木の一番左下の子を返す
    if (!nd->right->__is_nil_node()) {
      return __node<T, Allocator>::__get_min_node(nd->right);
    }

    //                       G
    //               +-------+-------+
    //               P
    //         +-----+-----+
    //         N           S
    //     +---+---+   +---+---+
    //    NL      　　　　           SR
    //                     +---+---+
    //                             NE

    // 左の子がいるノードまで親を辿る
    __node_pointer p = nd->parent;
    while (nd == p->right && nd->left->__is_nil_node()) {
      nd = nd->parent;
    }

    return nd->parent;
  }

  __node_pointer __prev_node(__node_pointer nd) {
    // TODO end nodeなら親を返すだけで良い
    if (nd == __end_node_) {
      return nd->parent;
    }
    // 左の子がある場合
    // - 左の子を根とする部分木の一番右したの子を返す
    if (!nd->left->__is_nil_node()) {
      return __node<T, Allocator>::__get_max_node(nd->left, __end_node_);
    }
    // 右の子がいるノードまで親を辿る
    __node_pointer p = nd->parent;
    while (nd == p->left && nd->right->__is_nil_node()) {
      nd = nd->parent;
      LOG(ERROR) << "__prev_node/ loop";
    }
    // 以下のノードは訪れているので親を返す
    // return nd->parent;
    return nd->parent;
  }
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
  typedef Allocator allocator_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef __node<value_type, Allocator> node;
  typedef typename Allocator::template rebind<node>::other node_allocator;
  typedef typename node::node_pointer node_pointer;
  typedef __tree_iterator<value_type, Allocator> iterator;
  typedef const iterator const_iterator;
  typedef typename std::reverse_iterator<iterator> reverse_iterator;
  typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

  __tree()
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(__allocate_end_node()), __tree_size_(0) {}
  explicit __tree(const Compare& comp, const Allocator& alloc = Allocator())
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(__allocate_end_node()), __comp_(comp), __tree_size_(0) {}
  // : root_(NULL), end_node_(__allocate_node(pair<Key, Val>(Key(), Val()))) {}
  // TODO メモリ解放したらクラッシュする
  ~__tree() {}

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

  ft::pair<iterator, bool> __insert(const_reference value) {
    LOG(ERROR) << "__insert/ called";
    ft::pair<iterator, bool> p = __insert_helper(value);
    if (p.second) {
      ++__tree_size_;
    }
    LOG(ERROR) << "__insert/ finished";
    return p;
  }

  //  Inserts value in the position as close as possible to the position just prior to pos.
  iterator __insert(iterator pos, const_reference value) { return __end(); }

  // ノードの要素を返す
  size_type __size() const { return __tree_size_; }

  bool __empty() const { return __size() == 0; }

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

  // upper bound
  // lower boundの不等号変わったやつ
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
  const_iterator __upper_bound(const Key& k) {
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

  // count
  size_type __count(const Key& key) const {
    return __find(key) == __end() ? 0 : 1;
  }

  // max_size
  size_type __max_size() const { return node_alloc_.max_size(); }

  // rootを返す
  // For testable
  node_pointer root() { return root_; }

  // allocatorを返す
  allocator_type __get_allocator() const { return allocator_type(node_alloc_); }
  // key_compareを返す
  key_compare __key_comp() const { return __comp_; }

  // __erase
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

  // node操作するメソッド ここから
  // TODO こういうのはtemplateにしてクラス外にして良い気がする
  bool __has_right_child(node_pointer nd) { return !__has_no_right_child(nd); }
  bool __has_no_right_child(node_pointer nd) {
    // return nd->right == NULL || nd->right == __end_node();
    // return nd->right->__is_nil_node();
    return nd->right == NULL;
  }
  bool __has_left_child(node_pointer nd) { return !__has_no_left_child(nd); }
  bool __has_no_left_child(node_pointer nd) {
    // return nd->left->__is_nil_node();
    return nd->left == NULL;
  }
  bool __has_both_child(node_pointer nd) {
    return __has_left_child(nd) && __has_right_child(nd);
  }
  bool __has_only_right_child(node_pointer nd) {
    return !__has_left_child(nd) && __has_right_child(nd);
  }
  bool __has_only_left_child(node_pointer nd) {
    return __has_left_child(nd) && !__has_right_child(nd);
  }
  bool __has_no_child(node_pointer nd) {
    return __has_no_left_child(nd) && __has_no_right_child(nd);
  }
  bool __has_one_child(node_pointer nd) {
    return __has_only_left_child(nd) || __has_only_right_child(nd);
  }
  bool __has_only_one_red_child_on_left(node_pointer nd) {
    return __has_only_left_child(nd) && nd->left->__is_red_node();
  }
  bool __has_only_one_red_child_on_right(node_pointer nd) {
    return __has_only_right_child(nd) && nd->right->__is_red_node();
  }
  bool __has_only_one_red_child(node_pointer nd) {
    return __has_only_one_red_child_on_left(nd) ||
           __has_only_one_red_child_on_right(nd);
  }

  // 自分が親から見て左側にあるか
  bool __has_exist_on_left_from_parent_side(node_pointer nd) {
    return nd->parent->left == nd;
  }
  bool __has_exist_on_right_from_parent_side(node_pointer nd) {
    return !__has_exist_on_left_from_parent_side(nd);
  }

  // rootかどうか
  bool __is_root(node_pointer nd) { return nd->parent == nd; }

  // node操作するメソッド　ここまで

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
      LOG(ERROR) << "__tree/__allocate_node pointer is null";
    }
    return n;
  }

  node_pointer __allocate_end_node() { return __allocate_nil_node(); }

  node_pointer __allocate_nil_node() {
    node_pointer n = __allocate();
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
    return node::__get_min_node(root_);
  }

  size_type __erase_helper(const Key& key) {
    LOG(ERROR) << "__erase_helper/ called";
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
    LOG(ERROR) << "__erase_node_pointer/ called";

    // keyがなかったら0を返す
    if (n == NULL) {
      LOG(ERROR) << "__erase_node_pointer/ not found";
      return 0;
    }

    node_pointer cl = n->left;
    node_pointer cr = n->right;

    // TODO この処理実はいらない説
    // // 子を持たない
    // // if (cl->__is_nil_node() && cr->__is_nil_node()) {
    // if (cl == NULL && cr == NULL) {
    //   LOG(ERROR) << "__erase_node_pointer/ n has no child";
    //   return __erase_no_child(n);
    // }

    // TODO 要素がrootだけの時
    if (n == n->parent && cl->__is_nil_node() && cr->__is_nil_node()) {
      root_ = NULL;
      return 1;
    }

    if ((cl->__is_nil_node() && cr->__is_nil_node()) ||
        (!cl->__is_nil_node() && cr->__is_nil_node()) ||
        (cl->__is_nil_node() && !cr->__is_nil_node())) {
      LOG(ERROR) << "__erase_node_pointer/ n has one or zero child";
      return __erase_node_with_one_or_zero_child(n);
    }

    // 子を2つ持つ
    LOG(ERROR) << "__erase_node_pointer/ n has two child";
    node_pointer partial_min = node::__get_min_node(n->right);
    // targetとpartial_minを入れ替える
    __exchange_node(n, partial_min);
    LOG(ERROR) << "__erase_node_pointer/ after __exchange_node";
    // 削除対象のtargetは子を一つ持つ or いないはず。
    // 再帰して削除処理を委譲する
    return __erase_node_pointer(n);
  }

  // Nの子はNULL
  size_type __erase_no_child(node_pointer n) {
    LOG(ERROR) << "__erase_no_child/ called";

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
    LOG(ERROR) << "__rebalance_when_erase/ called";

    // あとは、targetと子供が黒の場合
    // - 黒を削除すると、条件5を満たすためにリバランスが必要
    // - 形状は以下の2ケースを考える
    //  - 最終的には一つの形状に変形していき、処理を委譲する

    // case 1
    // - Nがrootだと葉から根までの全パスから黒ノードが一つ減るだけなので条件5を破らない
    // - 子をrootに持ってくるだけで良い
    if (n->parent == n) {
      LOG(ERROR) << "__erase/ case 1: N is root";
      return 1;
    }
    LOG(ERROR) << "__erase/ case 1: not match";

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

    if (sl == NULL) {
      LOG(ERROR) << "__erase/ sl == NULL";
      assert(false);
    }
    if (sr == NULL) {
      LOG(ERROR) << "__erase/ sr == NULL";
      assert(false);
    }

    sl->parent = s;
    sr->parent = s;

    LOG(ERROR) << "__erase/ prepare finish";

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
      LOG(ERROR) << "__erase/ case 2: shape (i)";
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
      LOG(ERROR) << "__erase/ case 2: shape (ii)";
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

    LOG(ERROR) << "__erase/ case 2: not match";

    // case 3
    // - 全部黒色
    //               Pb                          Pb
    //         +-----+-----+               +-----+-----+
    //        Nb           Sb      ->     Nb           Sr
    //                 +---+---+                   +---+---+
    //                SLb     SRb                 SLb     SRb
    if (n->__is_black_node() && p->__is_black_node() && s->__is_black_node() &&
        sl->__is_black_node() && sr->__is_black_node()) {
      LOG(ERROR) << "__erase/ case 3";
      // Sを赤に塗り替える
      // - NからP、SL or SRからPまでのパスで黒ノードの数が等しくなるので、部分的に条件5を満たす
      s->__set_red_kind();
      // Pからの深さで黒ノードを一つ減らしたため、他の部分で色の調整を行いたいため、再帰する
      return __rebalance_when_erase(p);
    }
    LOG(ERROR) << "__erase/ case 3: not match";

    // case 4
    // - Pが赤、SLが黒、SRが黒
    if (n->__is_black_node() && p->__is_red_node() && s->__is_black_node() &&
        sl->__is_black_node() && sr->__is_black_node()) {
      LOG(ERROR) << "__erase/ case 4";
      // PとSの色を入れ替える
      __exchange_node_color(p, s);
      return 1;
    }
    LOG(ERROR) << "__erase/ case 4: not match";

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
      LOG(ERROR) << "__erase/ case 5";
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
      LOG(ERROR) << "__erase/ case 5";
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
    LOG(ERROR) << "__erase/ case 5: not match";

    // case 6
    // - SRが赤、NがPの左側の子供

    //       　   　　　　  P                            　 S
    //　　　   　　　  +-----+-----+                  +-----+-----+
    //       Nb           Sb      ->         Pb          SRb
    //                +---+---+          +---+---+
    //               SL      SRr        Nb       SL
    if (n == p->left && n->__is_black_node() && s->__is_black_node() &&
        sr->__is_red_node()) {
      LOG(ERROR) << "__erase/ case 6: SR is red";
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
      LOG(ERROR) << "__erase/ case 6: SL is red";
      // Pを中心に右回転
      __rotate_right(p, s);
      // PとSの色を交換する
      __exchange_node_color(p, s);
      // SLを黒に
      sl->__set_black_kind();
      return 1;
    }
    LOG(ERROR) << "__erase/ unreachable";
    assert(false);
    return 1;
  }

  size_type __erase_node_with_one_or_zero_child(node_pointer target) {
    LOG(ERROR) << "__erase/ called";

    // case 0
    // - targetが赤
    //  - 条件4、5を破らないのでリバランスは不要
    if (target->__is_red_node()) {
      LOG(ERROR) << "__erase/ case 0: target is red";
      return __erase_own_and_replace_child(target);
    }

    // - targetが黒で子が赤
    //  - targetを子に置き換えて、黒に塗り替えるだけ
    node_pointer tl = target->left, tr = target->right;
    if (target->__is_black_node() &&
        ((tl->__is_nil_node() && tr->__is_red_node()) ||
         (tl->__is_red_node() && tr->__is_nil_node()))) {
      LOG(ERROR) << "__erase/ case 0: target is black, child is red";
      return __erase_own_and_repaint_after_replace_child(target);
    }

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

  // TODO 色（kind）も交換するか
  void __exchange_node(node_pointer n1, node_pointer n2) {
    // これだとmapからtreeを使うときコンパイルエラーになる
    // error: assignment of read-only member ‘ft::pair<const int, int>::first’

    // value_type tmp_val = n1->value;
    // n1->value = n2->value;
    // n2->value = tmp_val;

    node_pointer p1 = n1->parent, nl1 = n1->left, nr1 = n1->right;
    node_pointer p2 = n2->parent, nl2 = n2->left, nr2 = n2->right;

    //              N1
    //       +------+------+
    //      N2            NR1
    //  +---+---+
    // NL2     NR2
    // TODO N1とN2が親子
    if (p2 == n1) {
      LOG(ERROR) << "__exchange_node/ p2 == n1";
      if (nl1 == n2) {
        LOG(ERROR) << "__exchange_node/ nl1 == n2";
        if (n1 == root_) {
          LOG(ERROR) << "__exchange_node/ n1 == root_";
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
        LOG(ERROR) << "__exchange_node/ nr1 == n2";
        if (n1 == root_) {
          LOG(ERROR) << "__exchange_node/ n1 == root_";
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
      } else {
        assert(false);
      }

      // TODO 色も交換する？
      __exchange_node_color(n1, n2);
      return;
    }

    // N2をN1の場所に持ってくる
    // N1がrootだった時
    if (n1 == root_) {
      LOG(ERROR) << "__exchange_node/ n1 == root_";
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
    LOG(ERROR) << "__erase_own_and_repaint_after_replace_child/ called";
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
    LOG(ERROR) << "__erase_own_and_replace_child/ called";

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
      LOG(ERROR) << "__erase_own_and_replace_child/ end node";
      c = n->right;
    } else {
      if (!n->left->__is_nil_node()) {
        LOG(ERROR) << "__erase_own_and_replace_child/ left";
        c = n->left;
      } else {
        LOG(ERROR) << "__erase_own_and_replace_child/ right";
        c = n->right;
      }
    }

    // Nがroot
    if (n->parent == n) {
      // TODO end nodeをつけないといけない
      if (n->right == __end_node()) {
        c->right = __end_node();
        c->right->parent = c;
      }
      root_ = c;
      root_->parent = root_;
      return 1;
    }

    // NがPの左側にある場合
    if (n == p->left) {
      p->left = c;
    } else {
      // NがPの右側にある場合
      LOG(ERROR) << "__erase_own_and_replace_child/ N on the right";
      p->right = c;
    }
    c->parent = p;

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
        LOG(ERROR) << "__lower_bound_pointer/ found";
        break;
      }

      // TODO end nodeまで到達するとこれ以上のノードは存在しないので、見つからなかったとする
      if (nd == end_node_) {
        return NULL;
      }
      if (nd->__is_nil_node()) {
        LOG(ERROR) << "__lower_bound_pointer/ not found";
        // ここで一個前のノードの値をチェック
        // k > nd->valueならそのノードを返す
        if (__comp_(KeyOfValue()(nd->parent->value), k)) {
          LOG(ERROR) << "__lower_bound_pointer/ hoge";
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
      LOG(ERROR) << "__rebalance_tree/ case 1: N is root";
      // 条件2より黒にする
      n->__set_black_kind();
      // ノードがrootしか存在しないので、全ての葉から根までのパスに黒いノードは1個のため条件5もクリア
      // TODO rootのparentをつける？
      LOG(ERROR) << "__rebalance_tree/ finish";
      return;
    }

    // - Pが黒
    if (p->__is_black_node()) {
      LOG(ERROR) << "__rebalance_tree/ case 1: P is black";
      // Nは赤なので条件4はクリア。Nが挿入された場所は元々nilであるため、nilからrootまでのパスの黒ノードの数は変わらない
      // 従って条件5もクリア
      LOG(ERROR) << "__rebalance_tree/ finish";
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
      LOG(ERROR) << "__rebalance_tree/ case 2: U is red";
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
    LOG(ERROR) << "__rebalance_tree/ U is black";

    // - (i)を(ii)に変形
    if (p == g->left && u == g->right && n == p->right) {
      LOG(ERROR) << "__rebalance_tree/ tree shape is (i)";
      __rotate_left(p, n);
      // PとNの名称を入れ替える　
      node_pointer tmp = n;
      n = p;
      p = tmp;
    }

    // - (iii)を(iv)に変形
    if (p == g->right && u == g->left && n == p->left) {
      LOG(ERROR) << "__rebalance_tree/ tree shape is (iii)";
      __rotate_right(p, n);
      // PとNの名称を入れ替える　
      node_pointer tmp = n;
      n = p;
      p = tmp;
    }

    // case 4
    // - (ii)の場合
    if (p == g->left && u == g->right && n == p->left) {
      LOG(ERROR) << "__rebalance_tree/ tree shape is (ii)";
      __rotate_right(g, p);
    }

    // - (iv)の場合
    //         Gb
    //     +---+---+
    //    Ub      Pr
    //         +--+--+
    //               Nr
    if (p == g->right && u == g->left && n == p->right) {
      LOG(ERROR) << "__rebalance_tree/ tree shape is (iv)";
      __rotate_left(g, p);
    }

    // PとGの色を入れ替える
    __exchange_node_color(p, g);
    LOG(ERROR) << "__rebalance_tree/ finish";
  }

  // 要素を追加
  ft::pair<iterator, bool> __insert_helper(const_reference value) {
    node_pointer inserted_node = NULL;
    bool has_inserted = false;

    // 初めて要素を追加
    if (__empty()) {
      LOG(ERROR) << "__insert_helper/ node is root";
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
    LOG(ERROR) << "__rotate_left/ called";
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
