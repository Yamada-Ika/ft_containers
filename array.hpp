#ifndef F501011C_1E75_4998_AB12_88D20EF55DFC
#define F501011C_1E75_4998_AB12_88D20EF55DFC
#ifndef ARRAY_HPP
#define ARRAY_HPP

namespace ft {
// Iterator
template <typename Array> class array_iterator {
public:
  array_iterator(Array &arr, std::size_t i) : arr(arr), i(i) {}

  array_iterator &operator++() {
    ++i;
    return *this;
  }
  array_iterator operator++(int) {
    array_iterator copy = *this;
    ++*this;
    return copy;
  }
  array_iterator &operator--() {
    --i;
    return *this;
  }
  array_iterator &operator--(int) {
    array_iterator copy = *this;
    --*this;
    return copy;
  }
  array_iterator &operator+=(std::size_t n) {
    i += n;
    return *this;
  }
  array_iterator &operator+(std::size_t n) const {
    array_iterator copy = *this;
    copy += n;
    return copy;
  }
  array_iterator &operator-=(std::size_t n) {
    i -= n;
    return *this;
  }
  array_iterator &operator-(std::size_t n) const {
    array_iterator copy = *this;
    copy -= n;
    return copy;
  }
  typename Array::reference operator*() { return arr[i]; }
  typename Array::reference operator[](std::size_t n) const {
    return *(*this + n);
  }
  bool operator==(array_iterator const &rhs) { return i == rhs.i; }
  bool operator<(array_iterator const &rhs) { return i < rhs.i; }
  bool operator>(array_iterator const &rhs) { return i > rhs.i; }
  bool operator!=(array_iterator const &rhs) { return !(*this == rhs); }
  bool operator>=(array_iterator const &rhs) { return !(i < rhs.i); }
  bool operator<=(array_iterator const &rhs) { return !(i > rhs.i); }

private:
  Array &arr;
  std::size_t i;
};

// Const Iterator (値は変更できないがイテレータを介して値にアクセスできるクラス)
template <typename Array> class array_const_iterator {
public:
  // Constructor
  array_const_iterator(Array const &arr, std::size_t i) : arr(arr), i(i) {}
  array_const_iterator(typename array_iterator<Array>::iterator const &iter)
      : arr(iter.arr), i(iter.i) {}

  // Operator
  array_const_iterator &operator++() {
    ++i;
    return *this;
  }
  array_const_iterator operator++(int) {
    array_const_iterator copy = *this;
    ++i;
    return copy;
  }
  array_const_iterator &operator--() {
    --i;
    return *this;
  }
  array_const_iterator operator--(int) {
    array_const_iterator copy = *this;
    --i;
    return copy;
  }
  array_const_iterator &operator+=(std::size_t n) {
    i += n;
    return *this;
  }
  array_const_iterator &operator+(std::size_t n) {
    array_const_iterator copy = *this;
    i += n;
    return copy;
  }
  array_const_iterator &operator-=(std::size_t n) {
    i -= n;
    return *this;
  }
  array_const_iterator &operator-(std::size_t n) {
    array_const_iterator copy = *this;
    i -= n;
    return copy;
  }
  typename Array::const_reference operator*() const { return arr[i]; }
  typename Array::const_reference operator[](std::size_t i) const {
    return *(*this + i);
  }
  bool operator==(array_const_iterator const &rhs) { return i == rhs.i; }
  bool operator<(array_const_iterator const &rhs) { return i < rhs.i; }
  bool operator>(array_const_iterator const &rhs) { return i > rhs.i; }
  bool operator!=(array_const_iterator const &rhs) { return !(*this == rhs); }
  bool operator>=(array_const_iterator const &rhs) { return !(i < rhs.i); }
  bool operator<=(array_const_iterator const &rhs) { return !(i > rhs.i); }

private:
  Array const &arr;
  std::size_t i;
};

template <typename T, std::size_t N> class array {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;

  // Iterator type
  typedef array_iterator<array> iterator;
  typedef array_const_iterator<array> const_iterator;

  typedef std::size_t size_type;

  reference operator[](size_type i) { return storage_[i]; }
  const_reference operator[](size_type i) const { return storage_[i]; }
  size_type size() const { return sizeof(storage_) / sizeof(storage_[0]); }
  reference front() { return storage_[0]; }
  const_reference front() const { return storage_[0]; }
  reference back() { return storage_[N - 1]; }
  const_reference back() const { return storage_[N - 1]; }
  void fill(value_type v) {}
  reference at(size_type n) {
    if (n >= size())
      throw std::out_of_range("Error: Out of range");

    return storage_[n];
  }

  iterator begin() { return iterator(*this, 0); }
  iterator end() { return iterator(*this, N); }
  const_iterator begin() const { return iterator(*this, 0); }
  const_iterator end() const { return iterator(*this, N); }
  const_iterator cbegin() { return const_iterator(*this, 0); }
  const_iterator cend() { return const_iterator(*this, N); }

private:
  value_type storage_[N];
};
} // namespace ft

#endif

#endif /* F501011C_1E75_4998_AB12_88D20EF55DFC */
