#ifndef C0B8EABC_51F0_4DBA_B6D9_11DC858D0094
#define C0B8EABC_51F0_4DBA_B6D9_11DC858D0094

#include "utils.hpp"
#include "is_integral.hpp"
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"
#include <memory>
#include <algorithm>

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
      : alloc(allocator_type()), first(allocate(0)), last(first),
        reserved_last(first + size()) {}

  explicit vector(const allocator_type& alloc)
      : alloc(alloc), first(allocate(0)), last(first),
        reserved_last(first + size()) {}

  explicit vector(size_type count, const_reference value = T(),
                  const allocator_type& alloc = allocator_type())
      : alloc(alloc), first(allocate(0)), last(first),
        reserved_last(first + size()) {
    resize(count, value);
  }

  template <typename InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type())
      : alloc(alloc) {
    typedef typename ft::is_integral<InputIterator>::type integral;
    initialize_dispatch(first, last, integral());
  }

  vector(const vector& other)
      : alloc(allocator_type()), first(allocate(0)), last(first),
        reserved_last(first + size()) {
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

  void assign(size_type count, const T& value) { fill_assign(count, value); }

  template <class InputIt>
  void assign(InputIt first, InputIt last) {
    typedef typename ft::is_integral<InputIt>::type integral;
    assign_dispatch(first, last, integral());
  }

  allocator_type get_allocator() { return alloc; }

  /*
  * Element access
  */
  reference at(size_type pos) {
    if (pos >= size()) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return first[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size()) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return first[pos];
  }

  reference operator[](size_type pos) { return first[pos]; }

  const_reference operator[](size_type pos) const { return first[pos]; }

  reference front() { return *first; }

  const_reference front() const { return *first; }

  reference back() { return *(last - 1); }

  const_reference back() const { return *(last - 1); }

  pointer data() { return first; }

  const_pointer data() const { return first; }

  /*
  * Iterators
  */
  iterator begin() { return first; }

  iterator end() { return last; }

  const_iterator begin() const { return first; }

  const_iterator end() const { return last; }

  reverse_iterator rbegin() { return reverse_iterator(last); }

  reverse_iterator rend() { return reverse_iterator(first); }

  const_reverse_iterator rbegin() const { return reverse_iterator(last); }

  const_reverse_iterator rend() const { return reverse_iterator(first); }

  /*
  * Capacity
  */
  bool empty() const { return begin() == end(); }

  size_type size() const { return std::distance(begin(), end()); }

  size_type max_size() const { return alloc.max_size(); }

  void reserve(size_type sz) {
    if (sz <= capacity()) {
      return;
    }

    // memory allocate before deallocate this instance's memmory
    pointer tmp = allocate(sz);
    iterator old_first = first;
    iterator old_last = last;
    size_type old_capacity = capacity();
    first = tmp;
    last = first;
    reserved_last = first + sz;

    // copy
    for (iterator old_iter = old_first; old_iter != old_last;
         ++old_iter, ++last) {
      construct(last, *old_iter);
    }

    alloc.deallocate(old_first, old_capacity);

    // deallocate old memory
    for (reverse_iterator riter = reverse_iterator(old_last),
                          rend = reverse_iterator(old_first);
         riter != rend; ++riter) {
      destroy(&*riter);
    }
  }

  size_type capacity() const { return reserved_last - first; }

  /*
  * Modifiers
  */
  void clear() { destroy_until(rend()); }

  iterator insert(const_iterator pos, const T& value) {
    return insert(pos, 1, value);
  }

  iterator insert(const_iterator pos, size_type count, const T& value) {
    return insert_fill(pos, count, value);
  }

  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    typedef typename ft::is_integral<InputIt>::type integral;
    return insert_dispatch(pos, first, last, integral());
  }

  iterator erase(iterator pos) { return erase_range(pos, pos + 1); }

  iterator erase(iterator first, iterator last) {
    return erase_range(first, last);
  }

  void push_back(const_reference v) {
    size_type cur_sz = size();

    if (cur_sz + 1 > capacity()) {
      if (cur_sz == 0) {
        cur_sz = 1;
      } else {
        cur_sz *= 2; // TODO care of overflow
      }
      reserve(cur_sz);
    }
    construct(last, v);
    ++last;
  }

  void pop_back() {
    alloc.destroy(last);
    --last;
  }

  void resize(size_type sz, const_reference v = T()) {
    size_type cur_sz = size();

    if (sz == cur_sz)
      return;
    if (sz < cur_sz) {
      size_type diff = cur_sz - sz;
      destroy_until(rbegin() + diff);
      last = first + sz;
      return;
    }
    reserve(sz);
    for (; last != reserved_last; ++last) {
      construct(last, v);
    }
  }

  void swap(vector& other) {
    vector tmp = other;
    other = *this;
    *this = tmp;
  }

