#ifndef TREE_HPP
#define TREE_HPP

#include "deque.hpp"
#include "stack.hpp"
#include "pair.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"
#include <functional>
#include <limits>
#include <algorithm>
#include <cstddef>
#include <memory>

namespace ft {
/// @brief Used for package internal
namespace detail {

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
  typedef const_pointer const_iterator;
  typedef __node self;
  typedef __node* node_pointer;

  enum kind { BLACK = 1, RED, NIL };

  node_pointer left;
  node_pointer right;
  node_pointer parent;
  value_type value;
  int node_kind;

  __node()
      : left(NULL), right(NULL), parent(NULL), value(value_type()),
        node_kind(0), node_alloc(node_allocator()) {}
  __node(const_reference v)
      : left(NULL), right(NULL), parent(NULL), value(v), node_kind(0),
        node_alloc(node_allocator()) {}
  ~__node() {}
  __node(const __node& other) { *this = other; }
  __node& operator=(const __node& other) {
    if (this == &other) {
      return *this;
    }

    left = other.left;
    right = other.right;
    parent = other.parent;
    // pair<const Key, Value>の代入はコンパイルエラーになるのでそれを避ける
    // value = other.value;
    node_alloc = other.node_alloc;
    node_kind = other.node_kind;
    return *this;
  }

  bool is_black_node() { return node_kind & (1 << BLACK); }
  bool is_red_node() { return node_kind & (1 << RED); }
  bool is_nil_node() { return is_black_node() && node_kind & (1 << NIL); }
  void set_black_kind() { node_kind = 1 << BLACK; }
  void set_red_kind() { node_kind = 1 << RED; }
  void set_nil_kind() { node_kind = (1 << BLACK) | (1 << NIL); }
  int get_node_kind() { return node_kind; }
  void set_node_kind(int k) { node_kind = k; }

private:
  allocator_type node_alloc;
};

/*
 * ノードを扱う関数群
*/
template <typename NodePtr>
static NodePtr get_min_node(NodePtr node) {
  while (!node->is_nil_node()) {
    node = node->left;
  }
  return node->parent;
}

template <typename NodePtr>
static NodePtr get_max_node(NodePtr node) {
  while (!node->is_nil_node()) {
    node = node->right;
  }
  return node->parent;
}

template <typename NodePtr>
static NodePtr next_node(NodePtr node, NodePtr end_node) {
  if (node->right == end_node) {
    return end_node;
  }

  if (!node->right->is_nil_node()) {
    return get_min_node(node->right);
  }

  NodePtr p = node->parent;

  while (node == p->right) {
    node = node->parent;
    p = node->parent;
  }

  return node->parent;
}

template <typename NodePtr>
static NodePtr prev_node(NodePtr node, NodePtr end_node) {
  if (node == end_node) {
    return node->parent;
  }

  if (!node->left->is_nil_node()) {
    return get_max_node(node->left);
  }

  NodePtr p = node->parent;

  while (node == p->left) {
    node = node->parent;
    p = node->parent;
  }

  return node->parent;
}

template <typename T, typename Allocator>
struct __tree_iterator {
  typedef T value_type;
  typedef T& reference;
  typedef T* pointer;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
  typedef __tree_iterator<T, Allocator> self;
  typedef typename __node<T, Allocator>::node_pointer node_pointer;

  __tree_iterator() : nd_ptr(NULL), end_nd(NULL) {}
  explicit __tree_iterator(const node_pointer& bgn, const node_pointer& end)
      : nd_ptr(bgn), end_nd(end) {}
  __tree_iterator(const self& other) { *this = other; }
  self& operator=(const self& other) {
    if (this == &other) {
      return *this;
    }
    nd_ptr = other.nd_ptr;
    end_nd = other.end_nd;
    return *this;
  }

  reference operator*() const { return nd_ptr->value; }
  pointer operator->() const { return &nd_ptr->value; }
  self& operator++() {
    nd_ptr = next_node(nd_ptr, end_nd);
    return *this;
  }
  self operator++(int) {
    self tmp = *this;
    operator++();
    return tmp;
  }
  self& operator--() {
    nd_ptr = prev_node(nd_ptr, end_nd);
    return *this;
  }
  self operator--(int) {
    self tmp = *this;
    operator--();
    return tmp;
  }

