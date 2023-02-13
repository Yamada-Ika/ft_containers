#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include <algorithm>
#include "tree.hpp"
#include "pair.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"

namespace ft {
template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
public:
  /*
  *  Member types
  */
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const Key, T> value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef typename ft::detail::__tree<Key, value_type,
                                      ft::detail::__Select1st<value_type>,
                                      Compare, Allocator>::iterator iterator;
  typedef
      typename ft::detail::__tree<Key, value_type,
                                  ft::detail::__Select1st<value_type>, Compare,
                                  Allocator>::const_iterator const_iterator;
  typedef typename ft::reverse_iterator<iterator> reverse_iterator;
  typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

  /*
  *  Member classes
  */
  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    friend class map<Key, T, Compare, Allocator>;

  public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;

    bool operator()(const value_type& lhs, const value_type& rhs) const {
      return comp(lhs.first, rhs.first);
    }

  protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}
  };

  /*
  *  Member functions
  */
  map() {}

  explicit map(const Compare& comp, const Allocator& alloc = Allocator())
      : tree_(comp, alloc) {}

  template <class InputIt>
  map(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator())
      : tree_(comp, alloc) {
    insert(first, last);
  }

  map(const map& other) { *this = other; }

  ~map() {}

  map& operator=(const map& other) {
    if (this == &other)
      return *this;

    tree_ = other.tree_;
    return *this;
  }

  allocator_type get_allocator() const {
    return allocator_type(tree_.get_allocator());
  }

  /*
  *  Member functions
  */
  T& at(const Key& key) {
    iterator itr = find(key);
    if (itr == end()) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return itr->second;
  }

  const T& at(const Key& key) const {
    const_iterator itr = find(key);
    if (itr == end()) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return itr->second;
  }

  T& operator[](const Key& key) {
    iterator itr = find(key);
    if (itr == end()) {
      return insert(ft::make_pair(key, T())).first->second;
    }
    return itr->second;
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

  void swap(map& other) { tree_.swap(other.tree_); }

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

  iterator upper_bound(const Key& key) { return tree_.upper_bound(key); }

  const_iterator upper_bound(const Key& key) const {
    return tree_.upper_bound(key);
  }

  /*
  *  Observers
  */
  key_compare key_comp() const { return tree_.key_comp(); }

  value_compare value_comp() const { return value_compare(key_comp()); }

  /*
  *  Non-member functions
  */
  friend bool operator==(const map& lhs, const map& rhs) {
    return lhs.tree_ == rhs.tree_;
  }

  friend bool operator!=(const map& lhs, const map& rhs) {
    return lhs.tree_ != rhs.tree_;
  }

  friend bool operator<(const map& lhs, const map& rhs) {
    return lhs.tree_ < rhs.tree_;
  }

  friend bool operator>=(const map& lhs, const map& rhs) {
    return lhs.tree_ >= rhs.tree_;
  }

  friend bool operator>(const map& lhs, const map& rhs) {
    return lhs.tree_ > rhs.tree_;
  }

  friend bool operator<=(const map& lhs, const map& rhs) {
    return lhs.tree_ <= rhs.tree_;
  }

private:
  typedef typename ft::detail::__tree<key_type, value_type,
                                      ft::detail::__Select1st<value_type>,
                                      Compare, Allocator>
      tree;

  tree tree_;
};

template <class Key, class Compare, class Alloc>
void swap(ft::map<Key, Compare, Alloc>& lhs,
          ft::map<Key, Compare, Alloc>& rhs) {
  lhs.swap(rhs);
}
} // namespace ft

#endif
