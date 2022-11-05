#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

// std::pair
template <class T1, class T2>
struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;

  // constructor
  pair() : first(), second() {}
  pair(const T1& x, const T2& y) : first(x), second(y) {}
  template <class U1, class U2>
  pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
  // TODO firstがconstの時、こうしないとコンパイルエラーに
  pair(const pair& p) : first(p.first), second(p.second) {}

  // operator=
  pair& operator=(const pair& other) {
    if (this == &other)
      return *this;

    first = other.first;
    second = other.second;

    return *this;
  }
};

// make_pair
template <class T1, class T2>
ft::pair<T1, T2> make_pair(T1 t, T2 u) {
  return ft::pair<T1, T2>(t, u);
}

// compare operators
template <class T1, class T2>
bool operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
  return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
  return (lhs.first < rhs.first ||
          (!(rhs.first < lhs.first) && lhs.second < rhs.second));
}
template <class T1, class T2>
bool operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
  return rhs < lhs;
}
template <class T1, class T2>
bool operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
  return !(lhs > rhs);
}
template <class T1, class T2>
bool operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
  return !(lhs < rhs);
}

}; // namespace ft

#endif