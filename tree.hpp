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
    // 左の子がいるノードまで親を辿る
    while (nd->left->__is_nil_node()) {
      nd = nd->parent;
    }
    // 左の子以下のノードはすでに訪れているので親に移動
    // return nd->parent;
    return nd;
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
    while (nd->right->__is_nil_node()) {
      nd = nd->parent;
      LOG(ERROR) << "__prev_node/ loop";
    }
    // 以下のノードは訪れているので親を返す
    // return nd->parent;
    return nd;
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
          class Compare = ft::less<Key>,
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
        end_node_(__allocate_end_node()), __tree_size_(0) {}
  explicit __tree(const Compare& comp, const Allocator& alloc = Allocator())
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(__allocate_end_node()), __comp_(comp), __tree_size_(0) {}
  // : root_(NULL), end_node_(__allocate_node(pair<Key, Val>(Key(), Val()))) {}
  // TODO メモリ解放したらクラッシュする
  ~__tree() {}

  // TODO テキトー
  iterator __begin() {
    LOG(ERROR) << "__begin/ called";
    iterator itr = iterator(__begin_node(), __end_node());
    LOG(ERROR) << "__begin/ finished";
    return itr;
  }
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

  node_pointer __end_node() const { return end_node_; }

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
      LOG(ERROR) << "__rebalance_tree/ N is root";
      // 条件2より黒にする
      n->__set_black_kind();
      // ノードがrootしか存在しないので、全ての葉から根までのパスに黒いノードは1個のため条件5もクリア
      // TODO rootのparentをつける？
      return;
    }

    // - Pが黒
    if (p->__is_black_node()) {
      LOG(ERROR) << "__rebalance_tree/ P is black";
      // Nは赤なので条件4はクリア。Nが挿入された場所は元々nilであるため、nilからrootまでのパスの黒ノードの数は変わらない
      // 従って条件5もクリア
      return;
    }

    // case 2
    // - Pが赤
    LOG(ERROR) << "__rebalance_tree/ P is red";
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
      LOG(ERROR) << "__rebalance_tree/ U is red";
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
  }

  // 要素を追加
  ft::pair<iterator, bool> __insert_helper(const_reference value) {
    node_pointer inserted_node = NULL;
    bool has_inserted = false;

    // 初めて要素を追加
    if (__empty()) {
      LOG(ERROR) << "__insert/ node is root";

      // TODO とりあえず左側に
      inserted_node = __allocate_node(value);

      root_ = inserted_node;
      root_->parent = root_; // TODO 根の親は自分自身を指しておく

      // TODO 最後のイテレータのためだけにつける
      __attach_end_node(inserted_node);
      __attach_nil_node_to_left(inserted_node);

      has_inserted = true;

      // リバランス
      inserted_node->__set_red_kind();
      __rebalance_tree(inserted_node, inserted_node);
      LOG(ERROR) << "__rebalance_tree/ finished";

      return ft::make_pair(iterator(inserted_node, __end_node()), has_inserted);
    }

    // ノードを辿って適切な場所にノードを作成
    // node_pointer prev_parent = root_;
    node_pointer nd = root_;

    LOG(ERROR) << "__insert_helper/ loop";
    while (true) {
      if (KeyOfValue()(value) < KeyOfValue()(nd->value)) {
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
      } else if (KeyOfValue()(value) > KeyOfValue()(nd->value)) {
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
      // prev_parent = nd;
    }

    return ft::make_pair(iterator(inserted_node, __end_node()), has_inserted);
  }

  ft::pair<iterator, bool> __insert(const_reference value) {
    LOG(ERROR) << "__insert/ called";
    ft::pair<iterator, bool> p = __insert_helper(value);
    LOG(ERROR) << "__insert_helper/ finished";
    if (p.second) {
      ++__tree_size_;
    }
    LOG(ERROR) << "__insert/ finished";
    return p;
  }

  //  Inserts value in the position as close as possible to the position just prior to pos.
  iterator __insert(iterator pos, const_reference value) {
    // posからnode pointerをとる
    node_pointer pos_node;
    node_pointer new_node; // valueを持つノード

    // pos_nodeが右側にあればその間にnew nodeを挿入する
    // TODO コンパイルエラーを防ぐ
    return __end();
  }

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

  //     10
  //   5   15
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
        if (k > KeyOfValue()(nd->parent->value)) {
          LOG(ERROR) << "__lower_bound_pointer/ hoge";
          return nd->parent->parent;
        }
        return nd->parent;
      }
      prev_parent = nd;
    }
    return nd;
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
  node_pointer root() { return root_; }

  // allocatorを返す
  allocator_type __get_allocator() const { return allocator_type(node_alloc_); }
  // key_compareを返す
  key_compare __key_comp() const { return __comp_; }

  size_type __erase_no_child(node_pointer target) {

    LOG(ERROR) << "__erase no child";
    // targetの親から見てtargetがleftにある場合
    if (__has_exist_on_left_from_parent_side(target)) {
      // TODO メモリ解放
      __attach_nil_node_to_left(target->parent);
    } else {
      // targetの親から見てtargetがrightにある場合
      if (target->right == __end_node()) {
        // TODO メモリ解放
        __attach_end_node(target->parent);
      } else if (target->right->__is_nil_node()) {
        __attach_nil_node_to_right(target->parent);
      } else {
        // ここに来るのはあり得ない
        assert(false);
      }
    }
    LOG(ERROR) << "__erase end";
    return 1;
  }

  size_type __erase_one_red_child(node_pointer target) {

    // - 形状の例
    //         P
    //     +---+
    //     N
    // +---+
    // C

    node_pointer p = target->parent;
    node_pointer n = target;
    node_pointer c = NULL;
    if (__has_only_left_child(n)) {
      c = n->left;
    } else {
      c = n->right;
    }

    // NがPの左側にある場合
    if (n == p->left) {
      p->left = c;
      c->parent = p;
      return 1;
    }

    // NがPの右側にある場合
    p->right = n;
    c->parent = p;
    return 1;
  }

  size_type __erase_one_red_child_and_repaint_black(node_pointer target) {
    // targetのchildがtargetの場所に来る
    // あらかじめchildを覚えておき、削除した後に黒に塗り替える
    node_pointer child = NULL;
    if (__has_only_left_child(target)) {
      child = target->left;
    } else {
      child = target->right;
    }

    // TODO targetがrootの時、rootを付け替える必要がある
    root_ = child;

    size_type ret = __erase_one_red_child(target);

    // 黒に塗り替える
    child->__set_black_kind();

    return ret;
  }

  size_type __erase_one_child(node_pointer target) {
    // case 0
    // - targetが赤
    //  - 条件4、5を破らないのでリバランスは不要
    if (target->__is_red_node()) {
      LOG(ERROR) << "__erase_one_child/ target is red";
      return __erase_one_red_child(target);
    }

    // - targetが黒で子供が赤
    //  - targetを子供に置き換えて、黒に塗り替えるだけ
    if (target->__is_black_node() && __has_only_one_red_child(target)) {
      LOG(ERROR) << "__erase_one_child/ target is black";
      LOG(ERROR) << "__erase_one_child/ child is red";
      return __erase_one_red_child_and_repaint_black(target);
    }

    // あとは、targetと子供が黒の場合
    // - 黒を削除すると、条件5を満たすためにリバランスが必要
    // - 形状は以下の2ケースを考える
    //  - 最終的には一つの形状に変形していき、処理を委譲する

    LOG(ERROR) << "__erase_one_child/ target and N are black";

    node_pointer p = target->parent;
    node_pointer n = NULL;
    node_pointer s = NULL;
    // Nはtargetの子供
    if (__has_only_left_child(target)) {
      LOG(ERROR) << "__erase_one_child/ N on left of target";
      n = target->left;
    } else {
      LOG(ERROR) << "__erase_one_child/ N on right of target";
      n = target->right;
    }

    // Sはtargetの兄弟
    if (target == p->left) {
      LOG(ERROR) << "__erase_one_child/ S on right of target";
      s = p->right;
      p->left = n; // Nをtargetの場所に持ってくる
    } else {
      LOG(ERROR) << "__erase_one_child/ S on left of target";
      s = p->left;
      p->right = n;
    }
    s->parent = p;
    n->parent = p;

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

    // case 1
    // TODO Nがrootの場合は？　
    // - Nがrootだと葉から根までの全パスから黒ノードが一つ減るだけなので条件5を破らない
    // - 子をrootに持ってくるだけで良い
    if (__is_root(n)) {
      LOG(ERROR) << "__erase_one_child/ case 1: N is root";
      if (__has_only_left_child(n)) {
        root_ = n->left;
        n->left->parent = root_;
      } else {
        root_ = n->right;
        n->right->parent = root_;
      }
      return 1;
    }

    // case 2
    // - Sが赤の場合
    //  - SLとSRは黒
    //  - 左回転して、SとPの色を交換

    //        Pb                            Sb
    //  +-----+------+                +-----+-----+
    // Nb            Sr       ->      Pr         SRb
    //           +---+---+        +---+---+
    //          SLb     SRb       Nb     SLb

    // 形状が(i)の場合
    if (p->left == n && p->right == s) {
      LOG(ERROR) << "__erase_one_child/ case 2: shape is (i)";
      // Pを中心に左回転する
      p->right = sl;
      sl->parent = p;
      s->left = p;
      p->parent = s;
      // SとPの色を交換する
      __exchange_node_color(s, p);
    }

    // 形状が(ii)の場合
    if (p->left == s && p->right == n) {
      LOG(ERROR) << "__erase_one_child/ case 2: shape is (ii)";
      // Pを中心に右回転する
      p->left = sr;
      sr->parent = p;
      s->right = p;
      p->parent = s;
      // SとPの色を交換する
      __exchange_node_color(s, p);
    }

    // case 3
    // - Sが黒、Pが黒、SLとSRが黒の場合
    if (n->__is_black_node() && p->__is_black_node() && s->__is_black_node() &&
        sl->__is_black_node() && sr->__is_black_node()) {
      LOG(ERROR) << "__erase_one_child/ case 3";
      // Sを赤に塗り替える
      // - NからP、SL or SRからPまでのパスで黒ノードの数が等しくなるので、部分的に条件5を満たす
      s->__set_red_kind();
      // Pからの深さで黒ノードを一つ減らしたため、他の部分で色の調整を行いたいため、再帰する
      return __erase_one_child(p);
    }

    // case 4
    // - Pが赤、SLが黒、SRが黒
    if (p->__is_red_node() && sl->__is_black_node() && sr->__is_black_node()) {
      LOG(ERROR) << "__erase_one_child/ case 4";
      // PとSの色を入れ替える
      __exchange_node_color(p, s);
      // TODO 多分ここで終了？
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
    if (sl->__is_red_node() && sr->__is_black_node() && n == p->left) {
      LOG(ERROR) << "__erase_one_child/ case 5";
      // Sを中心に右回転
      s->left = sl->right;
      sl->right->parent = s;
      sl->right = s;
      s->parent = sl;
      p->right = sl;
      sl->parent = p;
      // SLとSの色を入れ替える
      __exchange_node_color(sl, s);
    }

    // SLが黒、SRが赤、NがPの右側の子
    if (sl->__is_black_node() && sr->__is_red_node() && n == p->right) {
      LOG(ERROR) << "__erase_one_child/ case 5";
      // Sを中心に左回転
      s->right = sr->left;
      sr->left->parent = s;
      sr->left = s;
      s->parent = sr;
      p->left = sr;
      sr->parent = p;
      // SRとSの色を入れ替える
      __exchange_node_color(sr, s);
    }

    // case 6
    // - SRが赤、NがPの左側の子供
    if (sr->__is_red_node() && n == p->left) {
      LOG(ERROR) << "__erase_one_child/ case 6";
      // Pを中心に左回転
      p->right = sl;
      sl->parent = p;
      s->left = p;
      p->parent = s;
      // PとSの色を交換
      __exchange_node_color(p, s);
      // SRを黒に
      sr->__set_black_kind();
    }

    // - SLが赤、NがPの右側の子供
    if (sl->__is_red_node() && n == p->right) {
      LOG(ERROR) << "__erase_one_child/ case 6";
      // Pを中心に右回転
      p->left = sr;
      sr->parent = p;
      s->right = p;
      p->parent = s;
      // PとSの色を交換する
      __exchange_node_color(p, s);
      // SLを黒に
      sl->__set_black_kind();
    }

    return 1;
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

    if (__has_no_child(n)) {
      LOG(ERROR) << "__erase_node_pointer/ n has no child";
      return __erase_no_child(n);
    }

    if (__has_one_child(n)) {
      LOG(ERROR) << "__erase_node_pointer/ n has one child";
      return __erase_one_child(n);
    }

    // TODO targetの子供が両方ともnilの場合
    // 無限ループ回避するため
    if (n->left->__is_nil_node() && n->right->__is_nil_node()) {
      LOG(ERROR) << "__erase_node_pointer/ both nodes are nil";

      node_pointer p = n->parent;
      node_pointer nr = n->right;

      if (p == root_) {
        LOG(ERROR) << "__erase_node_pointer/ p == root_";
      }
      if (nr == end_node_) {
        LOG(ERROR) << "__erase_node_pointer/ nr == end_node_";
        assert(nr->__is_nil_node());
      }

      if (n == p->left) {
        LOG(ERROR) << "__erase_node_pointer/ p->left = nr";
        p->left = nr;
      } else {
        LOG(ERROR) << "__erase_node_pointer/ p->right = nr";
        p->right = nr;
      }
      nr->parent = p;
      return 1;
    }

    // 削除対象のノードが二つ子を持つ場合
    // - targetの右側部分木の最小ノードをtargetの位置に持ってこればよいらしい
    LOG(ERROR) << "__erase_node_pointer/ n has two child";
    node_pointer partial_min = node::__get_min_node(n->right);
    // node_pointer partial_min = node::__get_max_node(n->left, end_node_);

    // targetとpartial_minを入れ替える
    __exchange_node(n, partial_min);

    LOG(ERROR) << "__erase_node_pointer/ after __exchange_node";

    // 削除対象のtargetは子を一つ持つ or いないはず。
    // 再帰して削除処理を委譲する
    return __erase_node_pointer(n);
  }

  size_type __erase_helper(const Key& key) {
    LOG(ERROR) << "__erase_helper/ called";
    node_pointer target = __find_node_pointer(key);
    return __erase_node_pointer(target);
  }

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
    nd->left = l;
    l->parent = nd;
  }

  void __attach_nil_node_to_right(node_pointer nd) {
    node_pointer r = __allocate_nil_node();
    nd->right = r;
    r->parent = nd;
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
