#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> v = {1,2,3,4,5};
  int counter = 0;
  do { 
    ++counter; 
    // cerr << "count ";
    // for (int i : v) cerr << i << ' ';
    // cerr << endl;
  } while (next_permutation(v.begin(), v.end()));
  cerr << "counter = " << counter << endl;

  int n = v.size(), l = n - 2;
  set<vector<int>> st; st.insert(v);

  while (true) {
    int sz = st.size();
    vector<vector<int>> news;
    for (auto v : st) {
      auto vv = v;

      for (int i = 0; i < n - l + 1; ++i) {
        v = vv;
        int o = v[i];
        for (int j = 0; j < l - 1; ++j) v[i + j] = v[i + j + 1];
        v[i + l - 1] = o;
        if (!st.count(v)) {
          news.push_back(v);
          // for (int i : vv) cerr << i << ' ';
          // cerr << " to ";
          // for (int i : v) cerr << i << ' ';
          // cerr << endl;
        }
      }
    }
    for (auto &v : news) st.insert(v);
    if (sz == (int)st.size()) break;
  }

  // cerr << "in set " << endl;
  // for (auto &v : st) {
  //   for (int i : v) cerr << i << ' ';
  //   cerr << endl;
  // }

  cerr << "can do: " << st.size() << endl;

  assert(counter == (int)st.size());
}
