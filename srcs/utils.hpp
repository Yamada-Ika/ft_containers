#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {
/// @brief Used for package internal
namespace detail {

/// @brief Used for retrieve key of node value in map
template <typename Pair>
struct __Select1st {
  typename Pair::first_type& operator()(Pair& __x) const { return __x.first; }
  const typename Pair::first_type& operator()(const Pair& __x) const {
    return __x.first;
  }
};

/// @brief Used for retrieve key of node value in set
template <typename T>
struct __Identity {
  T& operator()(T& __x) const { return __x; }
  const T& operator()(const T& __x) const { return __x; }
};

} // namespace detail
} // namespace ft

#endif
