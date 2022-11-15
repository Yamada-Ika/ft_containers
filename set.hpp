#ifndef SET_HPP
#define SET_HPP

#include <functional>
#include <memory>
#include "tree.hpp"
#include "utils.hpp"

namespace ft {

// Function object for performing comparisons. Unless specialized, invokes operator< on type T.
// std::less

template <class Key, class Compare = ft::less<Key>,
          class Allocator = std::allocator<Key> >
class set {
public:
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
                          Allocator>::const_iterator const_iterator;
  typedef typename std::reverse_iterator<iterator> reverse_iterator;
  typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

  set() {}
  explicit set(const Compare& comp, const Allocator& alloc = Allocator());
  template <class InputIt>
  set(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator());
  set(const set& other);

  ~set() {}

  set& operator=(const set& other);

  allocator_type get_allocator() const;

  iterator begin() { return __tree_.__begin(); }
  const_iterator begin() const { return __tree_.__begin(); }
  iterator end() { return __tree_.__end(); }
  const_iterator end() const { return __tree_.__end(); }
  reverse_iterator rbegin() { return __tree_.__rbegin(); }
  const_reverse_iterator rbegin() const { return __tree_.__rbegin(); }
  reverse_iterator rend() { return __tree_.__rend(); }
  const_reverse_iterator rend() const { return __tree_.__rend(); }

  bool empty() const { return __tree_.__empty(); }
  size_type size() const { return __tree_.__size(); }
  size_type max_size() const;
  void clear();
  ft::pair<iterator, bool> insert(const value_type& value) {
    return __tree_.__insert(value);
  }
  // iterator insert(iterator pos, const value_type& value);
  template <class InputIt>
  void insert(InputIt first, InputIt last) {
    for (InputIt itr = first; itr != last; ++itr) {
      insert(*itr);
    }
  }
  //   iterator erase(iterator pos);
  //   iterator erase(iterator first, iterator last);
  //   size_type erase(const Key& key);
  void swap(set& other);
  size_type count(const Key& key) const { return __tree_.__count(key); }
  iterator find(const Key& key) { return __tree_.__find(key); }
  const_iterator find(const Key& key) const { return __tree_.__find(key); }
  ft::pair<iterator, iterator> equal_range(const Key& key) {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }
  ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }
  iterator lower_bound(const Key& key) { return __tree_.__lower_bound(key); }
  const_iterator lower_bound(const Key& key) const {
    return __tree_.__lower_bound(key);
  }
  iterator upper_bound(const Key& key) { return __tree_.__upper_bound(key); }
  const_iterator upper_bound(const Key& key) const {
    return __tree_.__upper_bound(key);
  }
  key_compare key_comp() const { return __tree_.__key_comp(); }
  value_compare value_comp() const { return key_comp(); }

private:
  typedef typename ft::__tree<key_type, key_type, ft::Identity<value_type>,
                              Compare, Allocator>
      __tree;

  __tree __tree_;
};

// compare operators
template <class Key, class Compare, class Alloc>
bool operator==(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs);
template <class Key, class Compare, class Alloc>
bool operator!=(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs);
template <class Key, class Compare, class Alloc>
bool operator<(const ft::set<Key, Compare, Alloc>& lhs,
               const ft::set<Key, Compare, Alloc>& rhs);
template <class Key, class Compare, class Alloc>
bool operator>(const ft::set<Key, Compare, Alloc>& lhs,
               const ft::set<Key, Compare, Alloc>& rhs);
template <class Key, class Compare, class Alloc>
bool operator>=(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs);
template <class Key, class Compare, class Alloc>
bool operator<=(const ft::set<Key, Compare, Alloc>& lhs,
                const ft::set<Key, Compare, Alloc>& rhs);

// swap
template <class Key, class Compare, class Alloc>
void swap(ft::set<Key, Compare, Alloc>& lhs, ft::set<Key, Compare, Alloc>& rhs);

}; // namespace ft

#endif
