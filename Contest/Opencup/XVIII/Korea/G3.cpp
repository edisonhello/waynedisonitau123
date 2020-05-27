#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> x(m), y(m), w(m);
  vector<vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    cin >> x[i] >> y[i] >> w[i];
    x[i]--;
    y[i]--;
    g[x[i]].push_back(i);
    g[y[i]].push_back(i);
  }
  vector<int> ord(m);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int i, int j) { return w[i] < w[j]; });

  vector<int> uf(n);
  iota(uf.begin(), uf.end(), 0);

  vector<set<int>> st(n);

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  vector<int64_t> sum(n);

  auto Merge = [&](int x, int y, int w) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (st[x].size() > st[y].size()) swap(x, y);
    uf[x] = y;
    for (int u : st[x]) {
      if (st[y].count(u)) {
        sum[u] += w;
      }
      st[y].insert(u);
    }
  };

  vector<bool> choose(m);

  int64_t mst = 0;
  for (int i = 0; i < m; ++i) {
    if (Find(x[ord[i]]) != Find(y[ord[i]])) {
      choose[ord[i]] = true;
      mst += w[ord[i]];
      Merge(x[ord[i]], y[ord[i]], w[ord[i]]);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int e : g[i]) {
      int u = x[e] ^ y[e] ^ i;
      st[u].insert(i);
    }
    st[i].insert(i);
  }

  iota(uf.begin(), uf.end(), 0);
  for (int i = 0; i < m; ++i) {
    if (Find(x[ord[i]]) != Find(y[ord[i]])) {
      Merge(x[ord[i]], y[ord[i]], w[ord[i]]);
    }
  }
  for (int i = 0; i < n; ++i) {
    int64_t res = mst - sum[i];
    for (int e : g[i]) {
      res += w[e];
    }
    cout << res << "\n";
  }
}
