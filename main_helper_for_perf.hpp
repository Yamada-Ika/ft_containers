#ifndef MAIN_HELPER_FOR_PERF
#define MAIN_HELPER_FOR_PERF

#include <iostream>
#include <time.h>
#include <iomanip>

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

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      v.push_back(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Vector v;

    double start = static_cast<double>(clock());

    v.assign(1000000, 42);

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Vector v;

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      v.push_back(i);
    }
    v.clear();

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Vector v;

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      v.insert(v.begin(), i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Vector v;

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      v.insert(v.begin(), i);
    }

    for (int i = 0; i < 100000; ++i) {
      v.insert(v.begin(), i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Vector v;

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      v.push_back(i);
    }
    for (int i = 0; i < 100000; ++i) {
      v.pop_back();
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Vector v;

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      v.push_back(i);
    }
    v.resize(10);
    v.resize(10000000);

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
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

    double start = static_cast<double>(clock());

    v.swap(v2);

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }
}

template <typename Stack>
void vec_stack(Stack) {
  {
    Stack st;

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      st.push(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Stack st;

    for (int i = 0; i < 100000; ++i) {
      st.push(i);
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      st.pop();
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Stack st;

    for (int i = 0; i < 100000; ++i) {
      st.push(i);
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      st.top();
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }
}

template <typename Map, typename Pair>
void vec_map(Map, Pair) {
  {
    Map mp;

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp.at(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp[i];
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp.size();
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp.clear();
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp.erase(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp.count(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp.find(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp.equal_range(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp.lower_bound(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Map mp;

    for (int i = 0; i < 100000; ++i) {
      mp.insert(Pair(i, i));
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      mp.upper_bound(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
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

    double start = static_cast<double>(clock());

    mp.swap(mp1);

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }
}

template <typename Set>
void vec_set(Set) {
  {
    Set st;

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    double start = static_cast<double>(clock());

    st.size();

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    double start = static_cast<double>(clock());

    st.clear();

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      st.erase(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
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

    double start = static_cast<double>(clock());

    st.swap(st2);

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      st.count(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      st.find(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      st.equal_range(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      st.lower_bound(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }

  {
    Set st;

    for (int i = 0; i < 100000; ++i) {
      st.insert(i);
    }

    double start = static_cast<double>(clock());

    for (int i = 0; i < 100000; ++i) {
      st.upper_bound(i);
    }

    double end = static_cast<double>(clock());

    std::cout << std::fixed << std::setprecision(15) << end - start
              << std::endl;
  }
}

#endif
