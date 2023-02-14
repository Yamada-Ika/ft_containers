#ifndef MAIN_HELPER_FOR_COMP_OUTPUT
#define MAIN_HELPER_FOR_COMP_OUTPUT

#include <iostream>

#include <vector>
#include <stack>
#include <map>
#include <set>
#include <utility>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"
#include "pair.hpp"

template <typename Vector>
void vec_test(Vector) {
  {
    Vector v;

    v.push_back(1);
    v.push_back(42);
    v.push_back(142);

    std::cout << v.at(0) << std::endl;
    std::cout << v.at(1) << std::endl;
    std::cout << v.at(2) << std::endl;
  }

  {
    Vector v;

    v.push_back(1);
    v.push_back(42);
    v.push_back(142);
    v.pop_back();

    std::cout << v.size() << std::endl;
    std::cout << v.at(0) << std::endl;
    std::cout << v.at(1) << std::endl;
  }

  {
    Vector v;

    v.push_back(1);
    v.push_back(42);
    v.push_back(142);

    std::cout << v[0] << std::endl;
    std::cout << v[1] << std::endl;
    std::cout << v[2] << std::endl;
  }
}

template <typename Stack>
void stack_test(Stack) {
  {
    Stack st;

    st.push(1);
    st.push(42);
    st.push(142);

    std::cout << st.size() << std::endl;
    std::cout << st.top() << std::endl;
    st.pop();
    std::cout << st.top() << std::endl;
    st.pop();
    std::cout << st.top() << std::endl;
    st.pop();
  }
}

template <typename Map, typename Pair>
void map_test(Map, Pair) {
  {
    Map m;

    m.insert(Pair(1, 2));
    std::cout << m.find(1)->first << std::endl;
    std::cout << m.find(1)->second << std::endl;
  }
}

template <typename Set>
void set_test(Set) {
  {
    Set m;

    m.insert(1);
    std::cout << *(m.find(1)) << std::endl;
  }
}

#endif
