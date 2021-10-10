#include <bits/stdc++.h>
using namespace std;

set<vector<int>> shape;

void dfs(vector<int> v, const vector<int> &mo, vector<int>::iterator it) {
  shape.insert(v);
  if (it == mo.end()) return;

  int n = v.size();
  for (int l = 0; l <= *it; ++l) {
    for (int r = max(*it, l); r < n; ++r) {
      int mn = INT_MAX;
      for (int i = l; i <= r; ++i) mn = min(mn, v[i]);
      if (mn == v[*it]) {
        auto vv = v;
        for (int i = l; i <= r; ++i) vv[i] = v[*it];
        dfs(vv, mo, next(it));
      }
    }
  }
}

int main() {
  int n; cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];

  vector<int> mo(n);
  iota(mo.begin(), mo.end(), 0);
  do {
    auto vv = v;
    dfs(vv, mo, mo.begin());
  } while (next_permutation(mo.begin(), mo.end()));

  cout << shape.size() << endl;
  for (auto &v : shape) {
    for (int i : v) cerr << i << ' ';
    cerr << endl;
  }
}
