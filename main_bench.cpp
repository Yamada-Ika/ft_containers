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

// test data
ft::vector<int> g_ft_vec(1000000, 42);
std::vector<int> g_std_vec(1000000, 42);
ft::stack<int> g_ft_stack;
std::stack<int> g_std_stack;
ft::map<int, int> g_ft_mp;
std::map<int, int> g_std_mp;
ft::set<int> g_ft_set;
std::set<int> g_std_set;

// --------- vector/construct ---------
void ft_vector_construct() { ft::vector<int> v(1000000, 42); }
void std_vector_construct() { std::vector<int> v(1000000, 42); }

// --------- vector/assign operator ---------
void ft_vector_assign_operator() {
  ft::vector<int> v1;
  v1 = g_ft_vec;
}
void std_vector_assign_operator() {
  std::vector<int> v1;
  v1 = g_std_vec;
}

// --------- vector/assign ---------
void ft_vector_assign() {
  ft::vector<int> v;
  v.assign(1, 10000);
}
void std_vector_assign() {
  std::vector<int> v;
  v.assign(1, 10000);
}

void ft_vector_assign_1() {
  ft::vector<int> v;
  v.assign(g_ft_vec.begin(), g_ft_vec.end());
}
void std_vector_assign_1() {
  std::vector<int> v;
  v.assign(g_std_vec.begin(), g_std_vec.end());
}

// --------- vector/at ---------
void ft_vector_at() {
  for (size_t i = 0; i < g_ft_vec.size(); ++i) {
    g_ft_vec.at(i);
  }
}
void std_vector_at() {
  for (size_t i = 0; i < g_std_vec.size(); ++i) {
    g_std_vec.at(i);
  }
}

// --------- vector/brackets operator ---------
void ft_vector_brackets_operator() {
  for (size_t i = 0; i < g_ft_vec.size(); ++i) {
    g_ft_vec[i];
  }
}
void std_vector_brackets_operator() {
  for (size_t i = 0; i < g_std_vec.size(); ++i) {
    g_std_vec[i];
  }
}

// --------- vector/front ---------
void ft_vector_front() {
  for (size_t i = 0; i < g_ft_vec.size(); ++i) {
    g_ft_vec.front();
  }
}
void std_vector_front() {
  for (size_t i = 0; i < g_std_vec.size(); ++i) {
    g_std_vec.front();
  }
}

// --------- vector/back ---------
void ft_vector_back() {
  for (size_t i = 0; i < g_ft_vec.size(); ++i) {
    g_ft_vec.back();
  }
}
void std_vector_back() {
  for (size_t i = 0; i < g_std_vec.size(); ++i) {
    g_std_vec.back();
  }
}

// --------- vector/data ---------
void ft_vector_data() {
  for (size_t i = 0; i < g_ft_vec.size(); ++i) {
    g_ft_vec.data();
  }
}
void std_vector_data() {
  for (size_t i = 0; i < g_std_vec.size(); ++i) {
    g_std_vec.data();
  }
}

// --------- vector/begin ---------
void ft_vector_begin() {
  for (ft::vector<int>::iterator itr = g_ft_vec.begin(); itr != g_ft_vec.end();
       ++itr) {
  }
}
void std_vector_begin() {
  for (std::vector<int>::iterator itr = g_std_vec.begin();
       itr != g_std_vec.end(); ++itr) {
  }
}

// --------- vector/empty ---------
void ft_vector_empty() {
  for (size_t i = 0; i < g_ft_vec.size(); ++i) {
    g_ft_vec.empty();
  }
}
void std_vector_empty() {
  for (size_t i = 0; i < g_std_vec.size(); ++i) {
    g_std_vec.empty();
  }
}

// --------- vector/size ---------
void ft_vector_size() {
  for (size_t i = 0; i < g_ft_vec.size(); ++i) {
    g_ft_vec.size();
  }
}
void std_vector_size() {
  for (size_t i = 0; i < g_std_vec.size(); ++i) {
    g_std_vec.size();
  }
}

// --------- vector/max_size ---------
void ft_vector_max_size() {
  for (size_t i = 0; i < g_ft_vec.size(); ++i) {
    g_ft_vec.max_size();
  }
}
void std_vector_max_size() {
  for (size_t i = 0; i < g_std_vec.size(); ++i) {
    g_std_vec.max_size();
  }
}

// --------- vector/reserve ---------
void ft_vector_reserve() {
  ft::vector<int> v;
  for (int i = 0; i < 100000; ++i) {
    v.reserve(i);
  }
}
void std_vector_reserve() {
  std::vector<int> v;
  for (int i = 0; i < 100000; ++i) {
    v.reserve(i);
  }
}

