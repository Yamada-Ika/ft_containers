#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "is_integral.hpp"
#include "enable_if.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"
#include <memory>
#include <algorithm>

namespace ft {

template <typename T>
class deque_iterator {
public:
  typedef std::random_access_iterator_tag iterator_category;
  typedef deque_iterator<T> iterator;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef deque_iterator Self;

  deque_iterator(pointer first, pointer pos, size_type size, size_type cap,
                 pointer front, pointer back)
      : first_(first), pos_(pos), size_(size), cap_(cap), front_(front),
        back_(back) {}
  deque_iterator(const Self& other) { *this = other; }
  ~deque_iterator() {}
  deque_iterator& operator=(const deque_iterator& other) {
    if (this == &other)
      return *this;

    first_ = other.first_;
    pos_ = other.pos_;
    size_ = other.size_;
    cap_ = other.cap_;
    front_ = other.front_;
    back_ = other.back_;
    return *this;
  }

  reference operator*() const { return *pos_; }
  pointer operator->() const { return pos_; }
  Self& operator++() {
    ++pos_;
    if (pos_ >= first_ + cap_) {
      // xxxxxxxx
      //         |
      //       pos_
      pos_ = first_;
    }
    return *this;
  }
  Self operator++(int) {
    Self tmp = *this;
    ++*this;
    return tmp;
  }
  Self& operator--() {
    --pos_;
    if (pos_ < first_) {
      pos_ = first_ + cap_ - 1;
    }
    return *this;
  }
  Self operator--(int) {
    Self tmp = *this;
    --*this;
    return tmp;
  }
  Self& operator+=(difference_type n) {
    if (pos_ + n >= first_ + cap_) {
      // n > cap_
      // xxxxxxxxxxxxx
      //         |
      //        pos_
      size_type pos_to_r_buf_boundry = first_ + cap_ - pos_;
      pos_ = first_ + ((n - pos_to_r_buf_boundry) % cap_);
    } else {
      pos_ += n;
    }
    return *this;
  }
  Self& operator-=(difference_type n) {
    if (pos_ - n < first_) {
      // n > cap_
      // xxxxxxxxxxxxx
      //         |
      //        pos_
      size_type pos_to_l_buf_boundry = pos_ - first_;
      pos_ = first_ + cap_ - ((n - pos_to_l_buf_boundry) % cap_);
    } else {
      pos_ -= n;
    }
    return *this;
  }
  reference operator[](difference_type n) const {
    if (pos_ + n >= first_ + cap_) {
      // n > cap_
      // xxxxxxxxxxxxx
      //         |
      //        pos_
      size_type pos_to_r_buf_boundry = first_ + cap_ - pos_;
      n = (n - pos_to_r_buf_boundry) % cap_;
      return first_[n];
    }
    return pos_[n];
  }

  // compare operators
  friend bool operator==(const Self& lhs, const Self& rhs) {
    return lhs.pos_ == rhs.pos_;
  }
  friend bool operator!=(const Self& lhs, const Self& rhs) {
    return !(lhs == rhs);
  }
  friend bool operator<(const Self& lhs, const Self& rhs) {
    return (lhs.first_ == rhs.first_) ? lhs.pos_ < rhs.pos_
                                      : lhs.first_ < rhs.first_;
  }
  friend bool operator>=(const Self& lhs, const Self& rhs) {
    return !(lhs < rhs);
  }
  friend bool operator>(const Self& lhs, const Self& rhs) { return rhs < lhs; }
  friend bool operator<=(const Self& lhs, const Self& rhs) {
    return !(lhs > rhs);
  }
  friend difference_type operator-(const Self& lhs, const Self& rhs) {
    if (lhs.front_ < lhs.back_) {
      // xxxxxxxxxxxxxxx
      //    f      b
      return lhs.pos_ - rhs.pos_;
    } else {
      // xxxxxxxxxxxxxxx
      //  l b      f  r
      if (lhs.pos_ <= lhs.back_ && rhs.front_ <= rhs.pos_) {
        return lhs.cap_ - (rhs.pos_ - lhs.pos_);
      } else if (rhs.pos_ <= lhs.back_ && rhs.front_ <= lhs.pos_) {
        // xxxxxxxxxxxxxxx
        //  r b      f  l
        return -(lhs.cap_ - (lhs.pos_ - rhs.pos_));
      } else {
        // xxxxxxxxxxxxxxx
        //    b      f r l
        return lhs.pos_ - rhs.pos_;
      }
    }
    return 0;
  }
  friend Self operator+(const Self& lhs, difference_type n) {
    Self tmp = lhs;
    return tmp += n;
  }
  friend Self operator+(difference_type n, const Self& rhs) { return rhs + n; }
  friend Self operator-(const Self& lhs, difference_type n) {
    Self tmp = lhs;
    return tmp -= n;
  }

