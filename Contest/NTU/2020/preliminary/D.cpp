#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  vector<int> sz(n), mx(n);
  vector<int> tour;
  vector<bool> vis(n);
  vector<vector<int64_t>> dist(n);
  vector<int> dep(n);
  vector<int> fa(n);

  auto DfsSz = [&](auto dfs, int x) -> void {
    vis[x] = true;
    sz[x] = 1;
    mx[x] = 0;
    tour.push_back(x);
    for (auto [u, w] : g[x]) {
      if (vis[u]) continue;
      dfs(dfs, u);
      sz[x] += sz[u];
      mx[x] = max(mx[x], sz[u]);
    }
  };

  auto DfsDist = [&](auto dfs, int x, int64_t s = 0) -> void {
    dist[x].push_back(s);
    vis[x] = true;
    for (auto [u, w] : g[x]) {
      if (vis[u]) continue;
      dfs(dfs, u, s + w);
    }
  };

  auto Dfs = [&](auto dfs, int x, int d = 0, int p = -1) -> void {
    tour.clear();
    DfsSz(DfsSz, x);
    int m = tour.size();
    int cent = -1;
    for (int u : tour) {
      if (max(m - sz[u], mx[u]) * 2 <= m) cent = u;
      vis[u] = false;
    }
    assert(cent != -1);
    DfsDist(DfsDist, cent);
    for (int u : tour) {
      vis[u] = false;
    }
    fa[cent] = p;
    dep[cent] = d;
    vis[cent] = true;
    for (auto [u, w] : g[cent]) {
      if (vis[u]) continue;
      dfs(dfs, u, d + 1, cent);
    }
  };

  Dfs(Dfs, 0);
  vector<vector<int64_t>> sub(n);
  vector<vector<int64_t>> sub2(n);
  vector<vector<int>> fw(n);
  vector<vector<int>> fw2(n);
  for (int i = 0; i < n; ++i) {
    int z = -1;
    for (int j = dep[i], x = i; j >= 0; x = fa[x], --j) {
      assert(j < dist[i].size());
      sub[x].push_back(dist[i][j]);
      if (z != -1) {
        sub2[z].push_back(dist[i][j]);
      }
      z = x;
    }
  }
  for (int i = 0; i < n; ++i) {
    sort(sub[i].begin(), sub[i].end());
    sort(sub2[i].begin(), sub2[i].end());
    sub[i].resize(unique(sub[i].begin(), sub[i].end()) - sub[i].begin());
    sub2[i].resize(unique(sub2[i].begin(), sub2[i].end()) - sub2[i].begin());
    fw[i].resize(sub[i].size() + 1);
    fw2[i].resize(sub2[i].size() + 1);
  }
  vector<bool> marked(n);

  auto Update = [&](auto &fw, int p, int v) {
    for (int i = p + 1; i < fw.size(); i += i & -i)
      fw[i] += v;
  };

  auto Query = [&](const auto &fw, int p) {
    int res = 0;
    for (int i = p + 1; i > 0; i -= i & -i)
      res += fw[i];
    return res;
  };

  auto Mark = [&](int x) {
    if (marked[x]) return;
    int z = -1;
    for (int i = dep[x], y = x; i >= 0; --i, y = fa[y]) {
      int b = lower_bound(sub[y].begin(), sub[y].end(), dist[x][i]) - sub[y].begin();
      Update(fw[y], b, 1);
      if (z != -1) {
        b = lower_bound(sub2[z].begin(), sub2[z].end(), dist[x][i]) - sub2[z].begin();
        Update(fw2[z], b, 1);
      }
      z = y;
    }
    marked[x] = true;
  };

  auto UnMark = [&](int x) {
    if (!marked[x]) return;
    int z = -1;
    for (int i = dep[x], y = x; i >= 0; --i, y = fa[y]) {
      int b = lower_bound(sub[y].begin(), sub[y].end(), dist[x][i]) - sub[y].begin();
      Update(fw[y], b, -1);
      if (z != -1) {
        b = lower_bound(sub2[z].begin(), sub2[z].end(), dist[x][i]) - sub2[z].begin();
        Update(fw2[z], b, -1);
      }
      z = y;
    }
    marked[x] = false;
  };

  auto Count = [&](int x, int64_t d) {
    int res = 0;
    int z = -1;
    for (int i = dep[x], y = x; i >= 0; --i, y = fa[y]) {
      int64_t v = d - dist[x][i];
      if (v >= 0) {
        int b = upper_bound(sub[y].begin(), sub[y].end(), v) - sub[y].begin() - 1;
        res += Query(fw[y], b);
        if (z != -1) {
          b = upper_bound(sub2[z].begin(), sub2[z].end(), v) - sub2[z].begin() - 1;
          res -= Query(fw2[z], b);
        }
      }
      z = y;
    }
    return res;
  };

  for (int i = 0; i < m; ++i) {
    int t;
    cin >> t;
    if (t == 1) {
      int x;
      cin >> x;
      x--;
      Mark(x);
    }
    if (t == 2) {
      int x;
      cin >> x;
      x--;
      UnMark(x);
    }
    if (t == 3) {
      int x, k;
      cin >> x >> k;
      x--;
      int64_t res = 1'000'000'000'000'000;
      for (int bit = 50; bit >= 0; --bit) {
        if (res - (1LL << bit) < 0) continue;
        int v = Count(x, res - (1LL << bit));
        if (v >= k) res -= (1LL << bit);
      }
      cout << res << "\n";
    }
  }
}
