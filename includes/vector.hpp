#ifndef C0B8EABC_51F0_4DBA_B6D9_11DC858D0094
#define C0B8EABC_51F0_4DBA_B6D9_11DC858D0094

#include "utils.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"
#include <memory>
#include <algorithm>
#include <iostream>

namespace ft {
template <typename T, typename Allocator = std::allocator<T> >
class vector {
public:
  /*
  * Member types
  */
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef pointer iterator;
  typedef const_pointer const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  /*
  * Member functions
  */
  vector()
      : alloc_(allocator_type()), first_(allocate(0)), last_(first_),
        reserved_last_(first_ + size()) {}

  explicit vector(const allocator_type& alloc_)
      : alloc_(alloc_), first_(allocate(0)), last_(first_),
        reserved_last_(first_ + size()) {}

  explicit vector(size_type count, const_reference value = T(),
                  const allocator_type& alloc_ = allocator_type())
      : alloc_(alloc_), first_(allocate(0)), last_(first_),
        reserved_last_(first_ + size()) {
    resize(count, value);
  }

  template <typename InputIterator>
  vector(InputIterator first,
         typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                InputIterator>::type last,
         const allocator_type& alloc = allocator_type())
      : alloc_(alloc) {
    first_ = allocate(0);
    last_ = first_;
    reserved_last_ = first_ + size();

    std::ptrdiff_t diff = std::distance(first, last);
    reserve(diff);
    for (InputIterator itr = first; itr != last; ++itr) {
      push_back(*itr);
    }
  }

  vector(const vector& other)
      : alloc_(allocator_type()), first_(allocate(0)), last_(first_),
        reserved_last_(first_ + size()) {
    *this = other;
  }

  ~vector() {
    clear();
    deallocate();
  }

  vector& operator=(const vector& other) {
    if (this == &other) {
      return *this;
    }
    resize(other.size());
    std::copy(other.begin(), other.end(), begin());
    return *this;
  }

  void assign(size_type count, const T& value) { resize(count, value); }

  template <class InputIt>
  void assign(InputIt first,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type last) {
    resize(0);
    size_type i = 0;
    for (iterator itr = first; itr != last; ++itr) {
      push_back(*itr);
      ++i;
    }
  }

  allocator_type get_allocator() { return alloc_; }

  /*
  * Element access
  */
  reference at(size_type pos) {
    if (pos >= size()) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return first_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size()) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return first_[pos];
  }

  reference operator[](size_type pos) { return first_[pos]; }

  const_reference operator[](size_type pos) const { return first_[pos]; }

  reference front() { return *first_; }

  const_reference front() const { return *first_; }

  reference back() { return *(last_ - 1); }

  const_reference back() const { return *(last_ - 1); }

  pointer data() { return first_; }

  const_pointer data() const { return first_; }

  /*
  * Iterators
  */
  iterator begin() { return first_; }

  iterator end() { return last_; }

  const_iterator begin() const { return first_; }

  const_iterator end() const { return last_; }

  reverse_iterator rbegin() { return reverse_iterator(last_); }

  reverse_iterator rend() { return reverse_iterator(first_); }

  const_reverse_iterator rbegin() const { return reverse_iterator(last_); }

  const_reverse_iterator rend() const { return reverse_iterator(first_); }

  /*
  * Capacity
  */
  bool empty() const { return begin() == end(); }

  size_type size() const { return std::distance(begin(), end()); }

  size_type max_size() const { return alloc_.max_size(); }

  void reserve(size_type new_cap) {
    if (new_cap > max_size()) {
      throw std::length_error("vector::reserve");
    }
    if (new_cap <= capacity()) {
      return;
    }

    // memory allocate before deallocate this instance's memmory
    pointer tmp = allocate(new_cap);
    iterator old_first_ = first_;
    iterator old_last = last_;
    size_type old_capacity = capacity();
    first_ = tmp;
    last_ = first_;
    reserved_last_ = first_ + new_cap;

    // copy
    for (iterator old_iter = old_first_; old_iter != old_last;
         ++old_iter, ++last_) {
      construct(last_, *old_iter);
    }

    // deallocate old memory
    alloc_.deallocate(old_first_, old_capacity);
    for (reverse_iterator riter = reverse_iterator(old_last),
                          rend = reverse_iterator(old_first_);
         riter != rend; ++riter) {
      destroy(&*riter);
    }
  }

  size_type capacity() const { return reserved_last_ - first_; }

  /*
  * Modifiers
  */
  void clear() { destroy_from_to_in_reverse_order(rend()); }

  iterator insert(const_iterator pos, const T& value) {
    return insert(pos, 1, value);
  }

