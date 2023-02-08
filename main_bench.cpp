#include <queue>
#include <utility>
#include <iostream>
#include <chrono>
#include <tuple>

#include <vector>

#include "vector.hpp"

#define ADDBENCHMARKFUNC(block1, block2)                                       \
  addBenchmarkFuncYouWant(#block1, #block2, block1, block2)

template <typename Func>
class TestRunner {
public:
  void addBenchmarkFuncYouWant(std::string block1_name, std::string block2_name,
                               Func block1, Func block2) {
    runnableQueu.push(
        std::make_tuple(block1_name, block2_name, block1, block2));
  }

  void runAll() {
    while (!runnableQueu.empty()) {
      std::tuple<std::string, std::string, Func, Func> t = runnableQueu.front();
      runnableQueu.pop();
      std::string b1_name = std::get<0>(t);
      std::string b2_name = std::get<1>(t);
      Func b1 = std::get<2>(t);
      Func b2 = std::get<3>(t);
      runSingleFunc(b1_name, b2_name, b1, b2);
    }
  }

  void runSingleFunc(std::string block1_name, std::string block2_name,
                     Func block1, Func block2) {
    auto start = std::chrono::steady_clock::now();
    block1();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> block1_erapsed_time = end - start;

    start = std::chrono::steady_clock::now();
    block2();
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> block2_erapsed_time = end - start;

    std::cerr << "LOG/" << block2_name << "/" << block1_name << ": "
              << block2_erapsed_time.count() / block1_erapsed_time.count()
              << std::endl;
  }

private:
  std::queue<std::tuple<std::string, std::string, Func, Func> > runnableQueu;
};

// --------- vector/assign ---------
void ft_vector_test_assign_1() {
  ft::vector<int> v;
  v.assign(1, 10000);
}
void std_vector_test_assign_1() {
  std::vector<int> v;
  v.assign(1, 10000);
}

// --------- vector/size ---------
void ft_vector_test_size_1() {
  ft::vector<int> v;
  v.assign(1, 10000);
  v.size();
}
void std_vector_test_size_1() {
  std::vector<int> v;
  v.assign(1, 10000);
  v.size();
}

// --------- vector/reserve ---------
void ft_vector_test_reserve_1() {
  ft::vector<int> v;
  v.reserve(100000);
}
void std_vector_test_reserve_1() {
  std::vector<int> v;
  v.reserve(100000);
}

// --------- vector/clear ---------
void ft_vector_test_clear_1() {
  ft::vector<int> v;
  v.assign(1, 10000);
  v.clear();
}
void std_vector_test_clear_1() {
  std::vector<int> v;
  v.assign(1, 10000);
  v.clear();
}

// --------- vector/insert ---------
void ft_vector_test_insert_1() {
  ft::vector<int> v;
  v.insert(v.begin(), 10000, 42);
}
void std_vector_test_insert_1() {
  std::vector<int> v;
  v.insert(v.begin(), 10000, 42);
}

// --------- vector/erase ---------
void ft_vector_test_erase_1() {
  ft::vector<int> v;
  v.insert(v.begin(), 10000, 42);
  v.erase(v.begin(), v.end());
}
void std_vector_test_erase_1() {
  std::vector<int> v;
  v.insert(v.begin(), 10000, 42);
  v.erase(v.begin(), v.end());
}

// --------- vector/push_back ---------
void ft_vector_test_push_back_1() {
  ft::vector<int> v;
  for (int i = 0; i < 10000; ++i) {
    v.push_back(i);
  }
}
void std_vector_test_push_back_1() {
  std::vector<int> v;
  for (int i = 0; i < 10000; ++i) {
    v.push_back(i);
  }
}

// --------- vector/resize ---------
void ft_vector_test_resize_1() {
  ft::vector<int> v;
  v.resize(10000);
}
void std_vector_test_resize_1() {
  std::vector<int> v;
  v.resize(10000);
}

// --------- vector/swap ---------
void ft_vector_test_swap_1() {
  ft::vector<int> v;
  v.assign(1000000, 42);
  ft::vector<int> v2;
  v2.assign(42, 10000);
  v.swap(v2);
}
void std_vector_test_swap_1() {
  std::vector<int> v;
  v.assign(1000000, 42);
  std::vector<int> v2;
  v2.assign(42, 10000);
  v.swap(v2);
}

typedef void (*testRunnable)();

int main() {
  TestRunner<testRunnable> runner;

  runner.ADDBENCHMARKFUNC(std_vector_test_assign_1, ft_vector_test_assign_1);
  runner.ADDBENCHMARKFUNC(std_vector_test_size_1, ft_vector_test_size_1);
  runner.ADDBENCHMARKFUNC(std_vector_test_reserve_1, ft_vector_test_reserve_1);
  runner.ADDBENCHMARKFUNC(std_vector_test_clear_1, ft_vector_test_clear_1);
  runner.ADDBENCHMARKFUNC(std_vector_test_insert_1, ft_vector_test_insert_1);
  runner.ADDBENCHMARKFUNC(std_vector_test_push_back_1,
                          ft_vector_test_push_back_1);
  runner.ADDBENCHMARKFUNC(std_vector_test_resize_1, ft_vector_test_resize_1);
  runner.ADDBENCHMARKFUNC(std_vector_test_swap_1, ft_vector_test_swap_1);
  runner.runAll();

  return 0;
}
