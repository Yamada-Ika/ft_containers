#include <iostream>
#include <set>

using namespace std;
int main(void) {
  // Your code here!
  set<int> st;
  st.insert(1);
  st.insert(2);
  st.insert(3);
  st.insert(4);
  auto itr = st.begin();
  st.erase(itr, ++itr);
  cout << "size " << st.size() << endl;
  for (auto e : st) {
    cout << e << endl;
  }
}
