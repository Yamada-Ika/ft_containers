#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <memory>
#include "is_integral.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"
#include <cassert>

namespace ft {

template <typename T>
class deque_iterator {
public:
  typedef std::random_access_iterator_tag iterator_category;
  typedef deque_iterator<T> iterator;
  typedef const deque_iterator<T> const_iterator;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef deque_iterator Self;

  deque_iterator(pointer first, pointer pos, size_type size, size_type cap)
      : first_(first), pos_(pos), size_(size), cap_(cap) {}
  deque_iterator(const Self& other) { *this = other; }
  ~deque_iterator() {}
  deque_iterator& operator=(const deque_iterator& other) {
    if (this == &other)
      return *this;

    first_ = other.first_;
    pos_ = other.pos_;
    size_ = other.size_;
    cap_ = other.cap_;
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
  // TODO これだと曖昧らしいけどわからん
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
  // TODO よくわからない
  friend difference_type operator-(const Self& lhs, const Self& rhs) {
    if (lhs.pos_ < rhs.pos_) {
      return rhs.pos_ - lhs.pos_;
    }
    return lhs.pos_ - rhs.pos_;
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

private:
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
  typedef const deque_iterator<T> const_iterator;
  typedef typename ft::reverse_iterator<iterator> reverse_iterator;
  typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

  /*
  * Member functions
  */
  deque()
      : alloc_(Allocator()), first_(allocate(buffer_size)), front_(NULL),
        back_(NULL), current_bufsize(buffer_size) {}

  explicit deque(const Allocator& alloc)
      : alloc_(alloc), first_(allocate(buffer_size)), front_(NULL), back_(NULL),
        current_bufsize(buffer_size) {}

  explicit deque(size_type count, const T& value = T(),
                 const Allocator& alloc = Allocator())
      : alloc_(alloc), first_(allocate(buffer_size)), front_(NULL), back_(NULL),
        current_bufsize(buffer_size) {
    assign_fill(count, value);
  }

  template <class InputIt>
  deque(InputIt first, InputIt last, const Allocator& alloc = Allocator())
      : alloc_(Allocator()), first_(allocate(buffer_size)), front_(NULL),
        back_(NULL), current_bufsize(buffer_size) { // 曖昧さ回避
    typedef typename ft::is_integral<InputIt>::type integral;
    initialize_dispatch(first, last, integral());
  }

  deque(const deque& other)
      : alloc_(Allocator()), first_(allocate(buffer_size)), front_(NULL),
        back_(NULL), current_bufsize(buffer_size) {
    assign_fill(other.size(), T());
    *this = other;
  }

  ~deque() {
    alloc_.deallocate(first_, buffer_size);
    alloc_.destroy(first_);
  }

  deque& operator=(const deque& other) {
    if (this == &other)
      return *this;

    if (size() != other.size()) {
      resize(other.size());
    }
    ft::copy(other.begin(), other.end(), begin());
    return *this;
  }

  void assign(size_type count, const T& value) { assign_fill(count, value); }
  template <class InputIt>
  void assign(InputIt first, InputIt last) {
    // 曖昧さ回避
    typedef typename ft::is_integral<InputIt>::type integral;
    assign_dispatch(first, last, integral());
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

  reference back() { return *(back_ - 1); }
  const_reference back() const { return *(back_ - 1); }

  /*
  * Iterators
  */
  iterator begin() { return iterator(first_, front_, size(), current_bufsize); }
  const_iterator begin() const {
    return const_iterator(first_, front_, size(), current_bufsize);
  }
  iterator end() { return iterator(first_, back_, size(), current_bufsize); }
  const_iterator end() const {
    return const_iterator(first_, back_, size(), current_bufsize);
  }
  reverse_iterator rbegin() {
    return reverse_iterator(iterator(first_, back_, size(), current_bufsize));
  }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(
        const_iterator(first_, back_, size(), current_bufsize));
  }
  reverse_iterator rend() {
    return reverse_iterator(iterator(first_, front_, size(), current_bufsize));
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(
        const_iterator(first_, front_, size(), current_bufsize));
  }

  /*
  * Capacity
  */
  bool empty() const { return front_ == NULL && back_ == NULL; }
  size_type size() const {
    if (empty()) {
      return 0;
    }
    if (front_ == back_) {
      return current_bufsize;
    }
    // xxxxxxxxxxx
    //  |      |
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
  void clear() {
    front_ = NULL;
    back_ = front_;
  }

  iterator insert(const_iterator pos, const T& value) {
    // xaaaaaaxxxx
    //  |  |  |
    //  f  p  b
    //
    // xaavaaaaxxxx
    size_type pos_at = pos - begin();
    size_type old_size = size();

    push_back(at(old_size - 1));
    for (size_type i = old_size - 1; i >= pos_at; --i) {
      at(i + 1) = at(i);
      if (i == 0) {
        break;
      }
    }
    at(pos_at) = value;
    return begin() + pos_at;
  }
  iterator insert(const_iterator pos, size_type count, const T& value) {
    return insert_fill(pos, count, value);
  }
  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last) {
    // 曖昧さ回避
    typedef typename ft::is_integral<InputIt>::type integral;
    return insert_dispatch(pos, first, last, integral());
  }

  iterator erase(iterator pos) { return erase(pos, pos + 1); }
  iterator erase(iterator first, iterator last) {
    difference_type n = first - begin();
    difference_type diff = last - first;
    for (iterator itr = last; itr != end(); ++itr) {
      *(itr - diff) = *itr;
    }
    decrease_back_pointer(diff);
    return iterator(first_, pointer_at(n), size(), current_bufsize);
  }

  void push_back(const T& value) {
    if (empty()) {
      first_[0] = value;
      front_ = &first_[0];
      back_ = front_ + 1;
      return;
    }
    first_[last_index()] = value;
    ++back_;
  }

  void pop_back() {
    if (size() == 1) {
      front_ = NULL;
      back_ = NULL;
      return;
    }
    decrement_back_pointer();
  }

  void push_front(const T& value) {
    if (front_ == NULL && back_ == NULL) {
      size_type index_to_be_first = 0;
      first_[index_to_be_first] = value;
      front_ = &(first_[index_to_be_first]);
      back_ = front_ + 1;
      return;
    }
    size_type index_to_be_first = calc_index_to_be_first();
    first_[index_to_be_first] = value;
    front_ = &(first_[index_to_be_first]);
  }

  void pop_front() {
    if (size() == 1) {
      front_ = NULL;
      back_ = NULL;
      return;
    }
    // xxxxxxxxxxxxxxxx
    // |              |
    // b            front
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
    size_type this_old_size = size();
    size_type other_old_size = other.size();
    for (size_type i = 0; i < other_old_size; ++i) {
      push_back(other.at(i));
    }
    for (size_type i = 0; i < this_old_size; ++i) {
      other.push_back(at(i));
    }
    for (size_type i = 0; i < this_old_size; ++i) {
      pop_front();
    }
    for (size_type i = 0; i < other_old_size; ++i) {
      other.pop_front();
    }
  }

private:
  // 配列の先頭ポインタを持つ
  pointer first_;
  // 要素の先頭ポインタを持つ
  pointer front_;
  // 要素の最後の1個後ろのポインタを持つ
  pointer back_;
  // メモリアロケーた
  allocator_type alloc_;
  // 現在のバッファーサイズ（キャパシティ）
  size_type current_bufsize;

  // デフォルトのバッファーサイズ
  const static size_type buffer_size = 512;

  // helper
  // 一番後ろのインデックスを返す
  size_type last_index() { return back_ - first_; }
  // 一番前のインデックスを返す
  size_type first_index() { return front_ - first_; }
  // push_frontした時に値を挿入すべきインデックスを返す
  size_type calc_index_to_be_first() {
    if (first_index() == 0) {
      return current_bufsize - 1;
    }
    return first_index() - 1;
  }
  // posのポインターを返す
  // TODO メモリ再確保の処理ここでやる？
  pointer pointer_at(size_type pos) {
    assert(front_ != NULL);
    assert(back_ != NULL);
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
    // TODO コンパイルエラー回避
    return front_ + pos;
  }
  // 最後の要素がある場所を指すポインターを一個手前にずらす
  void decrement_back_pointer() { decrease_back_pointer(1); }
  // 最後の要素がある場所を指すポインターをn個手前にずらす
  void decrease_back_pointer(difference_type n) {
    // xxxxxxxxxxxxxxxx
    // |      |        |
    // b    front  first[size]
    // back_がダングリングになるのを防ぐ
    if (back_ == first_) {
      back_ = first_ + current_bufsize + n;
      return;
    }
    back_ -= n;
  }
  // inser helper
  template <typename Integral>
  iterator insert_dispatch(const_iterator pos, Integral count, Integral value,
                           true_type) {
    return insert_fill(pos, count, value);
  }
  template <typename InputIt>
  iterator insert_dispatch(const_iterator pos, InputIt first, InputIt last,
                           false_type) {
    size_type pos_at = pos - begin();
    iterator itr = static_cast<iterator>(pos);
    for (InputIt ritr = first; ritr != last; ++ritr) {
      insert(itr, *ritr);
      ++itr;
    }
    return begin() + pos_at;
  }
  // insert helper
  iterator insert_fill(const_iterator pos, size_type count, const T& value) {
    size_type pos_at = pos - begin();
    iterator itr = static_cast<iterator>(pos);
    for (size_type left = count; left > 0; --left) {
      insert(itr, value);
      ++itr;
    }
    return begin() + pos_at;
  }

  template <class InputIt>
  void initialize_dispatch(InputIt first, InputIt last, false_type) {
    assign_with_iterator(first, last);
  }

  template <class Integral>
  void initialize_dispatch(Integral count, Integral value, true_type) {
    assign_fill(count, value);
  }

  pointer allocate(size_type sz) { return alloc_.allocate(sz); }

  void init_deque() {
    alloc_ = Allocator();
    first_ = alloc_.allocate(buffer_size);
    front_ = NULL;
    back_ = NULL;
    current_bufsize = buffer_size;
  }

  template <class Integral>
  void assign_dispatch(Integral count, Integral value, true_type) {
    assign_fill(count, value);
  }
  template <class InputIt>
  void assign_dispatch(InputIt first, InputIt last, false_type) {
    assign_with_iterator(first, last);
  }
  template <class InputIt>
  void assign_with_iterator(InputIt first, InputIt last) {
    // TODO リファクタ
    if (size() == 0) {
      for (InputIt itr = first; itr != last; ++itr) {
        push_back(*itr);
      }
      return;
    }
    difference_type sz = last - first;
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
};

/*
* Non-member functions
*/
template <class T, class Alloc>
bool operator==(const ft::deque<T, Alloc>& lhs,
                const ft::deque<T, Alloc>& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (typename ft::deque<T>::size_type i = 0; i < lhs.size(); ++i) {
    if (lhs.at(i) != rhs.at(i)) {
      return false;
    }
  }
  return true;
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

}; // namespace ft

#endif
