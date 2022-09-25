#include <gtest/gtest.h>

#include "../type_traits.hpp"
#include <type_traits>

TEST(IsIntegralTest, basic_int) {
  ASSERT_EQ(ft::is_integral<int>::value, true);
}

// TEST(IsIntegralTest, basic_intstd) {
//   ASSERT_EQ(std::is_integral<int>::value, true);
// }