  node_pointer nd_ptr;
  node_pointer end_nd;
};

template <typename T, typename Allocator>
bool operator==(const ft::detail::__tree_iterator<T, Allocator>& lhs,
                const ft::detail::__tree_iterator<T, Allocator>& rhs) {
  return lhs.nd_ptr == rhs.nd_ptr;
}
template <typename T, typename Allocator>
bool operator!=(const ft::detail::__tree_iterator<T, Allocator>& lhs,
                const ft::detail::__tree_iterator<T, Allocator>& rhs) {
  return !(lhs == rhs);
}

template <typename T, typename Allocator>
struct __const_tree_iterator {
  typedef T value_type;
  typedef const T& reference;
  typedef T* pointer;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef std::ptrdiff_t difference_type;
  typedef __const_tree_iterator<T, Allocator> self;
  typedef typename __node<T, Allocator>::node_pointer node_pointer;
  typedef __tree_iterator<T, Allocator> non_const_iterator;

  __const_tree_iterator() : nd_ptr(NULL), end_nd(NULL) {}
  explicit __const_tree_iterator(const node_pointer& bgn,
                                 const node_pointer& end)
      : nd_ptr(bgn), end_nd(end) {}
  __const_tree_iterator(const self& other) { *this = other; }
  self& operator=(const self& other) {
    if (this == &other) {
      return *this;
    }
    nd_ptr = other.nd_ptr;
    end_nd = other.end_nd;
    return *this;
  }
  __const_tree_iterator(non_const_iterator itr)
      : nd_ptr(itr.nd_ptr), end_nd(itr.end_nd) {}

  reference operator*() const { return nd_ptr->value; }
  pointer operator->() const { return &nd_ptr->value; }
  self& operator++() {
    nd_ptr = next_node(nd_ptr, end_nd);
    return *this;
  }
  self operator++(int) {
    self tmp = *this;
    operator++();
    return tmp;
  }
  self& operator--() {
    nd_ptr = prev_node(nd_ptr, end_nd);
    return *this;
  }
  self operator--(int) {
    self tmp = *this;
    operator--();
    return tmp;
  }

  friend bool operator==(const self& lhs, const self& rhs) {
    return lhs.nd_ptr == rhs.nd_ptr;
  }
  friend bool operator!=(const self& lhs, const self& rhs) {
    return !(lhs == rhs);
  }

private:
  node_pointer nd_ptr;
  node_pointer end_nd;
};

/// @brief Red Black Tree used in set and map
template <typename Key, typename Val, typename KeyOfValue,
          class Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
class __tree {
public:
  /*
  *  Member types
  */
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
  typedef __const_tree_iterator<value_type, Allocator> const_iterator;
  typedef typename ft::reverse_iterator<iterator> reverse_iterator;
  typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

  /*
  *  Member functions
  */
  __tree()
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(allocate_end_node()), tree_size_(0) {}

  __tree(iterator first, iterator last)
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(allocate_end_node()), tree_size_(0) {
    insert(first, last);
  }

  explicit __tree(const Compare& comp, const Allocator& alloc = Allocator())
      : node_alloc_(node_allocator(alloc)), root_(NULL),
        end_node_(allocate_end_node()), comp_(comp), tree_size_(0) {}

  __tree(const __tree& other)
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(allocate_end_node()), tree_size_(0) {
    *this = other;
  }

  ~__tree() {
    destruct_tree();
    destruct_node(end_node_);
  }

  __tree& operator=(const __tree& other) {
    if (this == &other) {
      return *this;
    }
    destruct_tree();
    insert(other.begin(), other.end());
    return *this;
  }

  allocator_type get_allocator() const { return allocator_type(node_alloc_); }

  /*
   * Iterators
  */
  iterator begin() { return iterator(begin_node(), end_node()); }

  const_iterator begin() const {
    return const_iterator(begin_node(), end_node());
  }

  iterator end() { return iterator(end_node(), end_node()); }

  const_iterator end() const { return const_iterator(end_node(), end_node()); }

  reverse_iterator rbegin() {
    return reverse_iterator(iterator(end_node(), end_node()));
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(const_iterator(end_node(), end_node()));
  }

  reverse_iterator rend() {
    return reverse_iterator(iterator(begin_node(), end_node()));
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(const_iterator(begin_node(), end_node()));
  }

  node_pointer end_node() const { return end_node_; }

  /*
   * Capacity
  */
  bool empty() const { return size() == 0; }

  size_type size() const { return tree_size_; }

  size_type max_size() const {
    return std::min<size_type>(node_alloc_.max_size(),
                               std::numeric_limits<difference_type>::max());
  }

  /*
   * Modifiers
  */
  void clear() { erase(begin(), end()); }

