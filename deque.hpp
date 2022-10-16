#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <memory>

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
  deque();
};

}; // namespace ft

#endif
