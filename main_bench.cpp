#include <queue>
#include <utility>
#include <iostream>
#include <chrono>
#include <tuple>

#include <vector>
#include <stack>
#include <map>
#include <set>

#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"

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

  void runSingleFunc(std::string std_block_name, std::string ft_block_name,
                     Func std_block, Func ft_block) {
    // std_blockはstdコンテナの関数を実行するブロック
    auto start = std::chrono::steady_clock::now();
    std_block();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> std_block_erapsed_time = end - start;

    // ft_blockはftコンテナの関数を実行するブロック
    start = std::chrono::steady_clock::now();
    ft_block();
    end = std::chrono::steady_clock::now();
    std::chrono::duration<double> ft_block_erapsed_time = end - start;

    double std_result = std_block_erapsed_time.count();
    double ft_result = ft_block_erapsed_time.count();
    double performance_ratio = ft_result / std_result;

    // ftコンテナライブラリが20倍遅いと許容できない
    if (performance_ratio > 20.000) {
      std::cerr << "RESULT: \033[31mNG\033[0m"
                << " case: " << std_block_name << ", " << ft_block_name
                << std::endl;
      std::cerr << "  std: " << std_result << ", ft: " << ft_result
                << " , ratio: " << performance_ratio << std::endl;
    } else {
      std::cerr << "RESULT: \033[32mOK\033[0m"
                << " case: " << std_block_name << ", " << ft_block_name
                << std::endl;
      std::cerr << "  std: " << std_result << ", ft: " << ft_result
                << " , ratio: " << performance_ratio << std::endl;
    }
  }

private:
  std::queue<std::tuple<std::string, std::string, Func, Func> > runnableQueu;
};

// --------- vector/assign ---------
void ft_vector_assign() {
  ft::vector<int> v;
  v.assign(1, 10000);
}
void std_vector_assign() {
  std::vector<int> v;
  v.assign(1, 10000);
}

// --------- vector/size ---------
void ft_vector_size() {
  ft::vector<int> v;
  v.assign(1, 10000);
  v.size();
}
void std_vector_size() {
  std::vector<int> v;
  v.assign(1, 10000);
  v.size();
}

// --------- vector/reserve ---------
void ft_vector_reserve() {
  ft::vector<int> v;
  v.reserve(100000);
}
void std_vector_reserve() {
  std::vector<int> v;
  v.reserve(100000);
}

// --------- vector/clear ---------
void ft_vector_clear() {
  ft::vector<int> v;
  v.assign(1, 10000);
  v.clear();
}
void std_vector_clear() {
  std::vector<int> v;
  v.assign(1, 10000);
  v.clear();
}

// --------- vector/insert ---------
void ft_vector_insert() {
  ft::vector<int> v;
  v.insert(v.begin(), 10000, 42);
}
void std_vector_insert() {
  std::vector<int> v;
  v.insert(v.begin(), 10000, 42);
}

// --------- vector/erase ---------
void ft_vector_erase() {
  ft::vector<int> v;
  v.insert(v.begin(), 10000, 42);
  v.erase(v.begin(), v.end());
}
void std_vector_erase() {
  std::vector<int> v;
  v.insert(v.begin(), 10000, 42);
  v.erase(v.begin(), v.end());
}

// --------- vector/push_back ---------
void ft_vector_push_back() {
  ft::vector<int> v;
  for (int i = 0; i < 10000; ++i) {
    v.push_back(i);
  }
}
void std_vector_push_back() {
  std::vector<int> v;
  for (int i = 0; i < 10000; ++i) {
    v.push_back(i);
  }
}

// --------- vector/pop_back ---------
void ft_vector_pop_back() {
  ft::vector<int> v;
  v.assign(10000, 42);
  while (!v.empty()) {
    v.pop_back();
  }
}
void std_vector_pop_back() {
  std::vector<int> v;
  v.assign(10000, 42);
  while (!v.empty()) {
    v.pop_back();
  }
}

// --------- vector/resize ---------
void ft_vector_resize() {
  ft::vector<int> v;
  v.resize(10000);
}
void std_vector_resize() {
  std::vector<int> v;
  v.resize(10000);
}

