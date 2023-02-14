#ifndef MAIN_HELPER_FOR_PERF
#define MAIN_HELPER_FOR_PERF

#include <iostream>
#include <time.h>

#include <vector>
#include "vector.hpp"

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
}

#endif
