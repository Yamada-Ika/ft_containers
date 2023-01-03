#include "map.hpp"
#include "set.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "deque.hpp"

int main() {
  {
    ft::vector<int> vec1;
    vec1.push_back(1);

    ft::vector<int> vec2;

    vec2 = vec1;
  }

  {
    ft::vector<int> vec1;
    vec1.reserve(100);
  }

  {
    ft::vector<int> vec1;
    vec1.push_back(100);
    vec1.push_back(100);
    vec1.push_back(100);
    vec1.clear();
  }

  {
    ft::vector<int> vec1;
    vec1.insert(vec1.begin(), 100);
  }

  {
    ft::vector<int> vec1;
    vec1.insert(vec1.begin(), 100, 100);
  }

  {
    ft::vector<int> vec1;
    vec1.push_back(100);
    vec1.push_back(100);
    vec1.push_back(100);
    vec1.erase(vec1.begin());
  }

  {
    ft::vector<int> vec1;
    vec1.push_back(100);
    vec1.push_back(100);
    vec1.push_back(100);
    vec1.erase(vec1.begin(), vec1.end());
  }

  {
    ft::vector<int> vec1;
    vec1.push_back(100);
    vec1.pop_back();
  }

  {
    ft::vector<int> vec1;
    vec1.push_back(100);
    vec1.resize(100);
  }

  {
    ft::vector<int> vec1;
    vec1.push_back(100);
    vec1.resize(100, 100);
  }

  {
    ft::vector<int> vec1;
    vec1.push_back(100);
    vec1.push_back(100);
    vec1.push_back(100);
    vec1.push_back(100);
    ft::vector<int> vec2;
    vec1.push_back(200);
    vec1.push_back(200);
    vec1.push_back(200);
    vec1.push_back(200);

    vec1.swap(vec2);
  }
}
