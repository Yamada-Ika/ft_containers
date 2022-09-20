#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft {
  // See https://en.cppreference.com/w/cpp/iterator/iterator
  template <
    class Category,
    class T,
    class Distance = std::ptrdiff_t,
    class Pointer = T*,
    class Reference = T&,
  >
  struct iterator {
    typedef Category   iterator_category;
    typedef T          value_type;
    typedef Distance   difference_type;
    typedef Pointer    pointer;
    typedef Reference  reference;
  };
}


#endif