  ft::pair<iterator, bool> insert(const_reference value) {
    ft::pair<iterator, bool> p = insert_helper(value);
    if (p.second) {
      ++tree_size_;
    }
    return p;
  }

  iterator insert(iterator pos, const_reference value) {
    (void)pos;
    return insert(value).first;
  }

  template <class InputIt>
  void insert(InputIt first, InputIt last) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }

  size_type erase(const Key& key) {
    if (erase_helper(key) == 1) {
      --tree_size_;
      return 1;
    }
    return 0;
  }

  iterator erase(iterator pos) {
    iterator res = pos;
    ++res;
    erase(KeyOfValue()(*pos));
    return res;
  }

  iterator erase(iterator first, iterator last) {
    for (; first != last;) {
      first = erase(first);
    }
    return last;
  }

  /*
   * Lookup
  */
  size_type count(const Key& key) const { return find(key) == end() ? 0 : 1; }

  iterator find(const key_type& key) {
    iterator target = lower_bound(key);
    if (target == end()) {
      return end();
    }
    if (KeyOfValue()(*target) == key) {
      return target;
    }
    return end();
  }

  const_iterator find(const key_type& key) const {
    const_iterator target = lower_bound(key);
    if (target == end()) {
      return end();
    }
    if (KeyOfValue()(*target) == key) {
      return target;
    }
    return end();
  }

  ft::pair<iterator, iterator> equal_range(const Key& key) {
    return ft::make_pair(lower_bound(key), uppper_bound(key));
  }

  ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }

  iterator lower_bound(const Key& key) {
    node_pointer ptr = lower_bound_pointer(key);
    if (ptr == NULL) {
      return end();
    }
    return iterator(ptr, end_node());
  }

  const_iterator lower_bound(const Key& key) const {
    node_pointer ptr = lower_bound_pointer(key);
    if (ptr == NULL) {
      return end();
    }
    return const_iterator(ptr, end_node());
  }

  iterator uppper_bound(const Key& k) {
    iterator itr = lower_bound(k);
    if (itr == end()) {
      return end();
    }
    if (k == KeyOfValue()(*itr)) {
      return ++itr;
    }
    return itr;
  }

  const_iterator upper_bound(const Key& k) const {
    const_iterator itr = lower_bound(k);
    if (itr == end()) {
      return end();
    }
    if (k == KeyOfValue()(*itr)) {
      return ++itr;
    }
    return itr;
  }

  /*
  *  Observers
  */
  key_compare key_comp() const { return comp_; }

  node_pointer root() { return root_; }

  node_pointer find_node_pointer(const key_type& key) const {
    node_pointer target = lower_bound_pointer(key);
    if (target == NULL) {
      return NULL;
    }
    if (KeyOfValue()(target->value) == key) {
      return target;
    }
    return NULL;
  }

