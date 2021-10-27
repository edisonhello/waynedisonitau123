#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<vector<pair<int, int>>> g(N);
  for (int i = 0; i < N - 1; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  vector<int> up(N), down(N);

  auto Dfs = [&](auto dfs, int x, int p = -1, int f = -1) -> int64_t {
    int64_t res = 0;
    vector<pair<int, int>> ups, downs;
    up[x] = down[x] = 1;
    for (auto [u, w] : g[x]) {
      if (u == p) continue;
      res += dfs(dfs, u, x, w);
      ups.emplace_back(w, up[u]);
      downs.emplace_back(w, down[u]);
      res += up[u];
      res += down[u];
      if (f != -1) {
        if (f > w) up[x] += up[u];
        if (f < w) down[x] += down[u];
      }
    }
    sort(downs.begin(), downs.end());
    sort(ups.begin(), ups.end());
    int64_t s = 0;
    for (int i = 0, j = 0; i < downs.size(); ++i) {
      while (j < ups.size() && ups[j].first < downs[i].first) {
        s += ups[j].second;
        j++;
      }
      res += s * downs[i].second;
    }
    return res;
  };

  cout << Dfs(Dfs, 0) << "\n";
}
