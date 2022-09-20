#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {
  // See https://en.cppreference.com/w/cpp/iterator/reverse_iterator
  template < class Iter >
  class reverse_iterator
      : public ft::iterator<
                            ft::iterator_traits<Iter>::iterator_category,
                            ft::iterator_traits<Iter>::value_type,
                            ft::iterator_traits<Iter>::difference_type,
                            ft::iterator_traits<Iter>::pointer,
                            ft::iterator_traits<Iter>::reference,
                            > {
   public:
    // Member types
    typedef Iter                                                   iterator_type
    typedef typename ft::iterator_traits<Iter>::iterator_category  iterator_category
    typedef typename ft::iterator_traits<Iter>::value_type         value_type
    typedef typename ft::iterator_traits<Iter>::difference_type    difference_type
    typedef typename ft::iterator_traits<Iter>::pointer            pointer
    typedef typename ft::iterator_traits<Iter>::reference          reference

    // Member functions
    reverse_iterator() : itr(), current() {}
    explicit reverse_iterator(Iter it) : itr(it), current(it) {}

    reverse_iterator(const reverse_iterator<> other)
        : itr(other.base()), current(other.base()) {}
  
    reverse_iterator& operator=(const reverse_iterator& rhs) {}
    Iter base { return current; }
    reverse_iterator& operator*(const reverse_iterator& rhs) {}
    reverse_iterator& operator->(const reverse_iterator& rhs) {}
    reverse_iterator& operator++() {}
    reverse_iterator operator++(int) {}
    reverse_iterator& operator+=() {}
    reverse_iterator& operator--() {}
    reverse_iterator& operator--(int) {}
    reverse_iterator& operator-=(int) {}
    reverse_iterator& operator-(int) {}

   protected:
    Iter current;

   private:
    Iter itr;
  };
}

#endif