// --------- vector/capacity ---------
void ft_vector_capacity() {
  for (size_t i = 0; i < g_ft_vec.size(); ++i) {
    g_ft_vec.capacity();
  }
}
void std_vector_capacity() {
  for (size_t i = 0; i < g_std_vec.size(); ++i) {
    g_std_vec.capacity();
  }
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

void ft_vector_insert_1() {
  ft::vector<int> v;
  for (int i = 0; i < 10000; ++i) {
    v.insert(v.begin(), i);
  }
}
void std_vector_insert_1() {
  std::vector<int> v;
  for (int i = 0; i < 10000; ++i) {
    v.insert(v.begin(), i);
  }
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

void ft_vector_erase_1() {
  ft::vector<int> v;
  v.insert(v.begin(), 10000, 42);
  for (size_t i = 0; i < v.size(); ++i) {
    v.erase(v.begin());
  }
}
void std_vector_erase_1() {
  std::vector<int> v;
  v.insert(v.begin(), 10000, 42);
  for (size_t i = 0; i < v.size(); ++i) {
    v.erase(v.begin());
  }
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
  for (int i = 0; i < 10000; ++i) {
    v.resize(i);
  }
}
void std_vector_resize() {
  std::vector<int> v;
  for (int i = 0; i < 10000; ++i) {
    v.resize(i);
  }
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

// --------- stack/construct ---------
void ft_stack_construct() { ft::stack<int> s(g_ft_stack); }
void std_stack_construct() { std::stack<int> s(g_std_stack); }

void ft_stack_construct_1() {
  ft::stack<int> s;
  s = g_ft_stack;
}
void std_stack_construct_1() {
  std::stack<int> s;
  s = g_std_stack;
}

// --------- stack/top ---------
void ft_stack_top() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_stack.top();
  }
}
void std_stack_top() {
  for (int i = 0; i < 100000; ++i) {
    g_std_stack.top();
  }
}

// --------- stack/empty ---------
void ft_stack_empty() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_stack.empty();
  }
}
void std_stack_empty() {
  for (int i = 0; i < 100000; ++i) {
    g_std_stack.empty();
  }
}

// --------- stack/size ---------
void ft_stack_size() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_stack.size();
  }
}
void std_stack_size() {
  for (int i = 0; i < 100000; ++i) {
    g_std_stack.size();
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
  for (int i = 0; i < 100000; ++i) {
    g_ft_stack.pop();
  }
}
void std_stack_pop() {
  for (int i = 0; i < 100000; ++i) {
    g_std_stack.pop();
  }
}

// --------- map/construct ---------
void ft_map_construct() { ft::map<int, int> m(g_ft_mp.begin(), g_ft_mp.end()); }
void std_map_construct() {
  std::map<int, int> m(g_std_mp.begin(), g_std_mp.end());
}

void ft_map_construct_1() { ft::map<int, int> m(g_ft_mp); }
void std_map_construct_1() { std::map<int, int> m(g_std_mp); }

// --------- map/assign_operator ---------
void ft_map_assign_operator() {
  ft::map<int, int> m;
  m = g_ft_mp;
}
void std_map_assign_operator() {
  std::map<int, int> m;
  m = g_std_mp;
}

// --------- map/at ---------
void ft_map_at() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_mp.at(i);
  }
}
void std_map_at() {
  for (int i = 0; i < 100000; ++i) {
    g_std_mp.at(i);
  }
}

// --------- map/bracket_operator ---------
void ft_map_bracket_operator() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_mp[i];
  }
}
void std_map_bracket_operator() {
  for (int i = 0; i < 100000; ++i) {
    g_std_mp[i];
  }
}

// --------- map/iterator ---------
void ft_map_iterator() {
  for (ft::map<int, int>::iterator itr = g_ft_mp.begin(); itr != g_ft_mp.end();
       ++itr) {
  }
}
void std_map_iterator() {
  for (std::map<int, int>::iterator itr = g_std_mp.begin();
       itr != g_std_mp.end(); ++itr) {
  }
}

void ft_map_iterator_1() {
  for (ft::map<int, int>::reverse_iterator itr = g_ft_mp.rbegin();
       itr != g_ft_mp.rend(); ++itr) {
  }
}
void std_map_iterator_1() {
  for (std::map<int, int>::reverse_iterator itr = g_std_mp.rbegin();
       itr != g_std_mp.rend(); ++itr) {
  }
}

