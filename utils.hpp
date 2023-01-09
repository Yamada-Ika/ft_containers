#ifndef UTILS_HPP
#define UTILS_HPP

// #include <cstddef>

namespace ft {
/// @brief Used for package internal
namespace detail {
// treeでvalueからkeyを取得するときに使う構造体
// mapの内部で使う木の中で使うやつ
template <typename Pair>
struct __Select1st {
  typename Pair::first_type& operator()(Pair& __x) const { return __x.first; }
  const typename Pair::first_type& operator()(const Pair& __x) const {
    return __x.first;
  }
};

// setで使うやつ
template <typename T>
struct __Identity {
  T& operator()(T& __x) const { return __x; }
  const T& operator()(const T& __x) const { return __x; }
};
} // namespace detail
} // namespace ft

#endif