  // デフォルトのバッファーサイズ
  const static size_type buffer_size = 512;

  // member
  // dequeが内部的に持っている配列の先頭を指すポインタ
  pointer first_;
  // deque_iteratorが指す配列の要素を指すポインタ
  pointer pos_;
  // dequeが内部的に持っている配列の中に詰められている要素の数
  size_type size_;
  // dequeが内部的に持っている配列の容量
  size_type cap_;
  pointer front_;
  pointer back_;
};

template <typename T>
class const_deque_iterator {
public:
  typedef std::random_access_iterator_tag iterator_category;
  typedef const_deque_iterator<T> iterator;
  typedef T value_type;
  typedef T* pointer;
  typedef const T& reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef const_deque_iterator Self;
  typedef deque_iterator<T> __non_const_iterator;

  const_deque_iterator(pointer first, pointer pos, size_type size,
                       size_type cap, pointer front, pointer back)
      : first_(first), pos_(pos), size_(size), cap_(cap), front_(front),
        back_(back) {}
  const_deque_iterator(const Self& other) { *this = other; }
  ~const_deque_iterator() {}
  const_deque_iterator& operator=(const const_deque_iterator& other) {
    if (this == &other)
      return *this;

    first_ = other.first_;
    pos_ = other.pos_;
    size_ = other.size_;
    cap_ = other.cap_;
    front_ = other.front_;
    back_ = other.back_;
    return *this;
  }
  const_deque_iterator(__non_const_iterator itr)
      : first_(itr.first_), pos_(itr.pos_), size_(itr.size_), cap_(itr.cap_),
        front_(itr.front_), back_(itr.back_) {}

  reference operator*() const { return *pos_; }
  pointer operator->() const { return pos_; }
  Self& operator++() {
    ++pos_;
    if (pos_ >= first_ + cap_) {
      // xxxxxxxx
      //         |
      //       pos_
      pos_ = first_;
    }
    return *this;
  }
  Self operator++(int) {
    Self tmp = *this;
    ++*this;
    return tmp;
  }
  Self& operator--() {
    --pos_;
    if (pos_ < first_) {
      pos_ = first_ + cap_ - 1;
    }
    return *this;
  }
  Self operator--(int) {
    Self tmp = *this;
    --*this;
    return tmp;
  }
  Self& operator+=(difference_type n) {
    if (pos_ + n >= first_ + cap_) {
      // n > cap_
      // xxxxxxxxxxxxx
      //         |
      //        pos_
      size_type pos_to_r_buf_boundry = first_ + cap_ - pos_;
      pos_ = first_ + ((n - pos_to_r_buf_boundry) % cap_);
    } else {
      pos_ += n;
    }
    return *this;
  }
  Self& operator-=(difference_type n) {
    if (pos_ - n < first_) {
      // n > cap_
      // xxxxxxxxxxxxx
      //         |
      //        pos_
      size_type pos_to_l_buf_boundry = pos_ - first_;
      pos_ = first_ + cap_ - ((n - pos_to_l_buf_boundry) % cap_);
    } else {
      pos_ -= n;
    }
    return *this;
  }
  reference operator[](difference_type n) const {
    if (pos_ + n >= first_ + cap_) {
      // n > cap_
      // xxxxxxxxxxxxx
      //         |
      //        pos_
      size_type pos_to_r_buf_boundry = first_ + cap_ - pos_;
      n = (n - pos_to_r_buf_boundry) % cap_;
      return first_[n];
    }
    return pos_[n];
  }