// --------- map/empty ---------
void ft_map_empty() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_mp.empty();
  }
}
void std_map_empty() {
  for (int i = 0; i < 100000; ++i) {
    g_std_mp.empty();
  }
}

// --------- map/size ---------
void ft_map_size() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_mp.size();
  }
}
void std_map_size() {
  for (int i = 0; i < 100000; ++i) {
    g_std_mp.size();
  }
}

// --------- map/max_size ---------
void ft_map_max_size() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_mp.max_size();
  }
}
void std_map_max_size() {
  for (int i = 0; i < 100000; ++i) {
    g_std_mp.max_size();
  }
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

void ft_map_insert_1() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(m.begin(), ft::make_pair(i, i));
  }
}
void std_map_insert_1() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(m.begin(), std::make_pair(i, i));
  }
}

void ft_map_insert_2() {
  ft::map<int, int> m;
  m.insert(g_ft_mp.begin(), g_ft_mp.end());
}
void std_map_insert_2() {
  std::map<int, int> m;
  m.insert(g_std_mp.begin(), g_std_mp.end());
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

void ft_map_erase_1() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.erase(m.begin());
  }
}
void std_map_erase_1() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.erase(m.begin());
  }
}

void ft_map_erase_2() {
  ft::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.erase(i);
  }
}
void std_map_erase_2() {
  std::map<int, int> m;
  for (int i = 0; i < 100000; ++i) {
    m.insert(std::make_pair(i, i));
  }
  for (int i = 0; i < 100000; ++i) {
    m.erase(i);
  }
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
  for (int i = 0; i < 100000; ++i) {
    g_ft_mp.count(i);
  }
}
void std_map_count() {
  for (int i = 0; i < 100000; ++i) {
    g_std_mp.count(i);
  }
}

// --------- map/find ---------
void ft_map_find() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_mp.find(i);
  }
}
void std_map_find() {
  for (int i = 0; i < 100000; ++i) {
    g_std_mp.find(i);
  }
}

// --------- map/equal_range ---------
void ft_map_equal_range() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_mp.equal_range(i);
  }
}
void std_map_equal_range() {
  for (int i = 0; i < 100000; ++i) {
    g_std_mp.equal_range(i);
  }
}

// --------- map/lower_bound ---------
void ft_map_lower_bound() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_mp.lower_bound(i);
  }
}
void std_map_lower_bound() {
  for (int i = 0; i < 100000; ++i) {
    g_std_mp.lower_bound(i);
  }
}

// --------- map/upper_bound ---------
void ft_map_upper_bound() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_mp.upper_bound(i);
  }
}
void std_map_upper_bound() {
  for (int i = 0; i < 100000; ++i) {
    g_std_mp.upper_bound(i);
  }
}

// --------- set/construct ---------
void ft_set_construct() { ft::set<int> s(g_ft_set.begin(), g_ft_set.end()); }
void std_set_construct() {
  std::set<int> s(g_std_set.begin(), g_std_set.end());
}

void ft_set_construct_1() { ft::set<int> s(g_ft_set); }
void std_set_construct_1() { std::set<int> s(g_std_set); }

void ft_set_construct_2() {
  ft::set<int> s;
  s = g_ft_set;
}
void std_set_construct_2() {
  std::set<int> s;
  s = g_std_set;
}

// --------- set/iterator ---------
void ft_set_iterator() {
  for (ft::set<int>::iterator itr = g_ft_set.begin(); itr != g_ft_set.end();
       ++itr) {
  }
}
void std_set_iterator() {
  for (std::set<int>::iterator itr = g_std_set.begin(); itr != g_std_set.end();
       ++itr) {
  }
}

void ft_set_iterator_1() {
  for (ft::set<int>::reverse_iterator itr = g_ft_set.rbegin();
       itr != g_ft_set.rend(); ++itr) {
  }
}
void std_set_iterator_1() {
  for (std::set<int>::reverse_iterator itr = g_std_set.rbegin();
       itr != g_std_set.rend(); ++itr) {
  }
}

// --------- set/empty ---------
void ft_set_empty() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_set.empty();
  }
}
void std_set_empty() {
  for (int i = 0; i < 100000; ++i) {
    g_std_set.empty();
  }
}

// --------- set/size ---------
void ft_set_size() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_set.size();
  }
}
void std_set_size() {
  for (int i = 0; i < 100000; ++i) {
    g_std_set.size();
  }
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

void ft_set_insert_1() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(s.begin(), i);
  }
}
void std_set_insert_1() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(s.begin(), i);
  }
}

