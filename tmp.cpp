#include "map.hpp"
#include "set.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "deque.hpp"
#include "tree.hpp"
#include "utils.hpp"

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

  {
    ft::stack<int> st;
    st.push(1);
  }

  {
    ft::stack<int> st1;
    st1.push(1);
    ft::stack<int> st2(st1);
  }

  {
    ft::stack<int> st1;
    st1.push(1);
    ft::stack<int> st2 = st1;
  }

  {
    ft::stack<int> st1;
    st1.push(1);
    ft::stack<int> st2;
    st2 = st1;
  }

  {
    ft::stack<int> st;
    st.pop();
  }

  { ft::__tree<int, int, ft::Identity<int> > t; }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);
    t.__insert(5);
    t.__insert(6);
    t.__insert(7);
    t.__insert(8);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(-1);
    t.__insert(2);
    t.__insert(-2);
    t.__insert(3);
    t.__insert(-3);
    t.__insert(4);
    t.__insert(-4);
    t.__insert(5);
    t.__insert(-5);
    t.__insert(6);
    t.__insert(-6);
    t.__insert(7);
    t.__insert(-7);
  }

  {
    //            1
    //      +-----+-----+
    //     -1           2
    //  +---+---+   +---+---+
    // nil     nil nil     nil
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(-100);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(100);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(100);
    t.__insert(10);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(100);
    t.__insert(1000);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(100);
    t.__insert(1000);
    t.__insert(-100);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(100);
    t.__insert(1000);
    t.__insert(-100);
    t.__insert(-1000);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(100);
    t.__insert(1000);
    t.__insert(-100);
    t.__insert(-1000);
    t.__insert(-10000);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(100);
    t.__insert(10000);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(100);
    t.__insert(10000);
    t.__insert(100000);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(1);
    t.__insert(10000);
  }

  {
    //            100
    //       +-----+-----+
    //       1         10000
    //   +---+---+
    //           10
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(1);
    t.__insert(10000);
    t.__insert(10);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);
    t.__insert(5);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(3);
    t.__insert(4);
    t.__insert(5);
    t.__erase(5);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(1);
    t.__insert(10000);
    t.__insert(10);
    t.__insert(1000);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(1);
    t.__insert(10000);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(5);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__erase(100);
    t.__erase(10);
    t.__erase(1000);
    t.__erase(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(1);
    t.__insert(10000);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(5);
    t.__insert(500);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__insert(-100);
    t.__insert(100);
    t.__insert(-10);
    t.__insert(10);
    t.__insert(-50);
    t.__insert(50);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__erase(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__erase(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__erase(2);
  }

  {
    //            1
    //      +-----+-----+
    //     -1           2
    //  +---+---+   +---+---+
    // nil     nil nil     nil
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__erase(-1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__erase(2);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(1);
    t.__insert(2);
    t.__insert(-1);
    t.__erase(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__erase(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__erase(100);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__erase(10);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__erase(1000);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__insert(5);
    t.__insert(500);
    t.__erase(1000);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__insert(5);
    t.__insert(500);
    t.__insert(50);
    t.__erase(1000);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__insert(5);
    t.__insert(500);
    t.__insert(250);
    t.__erase(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__insert(5);
    t.__insert(500);
    t.__insert(250);
    t.__insert(750);
    t.__erase(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__insert(5);
    t.__insert(500);
    t.__insert(250);
    t.__insert(750);
    t.__insert(600);
    t.__erase(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__insert(5);
    t.__insert(500);
    t.__insert(250);
    t.__insert(750);
    t.__insert(600);
    t.__insert(50);
    t.__erase(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t;
    t.__insert(100);
    t.__insert(10);
    t.__insert(1000);
    t.__insert(1);
    t.__insert(5);
    t.__insert(500);
    t.__insert(250);
    t.__insert(750);
    t.__insert(600);
    t.__insert(50);
    t.__insert(2);
    t.__erase(1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr = t1.__begin();
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);

    ft::__tree<int, int, ft::Identity<int> >::iterator itr1 = t1.__begin();
    ft::__tree<int, int, ft::Identity<int> >::iterator itr2 = t1.__begin();

    if (itr1 == itr2) {
    }
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);

    ft::__tree<int, int, ft::Identity<int> >::__const_iterator itr1 =
        t1.__begin();
    ft::__tree<int, int, ft::Identity<int> >::__const_iterator itr2 =
        t1.__begin();

    if (itr1 == itr2) {
    }
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);

    ft::__tree<int, int, ft::Identity<int> > t2;
    t2.__insert(1);

    if (t1 == t2) {
    }
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);

    ft::__tree<int, int, ft::Identity<int> > t2;
    t2.__insert(1);

    if (t1 < t2) {
    }
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    ft::__tree<int, int, ft::Identity<int> > t2;
    t2 = t1;
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    ft::__tree<int, int, ft::Identity<int> > t2(t1);
  }

  {
    ft::__tree<int, int, ft::Identity<int> > t1;
    t1.__insert(1);
    ft::__tree<int, int, ft::Identity<int> > t2 = t1;
  }

  { ft::set<int> st; }

  {
    ft::set<int> st;
    st.insert(1);
  }

  {
    ft::set<int> st;
    st.insert(1);
    st.clear();
  }
}
