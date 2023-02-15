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

    std::cout << v.size() << std::endl;
    std::cout << v.empty() << std::endl;
    std::cout << v.at(0) << std::endl;
    std::cout << v.at(1) << std::endl;
    std::cout << v.at(2) << std::endl;

    Vector v2;
    v2 = v;

    v.push_back(1);
    v.push_back(42);
    v.push_back(142);

    std::cout << v.size() << std::endl;
    std::cout << v.empty() << std::endl;
    std::cout << v.at(0) << std::endl;
    std::cout << v.at(1) << std::endl;
    std::cout << v.at(2) << std::endl;
    std::cout << v.at(3) << std::endl;
    std::cout << v.at(4) << std::endl;
    std::cout << v.at(5) << std::endl;

    std::cout << v2.size() << std::endl;
    std::cout << v2.empty() << std::endl;
    std::cout << v2.at(0) << std::endl;
    std::cout << v2.at(1) << std::endl;
    std::cout << v2.at(2) << std::endl;
  }

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

  {
    Map m;

    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.clear();
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    m.erase(1);
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    m.insert(Pair(1, 2));
    m.insert(Pair(1, 2));
    m.erase(1);
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    m.insert(Pair(1, 2));
    m.insert(Pair(1, 2));
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    std::cout << m.at(1) << std::endl;
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    std::cout << m[1] << std::endl;
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    std::cout << m.begin()->first << std::endl;
    std::cout << m.begin()->second << std::endl;
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    std::cout << (++m.end())->first << std::endl;
    std::cout << (++m.end())->second << std::endl;
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    std::cout << m.rbegin()->first << std::endl;
    std::cout << m.rbegin()->second << std::endl;
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    std::cout << (--m.rend())->first << std::endl;
    std::cout << (--m.rend())->second << std::endl;
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;

    Map m2;

    m2.insert(Pair(1, 2));
    m2.insert(Pair(2, 3));
    m2.insert(Pair(3, 4));
    m2.insert(Pair(4, 5));
    std::cout << m2.empty() << std::endl;
    std::cout << m2.size() << std::endl;

    m.swap(m2);

    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
    std::cout << m.at(1) << std::endl;
    std::cout << m.at(2) << std::endl;
    std::cout << m.at(3) << std::endl;
    std::cout << m.at(4) << std::endl;

    std::cout << m2.empty() << std::endl;
    std::cout << m2.size() << std::endl;
    std::cout << m2.at(1) << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    m.erase(1);
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    m.erase(2);
    std::cout << m.empty() << std::endl;
    std::cout << m.size() << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    std::cout << m.count(1) << std::endl;
  }

  {
    Map m;

    std::cout << m.count(1) << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    m.insert(Pair(2, 2));
    std::cout << m.equal_range(1).first->first << std::endl;
    std::cout << m.equal_range(1).first->second << std::endl;
    std::cout << m.equal_range(1).second->first << std::endl;
    std::cout << m.equal_range(1).second->second << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    std::cout << m.lower_bound(1)->first << std::endl;
    std::cout << m.lower_bound(1)->second << std::endl;
  }

  {
    Map m;

    m.insert(Pair(1, 2));
    m.insert(Pair(2, 2));
    std::cout << m.upper_bound(1)->first << std::endl;
    std::cout << m.upper_bound(1)->second << std::endl;
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
