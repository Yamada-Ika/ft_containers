#ifndef STACK_HPP
#define STACK_HPP

#include <deque>

namespace ft {
template <class T, class Container = std::deque<T> >
class stack {
public:
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

  explicit stack(const Container& cont = Container()) {}
  stack(const stack& other) { *this = other; }
  ~stack() {}
  stack& operator=(const stack& other) {
    if (this == &other) {
      return *this;
    }
    c = other.c;
    return *this;
  }

  reference top() { return c.back(); }
  const_reference top() const { return c.back(); }

  bool empty() const { return c.empty(); }

  size_type size() const { return c.size(); }

  void push(const value_type& value) { c.push_back(value); }

  void pop() { c.pop_back(); }

protected:
  Container c;
};

// compare operators
template <class T, class Container>
bool operator==(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!=(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(const ft::stack<T, Container>& lhs,
               const ft::stack<T, Container>& rhs) {
  return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator>=(const ft::stack<T, Container>& lhs,
                ft::stack<T, Container>& rhs) {
  return !(lhs < rhs);
}

template <class T, class Container>
bool operator>(const ft::stack<T, Container>& lhs,
               ft::stack<T, Container>& rhs) {
  return rhs < lhs;
}

template <class T, class Container>
bool operator<=(const ft::stack<T, Container>& lhs,
                const ft::stack<T, Container>& rhs) {
  return !(lhs > rhs);
}

}; // namespace ft

#endif