#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft {
  // integral_constant that is used in is_integral
  // See https://en.cppreference.com/w/cpp/types/integral_constant
  template < class T, T v >
  struct integral_constant {
    static const T value = v;
    typedef T                  value_type;
    typedef integral_constant  type;
    const value_type operator ()() { return value; }
  };

  // Specializations
  typedef integral_constant<bool, true> true_type;
  typedef integral_constant<bool, false> false_type;

  // is_integral
  // See https://www.boost.org/doc/libs/1_60_0/libs/type_traits/doc/html/boost_typetraits/reference/is_integral.html
  template < class T > struct is_integral                   : public false_type {};
  template < class T > struct is_integral<const T>          : public is_integral<T> {};
  template < class T > struct is_integral<volatile const T> : public is_integral<T> {};
  template < class T > struct is_integral<volatile T>       : public is_integral<T> {};

  template <> struct is_integral<unsigned char>  : public true_type {};
  template <> struct is_integral<unsigned short> : public true_type {};
  template <> struct is_integral<unsigned int>   : public true_type {};
  template <> struct is_integral<unsigned long>  : public true_type {};
  template <> struct is_integral<signed char>    : public true_type {};
  template <> struct is_integral<short>          : public true_type {};
  template <> struct is_integral<int>            : public true_type {};
  template <> struct is_integral<long>           : public true_type {};
  template <> struct is_integral<char>           : public true_type {};
  template <> struct is_integral<bool>           : public true_type {};

  #ifndef FT_CONTAINERS_NO_INTRINSIC_WCHAR_T
  // If the following lines to compile, define FT_CONTAINERS_NO_INTRINSIC_WCHAR_T.
  template <> struct is_integral<wchar_t> : public true_type {};
  #endif

  // I do not support following microsoft extentions.
  // See https://docs.microsoft.com/ja-jp/cpp/cpp/int8-int16-int32-int64?view=msvc-170
  // template <> struct is_integral<unsigned __int8>  : public true_type {};
  // template <> struct is_integral<unsigned __int16> : public true_type {};
  // template <> struct is_integral<unsigned __int32> : public true_type {};
  // template <> struct is_integral<__int8>           : public true_type {};
  // template <> struct is_integral<__int16>          : public true_type {};
  // template <> struct is_integral<__int32>          : public true_type {};
  // template <> struct is_integral<unsigned __int64> : public true_type {};
  // template <> struct is_integral<__int64>          : public true_type {};

  // These types are implemented C++11
  // See https://en.cppreference.com/w/cpp/language/types
  //    , https://en.cppreference.com/w/cpp/keyword/char16_t
  //    , https://en.cppreference.com/w/c/string/multibyte/char32_t
  #if __cplusplus >= 201103L
  template <> struct is_integral<unsigned long long> : public true_type {};
  template <> struct is_integral<long long> : public true_type {};
  template <> struct is_integral<char16_t> : public true_type {};
  template <> struct is_integral<char32_t> : public true_type {};
  #endif

  // Multiprecision integer are implemented C99
  // See https://en.cppreference.com/w/c/language/type
  template <> struct is_integral<__int128> : public true_type {};
  template <> struct is_integral<unsigned __int128> : public true_type {};
}


#endif
