#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include "tree.hpp"
#include "pair.hpp"

namespace ft {
template <class Key, class T, class Compare = std::less<Key>,
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
  typedef typename __tree<Key, T, Compare, Allocator>::iterator iterator;
  typedef typename __tree<Key, T, Compare, Allocator>::const_iterator
      const_iterator;
  typedef typename std::reverse_iterator<iterator> reverse_iterator;
  typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

  // class value_compare {
  // public:
  //   typedef bool result_type;
  //   typedef value_type first_argument_type;
  //   typedef value_type second_argument_type;

  //   bool operator()(const value_type& lhs, const value_type& rhs);

  // protected:
  //   Compare comp;
  //   value_compare(Compare c);
  // };

  map() {}
  explicit map(const Compare& comp, const Allocator& alloc = Allocator());
  template <class InputIt>
  map(InputIt first, InputIt last, const Compare& comp = Compare(),
      const Allocator& alloc = Allocator());
  map(const map& other);

  ~map() {}

  map& operator=(const map& other);

  allocator_type get_allocator() const;
  T& at(const Key& key) {
    typename ft::__tree<key_type, mapped_type, Compare, Allocator>::node_pointer
        ptr = __tree_.__find(key);
    if (ptr == NULL) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return ptr->value.second;
  }
  const T& at(const Key& key) const {
    typename ft::__tree<key_type, mapped_type, Compare, Allocator>::node_pointer
        ptr = __tree_.__find(key);
    if (ptr == NULL) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return ptr->value.second;
  }
  T& operator[](const Key& key) {
    typename ft::__tree<key_type, mapped_type, Compare, Allocator>::node_pointer
        ptr = __tree_.__find(key);
    // 見つからなかったら挿入
    if (ptr == NULL) {
      pair<Key, T> p(key, T());
      insert(p);
      return at(key);
    }
    return ptr->value.second;
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
  size_type max_size() const;
  void clear();
  // ft::pair<iterator, bool> insert(const value_type& value);
  // //   iterator insert(iterator pos, const value_type& value);
  // template <class InputIt>
  // void insert(InputIt first, InputIt last);
  // TODO テストように生やしたメソッド
  void insert(const_reference value) { __tree_.__insert(value); }
  void insert(key_type k, mapped_type v) { __tree_.__insert(k, v); }
  // //   iterator erase(iterator pos);
  // // //   iterator erase(iterator first, iterator last);
  size_type erase(const Key& key);
  void swap(map& other);
  size_type count(const Key& key) const;
  //   iterator find(const Key& key);
  //   const_iterator find(const Key& key) const;
  // //   std::pair<iterator, iterator> equal_range(const Key& key);
  // //   std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
  //   iterator lower_bound(const Key& key);
  //   const_iterator lower_bound(const Key& key) const;
  //   iterator upper_bound(const Key& key);
  //   const_iterator upper_bound(const Key& key) const;
  key_compare key_comp() const;
  // value_compare value_comp() const;

private:
  // typedef typename ft::__tree<value_type, Compare, Allocator> __tree;
  typedef typename ft::__tree<key_type, mapped_type, Compare, Allocator> __tree;

  __tree __tree_;
};

// compare operators
template <class Key, class Compare, class Alloc>
bool operator==(const ft::map<Key, Compare, Alloc>& lhs,
                const ft::map<Key, Compare, Alloc>& rhs);
template <class Key, class Compare, class Alloc>
bool operator!=(const ft::map<Key, Compare, Alloc>& lhs,
                const ft::map<Key, Compare, Alloc>& rhs);
template <class Key, class Compare, class Alloc>
bool operator>(const ft::map<Key, Compare, Alloc>& lhs,
               const ft::map<Key, Compare, Alloc>& rhs);
template <class Key, class Compare, class Alloc>
bool operator<(const ft::map<Key, Compare, Alloc>& lhs,
               const ft::map<Key, Compare, Alloc>& rhs);
template <class Key, class Compare, class Alloc>
bool operator>=(const ft::map<Key, Compare, Alloc>& lhs,
                const ft::map<Key, Compare, Alloc>& rhs);
template <class Key, class Compare, class Alloc>
bool operator<=(const ft::map<Key, Compare, Alloc>& lhs,
                const ft::map<Key, Compare, Alloc>& rhs);

// swap
template <class Key, class Compare, class Alloc>
void swap(ft::map<Key, Compare, Alloc>& lhs, ft::map<Key, Compare, Alloc>& rhs);
}; // namespace ft

#endif
