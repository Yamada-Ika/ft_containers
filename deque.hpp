#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <memory>
#include <glog/logging.h>

namespace ft {
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
  typedef pointer iterator;
  typedef const_pointer const_iterator;
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
  // TODO 多分frontで良い気がする
  reference at(size_type pos) {
    // xxxxxxxxxxx
    //  |      |
    //  f      b
    if (front_ < back_) {
      return front_[pos];
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
        return first_[(index_at_front + pos) % current_bufsize];
      }
      // 超えていなかったら
      return front_[pos];
    }
    // TODO コンパイルエラー回避
    return front_[pos];
  }
  const_reference at(size_type pos) const { return front_[pos]; }

  // operator[]
  reference operator[](size_type pos) { return at(pos); }
  const_reference operator[](size_type pos) const;

  // front
  reference front() { return *front_; }
  const_reference front() const { return *front_; }

  // back
  reference back() { return *(back_ - 1); }
  const_reference back() const { return *(back_ - 1); }

  // begin
  iterator begin();
  const_iterator begin() const;

  // end
  iterator end();
  const_iterator end() const;

  // rbegin
  reverse_iterator rbegin();
  const_reverse_iterator rbegin() const;

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
  iterator insert(const_iterator pos, const T& value);
  iterator insert(const_iterator pos, size_type count, const T& value);
  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last);

  // erase
  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);

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
    // xxxxxxxxxxxxxxxx
    // |      |        |
    // b    front  first[size]
    // back_がダングリングになるのを防ぐ
    if (back_ == first_) {
      back_ = first_ + current_bufsize;
      return;
    }
    --back_;
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
  void resize(size_type count, T value = T());

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