  // compare operators
  friend bool operator==(const Self& lhs, const Self& rhs) {
    return lhs.pos_ == rhs.pos_;
  }
  friend bool operator!=(const Self& lhs, const Self& rhs) {
    return !(lhs == rhs);
  }
  friend bool operator<(const Self& lhs, const Self& rhs) {
    return (lhs.first_ == rhs.first_) ? lhs.pos_ < rhs.pos_
                                      : lhs.first_ < rhs.first_;
  }
  friend bool operator>=(const Self& lhs, const Self& rhs) {
    return !(lhs < rhs);
  }
  friend bool operator>(const Self& lhs, const Self& rhs) { return rhs < lhs; }
  friend bool operator<=(const Self& lhs, const Self& rhs) {
    return !(lhs > rhs);
  }
  friend difference_type operator-(const Self& lhs, const Self& rhs) {
    if (lhs.front_ < lhs.back_) {
      // xxxxxxxxxxxxxxx
      //    f      b
      return lhs.pos_ - rhs.pos_;
    } else {
      // xxxxxxxxxxxxxxx
      //  l b      f  r
      if (lhs.pos_ <= lhs.back_ && rhs.front_ <= rhs.pos_) {
        return lhs.cap_ - (rhs.pos_ - lhs.pos_);
      } else if (rhs.pos_ <= lhs.back_ && rhs.front_ <= lhs.pos_) {
        // xxxxxxxxxxxxxxx
        //  r b      f  l
        return -(lhs.cap_ - (lhs.pos_ - rhs.pos_));
      } else {
        // xxxxxxxxxxxxxxx
        //    b      f r l
        return lhs.pos_ - rhs.pos_;
      }
    }
    return 0;
  }
  friend Self operator+(const Self& lhs, difference_type n) {
    Self tmp = lhs;
    return tmp += n;
  }
  friend Self operator+(difference_type n, const Self& rhs) { return rhs + n; }
  friend Self operator-(const Self& lhs, difference_type n) {
    Self tmp = lhs;
    return tmp -= n;
  }

  // デフォルトのバッファーサイズ
  const static size_type buffer_size = 512;

  // member
  // dequeが内部的に持っている配列の先頭を指すポインタ
  pointer first_;
  // deque_iteratorが指す配列の要素を指すポインタ
  pointer pos_;
  // dequeが内部的に持っている配列の中に詰められている要素の数
  size_type size_;
  // dequeが内部的に持っている配列の容量
  size_type cap_;
  pointer front_;
  pointer back_;
};

template <class T, class Allocator = std::allocator<T> >
class deque {
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
  typedef deque_iterator<T> iterator;
  typedef const_deque_iterator<T> const_iterator;
  typedef typename ft::reverse_iterator<iterator> reverse_iterator;
  typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

  /*
  * Member functions
  */
  deque()
      : first_(allocate(buffer_size)), front_(first_), back_(front_),
        alloc_(Allocator()), current_bufsize(buffer_size) {}

  explicit deque(const Allocator& alloc)
      : first_(allocate(buffer_size)), front_(first_), back_(front_),
        alloc_(alloc), current_bufsize(buffer_size) {}

  explicit deque(size_type count, const T& value = T(),
                 const Allocator& alloc = Allocator())
      : first_(allocate(buffer_size)), front_(first_), back_(front_),
        alloc_(alloc), current_bufsize(buffer_size) {
    assign_fill(count, value);
  }