private:
  node_allocator node_alloc_;
  node_pointer root_;
  node_pointer end_node_;
  key_compare comp_;
  size_type tree_size_;

  void destruct_tree() {
    destruct_partial_tree(root_);
    root_ = NULL;
    tree_size_ = 0;
  }
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
    if (ptr->right != NULL && ptr->right->is_nil_node() &&
        ptr->right != end_node_) {
      destroy_node(ptr->right);
      deallocate_node(ptr->right);
    }
    if (ptr->left != NULL && ptr->left->is_nil_node()) {
      destroy_node(ptr->left);
      deallocate_node(ptr->left);
    }
    destroy_node(ptr);
    deallocate_node(ptr);
  }

  // rootかどうか
  bool is_root(node_pointer nd) { return nd->parent == nd; }

  // TODO tree_baseみたいなの作ってnodeいじるメソッドはそっちに移動させたい
  node_pointer allocate() {
    node_pointer n = node_alloc_.allocate(1);
    return n;
  }

  // nodeをアロケーションする
  node_pointer allocate_node(const_reference v) {
    node_pointer n = allocate();
    node_alloc_.construct(n, v);
    if (n == NULL) {
    }
    return n;
  }

  node_pointer allocate_end_node() { return allocate_nil_node(); }

  node_pointer allocate_nil_node() {
    node_pointer n = allocate();
    node_alloc_.construct(n, value_type());
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->set_nil_kind();
    return n;
  }

  void attach_nil_node_to_left(node_pointer nd) {
    node_pointer l = allocate_nil_node();
    l->parent = nd;
    nd->left = l;
  }

  void attach_nil_node_to_right(node_pointer nd) {
    node_pointer r = allocate_nil_node();
    r->parent = nd;
    nd->right = r;
  }

  void attach_nil_nodes(node_pointer nd) {
    attach_nil_node_to_left(nd);
    attach_nil_node_to_right(nd);
  }

  void attach_end_node(node_pointer nd) { attach_node_to_right(nd, end_node_); }

  void attach_node_to_left(node_pointer parent, node_pointer child) {
    parent->left = child;
    child->parent = parent;
  }
  void attach_node_to_right(node_pointer parent, node_pointer child) {
    parent->right = child;
    child->parent = parent;
  }

  void exchange_node_color(node_pointer node1, node_pointer node2) {
    int k = node1->get_node_kind();
    node1->set_node_kind(node2->get_node_kind());
    node2->set_node_kind(k);
  }

  node_pointer begin_node() const {
    if (empty()) {
      return end_node();
    }
    return get_min_node(root_);
  }

  size_type erase_helper(const Key& key) {
    node_pointer target = find_node_pointer(key);
    return erase_node_pointer(target);
  }

  // 以下の条件を満たすようにする
  // 1. ノードは赤か黒である
  // 2. 根は黒である
  // 3. 全ての葉は黒である
  // 4. 赤いノードの子は黒である
  // 5. 全ての葉から根までのパスには、同じ個数の黒いノードがある

  size_type erase_node_pointer(node_pointer n) {
    // keyがなかったら0を返す
    if (n == NULL) {
      return 0;
    }

    node_pointer cl = n->left;
    node_pointer cr = n->right;

    // TODO 要素がrootだけの時
    if (n == n->parent && cl->is_nil_node() && cr->is_nil_node()) {
      destruct_erased_node(root_);
      root_ = NULL;
      return 1;
    }

    if ((cl->is_nil_node() && cr->is_nil_node()) ||
        (!cl->is_nil_node() && cr->is_nil_node()) ||
        (cl->is_nil_node() && !cr->is_nil_node())) {
      return erase_node_with_one_or_zero_child(n);
    }

    // 子を2つ持つ
    node_pointer partial_min = get_min_node(n->right);
    // targetとpartial_minを入れ替える
    exchange_node(n, partial_min);
    // 削除対象のtargetは子を一つ持つ or いないはず。
    // 再帰して削除処理を委譲する
    return erase_node_pointer(n);
  }

  // Nの子はNULL
  size_type erase_no_child(node_pointer n) {
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

  size_type rebalance_when_erase(node_pointer n) {
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
    if (s->is_red_node() && sl->is_black_node() && sr->is_black_node() &&
        p->left == n && p->right == s) {
      // Pを中心に左回転する
      rotate_left(p, s);
      // SとPの色を交換する
      exchange_node_color(s, p);
      // case 4以降に委譲するためノードを再命名
      s = p->right;
      s->parent = p;
      sl = s->left;
      sl->parent = s;
      sr = s->right;
      sr->parent = s;
    }

    // 形状が(ii)の場合
    if (s->is_red_node() && sl->is_black_node() && sr->is_black_node() &&
        p->left == s && p->right == n) {
      // Pを中心に右回転する
      rotate_right(p, s);
      // SとPの色を交換する
      exchange_node_color(s, p);
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
    if (n->is_black_node() && p->is_black_node() && s->is_black_node() &&
        sl->is_black_node() && sr->is_black_node()) {
      // Sを赤に塗り替える
      // - NからP、SL or SRからPまでのパスで黒ノードの数が等しくなるので、部分的に条件5を満たす
      s->set_red_kind();
      // Pからの深さで黒ノードを一つ減らしたため、他の部分で色の調整を行いたいため、再帰する
      return rebalance_when_erase(p);
    }

    // case 4
    // - Pが赤、SLが黒、SRが黒
    if (n->is_black_node() && p->is_red_node() && s->is_black_node() &&
        sl->is_black_node() && sr->is_black_node()) {
      // PとSの色を入れ替える
      exchange_node_color(p, s);
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
    if (n == p->left && n->is_black_node() && s->is_black_node() &&
        sl->is_red_node() && sr->is_black_node()) {
      // Sを中心に右回転
      rotate_right(s, sl);
      // SLとSの色を入れ替える
      exchange_node_color(sl, s);
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
    if (n == p->right && n->is_black_node() && s->is_black_node() &&
        sl->is_black_node() && sr->is_red_node()) {
      // Sを中心に左回転
      rotate_left(s, sr);
      // SRとSの色を入れ替える
      exchange_node_color(sr, s);
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
    if (n == p->left && n->is_black_node() && s->is_black_node() &&
        sr->is_red_node()) {
      // Pを中心に左回転
      rotate_left(p, s);
      // PとSの色を交換
      exchange_node_color(p, s);
      // SRを黒に
      sr->set_black_kind();
      return 1;
    }

    // - SLが赤、NがPの右側の子供
    if (n == p->right && n->is_black_node() && s->is_black_node() &&
        sl->is_red_node()) {
      // Pを中心に右回転
      rotate_right(p, s);
      // PとSの色を交換する
      exchange_node_color(p, s);
      // SLを黒に
      sl->set_black_kind();
      return 1;
    }
    return 1;
  }

  size_type erase_node_with_one_or_zero_child(node_pointer target) {
    // case 0
    // - targetが赤
    //  - 条件4、5を破らないのでリバランスは不要
    if (target->is_red_node()) {
      return erase_own_and_replace_child(target);
    }

    // - targetが黒で子が赤
    //  - targetを子に置き換えて、黒に塗り替えるだけ
    node_pointer tl = target->left, tr = target->right;
    if (target->is_black_node() && ((tl->is_nil_node() && tr->is_red_node()) ||
                                    (tl->is_red_node() && tr->is_nil_node()))) {
      return erase_own_and_repaint_after_replace_child(target);
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
    if (!target->left->is_nil_node()) {
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

    return rebalance_when_erase(n);
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
  void exchange_node(node_pointer n1, node_pointer n2) {
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
      exchange_node_color(n1, n2);
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
    exchange_node_color(n1, n2);
  }

  //     n
  // +---+---+
  //         c
  size_type erase_own_and_repaint_after_replace_child(node_pointer n) {
    // nのchildがnの場所に来る
    // あらかじめchildを覚えておき、削除した後に黒に塗り替える
    node_pointer c = NULL;
    if (!n->left->is_nil_node()) {
      c = n->left;
    } else {
      c = n->right;
    }

    size_type ret = erase_own_and_replace_child(n);

    // 黒に塗り替える
    c->set_black_kind();

    return ret;
  }

  size_type erase_own_and_replace_child(node_pointer target) {

    // - 形状の例
    //         P
    //     +---+
    //     N
    // +---+
    // C

    node_pointer p = target->parent;
    node_pointer n = target;
    node_pointer c = NULL;

    if (n->left->is_nil_node() && n->right == end_node()) {
      c = n->right;
    } else {
      if (!n->left->is_nil_node()) {
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
      if (n->right == end_node()) {
        destruct_node(c->right);
        c->right = end_node();
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

  node_pointer lower_bound_pointer(const Key& k) const {
    // TODO うまくinsertと共通化したい
    if (empty()) {
      return NULL;
    }
    // ノードを辿って適切な場所にノードを作成
    node_pointer prev_parent = root_;
    node_pointer nd = root_;
    while (true) {
      if (comp_(k, KeyOfValue()(nd->value))) {
        nd = nd->left;
      } else if (comp_(KeyOfValue()(nd->value), k)) {
        nd = nd->right;
      } else {
        break;
      }

      // TODO end nodeまで到達するとこれ以上のノードは存在しないので、見つからなかったとする
      if (nd == end_node_) {
        return NULL;
      }
      if (nd->is_nil_node()) {
        // ここで一個前のノードの値をチェック
        // k > nd->valueならそのノードを返す
        if (comp_(KeyOfValue()(nd->parent->value), k)) {
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
  void rebalance_tree(node_pointer n, node_pointer p) {
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
    if (is_root(n)) {
      // 条件2より黒にする
      n->set_black_kind();
      // ノードがrootしか存在しないので、全ての葉から根までのパスに黒いノードは1個のため条件5もクリア
      return;
    }

    // - Pが黒
    if (p->is_black_node()) {
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
    if (u->is_red_node()) {
      // Gは黒、その下層のPとUは赤である。色を交換して、Gを赤、PとUを黒にしても条件5を満たしたままのはず
      // Nを黒にすると条件5を満たさないのでだめ
      g->set_red_kind();
      p->set_black_kind();
      u->set_black_kind();
      // Gを赤にしたことで、Gより上層の色を変更しないといけない
      // NをGにして根まで再帰的に辿る
      rebalance_tree(g, g->parent);
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
      rotate_left(p, n);
      // PとNの名称を入れ替える　
      node_pointer tmp = n;
      n = p;
      p = tmp;
    }

    // - (iii)を(iv)に変形
    if (p == g->right && u == g->left && n == p->left) {
      rotate_right(p, n);
      // PとNの名称を入れ替える　
      node_pointer tmp = n;
      n = p;
      p = tmp;
    }

    // case 4
    // - (ii)の場合
    if (p == g->left && u == g->right && n == p->left) {
      rotate_right(g, p);
    }

    // - (iv)の場合
    //         Gb
    //     +---+---+
    //    Ub      Pr
    //         +--+--+
    //               Nr
    if (p == g->right && u == g->left && n == p->right) {
      rotate_left(g, p);
    }

    // PとGの色を入れ替える
    exchange_node_color(p, g);
  }

  // 要素を追加
  ft::pair<iterator, bool> insert_helper(const_reference value) {
    node_pointer inserted_node = NULL;
    bool has_inserted = false;

    // 初めて要素を追加
    if (empty()) {
      inserted_node = allocate_node(value);
      // rootにつける
      root_ = inserted_node;
      root_->parent = root_;
      // TODO 最後のイテレータのためだけにつける
      attach_end_node(inserted_node);
      attach_nil_node_to_left(inserted_node);
      has_inserted = true;
      // リバランス
      inserted_node->set_red_kind();
      rebalance_tree(inserted_node, inserted_node);
      return ft::make_pair(iterator(inserted_node, end_node()), has_inserted);
    }

    // ノードを辿って適切な場所にノードを作成
    node_pointer nd = root_;

    while (true) {
      if (comp_(KeyOfValue()(value), KeyOfValue()(nd->value))) {
        nd = nd->left;
        if (nd->is_nil_node()) {
          inserted_node = allocate_node(value);
          // leftにノードをつける
          attach_node_to_left(nd->parent, inserted_node);
          destruct_node(nd);
          // nil nodeをつける
          attach_nil_nodes(inserted_node);
          has_inserted = true;
          // リバランス
          inserted_node->set_red_kind();
          rebalance_tree(inserted_node, inserted_node->parent);
          break;
        }
      } else if (comp_(KeyOfValue()(nd->value), KeyOfValue()(value))) {
        nd = nd->right;
        if (nd == end_node()) {
          inserted_node = allocate_node(value);
          // rightにノードをつける
          attach_node_to_right(nd->parent, inserted_node);
          // TODO 最後のイテレータのためだけにつける
          attach_end_node(inserted_node);
          // nil nodeをつける
          attach_nil_node_to_left(inserted_node);
          // prev_parent->right->right->parent = prev_parent->right;
          has_inserted = true;
          // リバランス
          inserted_node->set_red_kind();
          rebalance_tree(inserted_node, inserted_node->parent);
          break;
        }

        // TODO rightがend nodeじゃない時もある
        if (nd->is_nil_node()) {
          inserted_node = allocate_node(value);
          // rightにノードをつける　
          attach_node_to_right(nd->parent, inserted_node);
          destruct_node(nd);
          // nil nodeをつける
          attach_nil_nodes(inserted_node);
          has_inserted = true;
          // リバランス
          inserted_node->set_red_kind();
          rebalance_tree(inserted_node, inserted_node->parent);
          break;
        }
      } else {
        has_inserted = false;
        // 同じ要素がすでに存在していたら、その要素を指すイテレータを返したいので、ノードをセット
        inserted_node = nd;
        break;
      }
    }

    return ft::make_pair(iterator(inserted_node, end_node()), has_inserted);
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
  void rotate_left(node_pointer p, node_pointer n) {
    node_pointer g = p->parent;
    node_pointer nl = n->left;

    p->right = nl;
    nl->parent = p;

    // Pがrootの場合
    if (is_root(p)) {
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
  void rotate_right(node_pointer p, node_pointer n) {
    node_pointer g = p->parent;
    node_pointer nr = n->right;

    p->left = nr;
    nr->parent = p;

    // Pがrootの場合
    if (is_root(p)) {
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
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return !(lhs < rhs) && !(lhs > rhs);
}

template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator!=(
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return !(lhs == rhs);
}

template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator<(
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator>=(
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return !(lhs < rhs);
}

template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator>(
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return rhs < lhs;
}

template <class Key, class Val, class KeyOfValue, class Compare,
          class Allocator>
bool operator<=(
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& lhs,
    const ft::detail::__tree<Key, Val, KeyOfValue, Compare, Allocator>& rhs) {
  return !(lhs > rhs);
}

} // namespace detail

} // namespace ft

#endif
