# Google Test インストール用ルール

cmake_minimum_required(VERSION 3.14)
project(my_project)

add_compile_options(-std=c++98)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# テスト用ルール

enable_testing()

find_package (glog 0.4.0 REQUIRED)

add_executable(
  test_vector
  test_vector.cpp
)

add_executable(
  test_stack
  test_stack.cpp
)

add_executable(
  test_deque
  test_deque.cpp
)

add_executable(
  test_tree
  test_tree.cpp
)

add_executable(
  test_set
  test_set.cpp
)

add_executable(
  test_map
  test_map.cpp
)

add_executable(
  test_pair
  test_pair.cpp
)

target_link_libraries(
  test_vector
  GTest::gtest_main
  glog::glog
)

target_link_libraries(
  test_stack
  GTest::gtest_main
  glog::glog
)

target_link_libraries(
  test_deque
  GTest::gtest_main
  glog::glog
)

target_link_libraries(
  test_tree
  GTest::gtest_main
  glog::glog
)

target_link_libraries(
  test_set
  GTest::gtest_main
  glog::glog
)

target_link_libraries(
  test_map
  GTest::gtest_main
  glog::glog
)

target_link_libraries(
  test_pair
  GTest::gtest_main
  glog::glog
)

include(GoogleTest)
gtest_discover_tests(test_vector)
gtest_discover_tests(test_stack)
gtest_discover_tests(test_deque)
gtest_discover_tests(test_tree)
gtest_discover_tests(test_set)
gtest_discover_tests(test_map)
gtest_discover_tests(test_pair)