// --------- vector/swap ---------
void ft_vector_swap() {
  ft::vector<int> v;
  v.assign(1000000, 42);
  ft::vector<int> v2;
  v2.assign(42, 10000);
  v.swap(v2);
}
void std_vector_swap() {
  std::vector<int> v;
  v.assign(1000000, 42);
  std::vector<int> v2;
  v2.assign(42, 10000);
  v.swap(v2);
}

// --------- stack/top ---------
void ft_stack_top() {
  ft::stack<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.push(i);
    s.top();
  }
}
void std_stack_top() {
  std::stack<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.push(i);
    s.top();
  }
}

// --------- stack/size ---------
void ft_stack_size() {
  ft::stack<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.push(i);
    s.size();
  }
}
void std_stack_size() {
  std::stack<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.push(i);
    s.size();
  }
}

// --------- stack/push ---------
void ft_stack_push() {
  ft::stack<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.push(i);
  }
}
void std_stack_push() {
  std::stack<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.push(i);
  }
}

// --------- stack/pop ---------
void ft_stack_pop() {
  ft::stack<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.push(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.pop();
  }
}
void std_stack_pop() {
  std::stack<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.push(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.pop();
  }
}

// --------- map/at ---------
void ft_map_at() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  m.at(42);
}
void std_map_at() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  m.at(42);
}

// --------- map/iterator ---------
void ft_map_iterator() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  for (ft::map<int, int>::iterator itr = m.begin(); itr != m.end(); ++itr) {
  }
}
void std_map_iterator() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  for (std::map<int, int>::iterator itr = m.begin(); itr != m.end(); ++itr) {
  }
}

// --------- map/empty ---------
void ft_map_empty() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  m.empty();
}
void std_map_empty() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  m.empty();
}

// --------- map/size ---------
void ft_map_size() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  m.size();
}
void std_map_size() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  m.size();
}

// --------- map/clear ---------
void ft_map_clear() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  m.clear();
}
void std_map_clear() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  m.clear();
}

// --------- map/insert ---------
void ft_map_insert() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
}
void std_map_insert() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
}

// --------- map/erase ---------
void ft_map_erase() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  m.erase(m.begin(), m.end());
}
void std_map_erase() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  m.erase(m.begin(), m.end());
}

// --------- map/swap ---------
void ft_map_swap() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  ft::map<int, int> m2;
  m.swap(m2);
}
void std_map_swap() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  std::map<int, int> m2;
  m.swap(m2);
}

// --------- map/count ---------
void ft_map_count() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.count(i);
  }
}
void std_map_count() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.count(i);
  }
}

// --------- map/find ---------
void ft_map_find() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.find(i);
  }
}
void std_map_find() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.find(i);
  }
}

// --------- map/equal_range ---------
void ft_map_equal_range() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.equal_range(i);
  }
}
void std_map_equal_range() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.equal_range(i);
  }
}

// --------- map/lower_bound ---------
void ft_map_lower_bound() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.lower_bound(i);
  }
}
void std_map_lower_bound() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.lower_bound(i);
  }
}

// --------- map/upper_bound ---------
void ft_map_upper_bound() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.upper_bound(i);
  }
}
void std_map_upper_bound() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.upper_bound(i);
  }
}

// --------- set/iterator ---------
void ft_set_iterator() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (ft::set<int>::iterator itr = s.begin(); itr != s.end(); ++itr) {
  }
}
void std_set_iterator() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (std::set<int>::iterator itr = s.begin(); itr != s.end(); ++itr) {
  }
}

// --------- set/empty ---------
void ft_set_empty() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  s.empty();
}
void std_set_empty() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  s.empty();
}

// --------- set/size ---------
void ft_set_size() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  s.size();
}
void std_set_size() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  s.size();
}

// --------- set/clear ---------
void ft_set_clear() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  s.clear();
}
void std_set_clear() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  s.clear();
}

// --------- set/insert ---------
void ft_set_insert() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
}
void std_set_insert() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
}

// --------- set/erase ---------
void ft_set_erase() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  s.erase(s.begin(), s.end());
}
void std_set_erase() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  s.erase(s.begin(), s.end());
}

// --------- set/swap ---------
void ft_set_swap() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  ft::set<int> s2;
  s.swap(s2);
}
void std_set_swap() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  std::set<int> s2;
  s.swap(s2);
}

// --------- set/count ---------
void ft_set_count() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.count(i);
  }
}
void std_set_count() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.count(i);
  }
}

