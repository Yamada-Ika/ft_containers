#ifndef STACK_HPP
#define STACK_HPP

#include "deque.hpp"

namespace ft {
template <class T, class Container = ft::deque<T> >
class stack {
public:
  /*
  *  Member type	
  */
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::size_type size_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;

  /*
  *  Member functions
  */
  explicit stack(const Container& cont = Container()) : c(cont) {}
  stack(const stack& other) { *this = other; }
  ~stack() {}
  stack& operator=(const stack& other) {
    if (this == &other) {
      return *this;
    }
    c = other.c;
    return *this;
  }

  /*
  *  Element access
  */
  reference top() { return c.back(); }
  const_reference top() const { return c.back(); }

  /*
  *  Capacity
  */
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }

  /*
  *  Modifiers
  */
  void push(const value_type& value) { c.push_back(value); }
  void pop() { c.pop_back(); }

  /*
  *  Non-member functions
  */
  friend bool operator==(const ft::stack<T, Container>& lhs,
                         const ft::stack<T, Container>& rhs) {
    return lhs.c == rhs.c;
  }
  friend bool operator!=(const ft::stack<T, Container>& lhs,
                         const ft::stack<T, Container>& rhs) {
    return lhs.c != rhs.c;
  }
  friend bool operator<(const ft::stack<T, Container>& lhs,
                        const ft::stack<T, Container>& rhs) {
    return lhs.c < rhs.c;
  }
  friend bool operator>=(const ft::stack<T, Container>& lhs,
                         const ft::stack<T, Container>& rhs) {
    return lhs.c >= rhs.c;
  }
  friend bool operator>(const ft::stack<T, Container>& lhs,
                        const ft::stack<T, Container>& rhs) {
    return lhs.c > rhs.c;
  }
  friend bool operator<=(const ft::stack<T, Container>& lhs,
                         const ft::stack<T, Container>& rhs) {
    return lhs.c <= rhs.c;
  }

protected:
  Container c;
};

} // namespace ft

#endif
