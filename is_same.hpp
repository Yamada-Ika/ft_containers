#ifndef IS_SAME_HPP
#define IS_SAME_HPP

#include "is_integral.hpp"

namespace ft {
  // See https://en.cppreference.com/w/cpp/types/is_same
  template < class T, class U >
  struct is_same : ft::false_type {};

  template < class T >
  struct is_same<T, T> : ft::true_type {};
}

#endif
