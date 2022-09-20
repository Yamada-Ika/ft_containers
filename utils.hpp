#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>

namespace ft {
  // std::copy
  template < class InputIt, class OutputIt >
  OutputIt copy(InputIt first, InputIt last, OutputIt result) {
    for (InputIt itr = first; itr != last; ++itr, ++result) {
      *result = *itr;
    }
    return result;
  }

  // std::distance
  template < class InputIt >
  std::ptrdiff_t distance(InputIt first, InputIt last) {
    return last - first;
  }
}

#endif
