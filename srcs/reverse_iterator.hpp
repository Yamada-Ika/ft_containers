#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <memory>
#include "iterator_traits.hpp"

namespace ft {
template <class Iter>
class reverse_iterator
    : public std::iterator<
          typename ft::iterator_traits<Iter>::iterator_category,
          typename ft::iterator_traits<Iter>::value_type,
          typename ft::iterator_traits<Iter>::difference_type,
          typename ft::iterator_traits<Iter>::pointer,
          typename ft::iterator_traits<Iter>::reference> {
public:
  /*
  * Member types
  */
  typedef Iter iterator_type;
  typedef
      typename ft::iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename ft::iterator_traits<Iter>::value_type value_type;
  typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iter>::pointer pointer;
  typedef typename ft::iterator_traits<Iter>::reference reference;

  /*
  * Member functions
  */
  reverse_iterator() {}
  explicit reverse_iterator(iterator_type x) : current(x) {}
  template <class U>
  reverse_iterator(const reverse_iterator<U>& other) {
    *this = other;
  }
  template <class U>
  reverse_iterator& operator=(const reverse_iterator<U>& other) {
    current = other.base();
    return *this;
  }
  iterator_type base() const { return current; }
  reference operator*() const {
    iterator_type tmp = current;
    return *--tmp;
  }
  pointer operator->() const { return std::addressof(operator*()); }
  reference operator[](difference_type n) const { return base()[-n - 1]; }
  reverse_iterator& operator++() {
    --current;
    return *this;
  }
  reverse_iterator& operator--() {
    ++current;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
  reverse_iterator operator--(int) {
    reverse_iterator tmp(*this);
    --(*this);
    return tmp;
  }
  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(current - n);
  }
  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(current + n);
  }
  reverse_iterator& operator+=(difference_type n) {
    current -= n;
    return *this;
  }
  reverse_iterator& operator-=(difference_type n) {
    current += n;
    return *this;
  }

protected:
  /*
  * Member objects
  */
  iterator_type current;
};

/*
* Non-member functions
*/
template <class Iterator1, class Iterator2>
bool operator==(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() != rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<(const ft::reverse_iterator<Iterator1>& lhs,
               const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() <= rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() <= rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
               const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
  return lhs.base() >= rhs.base();
}

template <class Iter>
ft::reverse_iterator<Iter>
operator+(typename ft::reverse_iterator<Iter>::difference_type n,
          const ft::reverse_iterator<Iter>& it) {
  return ft::reverse_iterator<Iter>(it.base() - n);
}

template <class Iterator1, class Iterator2>
typename ft::reverse_iterator<Iterator1>::difference_type
operator-(const ft::reverse_iterator<Iterator1>& lhs,
          const ft::reverse_iterator<Iterator2>& rhs) {
  return rhs.base() - lhs.base();
}

} // namespace ft

#endif
