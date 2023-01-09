#ifndef SET_HPP
#define SET_HPP

#include <functional>
#include <memory>
#include "tree.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {

// Function object for performing comparisons. Unless specialized, invokes operator< on type T.
// std::less

template <class Key, class Compare = ft::less<Key>,
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
  typedef
      typename __tree<Key, Key, ft::Identity<Key>, Compare, Allocator>::iterator
          iterator;
  typedef typename __tree<Key, Key, ft::Identity<Key>, Compare,
                          Allocator>::__const_iterator const_iterator;
  typedef typename ft::reverse_iterator<iterator> reverse_iterator;
  typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

  /*
  *  Member types
  */
  set() {}

  explicit set(const Compare& comp, const Allocator& alloc = Allocator())
      : __tree_(comp, alloc) {}

  template <class InputIt>
  set(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator())
      : __tree_(comp, alloc) {
    // std::cerr << "set/constructor with iterator" << std::endl;
    insert(first, last);
  }

  set(const set& other) { *this = other; }

  ~set() {
    // _tree_.~__tree();
  }

  set& operator=(const set& other) {
    if (this == &other)
      return *this;

    __tree_ = other.__tree_;
    return *this;
  }

  allocator_type get_allocator() const {
    return allocator_type(__tree_.__get_allocator());
  }

  /*
  *  Iterators
  */
  iterator begin() { return __tree_.__begin(); }
  const_iterator begin() const { return __tree_.__begin(); }
  iterator end() { return __tree_.__end(); }
  const_iterator end() const { return __tree_.__end(); }
  reverse_iterator rbegin() { return __tree_.__rbegin(); }
  const_reverse_iterator rbegin() const { return __tree_.__rbegin(); }
  reverse_iterator rend() { return __tree_.__rend(); }
  const_reverse_iterator rend() const { return __tree_.__rend(); }

  /*
  *  Capacity
  */
  bool empty() const { return __tree_.__empty(); }
  size_type size() const { return __tree_.__size(); }
  size_type max_size() const { return __tree_.__max_size(); }

  /*
  *  Modifiers
  */
  void clear() { erase(begin(), end()); }
  ft::pair<iterator, bool> insert(const value_type& value) {
    return __tree_.__insert(value);
  }
  iterator insert(iterator pos, const value_type& value) {
    return __tree_.__insert(pos, value);
  }
  template <class InputIt>
  void insert(InputIt first, InputIt last) {
    for (; first != last; ++first) {
      insert(*first);
    }
  }
  iterator erase(iterator pos) { return __tree_.__erase(pos); }
  iterator erase(iterator first, iterator last) {
    return __tree_.__erase(first, last);
  }
  size_type erase(const Key& key) { return __tree_.__erase(key); }
  void swap(set& other) {
    set tmp;
    tmp.insert(other.begin(), other.end());
    other.clear();
    other.insert(begin(), end());
    clear();
    insert(tmp.begin(), tmp.end());
  }

  /*
  *  Lookup
  */
  size_type count(const Key& key) const { return __tree_.__count(key); }
  iterator find(const Key& key) { return __tree_.__find(key); }
  const_iterator find(const Key& key) const { return __tree_.__find(key); }
  ft::pair<iterator, iterator> equal_range(const Key& key) {
    return __tree_.__equal_range(key);
  }
  ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
    return __tree_.__equal_range_const(key);
  }
  iterator lower_bound(const Key& key) { return __tree_.__lower_bound(key); }
  const_iterator lower_bound(const Key& key) const {
    return __tree_.__lower_bound_const(key);
  }
  iterator upper_bound(const Key& key) { return __tree_.__upper_bound(key); }
  const_iterator upper_bound(const Key& key) const {
    return __tree_.__upper_bound(key);
  }

  /*
  *  Observers
  */
  key_compare key_comp() const { return __tree_.__key_comp(); }
  value_compare value_comp() const { return key_comp(); }

  /*
  *  Non-member functions
  */
  friend bool operator==(const ft::set<Key, Compare, Allocator>& lhs,
                         const ft::set<Key, Compare, Allocator>& rhs) {
    return lhs.__tree_ == rhs.__tree_;
  }
  friend bool operator!=(const ft::set<Key, Compare, Allocator>& lhs,
                         const ft::set<Key, Compare, Allocator>& rhs) {
    return lhs.__tree_ != rhs.__tree_;
  }
  friend bool operator<(const ft::set<Key, Compare, Allocator>& lhs,
                        const ft::set<Key, Compare, Allocator>& rhs) {
    return lhs.__tree_ < rhs.__tree_;
  }
  friend bool operator>(const ft::set<Key, Compare, Allocator>& lhs,
                        const ft::set<Key, Compare, Allocator>& rhs) {
    return lhs.__tree_ > rhs.__tree_;
  }
  friend bool operator>=(const ft::set<Key, Compare, Allocator>& lhs,
                         const ft::set<Key, Compare, Allocator>& rhs) {
    return lhs.__tree_ >= rhs.__tree_;
  }
  friend bool operator<=(const ft::set<Key, Compare, Allocator>& lhs,
                         const ft::set<Key, Compare, Allocator>& rhs) {
    return lhs.__tree_ <= rhs.__tree_;
  }

private:
  typedef typename ft::__tree<key_type, key_type, ft::Identity<value_type>,
                              Compare, Allocator>
      __tree;

  __tree __tree_;
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
