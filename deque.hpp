#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <memory>
#include <glog/logging.h>

namespace ft {

// deque用のイテレータ
// 内部的に配列でリングバッファを使っているので、イテレータをインクリメントなどした時に、さししめしす場所はリニアに変化しない
// 何を持っていれば良さそうか
// -　内部的な配列を指すポインタ
// template <typename T, typename Ref, typename Ptr>
template <typename T>
class deque_iterator {
public:
  // types
  typedef std::random_access_iterator_tag iterator_category;
  // typedef deque_iterator<T, T&, T*> iterator;
  // typedef deque_iterator<T, const T&, const T*> const_iterator;
  typedef deque_iterator<T> iterator;
  typedef const deque_iterator<T> const_iterator;
  typedef T value_type;
  // typedef Ptr pointer;
  // typedef Ref reference;
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
      LOG(ERROR) << "operator[] n : " << n;
      n = (n - pos_to_r_buf_boundry) % cap_;
      LOG(ERROR) << "operator[] n : " << n;
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
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  // typedef pointer iterator;
  // typedef const_pointer const_iterator;
  // typedef deque_iterator<T, T&, pointer> iterator;
  // typedef deque_iterator<T, const T&, const_pointer> const_iterator;
  typedef deque_iterator<T> iterator;
  typedef const deque_iterator<T> const_iterator;
  // TODO ftのやつに差し替える
  typedef typename std::reverse_iterator<iterator> reverse_iterator;
  typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

  // constructor
  deque()
      : alloc_(Allocator()), first_(alloc_.allocate(buffer_size)), front_(NULL),
        back_(NULL), current_bufsize(buffer_size) {}
  explicit deque(const Allocator& alloc)
      : alloc_(alloc), first_(alloc_.allocate(buffer_size)), front_(NULL),
        back_(NULL), current_bufsize(buffer_size) {}
  explicit deque(size_type count, const T& value = T(),
                 const Allocator& alloc = Allocator());
  template <class InputIt>
  deque(InputIt first, InputIt last, const Allocator& alloc = Allocator());
  deque(const deque& other) { *this = other; }

  // destructor
  ~deque() {
    alloc_.deallocate(first_, buffer_size);
    alloc_.destroy(first_);
  }

  // operator=
  // TODO どうしよう
  deque& operator=(const deque& other) {
    if (this == &other)
      return *this;

    return *this;
  }

  // assign
  void assign(size_type count, const T& value);
  template <class InputIt>
  void assign(InputIt first, InputIt last);

  // get_allocator
  allocator_type get_allocator() const { return alloc_; }

  // at
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

  // operator[]
  reference operator[](size_type pos) { return *pointer_at(pos); }
  const_reference operator[](size_type pos) const { return *pointer_at(pos); }

  // front
  reference front() { return *front_; }
  const_reference front() const { return *front_; }

  // back
  reference back() { return *(back_ - 1); }
  const_reference back() const { return *(back_ - 1); }

  // begin
  iterator begin() {
    // TODO 適当に実装してみる。メンバとして持たせないといけない気がする
    return iterator(first_, front_, size(), current_bufsize);
  }
  const_iterator begin() const {
    return const_iterator(first_, front_, size(), current_bufsize);
  }

  // end
  iterator end() { return iterator(first_, back_, size(), current_bufsize); }
  const_iterator end() const {
    return const_iterator(first_, back_, size(), current_bufsize);
  }

  // rbegin
  reverse_iterator rbegin() {
    return reverse_iterator(iterator(first_, back_, size(), current_bufsize));
  }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(
        const_iterator(first_, back_, size(), current_bufsize));
  }

  // rend
  reverse_iterator rend() {
    return reverse_iterator(iterator(first_, front_, size(), current_bufsize));
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(
        const_iterator(first_, front_, size(), current_bufsize));
  }

  // empty
  bool empty() const { return front_ == NULL && back_ == NULL; }

  // size
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

  // max_size
  size_type max_size() const { return alloc_.max_size(); }

  // clear
  void clear() {
    front_ = NULL;
    back_ = front_;
  }

  // insert
  iterator insert(const_iterator pos, const T& value) {
    size_type pos_at = pos - begin();
    size_type old_size = size();
    push_back(operator[](old_size - 1));
    for (size_type i = old_size - 1; i > pos_at; --i) {
      operator[](i + 1) = operator[](i);
    }
    operator[](pos_at) = value;
    return iterator(first_, pointer_at(pos_at), size(), current_bufsize);
  }
  iterator insert(const_iterator pos, size_type count, const T& value);
  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last);
  // erase
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

  // push_back
  void push_back(const T& value) {
    // TODO 初めてpush_backされたらfront_とback_はNULL
    if (front_ == NULL && back_ == NULL) {
      first_[0] = value;
      front_ = &first_[0];
      back_ = front_ + 1;
      return;
    }
    LOG(ERROR) << "push_back last_index : " << last_index();
    // TODO　サイズチェック
    first_[last_index()] = value;
    // TODO mod
    ++back_;
  }

  // pop_back
  // TODO mod
  void pop_back() {
    if (size() == 1) {
      front_ = NULL;
      back_ = NULL;
      return;
    }
    decrement_back_pointer();
  }

  // push_front
  // TODO frontを1個前に移動してその後ろにvalueを入れる？
  void push_front(const T& value) {
    // TODO 初めてpush_frontされたらfront_とback_はNULL
    if (front_ == NULL && back_ == NULL) {
      size_type index_to_be_first = 0;
      LOG(ERROR) << "push_front index_to_be_first : " << index_to_be_first;
      first_[index_to_be_first] = value;
      front_ = &(first_[index_to_be_first]);
      back_ = front_ + 1;
      return;
    }
    size_type index_to_be_first = calc_index_to_be_first(); // TODO mod
    LOG(ERROR) << "push_front index_to_be_first : " << index_to_be_first;
    first_[index_to_be_first] = value;
    front_ = &(first_[index_to_be_first]);
  }

  // pop_front
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

  // resize
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

  // swap
  void swap(deque& other);

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
        LOG(ERROR) << "index_at_front  : " << index_at_front;
        LOG(ERROR) << "return value at first["
                   << (index_at_front + pos) % current_bufsize << "]";
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
};

// compare operators
template <class T, class Alloc>
bool operator==(const ft::deque<T, Alloc>& lhs,
                const ft::deque<T, Alloc>& rhs) {
  return true;
}
template <class T, class Alloc>
bool operator!=(const ft::deque<T, Alloc>& lhs,
                const ft::deque<T, Alloc>& rhs) {
  return !(lhs == rhs);
}
template <class T, class Alloc>
bool operator<(const ft::deque<T, Alloc>& lhs, const ft::deque<T, Alloc>& rhs) {
  return true;
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
}; // namespace ft

#endif
