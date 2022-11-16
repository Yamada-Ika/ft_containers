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
        end_node_(__allocate_node(Val())), __tree_size_(0) {}
  explicit __tree(const Compare& comp, const Allocator& alloc = Allocator())
      : node_alloc_(node_allocator()), root_(NULL),
        end_node_(__allocate_node(Val())), __comp_(comp), __tree_size_(0) {}
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
  ft::pair<iterator, bool> __insert_helper(const_reference value) {
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
          has_inserted = true;
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

  ft::pair<iterator, bool> __insert(const_reference value) {
    ft::pair<iterator, bool> p = __insert_helper(value);
    LOG(ERROR) << "__insert/ has inserted " << p.second;
    if (p.second) {
      ++__tree_size_;
      LOG(ERROR) << "__insert/ size incremented";
      LOG(ERROR) << "__insert/ size : " << __tree_size_;
    }
    return p;
  }

  //  Inserts value in the position as close as possible to the position just prior to pos.
  iterator __insert(iterator pos, const_reference value) {
    // posからnode pointerをとる
    node_pointer pos_node;
    node_pointer new_node; // valueを持つノード

    // pos_nodeが右側にあればその間にnew nodeを挿入する
  }

  // ノードの要素を返す
  size_type __size() const {
    LOG(ERROR) << "__size/ " << __tree_size_;
    return __tree_size_;
  }

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

  size_type __erase_helper(const Key& key) {
    LOG(ERROR) << "__erase called";
    node_pointer target = __find_node_pointer(key);
    // keyがなかったら0を返す
    if (target == NULL) {
      LOG(ERROR) << "__erase not found";
      return 0;
    }

    // TODO ノード一個だけの時
    if (__is_root(target)) {
      root_->parent = NULL;
      root_ = NULL;
      return 1;
    }

    // 削除対象のノードが子を持たない場合
    if (__has_no_child(target)) {
      LOG(ERROR) << "__erase no child";
      // targetの親から見てtargetがleftにある場合
      if (__has_exist_on_left_from_parent_side(target)) {
        // TODO メモリ解放
        target->parent->left = NULL;
      } else {
        // targetの親から見てtargetがrightにある場合

        // targetのrightがend nodeの場合
        if (target->right == __end_node()) {
          // TODO メモリ解放
          target->parent->right = __end_node();
        } else if (target->right == NULL) {
          target->parent->right = NULL;
        } else {
          // ここに来るのはあり得ない
          LOG(ERROR) << "__erase/ " << key;
          assert(false);
        }
      }
      LOG(ERROR) << "__erase end";
      return 1;
    }

    // 削除対象のノードが一つだけ子を持つ場合
    // 左だけ
    if (__has_only_left_child(target)) {
      LOG(ERROR) << "__erase/__has_only_left_child";
      // その左にある子ノードをtargetの親のtargetがあった側につける
      // targetが親から見てleftにある場合
      if (__has_exist_on_left_from_parent_side(target)) {
        // 繋ぎかえ
        target->parent->left = target->left;
        target->left->parent = target->parent;
      } else {
        LOG(ERROR) << "__erase/__has_only_left_child/"
                      "__has_exist_on_right_from_parent_side";
        // rigth側にある場合
        target->parent->right = target->left;
        target->left->parent = target->parent;
      }
      // targetのrightにend nodeがあったら、一番右にあるノードにend nodeをつける
      if (target->right == __end_node()) {
        node::__get_max_node(target->left, __end_node())->right = __end_node();
      }
      return 1;
    }
    // 右だけ
    if (__has_only_right_child(target)) {
      LOG(ERROR) << "__erase/__has_only_right_child";
      // 同様
      // 右側にある子ノードをtargetの親のtargetがある側の子とする
      if (__has_exist_on_left_from_parent_side(target)) {
        target->parent->left = target->right;
        target->right->parent = target->parent;
      } else {
        target->parent->right = target->right;
        target->right->parent = target->parent;
      }
      return 1;
    }

    // 削除対象のノードが二つ子を持つ場合
    // - targetの右側部分木の最小ノードをtargetの位置に持ってこればよいらしい
    LOG(ERROR) << "__erase/ has two nodes";
    // 15
    node_pointer partial_min = node::__get_min_node(target->right);
    LOG(ERROR) << "__erase/ pmin val: " << partial_min->value;

    // 繋がれているノードを外す
    if (__has_exist_on_left_from_parent_side(partial_min)) {
      LOG(ERROR) << "__erase/ pmin on left from parent side";
      partial_min->parent->left = NULL;
    } else {
      LOG(ERROR) << "__erase/ pmin on right from parent side";
      if (partial_min->right == __end_node()) {
        LOG(ERROR) << "__erase/ pmin right node is end node";
        partial_min->parent->right = __end_node();
      } else {
        partial_min->parent->right = NULL;
      }
    }

    // 10
    // targetと隣接するノードをつなぐ
    if (__has_exist_on_left_from_parent_side(target)) {
      target->parent->left = partial_min;
    } else {
      LOG(ERROR) << "__erase/ target on right from parent side";
      target->parent->right = partial_min;
    }
    partial_min->parent = target->parent;
    partial_min->right = target->right;
    target->right->parent = partial_min;
    partial_min->left = target->left;
    target->left->parent = partial_min;

    return 1;
  }

  // __erase
  size_type __erase(const Key& key) {
    if (__erase_helper(key) == 1) {
      --__tree_size_;
      return 1;
    }
    return 0;
  }

  // iterator __erase(iterator pos)
  iterator __erase(iterator pos) {
    iterator res = pos;

    ++res;
    __erase(KeyOfValue()(*pos));
    return res;
  }

  // iterator __erase(iterator first, iterator last)
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
    return nd->right == NULL || nd->right == __end_node();
  }
  bool __has_left_child(node_pointer nd) { return !__has_no_left_child(nd); }
  bool __has_no_left_child(node_pointer nd) { return nd->left == NULL; }
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
