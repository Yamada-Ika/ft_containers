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

  {
    ft::deque<int> deq;
    deq.push_back(1);
  }

  {
    ft::deque<int> deq1;
    deq1.push_front(1);
    ft::deque<int> deq2(deq1);
  }

  {
    ft::deque<int> deq1;
    deq1.push_front(1);
    ft::deque<int> deq2 = deq1;
  }

  {
    ft::deque<int> deq1;
    deq1.push_front(1);
    ft::deque<int> deq2;
    deq2 = deq1;
  }

  {
    ft::deque<int> deq;
    deq.push_back(1);

    deq.at(0);
  }

  {
    ft::deque<int> deq;
    deq.push_back(1);

    deq.at(0) = 100;
  }

  {
    ft::deque<int> deq;
    deq.push_back(1);

    deq[0];
  }

  {
    ft::deque<int> deq;
    deq.push_back(1);

    deq[0] = 100;
  }

  {
    ft::deque<int> deq;
    deq.push_back(1);

    deq.front();
  }

  {
    ft::deque<int> deq;
    deq.push_back(1);

    deq.back();
  }

  {
    ft::deque<int> deq;
    deq.push_back(1);

    deq.clear();
  }

  {
    ft::deque<int> deq;
    deq.push_back(1);
    deq.push_front(1);
    deq.push_back(1);
    deq.push_front(1);
    deq.push_back(1);
    deq.push_front(1);
    deq.push_back(1);
    deq.push_front(1);
    deq.push_back(1);
    deq.push_front(1);

    deq.clear();
  }

  {
    ft::deque<int> deq;
    deq.insert(deq.begin(), 1);
  }

  {
    ft::deque<int> deq;
    deq.insert(deq.begin(), 100, 1);
  }

    {
    ft::deque<int> deq;
    deq.insert(deq.begin(), 100000, 1);
  }
}