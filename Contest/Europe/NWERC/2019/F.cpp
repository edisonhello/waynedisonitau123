#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  map<int, vector<int>> p;
  for (int i = 0; i < n; ++i) {
    int m;
    cin >> m;
    for (int j = 0; j < m; ++j) {
      int d;
      cin >> d;
      p[d].push_back(i);
    }
  }
  vector<int> uf(n);
  iota(uf.begin(), uf.end(), 0);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  vector<tuple<int, int, int>> res;
  for (auto &it : p) {
    vector<int> &v = it.second;
    for (int i = 1; i < v.size(); ++i) {
      int x = Find(v[i - 1]), y = Find(v[i]);
      if (x != y) {
        uf[x] = y;
        res.emplace_back(v[i - 1], v[i], it.first);
      }
    }
  }
  bool ok = true;
  for (int i = 1; i < n; ++i) {
    ok &= Find(i) == Find(0);
  }
  if (!ok) {
    cout << "impossible\n";
  } else {
    assert(res.size() == n - 1);
    for (auto [a, b, c] : res) {
      cout << a + 1 << " " << b + 1 << " " << c << "\n";
    }
  }
}
