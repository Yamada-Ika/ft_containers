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
  deque() : alloc_(Allocator()) {
    first_ = alloc_.allocate(buffer_size);
    // TODO とりあえず初期値はNULLで埋めてみた
    front_ = NULL;
    back_ = front_;
  }
  explicit deque(const Allocator& alloc);
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
  reference at(size_type pos) { return front_[pos]; }
  const_reference at(size_type pos) const { return front_[pos]; }

  // operator[]
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  // front
  reference front() { return *front_; }
  const_reference front() const { return *front_; }

  // back
  reference back() { return *back_; }
  const_reference back() const { return *back_; }

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
  bool empty() { return front_ == back_; }

  // size
  size_type size() const;

  // max_size
  size_type max_size() const { return alloc_.max_size(); }

  // clear
  void clear();

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
    LOG(ERROR) << "last_index : " << last_index();
    // TODO　サイズチェック
    first_[last_index()] = value;
    // TODO mod
    ++back_;
  }

  // pop_back
  // TODO mod
  void pop_back() { --back; }

  // push_front
  // TODO frontを1個前に移動してその後ろにvalueを入れる？
  void push_front(const T& value);

  // pop_front
  void pop_front();

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

  // デフォルトのバッファーサイズ
  const static size_type buffer_size = 512;

  // helper
  size_type last_index() { return back_ - first_; }
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
