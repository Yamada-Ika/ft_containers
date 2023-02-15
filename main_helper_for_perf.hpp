#ifndef MAIN_HELPER_FOR_PERF
#define MAIN_HELPER_FOR_PERF

#include <iostream>
#include <time.h>

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

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      v.push_back(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Vector v;

    clock_t start = clock();

    v.assign(1000000, 42);

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Vector v;

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      v.push_back(i);
    }
    v.clear();

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Vector v;

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      v.insert(v.begin(), i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Vector v;

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      v.insert(v.begin(), i);
    }

    for (int i = 0; i < 100000; ++i) {
      v.insert(v.begin(), i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Vector v;

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      v.push_back(i);
    }
    for (int i = 0; i < 100000; ++i) {
      v.pop_back();
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Vector v;

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      v.push_back(i);
    }
    v.resize(10);
    v.resize(10000000);

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Vector v;
    Vector v2;

    for (int i = 0; i < 100000; ++i) {
      v.push_back(i);
    }

    for (int i = 0; i < 100000; ++i) {
      v2.push_back(i);
    }

    clock_t start = clock();

    v.swap(v2);

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }
}

template <typename Stack>
void vec_stack(Stack) {
  {
    Stack st;

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      st.push(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Stack st;

    for (int i = 0; i < 100000; ++i) {
      st.push(i);
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      st.pop();
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Stack st;

    for (int i = 0; i < 100000; ++i) {
      st.push(i);
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      st.top();
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }
}

template <typename Map, typename Pair>
void vec_map(Map, Pair) {
  {
    Map mp;

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp.at(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp[i];
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp.size();
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp.clear();
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp.erase(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp.count(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp.find(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp.equal_range(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp.lower_bound(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      mp.upper_bound(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Map mp;
    Map mp1;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    for (int i = 0; i < 100000; ++i) {
      mp1.insert(Pair(i * 2, i));
    }

    clock_t start = clock();

    mp.swap(mp1);

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }
}

template <typename Set>
void vec_set(Set) {
  {
    Set st;

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    clock_t start = clock();

    st.size();

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    clock_t start = clock();

    st.clear();

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      st.erase(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Set st;
    Set st2;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }
    for (int i = 0; i < 100000; ++i) {
      st2.insert(i * 2);
    }

    clock_t start = clock();

    st.swap(st2);

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      st.count(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      st.find(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      st.equal_range(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      st.lower_bound(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    clock_t start = clock();

    for (int i = 0; i < 100000; ++i) {
      st.upper_bound(i);
    }

    clock_t end = clock();

    std::cout << static_cast<double>(end - start) << std::endl;
  }
}

#endif
