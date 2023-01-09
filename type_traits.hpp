#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {
template <class T, T v>
struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant type;
  const value_type operator()() { return value; }
};

// Specializations
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

// is_integral
template <class T>
struct is_integral : public false_type {};
template <class T>
struct is_integral<const T> : public is_integral<T> {};
template <class T>
struct is_integral<volatile const T> : public is_integral<T> {};
template <class T>
struct is_integral<volatile T> : public is_integral<T> {};

template <>
struct is_integral<unsigned char> : public true_type {};
template <>
struct is_integral<unsigned short> : public true_type {};
template <>
struct is_integral<unsigned int> : public true_type {};
template <>
struct is_integral<unsigned long> : public true_type {};
template <>
struct is_integral<signed char> : public true_type {};
template <>
struct is_integral<short> : public true_type {};
template <>
struct is_integral<int> : public true_type {};
template <>
struct is_integral<long> : public true_type {};
template <>
struct is_integral<char> : public true_type {};
template <>
struct is_integral<bool> : public true_type {};

#ifndef FT_CONTAINERS_NO_INTRINSIC_WCHAR_T
// If the following lines to compile, define FT_CONTAINERS_NO_INTRINSIC_WCHAR_T.
template <>
struct is_integral<wchar_t> : public true_type {};
#endif
} // namespace ft

#endif