private:
  allocator_type alloc;
  pointer first;
  pointer last;
  pointer reserved_last;

  pointer allocate(size_type n) { return alloc.allocate(n); }
  void deallocate() { alloc.deallocate(first, capacity()); }
  void construct(pointer ptr) { alloc.construct(ptr); }
  void construct(pointer ptr, const_reference value) {
    alloc.construct(ptr, value);
  }
  void destroy(pointer ptr) { alloc.destroy(ptr); }
  void destroy_all() { destroy(reserved_last); }
  void destroy_until(reverse_iterator rend) {
    for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last) {
      destroy(&*riter);
    }
  }

  template <typename Integral>
  void initialize_dispatch(Integral count, Integral value, true_type) {
    first = allocate(0);
    last = first;
    reserved_last = first + size();
    resize(count, value);
  }

  template <typename InputIterator>
  void initialize_dispatch(InputIterator other_first, InputIterator other_last,
                           false_type) {
    first = allocate(0);
    last = first;
    reserved_last = first + size();

    std::ptrdiff_t diff = std::distance(other_first, other_last);
    reserve(diff);
    for (InputIterator itr = other_first; itr != other_last; ++itr) {
      push_back(*itr);
    }
  }

  template <typename Integral>
  void assign_dispatch(Integral n, Integral val, true_type) {
    fill_assign(n, val);
  }

  template <typename InputIt>
  void assign_dispatch(InputIt first, InputIt last, false_type) {
    resize(0);
    size_type i = 0;
    for (iterator itr = first; itr != last; ++itr) {
      push_back(*itr);
      ++i;
    }
  }

  void fill_assign(size_type count, const T& value) { resize(count, value); }

  template <class InputIt>
  iterator insert_dispatch(const_iterator pos, InputIt first, InputIt last,
                           false_type) {
    size_type insert_from = pos - begin();
    iterator pos_itr = const_cast<iterator>(pos);
    for (InputIt itr = first; itr != last; ++itr) {
      pos_itr = insert(pos_itr, *itr);
      ++pos_itr;
    }
    return begin() + insert_from;
  }

  template <class Integral>
  iterator insert_dispatch(const_iterator pos, Integral count, Integral value,
                           true_type) {
    return insert_fill(pos, count, value);
  }

  iterator insert_fill(const_iterator pos, size_type count, const T& value) {
    // posにおけるインデックス
    size_type insert_from = pos - begin();
    size_type insert_to = insert_from + count - 1;

    // capaのチェック
    if (size() + count >= capacity()) {
      // 挿入したら要素がcountの数だけ増えるのでreserveする
      // TODO メモリ成長の効率化
      reserve(size() + count);
    }

    // 後ろからposまで値をムーブ
    for (size_type i = size() + count - 1; i > insert_to; --i) {
      first[i] = first[i - count];
      // ラップアラウンドによる意図せぬループを防ぐ
      if (i == 0) {
        break;
      }
    }
    // 挿入
    // TODO ラップアラウンド
    for (size_type i = insert_from; i <= insert_to; ++i) {
      first[i] = value;
      ++last; //　挿入した分要素が増える
    }
    return begin() + insert_from;
  }

  iterator erase_range(iterator from, iterator to) {
    size_type count = to - from;
    size_type erased_from = from - begin();

    // posの一個後ろから最後の要素まで前に詰める
    // TODO ラップアラウンド対策
    for (size_type i = erased_from; i + count <= size() - 1; ++i) {
      first[i] = first[i + count];
    }
    last -= count;
    // posの一個後ろのイテレータを返す
    return begin() + erased_from;
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