// --------- set/find ---------
void ft_set_find() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.find(i);
  }
}
void std_set_find() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.find(i);
  }
}

// --------- set/equal_range ---------
void ft_set_equal_range() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.equal_range(i);
  }
}
void std_set_equal_range() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.equal_range(i);
  }
}

// --------- set/lower_bound ---------
void ft_set_lower_bound() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.lower_bound(i);
  }
}
void std_set_lower_bound() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.lower_bound(i);
  }
}

// --------- set/upper_bound ---------
void ft_set_upper_bound() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.upper_bound(i);
  }
}
void std_set_upper_bound() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.upper_bound(i);
  }
}

typedef void (*testRunnable)();

int main() {
  TestRunner<testRunnable> runner;

  // vector
  runner.ADDBENCHMARKFUNC(std_vector_assign, ft_vector_assign);
  runner.ADDBENCHMARKFUNC(std_vector_size, ft_vector_size);
  runner.ADDBENCHMARKFUNC(std_vector_reserve, ft_vector_reserve);
  runner.ADDBENCHMARKFUNC(std_vector_clear, ft_vector_clear);
  runner.ADDBENCHMARKFUNC(std_vector_insert, ft_vector_insert);
  runner.ADDBENCHMARKFUNC(std_vector_push_back, ft_vector_push_back);
  runner.ADDBENCHMARKFUNC(std_vector_pop_back, ft_vector_pop_back);
  runner.ADDBENCHMARKFUNC(std_vector_resize, ft_vector_resize);
  runner.ADDBENCHMARKFUNC(std_vector_swap, ft_vector_swap);

  // stack
  runner.ADDBENCHMARKFUNC(std_stack_top, ft_stack_top);
  runner.ADDBENCHMARKFUNC(std_stack_size, ft_stack_size);
  runner.ADDBENCHMARKFUNC(std_stack_push, ft_stack_push);
  runner.ADDBENCHMARKFUNC(std_stack_pop, ft_stack_pop);

  // map
  runner.ADDBENCHMARKFUNC(std_map_at, ft_map_at);
  runner.ADDBENCHMARKFUNC(std_map_iterator, ft_map_iterator);
  runner.ADDBENCHMARKFUNC(std_map_empty, ft_map_empty);
  runner.ADDBENCHMARKFUNC(std_map_size, ft_map_size);
  runner.ADDBENCHMARKFUNC(std_map_clear, ft_map_clear);
  runner.ADDBENCHMARKFUNC(std_map_insert, ft_map_insert);
  runner.ADDBENCHMARKFUNC(std_map_erase, ft_map_erase);
  runner.ADDBENCHMARKFUNC(std_map_swap, ft_map_swap);
  runner.ADDBENCHMARKFUNC(std_map_count, ft_map_count);
  runner.ADDBENCHMARKFUNC(std_map_find, ft_map_find);
  runner.ADDBENCHMARKFUNC(std_map_equal_range, ft_map_equal_range);
  runner.ADDBENCHMARKFUNC(std_map_lower_bound, ft_map_lower_bound);
  runner.ADDBENCHMARKFUNC(std_map_upper_bound, ft_map_upper_bound);

  // set
  runner.ADDBENCHMARKFUNC(std_set_iterator, ft_set_iterator);
  runner.ADDBENCHMARKFUNC(std_set_empty, ft_set_empty);
  runner.ADDBENCHMARKFUNC(std_set_size, ft_set_size);
  runner.ADDBENCHMARKFUNC(std_set_clear, ft_set_clear);
  runner.ADDBENCHMARKFUNC(std_set_insert, ft_set_insert);
  runner.ADDBENCHMARKFUNC(std_set_erase, ft_set_erase);
  runner.ADDBENCHMARKFUNC(std_set_swap, ft_set_swap);
  runner.ADDBENCHMARKFUNC(std_set_count, ft_set_count);
  runner.ADDBENCHMARKFUNC(std_set_find, ft_set_find);
  runner.ADDBENCHMARKFUNC(std_set_equal_range, ft_set_equal_range);
  runner.ADDBENCHMARKFUNC(std_set_lower_bound, ft_set_lower_bound);
  runner.ADDBENCHMARKFUNC(std_set_upper_bound, ft_set_upper_bound);

  runner.runAll();

  return 0;
}