void ft_set_insert_2() {
  ft::set<int> s;
  s.insert(g_ft_set.begin(), g_ft_set.end());
}
void std_set_insert_2() {
  std::set<int> s;
  s.insert(g_std_set.begin(), g_std_set.end());
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

void ft_set_erase_1() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.erase(s.begin());
  }
}
void std_set_erase_1() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.erase(s.begin());
  }
}

void ft_set_erase_2() {
  ft::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.erase(i);
  }
}
void std_set_erase_2() {
  std::set<int> s;
  for (int i = 0; i < 100000; ++i) {
    s.insert(i);
  }
  for (int i = 0; i < 100000; ++i) {
    s.erase(i);
  }
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
  for (int i = 0; i < 100000; ++i) {
    g_ft_set.count(i);
  }
}
void std_set_count() {
  for (int i = 0; i < 100000; ++i) {
    g_std_set.count(i);
  }
}

// --------- set/find ---------
void ft_set_find() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_set.find(i);
  }
}
void std_set_find() {
  for (int i = 0; i < 100000; ++i) {
    g_std_set.find(i);
  }
}

// --------- set/equal_range ---------
void ft_set_equal_range() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_set.equal_range(i);
  }
}
void std_set_equal_range() {
  for (int i = 0; i < 100000; ++i) {
    g_std_set.equal_range(i);
  }
}

// --------- set/lower_bound ---------
void ft_set_lower_bound() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_set.lower_bound(i);
  }
}
void std_set_lower_bound() {
  for (int i = 0; i < 100000; ++i) {
    g_std_set.lower_bound(i);
  }
}

// --------- set/upper_bound ---------
void ft_set_upper_bound() {
  for (int i = 0; i < 100000; ++i) {
    g_ft_set.upper_bound(i);
  }
}
void std_set_upper_bound() {
  for (int i = 0; i < 100000; ++i) {
    g_std_set.upper_bound(i);
  }
}

typedef void (*testRunnable)();