  template <class InputIt>
  deque(InputIt first,
        typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type
            last,
        const Allocator& alloc = Allocator())
      : first_(allocate(buffer_size)), front_(first_), back_(front_),
        alloc_(alloc), current_bufsize(buffer_size) {
    assign_with_iterator(first, last);
  }

  deque(const deque& other)
      : first_(allocate(buffer_size)), front_(first_), back_(front_),
        alloc_(Allocator()), current_bufsize(buffer_size) {
    assign_fill(other.size(), T());
    *this = other;
  }

  ~deque() {
    deallocate(first_);
    destroy(first_);
  }

  deque& operator=(const deque& other) {
    if (this == &other)
      return *this;

    if (size() != other.size()) {
      resize(other.size());
    }
    std::copy(other.begin(), other.end(), begin());
    return *this;
  }

  void assign(size_type count, const T& value) { assign_fill(count, value); }

  template <class InputIt>
  void assign(InputIt first,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type last) {
    assign_with_iterator(first, last);
  }

  allocator_type get_allocator() const { return alloc_; }

  /*
  * Element access
  */
  reference at(size_type pos) {
    if (pos >= size()) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return operator[](pos);
  }

  const_reference at(size_type pos) const {
    if (pos >= size()) {
      throw std::out_of_range("Error: index is out of range.");
    }
    return operator[](pos);
  }

  reference operator[](size_type pos) { return *pointer_at(pos); }

  const_reference operator[](size_type pos) const {
    if (front_ < back_) {
      pos += front_ - first_;
      return first_[pos];
    }
    if (back_ < front_) {
      if (&front_[pos] >= &first_[current_bufsize]) {
        size_type index_at_front = front_ - first_;
        return first_[(index_at_front + pos) % current_bufsize];
      }
      pos += front_ - first_;
      return first_[pos];
    }
    return front_[pos];
  }

  reference front() { return *front_; }

  const_reference front() const { return *front_; }

  reference back() {
    if (back_ == first_) {
      return first_[current_bufsize - 1];
    }
    return *(back_ - 1);
  }

  const_reference back() const {
    if (back_ == first_) {
      return first_[current_bufsize - 1];
    }
    return *(back_ - 1);
  }

  /*
  * Iterators
  */
  iterator begin() {
    return iterator(first_, front_, size(), current_bufsize, front_, back_);
  }

  const_iterator begin() const {
    return const_iterator(first_, front_, size(), current_bufsize, front_,
                          back_);
  }

  iterator end() {
    return iterator(first_, back_, size(), current_bufsize, front_, back_);
  }

  const_iterator end() const {
    return const_iterator(first_, back_, size(), current_bufsize, front_,
                          back_);
  }

  reverse_iterator rbegin() {
    return reverse_iterator(
        iterator(first_, back_, size(), current_bufsize, front_, back_));
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(
        const_iterator(first_, back_, size(), current_bufsize, front_, back_));
  }

  reverse_iterator rend() {
    return reverse_iterator(
        iterator(first_, front_, size(), current_bufsize, front_, back_));
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(
        const_iterator(first_, front_, size(), current_bufsize, front_, back_));
  }

  /*
  * Capacity
  */
  bool empty() const { return front_ == back_; }

  size_type size() const {
    if (empty()) {
      return 0;
    }
    // xxxxxxxxxxx
    //  f      b
    if (front_ < back_) {
      return back_ - front_;
    }
    // xxxxxxxxxxxxxxxxx
    //  |      |        |
    //  b    front  first[size]
    return back_ - first_ + first_ + current_bufsize - front_;
  }

  size_type max_size() const { return alloc_.max_size(); }

  /*
  * Modifiers
  */
  void clear() { back_ = front_; }

  iterator insert(const_iterator pos, const T& value) {
    return insert_fill(pos, 1, value);
  }

  iterator insert(const_iterator pos, size_type count, const T& value) {
    return insert_fill(pos, count, value);
  }

