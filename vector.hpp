#ifndef C0B8EABC_51F0_4DBA_B6D9_11DC858D0094
#define C0B8EABC_51F0_4DBA_B6D9_11DC858D0094

#include "utils.hpp"
#include <memory>
#include <vector>

namespace ft {
template <typename T, typename Allocator = std::allocator<T> >
class vector {
public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  // typedef allocator_type::pointer     pointer; // See
  // https://en.cppreference.com/w/cpp/container/vector
  typedef const pointer const_pointer;
  // typedef allocator_type::const_pointer    const_pointer;

  typedef pointer iterator;
  typedef const_pointer const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  // ---- Constructor ----
  vector()
      : first(allocate(0)), last(first), reserved_last(first + size()),
        alloc(allocator_type()) {}

  explicit vector(const allocator_type& alloc) : alloc(alloc) {}

  explicit vector(size_type size, const_reference value = T(),
                  const allocator_type& alloc = allocator_type())
      : first(allocate(0)), last(first), reserved_last(first + this->size()),
        alloc(alloc) {
    resize(size, value);
  }

  // TODO enable_ifが必要
  template <typename InputIterator>
  explicit vector(InputIterator first, InputIterator last,
                  const allocator_type& alloc = allocator_type()) {
    reserve(distance(first, last));
    for (InputIterator itr = first; itr != last; ++itr) {
      push_back(*itr);
    }
  }

  // TODO deep copy
  vector(const vector& other) : vector(other.size()) { *this = other; }

  // ---- Destructor ----
  ~vector() {
    clear();      // Call destructor
    deallocate(); // Deallocate memory
  }

  // ---- Assigne Operator ----
  vector& operator=(const vector& other) {
    if (this == &other) {
      return *this;
    }

    if (size() == other.size()) {
      ft::copy(other.begin(), other.end(), begin());
      return *this;
    }

    if (capacity() >= other.size()) {
      ft::copy(other.begin(), other.begin() + other.size(), begin());
      for (iterator src_iter = other.begin() + other.size(),
                    src_end = other.end();
           src_iter != src_end; ++src_iter, ++last) {
        construct(last, *src_iter);
        return *this;
      }
    }

    destroy_all();
    reserve(other.size());
    for (iterator src_iter = other.begin(), src_end = other.end(),
                  dest_iter = begin();
         src_iter != src_end; ++src_iter, ++dest_iter, ++last) {
      construct(dest_iter, *src_iter);
    }
    return *this;
  }

  // Element access
  // at : access specified element with bounds checking
  reference at(size_type i) {
    if (i >= size())
      throw std::out_of_range("Error: index is out of range.");

    return first[i];
  }
  const_reference at(size_type i) const { return at(i); }

  // operator[] : access specified element
  reference operator[](size_type i) { return first[i]; }
  const_reference operator[](size_type i) const { return first[i]; }

  // front : access the first element
  reference front() { return *first; }
  const_reference front() const { return front(); }

  // back : access the last element
  reference back() { return *(last - 1); }
  const_reference back() const { return back(); }

  // data : direct access to the underlying array
  pointer data() { return first; }
  const_pointer data() const { return first; }

  // Iterators
  iterator begin() { return first; }
  iterator end() { return last; }
  const_iterator begin() const { return first; }
  const_iterator end() const { return last; }
  reverse_iterator rbegin() { return reverse_iterator(last); }
  reverse_iterator rend() { return reverse_iterator(first); }
  const_reverse_iterator rbegin() const { return reverse_iterator(last); }
  const_reverse_iterator rend() const { return reverse_iterator(first); }

  // Capacity
  // empty : checks whether the container is empty
  bool empty() const { return begin() == end(); }

  // size : returns the number of elements
  size_type size() const { return distance(begin(), end()); }

  // max_size : returns the maximum possible number of elements
  size_type max_size() const { return alloc.max_size(); }

  // reserve : reserves storage
  void reserve(size_type sz) {
    if (sz <= capacity())
      return;

    pointer tmp = allocate(sz);

    iterator old_first = first;
    iterator old_last = last;
    size_type old_capacity = capacity();

    first = tmp;
    last = first;
    reserved_last = first + sz;

    alloc.deallocate(old_first, old_capacity);

    // Copy
    for (iterator old_iter = old_first; old_iter != old_last;
         ++old_iter, ++last) {
      construct(last, *old_iter);
    }

    // Deallocate old memory
    for (reverse_iterator riter = reverse_iterator(old_last),
                          rend = reverse_iterator(old_first);
         riter != rend; ++riter) {
      destroy(&*riter);
    }
  }

  // capacity : returns the number of elements that can be held in currently allocated storage
  size_type capacity() const { return reserved_last - first; }

  // Modifiers
  // clear : clears the contents
  void clear() { destroy_until(rend()); }

  // TODO
  // insert : inserts elements

  // TODO
  // erase : erases elements

  // push_back : adds an element to the end
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
    // alloc.constuct(last, v);
    ++last;
  }

  // TODO
  // pop_back : removes the last element

  // resize : changes the number of elements stored
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

  // TODO
  // swap : swaps the contents

private:
  // Member
  pointer first;         // Head to storage
  pointer last;          // Tail - 1 to storage
  pointer reserved_last; // Tail to storage
  allocator_type alloc;  // Store of raw memory

  // Helper Method
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
  // size_type distance(iterator lhs, iterator rhs) { return rhs - lhs; }
};
} // namespace ft

#endif /* C0B8EABC_51F0_4DBA_B6D9_11DC858D0094 */
