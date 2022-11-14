#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include "tree.hpp"
#include "pair.hpp"
#include "utils.hpp"

namespace ft {
template <class Key, class T, class Compare = ft::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const Key, T> value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;
  // typedef value_type& reference;
  // typedef const value_type& const_reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef typename __tree<Key, value_type, ft::Select1st<value_type>, Compare,
                          Allocator>::iterator iterator;
  typedef typename __tree<Key, value_type, ft::Select1st<value_type>, Compare,
                          Allocator>::const_iterator const_iterator;
  typedef typename std::reverse_iterator<iterator> reverse_iterator;
  typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

  // TODO いつ使う
  class value_compare {
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

  map() {}
  explicit map(const Compare& comp, const Allocator& alloc = Allocator());
  template <class InputIt>
  map(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator());
  map(const map& other);

  ~map() {}

  map& operator=(const map& other);

  // TODO テスト
  allocator_type get_allocator() const {
    return allocator_type(__tree_.__get_allocator());
  }
  T& at(const Key& key) {
    typename ft::__tree<key_type, value_type, ft::Select1st<value_type>,
                        Compare, Allocator>::iterator itr = __tree_.__find(key);
    if (itr == end()) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return itr->second;
  }
  const T& at(const Key& key) const {
    typename ft::__tree<key_type, value_type, ft::Select1st<value_type>,
                        Compare, Allocator>::const_iterator itr =
        __tree_.__find(key);
    if (itr == end()) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return itr->second;
  }
  T& operator[](const Key& key) {
    typename ft::__tree<key_type, value_type, ft::Select1st<value_type>,
                        Compare, Allocator>::iterator itr = __tree_.__find(key);
    // 見つからなかったら挿入
    if (itr == end()) {
      // pair<Key, T> p(key, T());
      insert(*itr);
      return itr->second;
    }
    return itr->second;
  }
  iterator begin() { return __tree_.__begin(); }
  const_iterator begin() const { return __tree_.__begin(); }
  iterator end() { return __tree_.__end(); }
  const_iterator end() const { return __tree_.__end(); }
  reverse_iterator rbegin() { return __tree_.__rbegin(); }
  const_reverse_iterator rbegin() const { return __tree_.__rbegin(); }
  reverse_iterator rend() { return __tree_.__rend(); }
  const_reverse_iterator rend() const { return __tree_.__rend(); }
  bool empty() { return __tree_.__empty(); }
  size_type size() const { return __tree_.__size(); }
  size_type max_size() const { return __tree_.__max_size(); }
  void clear();
  ft::pair<iterator, bool> insert(const value_type& value) {
    return __tree_.__insert_alt(value);
  }
  // //   iterator insert(iterator pos, const value_type& value);
  template <class InputIt>
  void insert(InputIt first, InputIt last) {
    for (InputIt itr = first; itr != last; ++itr) {
      insert(*itr);
    }
  }
  iterator erase(iterator pos) { return __tree_.__erase(pos); }
  iterator erase(iterator first, iterator last) {
    return __tree_.__erase(first, last);
  }
  size_type erase(const Key& key) { return __tree_.__erase(key); }
  void swap(map& other);
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

  // TODO テスト
  key_compare key_comp() const { return __tree_.__key_comp(); }
  value_compare value_comp() const { return value_compare(key_comp()); }

  // compare functions
  friend bool operator==(const ft::map<Key, T, Compare, Allocator>& lhs,
                         const ft::map<Key, T, Compare, Allocator>& rhs) {
    return lhs.__tree_ == rhs.__tree_;
  }
  friend bool operator!=(const ft::map<Key, T, Compare, Allocator>& lhs,
                         const ft::map<Key, T, Compare, Allocator>& rhs) {
    return lhs.__tree_ != rhs.__tree_;
  }
  friend bool operator<(const ft::map<Key, T, Compare, Allocator>& lhs,
                        const ft::map<Key, T, Compare, Allocator>& rhs) {
    return lhs.__tree_ < rhs.__tree_;
  }
  friend bool operator>=(const ft::map<Key, T, Compare, Allocator>& lhs,
                         const ft::map<Key, T, Compare, Allocator>& rhs) {
    return lhs.__tree_ >= rhs.__tree_;
  }
  friend bool operator>(const ft::map<Key, T, Compare, Allocator>& lhs,
                        const ft::map<Key, T, Compare, Allocator>& rhs) {
    return lhs.__tree_ > rhs.__tree_;
  }
  friend bool operator<=(const ft::map<Key, T, Compare, Allocator>& lhs,
                         const ft::map<Key, T, Compare, Allocator>& rhs) {
    return lhs.__tree_ <= rhs.__tree_;
  }

private:
  // typedef typename ft::__tree<value_type, Compare, Allocator> __tree;
  typedef typename ft::__tree<key_type, value_type, ft::Select1st<value_type>,
                              Compare, Allocator>
      __tree;

  __tree __tree_;
};

// swap
template <class Key, class Compare, class Alloc>
void swap(ft::map<Key, Compare, Alloc>& lhs, ft::map<Key, Compare, Alloc>& rhs);
}; // namespace ft

#endif