  template <class InputIt>
  iterator insert(const_iterator pos,
                  typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                         InputIt>::type first,
                  InputIt last) {
    size_type pos_at = pos - begin();
    for (InputIt ritr = first; ritr != last; ++ritr) {
      insert(pos, *ritr);
      ++pos;
    }
    return begin() + pos_at;
  }

  iterator erase(iterator pos) { return erase(pos, pos + 1); }

  iterator erase(iterator first, iterator last) {
    difference_type n = first - begin();
    difference_type diff = last - first;
    for (iterator itr = last; itr != end(); ++itr) {
      *(itr - diff) = *itr;
    }
    decrease_back_pointer(diff);
    return iterator(first_, pointer_at(n), size(), current_bufsize, front_,
                    back_);
  }

  void push_back(const T& value) {
    if (size() == current_bufsize) {
      reallocate_internal_array(current_bufsize * 2);
    }
    first_[last_index()] = value;
    ++back_;
  }

  void pop_back() { decrement_back_pointer(); }

  void push_front(const T& value) {
    size_type index_to_be_first = calc_index_to_be_first();
    first_[index_to_be_first] = value;
    front_ = &(first_[index_to_be_first]);
    if (back_ + 1 == front_) {
      reallocate_internal_array(current_bufsize * 2);
    }
  }

  void pop_front() {
    if (front_ == first_ + current_bufsize - 1) {
      front_ = first_;
      return;
    }
    ++front_;
  }

  void resize(size_type count, T value = T()) {
    if (count == size()) {
      return;
    }
    // 内部配列を拡張
    if (count > current_bufsize - size()) {
      reallocate_internal_array(count + size());
    }
    if (count > size()) {
      size_type additional_size = count - size();
      for (size_type i = 0; i < additional_size; ++i) {
        push_back(value);
      }
      return;
    }
    back_ = front_ + count;
  }

  void swap(deque& other) {
    deque tmp = other;
    other = *this;
    *this = tmp;
  }

private:
  pointer first_;
  pointer front_;
  pointer back_;
  allocator_type alloc_;
  size_type current_bufsize;

  const static size_type buffer_size = 512;

  pointer allocate(size_type n) { return alloc_.allocate(n); }

  void destroy(pointer ptr) { alloc_.destroy(ptr); }

  void deallocate(pointer ptr) { alloc_.deallocate(ptr, current_bufsize); }

  size_type last_index() { return back_ - first_; }

  size_type first_index() { return front_ - first_; }

  size_type calc_index_to_be_first() {
    if (first_index() == 0) {
      return current_bufsize - 1;
    }
    return first_index() - 1;
  }

  pointer pointer_at(size_type pos) {
    // xxxxxxxxxxx
    //  |      |
    //  f      b
    if (front_ < back_) {
      pos += front_ - first_;
      return first_ + pos;
    }
    // xxxxxxxxxxxxxxxxx
    //  |      |        |
    //  b    front  first[size]
    if (back_ < front_) {
      // front_[pos]がサイズを超えていたら
      if (&front_[pos] >= &first_[current_bufsize]) {
        // front_が差している場所をインデックスに換算
        size_type index_at_front = front_ - first_;
        return first_ + (index_at_front + pos) % current_bufsize;
      }
      // 超えていなかったら
      // return front_[pos];
      pos += front_ - first_;
      return first_ + pos;
    }
    return front_ + pos;
  }

  // 最後の要素がある場所を指すポインターを一個手前にずらす
  void decrement_back_pointer() { decrease_back_pointer(1); }