int main() {
  for (int i = 0; i < 1000000; ++i) {
    g_ft_stack.push(i);
    g_std_stack.push(i);
    g_ft_mp.insert(ft::pair<int, int>(i, i));
    g_std_mp.insert(std::pair<int, int>(i, i));
    g_ft_set.insert(i);
    g_std_set.insert(i);
  }

  TestRunner<testRunnable> runner;

  // vector
  runner.ADDBENCHMARKFUNC(std_vector_construct, ft_vector_construct);
  runner.ADDBENCHMARKFUNC(std_vector_assign_operator,
                          ft_vector_assign_operator);
  runner.ADDBENCHMARKFUNC(std_vector_assign, ft_vector_assign);
  runner.ADDBENCHMARKFUNC(std_vector_assign_1, ft_vector_assign_1);
  runner.ADDBENCHMARKFUNC(std_vector_at, ft_vector_at);
  runner.ADDBENCHMARKFUNC(std_vector_front, ft_vector_front);
  runner.ADDBENCHMARKFUNC(std_vector_back, ft_vector_back);
  runner.ADDBENCHMARKFUNC(std_vector_data, ft_vector_data);
  runner.ADDBENCHMARKFUNC(std_vector_begin, ft_vector_begin);
  runner.ADDBENCHMARKFUNC(std_vector_empty, ft_vector_empty);
  runner.ADDBENCHMARKFUNC(std_vector_size, ft_vector_size);
  runner.ADDBENCHMARKFUNC(std_vector_max_size, ft_vector_max_size);
  runner.ADDBENCHMARKFUNC(std_vector_reserve, ft_vector_reserve);
  runner.ADDBENCHMARKFUNC(std_vector_capacity, ft_vector_capacity);
  runner.ADDBENCHMARKFUNC(std_vector_clear, ft_vector_clear);
  runner.ADDBENCHMARKFUNC(std_vector_erase, ft_vector_erase);
  runner.ADDBENCHMARKFUNC(std_vector_erase_1, ft_vector_erase_1);
  runner.ADDBENCHMARKFUNC(std_vector_insert, ft_vector_insert);
  runner.ADDBENCHMARKFUNC(std_vector_insert_1, ft_vector_insert_1);
  runner.ADDBENCHMARKFUNC(std_vector_push_back, ft_vector_push_back);
  runner.ADDBENCHMARKFUNC(std_vector_pop_back, ft_vector_pop_back);
  runner.ADDBENCHMARKFUNC(std_vector_resize, ft_vector_resize);
  runner.ADDBENCHMARKFUNC(std_vector_swap, ft_vector_swap);

  // stack
  runner.ADDBENCHMARKFUNC(std_stack_construct, ft_stack_construct);
  runner.ADDBENCHMARKFUNC(std_stack_construct_1, ft_stack_construct_1);
  runner.ADDBENCHMARKFUNC(std_stack_top, ft_stack_top);
  runner.ADDBENCHMARKFUNC(std_stack_empty, ft_stack_empty);
  runner.ADDBENCHMARKFUNC(std_stack_size, ft_stack_size);
  runner.ADDBENCHMARKFUNC(std_stack_push, ft_stack_push);
  runner.ADDBENCHMARKFUNC(std_stack_pop, ft_stack_pop);

  // map
  runner.ADDBENCHMARKFUNC(std_map_construct, ft_map_construct);
  runner.ADDBENCHMARKFUNC(std_map_construct_1, ft_map_construct_1);
  runner.ADDBENCHMARKFUNC(std_map_assign_operator, ft_map_assign_operator);
  runner.ADDBENCHMARKFUNC(std_map_at, ft_map_at);
  runner.ADDBENCHMARKFUNC(std_map_bracket_operator, ft_map_bracket_operator);
  runner.ADDBENCHMARKFUNC(std_map_iterator, ft_map_iterator);
  runner.ADDBENCHMARKFUNC(std_map_iterator_1, ft_map_iterator_1);
  runner.ADDBENCHMARKFUNC(std_map_empty, ft_map_empty);
  runner.ADDBENCHMARKFUNC(std_map_size, ft_map_size);
  runner.ADDBENCHMARKFUNC(std_map_max_size, ft_map_max_size);
  runner.ADDBENCHMARKFUNC(std_map_clear, ft_map_clear);
  runner.ADDBENCHMARKFUNC(std_map_insert, ft_map_insert);
  runner.ADDBENCHMARKFUNC(std_map_insert_1, ft_map_insert_1);
  runner.ADDBENCHMARKFUNC(std_map_insert_2, ft_map_insert_2);
  runner.ADDBENCHMARKFUNC(std_map_erase, ft_map_erase);
  runner.ADDBENCHMARKFUNC(std_map_erase_1, ft_map_erase_1);
  runner.ADDBENCHMARKFUNC(std_map_erase_2, ft_map_erase_2);
  runner.ADDBENCHMARKFUNC(std_map_swap, ft_map_swap);
  runner.ADDBENCHMARKFUNC(std_map_count, ft_map_count);
  runner.ADDBENCHMARKFUNC(std_map_find, ft_map_find);
  runner.ADDBENCHMARKFUNC(std_map_equal_range, ft_map_equal_range);
  runner.ADDBENCHMARKFUNC(std_map_lower_bound, ft_map_lower_bound);
  runner.ADDBENCHMARKFUNC(std_map_upper_bound, ft_map_upper_bound);

  // set
  runner.ADDBENCHMARKFUNC(ft_set_construct, ft_set_construct);
  runner.ADDBENCHMARKFUNC(ft_set_construct_1, ft_set_construct_1);
  runner.ADDBENCHMARKFUNC(ft_set_construct_2, std_set_construct_2);
  runner.ADDBENCHMARKFUNC(std_set_iterator, ft_set_iterator);
  runner.ADDBENCHMARKFUNC(std_set_iterator_1, ft_set_iterator_1);
  runner.ADDBENCHMARKFUNC(std_set_empty, ft_set_empty);
  runner.ADDBENCHMARKFUNC(std_set_size, ft_set_size);
  runner.ADDBENCHMARKFUNC(std_set_clear, ft_set_clear);
  runner.ADDBENCHMARKFUNC(std_set_insert, ft_set_insert);
  runner.ADDBENCHMARKFUNC(std_set_insert_1, ft_set_insert_1);
  runner.ADDBENCHMARKFUNC(std_set_insert_2, ft_set_insert_2);
  runner.ADDBENCHMARKFUNC(std_set_erase, ft_set_erase);
  runner.ADDBENCHMARKFUNC(std_set_erase_1, ft_set_erase_1);
  runner.ADDBENCHMARKFUNC(std_set_erase_2, ft_set_erase_2);
  runner.ADDBENCHMARKFUNC(std_set_swap, ft_set_swap);
  runner.ADDBENCHMARKFUNC(std_set_count, ft_set_count);
  runner.ADDBENCHMARKFUNC(std_set_find, ft_set_find);
  runner.ADDBENCHMARKFUNC(std_set_equal_range, ft_set_equal_range);
  runner.ADDBENCHMARKFUNC(std_set_lower_bound, ft_set_lower_bound);
  runner.ADDBENCHMARKFUNC(std_set_upper_bound, ft_set_upper_bound);

  runner.runAll();

  return 0;
}
