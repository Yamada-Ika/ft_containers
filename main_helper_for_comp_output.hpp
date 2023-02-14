#ifndef MAIN_HELPER_FOR_COMP_OUTPUT
#define MAIN_HELPER_FOR_COMP_OUTPUT

#include <iostream>

#include <vector>
#include "vector.hpp"

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

#endif
