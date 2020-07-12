#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m; cin >> n >> m;
  map<pair<int, int>, int> e;
  vector<int> g(n + 1);
  for (int i = 1; i < n; ++i) {
    int u, v, w; cin >> u >> v >> w;
    e[minmax(u, v)] = w;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto Calc = [&] () {
    vector<vector<long long>> ee(n + 1, vector<long long>(n + 1, 1000000000000000000));
    for (auto &p : e) ee[p.first.first][p.first.second] = ee[p.first.second][p.first.first] = p.second;
    for (int i = 1; i <= n; ++i) ee[i][i] = 0;
    for (int k = 1; k <= n; ++k) for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j)
      ee[i][j] = min(ee[i][j], ee[i][k] + ee[k][j]);
    long long t = 0;
    for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) t += ee[i][j];
    return t;
  };

  cout << Calc() << '\n';

  while (m--) {
    auto Dfs = [&] (auto self, int now, int pa, int to) -> bool {
      if (now == to) return true;
      for (int i : g[now]) if (i != pa) {
        if (self(self, i, now, to)) {
          auto &v = e[minmax(i, now)];
          v = floor(sqrt(v + 0.5));
          return true;
        }
      }
      return false;
    };
    int u, v; cin >> u >> v;
    Dfs(Dfs, u, -1, v);
    cout << Calc() << '\n';
  }
}
