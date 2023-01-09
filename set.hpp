#ifndef SET_HPP
#define SET_HPP

#include <functional>
#include <memory>
#include <algorithm>
#include "tree.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {
template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key> >
class set {
public:
  /*
  *  Member types
  */
  typedef Key key_type;
  typedef Key value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Allocator allocator_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef typename ft::detail::__tree<Key, Key, ft::detail::__Identity<Key>,
                                      Compare, Allocator>::iterator iterator;
  typedef typename ft::detail::__tree<Key, Key, ft::detail::__Identity<Key>,
                                      Compare, Allocator>::const_iterator
      const_iterator;
  typedef typename ft::reverse_iterator<iterator> reverse_iterator;
  typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

  /*
  *  Member functions
  */
  set() {}

  explicit set(const Compare& comp, const Allocator& alloc = Allocator())
      : tree_(comp, alloc) {}

  template <class InputIt>
  set(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator())
      : tree_(comp, alloc) {
    insert(first, last);
  }

  set(const set& other) { *this = other; }

  ~set() {}

  set& operator=(const set& other) {
    if (this == &other) {
      return *this;
    }
    tree_ = other.tree_;
    return *this;
  }

  allocator_type get_allocator() const {
    return allocator_type(tree_.get_allocator());
  }

  /*
  *  Iterators
  */
  iterator begin() { return tree_.begin(); }

  const_iterator begin() const { return tree_.begin(); }

  iterator end() { return tree_.end(); }

  const_iterator end() const { return tree_.end(); }

  reverse_iterator rbegin() { return tree_.rbegin(); }

  const_reverse_iterator rbegin() const { return tree_.rbegin(); }

  reverse_iterator rend() { return tree_.rend(); }

  const_reverse_iterator rend() const { return tree_.rend(); }

  /*
  *  Capacity
  */
  bool empty() const { return tree_.empty(); }

  size_type size() const { return tree_.size(); }

  size_type max_size() const { return tree_.max_size(); }

  /*
  *  Modifiers
  */
  void clear() { tree_.clear(); }

  ft::pair<iterator, bool> insert(const value_type& value) {
    return tree_.insert(value);
  }

  iterator insert(iterator pos, const value_type& value) {
    return tree_.insert(pos, value);
  }

  template <class InputIt>
  void insert(InputIt first, InputIt last) {
    tree_.insert(first, last);
  }

  iterator erase(iterator pos) { return tree_.erase(pos); }

  iterator erase(iterator first, iterator last) {
    return tree_.erase(first, last);
  }

  size_type erase(const Key& key) { return tree_.erase(key); }

  void swap(set& other) {
    set tmp(other);
    other = *this;
    *this = tmp;
  }

  /*
  *  Lookup
  */
  size_type count(const Key& key) const { return tree_.count(key); }

  iterator find(const Key& key) { return tree_.find(key); }

  const_iterator find(const Key& key) const { return tree_.find(key); }

  ft::pair<iterator, iterator> equal_range(const Key& key) {
    return tree_.equal_range(key);
  }

  ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
    return tree_.equal_range(key);
  }

  iterator lower_bound(const Key& key) { return tree_.lower_bound(key); }

  const_iterator lower_bound(const Key& key) const {
    return tree_.lower_bound(key);
  }

  iterator upper_bound(const Key& key) { return tree_.__upper_bound(key); }

  const_iterator upper_bound(const Key& key) const {
    return tree_.__upper_bound(key);
  }

  /*
  *  Observers
  */
  key_compare key_comp() const { return tree_.key_comp(); }

  value_compare value_comp() const { return key_comp(); }

  /*
  *  Non-member functions
  */
  friend bool operator==(const set& lhs, const set& rhs) {
    return lhs.tree_ == rhs.tree_;
  }

  friend bool operator!=(const set& lhs, const set& rhs) {
    return lhs.tree_ != rhs.tree_;
  }

  friend bool operator<(const set& lhs, const set& rhs) {
    return lhs.tree_ < rhs.tree_;
  }

  friend bool operator>(const set& lhs, const set& rhs) {
    return lhs.tree_ > rhs.tree_;
  }

  friend bool operator>=(const set& lhs, const set& rhs) {
    return lhs.tree_ >= rhs.tree_;
  }

  friend bool operator<=(const set& lhs, const set& rhs) {
    return lhs.tree_ <= rhs.tree_;
  }

private:
  typedef typename ft::detail::__tree<key_type, key_type,
                                      ft::detail::__Identity<value_type>,
                                      Compare, Allocator>
      tree;

  tree tree_;
};

/*
*  Non-member functions
*/
template <class Key, class Compare, class Alloc>
void swap(ft::set<Key, Compare, Alloc>& lhs,
          ft::set<Key, Compare, Alloc>& rhs) {
  lhs.swap(rhs);
}
} // namespace ft

#endif
