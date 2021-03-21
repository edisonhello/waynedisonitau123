#include <bits/stdc++.h>
using namespace std;

void Solve() {
  int N;
  cin >> N;
  vector<vector<int>> D(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cin >> D[i][j];
  }

  if (N == 2) {
    cout << "NO" << '\n';
    return;
  }

  vector<vector<int>> g(N), r(N);
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      assert(D[i][j] == 0 || D[j][i] == 0);
      if (D[i][j] == 0) {
        g[i].push_back(j);
        r[j].push_back(i);
      } else {
        r[i].push_back(j);
        g[j].push_back(i);
      }
    } 
  }
  vector<bool> visited(N);
  vector<int> order;

  auto Dfs = [&](auto dfs, int x) -> void {
    visited[x] = true;
    for (int u : g[x]) {
      if (visited[u]) continue;
      dfs(dfs, u);
    }
    order.push_back(x);
  };

  for (int i = 0; i < N; ++i) {
    if (!visited[i]) Dfs(Dfs, i);
  }
  reverse(order.begin(), order.end());
  vector<int> scc(N, -1);
  int S = 0;

  auto RevDfs = [&](auto dfs, int x, int p) -> void {
    scc[x] = p;
    for (int u : r[x]) {
      if (scc[u] != -1) continue;
      dfs(dfs, u, p);
    }
  };

  for (int u : order) {
    if (scc[u] != -1) continue;
    RevDfs(RevDfs, u, S++);
  }

  vector<vector<tuple<int, int, int, int>>> dg(S);
  for (int i = 0; i < N; ++i) {
    for (int u : g[i]) {
      if (scc[i] == scc[u]) continue;
      assert(scc[i] < scc[u]);
      dg[scc[i]].emplace_back(scc[u], 0, -1, -1);
      dg[scc[u]].emplace_back(scc[i], max(D[i][u], D[u][i]), i, u);
    }
  }
  priority_queue<pair<int64_t, int>> pq;
  constexpr int64_t kInf = 1'000'000'000'000'000'000;
  vector<int64_t> dist(N, kInf);
  dist[S - 1] = 0;
  pq.emplace(0, S - 1);
  vector<bool> vis(N);
  vector<int> from(N, -1);
  while (!pq.empty()) {
    auto [d, x] = pq.top();
    pq.pop();
    if (vis[x]) continue;
    vis[x] = true;
    for (auto [y, w, a, b] : dg[x]) {
      if (dist[y] > dist[x] + w) {
        dist[y] = dist[x] + w;
        from[y] = x;
        pq.emplace(-dist[y], y);
      }
    }
  }
  cout << "YES\n";
  int x = 0;
  vector<pair<int, int>> res;
  while (x != S - 1) {
    int y = from[x];
    if (y > x) {
      int W = 2'000'000'000 + 1;
      int A = -1, B = -1;
      for (auto [t, w, a, b] : dg[y]) {
        if (t == x && w < W) {
          W = w;
          A = a;
          B = b;
        }
      }
      res.emplace_back(A, B);
    }
    x = y;
  }
  cout << res.size() << " " << dist[0] << "\n";
  for (auto [a, b] : res) {
    if (D[a][b] == 0) swap(a, b);
    cout << a + 1 << " " << b + 1 << "\n";
  }
}

int main() {
  int T;
  cin >> T;
  while (T--) Solve();
}