  // 最後の要素がある場所を指すポインターをn個手前にずらす
  void decrease_back_pointer(size_type n) {
    // xxxxxxxxxxxxx
    //   f       b
    if (front_ < back_) {
      back_ -= n;
      return;
    }

    // xxxxxxxxxxxxx
    //   b       f

    size_type back_idx = back_ - first_;
    if (back_idx >= n) {
      back_ -= n;
      return;
    }

    if (back_ < front_) {
      n -= back_idx;
      size_type rounded_back_idx = current_bufsize - n;
      back_ = first_ + rounded_back_idx;
      return;
    }

    // xxxxxxxxxxxxxxxx
    // |      |        |
    // b    front  first[size]
    if (back_ == first_) {
      back_ = first_ + current_bufsize + n;
      return;
    }
    back_ -= n;
  }

  // insert helper
  iterator insert_fill(const_iterator pos, size_type count, const T& value) {
    size_type pos_idx = pos - begin();

    if (empty()) {
      assign_fill(count, value);
      return begin() + pos_idx;
    }

    if (count > current_bufsize - size()) {
      reallocate_internal_array(count + size());
    }

    // xxxxxxxxxxxxxxx
    //   f    p    b

    // 内部配列のメモリ再確保が必要ないケース
    if (size() + count < current_bufsize) {
      size_type offset = front_ - first_;
      // pos_idxから後ろの要素をcountだけずらす
      // backを更新
      back_ = back_ + count;
      for (size_type i = size() - 1; i >= pos_idx; --i) {
        first_[(offset + count + i) % current_bufsize] =
            first_[(offset + i) % current_bufsize];
        if (i == 0) {
          break;
        }
      }
      // pos_idxからcountまでの範囲にvalueを代入する
      for (size_type i = 0; i < count; ++i) {
        first_[(offset + pos_idx + i) % current_bufsize] = value;
      }
    }
    return begin() + pos_idx;
  }

  template <class InputIt>
  void assign_with_iterator(InputIt first, InputIt last) {
    if (empty()) {
      for (InputIt itr = first; itr != last; ++itr) {
        push_back(*itr);
      }
      return;
    }
    size_type sz = last - first;
    back_ = front_ + sz;
    for (size_type i = 0; i < sz; ++i) {
      at(i) = first[i];
    }
  }

  void assign_fill(size_type count, const T& value) {
    if (empty()) {
      for (size_type i = 0; i < count; ++i) {
        push_back(value);
      }
      return;
    }
    back_ = front_ + count;
    for (size_type i = 0; i < count; ++i) {
      at(i) = value;
    }
  }

  void reallocate_internal_array(size_type new_size) {
    pointer tmp = first_;
    size_type old_size = size();
    size_type offset = front_ - tmp;
    first_ = allocate(new_size);
    for (size_type i = 0; i < old_size; ++i) {
      first_[i] = tmp[(i + offset) % current_bufsize];
    }
    deallocate(tmp);
    destroy(tmp);
    current_bufsize = new_size;
    front_ = first_;
    back_ = first_ + old_size;
  }
};

/*
* Non-member functions
*/
template <class T, class Alloc>
bool operator==(const ft::deque<T, Alloc>& lhs,
                const ft::deque<T, Alloc>& rhs) {
  return !(lhs < rhs) && !(lhs > rhs);
}

template <class T, class Alloc>
bool operator!=(const ft::deque<T, Alloc>& lhs,
                const ft::deque<T, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const ft::deque<T, Alloc>& lhs, const ft::deque<T, Alloc>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template <class T, class Alloc>
bool operator>=(const ft::deque<T, Alloc>& lhs,
                const ft::deque<T, Alloc>& rhs) {
  return !(lhs < rhs);
}

template <class T, class Alloc>
bool operator>(const ft::deque<T, Alloc>& lhs, const ft::deque<T, Alloc>& rhs) {
  return rhs < lhs;
}

template <class T, class Alloc>
bool operator<=(const ft::deque<T, Alloc>& lhs,
                const ft::deque<T, Alloc>& rhs) {
  return !(lhs > rhs);
}

template <class T, class Alloc>
void swap(ft::deque<T, Alloc>& lhs, ft::deque<T, Alloc>& rhs) {
  lhs.swap(rhs);
}
} // namespace ft

#endif
