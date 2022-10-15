#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>
#include <glog/logging.h>

namespace ft {
// std::copy
template <class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt result) {
  for (InputIt itr = first; itr != last; ++itr, ++result) {
    *result = *itr;
  }
  return result;
}

// std::distance
template <class InputIt>
std::ptrdiff_t distance(InputIt first, InputIt last) {
  return last - first;
}

// std::min
template <class T>
const T& min(const T& a, const T& b) {
  return a <= b ? a : b;
}

// std::lexicographical_compare
// Elements are compared using operator<
template <class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2) {
  for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
    if (*first1 < *first2) {
      return true;
    }
    if (*first2 < *first1) {
      return false;
    }
  }
  return (first1 == last1) && (first2 != last2);
}

} // namespace ft

#endif
