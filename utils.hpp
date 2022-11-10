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

// treeでvalueからkeyを取得するときに使う構造体
// mapの内部で使う木の中で使うやつ
template <typename Pair>
struct Select1st {
  typename Pair::first_type& operator()(Pair& __x) const { return __x.first; }
  const typename Pair::first_type& operator()(const Pair& __x) const {
    return __x.first;
  }
};

// setで使うやつ
template <typename T>
struct Identity {
  T& operator()(T& __x) const { return __x; }
  const T& operator()(const T& __x) const { return __x; }
};

// 二つの値を比較するやつ
// <
template <typename T>
struct less {
  bool operator()(const T& lhs, const T& rhs) { return lhs < rhs; }
};

// >
template <typename T>
struct greater {
  bool operator()(const T& lhs, const T& rhs) { return lhs > rhs; }
};

} // namespace ft

#endif