  iterator insert(const_iterator pos, size_type count, const T& value) {
    return insert_fill(pos, count, value);
  }

  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first,
                  typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                         InputIt>::type last) {
    size_type insert_from = pos - begin();
    iterator pos_itr = const_cast<iterator>(pos);
    for (InputIt itr = first; itr != last; ++itr) {
      pos_itr = insert(pos_itr, *itr);
      ++pos_itr;
    }
    return begin() + insert_from;
  }

  iterator erase(iterator pos) { return erase_range(pos, pos + 1); }

  iterator erase(iterator first, iterator last) {
    return erase_range(first, last);
  }

  void push_back(const_reference v) {
    if (size() + 1 > capacity()) {
      grow_memory_twice_if_needed();
    }
    construct(last_, v);
    ++last_;
  }

  void pop_back() {
    alloc_.destroy(last_);
    --last_;
  }

  void resize(size_type count, const_reference v = T()) {
    size_type current_size = size();

    if (count == current_size) {
      return;
    }

    if (current_size > count) {
      size_type size_to_be_destroyed = current_size - count;
      destroy_from_to_in_reverse_order(rbegin() + size_to_be_destroyed);
      last_ = first_ + count;
      return;
    }

    grow_memory_if_needed(count - current_size);

    for (; current_size < count; ++last_, ++current_size) {
      construct(last_, v);
    }
  }

  void swap(vector& other) {
    vector tmp = other;
    other = *this;
    *this = tmp;
  }

private:
  allocator_type alloc_;
  pointer first_;
  pointer last_;
  pointer reserved_last_;

  pointer allocate(size_type n) { return alloc_.allocate(n); }
  void deallocate() { alloc_.deallocate(first_, capacity()); }
  void construct(pointer ptr) { alloc_.construct(ptr); }
  void construct(pointer ptr, const_reference value) {
    alloc_.construct(ptr, value);
  }
  void destroy(pointer ptr) { alloc_.destroy(ptr); }
  void destroy_all() { destroy(reserved_last_); }
  void destroy_from_to_in_reverse_order(reverse_iterator rend) {
    for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last_) {
      destroy(&*riter);
    }
  }

  iterator insert_fill(const_iterator pos, size_type count, const T& value) {
    // posにおけるインデックス
    size_type insert_from = pos - begin();
    size_type insert_to = insert_from + count - 1;

    grow_memory_if_needed(count);

    // 後ろからposまで値をムーブ
    for (size_type i = size() + count - 1; i > insert_to; --i) {
      first_[i] = first_[i - count];
      // ラップアラウンドによる意図せぬループを防ぐ
      if (i == 0) {
        break;
      }
    }
    // 挿入
    // TODO ラップアラウンド
    for (size_type i = insert_from; i <= insert_to; ++i) {
      first_[i] = value;
      ++last_; //　挿入した分要素が増える
    }
    return begin() + insert_from;
  }

  iterator erase_range(iterator from, iterator to) {
    size_type count = to - from;
    size_type erased_from = from - begin();

    // posの一個後ろから最後の要素まで前に詰める
    // TODO ラップアラウンド対策
    for (size_type i = erased_from; i + count <= size() - 1; ++i) {
      first_[i] = first_[i + count];
    }
    last_ -= count;
    // posの一個後ろのイテレータを返す
    return begin() + erased_from;
  }

  void grow_memory_if_needed(size_type count) {
    // capaのチェック
    if (size() + count >= capacity()) {
      if (size() + count > size() * 2) {
        reserve(size() + count);
      } else {
        grow_memory_twice_if_needed();
      }
    }
  }

  void grow_memory_twice_if_needed() {
    size_type cur_sz = size();

    if (cur_sz == 0) {
      cur_sz = 1;
    } else {
      cur_sz *= 2; // TODO care of overflow
    }
    reserve(cur_sz);
  }
};

/*
* Non-member functions
*/
template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return !(lhs < rhs) && !(lhs > rhs);
}

template <class T, class Alloc>
bool operator!=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc>& lhs,
               const ft::vector<T, Alloc>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template <class T, class Alloc>
bool operator>=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return !(lhs < rhs);
}

template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc>& lhs,
               const ft::vector<T, Alloc>& rhs) {
  return rhs < lhs;
}

template <class T, class Alloc>
bool operator<=(const ft::vector<T, Alloc>& lhs,
                const ft::vector<T, Alloc>& rhs) {
  return !(lhs > rhs);
}

template <class T, class Alloc>
void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) {
  lhs.swap(rhs);
}

} // namespace ft

#endif /* C0B8EABC_51F0_4DBA_B6D9_11DC858D0094 */
