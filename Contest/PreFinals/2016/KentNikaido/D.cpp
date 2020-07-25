#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<int> deg(n);
  vector<pair<int, int>> ed;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    deg[u]++;
    deg[v]++;
    ed.emplace_back(u, v);
  }
  vector<int> pw(m + 1, 1);
  constexpr int kMod = 1'000'000'000 + 7;
  int res = 0;
  for (int i = 1; i <= m; ++i) {
    pw[i] = (pw[i - 1] + pw[i - 1]) % kMod;
    (res += pw[i]) >= kMod ? res -= kMod : 0;
  }
  vector<int> uf(n);
  for (int i = 0; i < n; ++i) {
    uf[i] = i;
  }

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < m; ++i) {
    int x = Find(ed[i].first);
    int y = Find(ed[i].second);
    if (x == y) continue;
    uf[x] = y;
    g[ed[i].first].emplace_back(ed[i].second, i);
    g[ed[i].second].emplace_back(ed[i].first, i);
  }

  vector<int> sz(n);
  auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
    sz[x] = (deg[x] % 2 == 1);
    for (auto e : g[x]) {
      int u = e.first;
      if (u == p) continue;
      dfs(dfs, u, x);
      sz[x] += sz[u];
      int w = e.second;
      if (sz[u] % 2 == 1) {
        (res += pw[w + 1]) >= kMod ? res -= kMod : 0;
      }
    }
  };

  Dfs(Dfs, 0);
  cout << res << "\n";
}
