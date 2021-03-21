#include <bits/stdc++.h>
using namespace std;

int Solve() {
  int N;
  cin >> N;
  vector<vector<int>> g(N);
  vector<int> deg(N);
  for (int i = 0; i < N; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
    deg[u]++;
    deg[v]++;
  }
  vector<int> que;
  for (int i = 0; i < N; ++i) {
    if (deg[i] == 1) que.push_back(i);
  }
  for (int it = 0; it < que.size(); ++it) {
    int x = que[it];
    for (int u : g[x]) {
      if (--deg[u] == 1) que.push_back(u);
    }
  }
  vector<bool> on_cycle(N, true);
  for (int u : que) on_cycle[u] = false;
  vector<int> cycle;
  for (int i = 0; i < N; ++i) {
    if (on_cycle[i]) cycle.push_back(i);
  }

  int ans = 0, sum = 0;
  bool has_special = false;
  vector<pair<int, bool>> vec;

  vector<int> order;
  vector<bool> visited(N);

  auto DfsCycle = [&](auto dfs, int x) -> void {
    order.push_back(x);
    visited[x] = true;
    for (int u : g[x]) {
      if (visited[u]) continue;
      if (!on_cycle[u]) continue;
      dfs(dfs, u);
    }
  };

  DfsCycle(DfsCycle, cycle[0]);

  for (int u : order) {
    int leaf = 0;
    bool special = false;

    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
      int child = 0;
      for (int u : g[x]) {
        if (u == p || on_cycle[u]) continue;
        dfs(dfs, u, x);
        child++;
      }
      leaf += (child == 0);
      special = (x == u && child == 0);
    };

    Dfs(Dfs, u);
    vec.emplace_back(leaf, special);
    if (!special) sum += leaf;
    has_special |= special;
  }

  ans = sum + has_special;
  int M = order.size();
  for (int i = 0; i < M; ++i) {
    int v = sum;
    if (!vec[i].second) v -= vec[i].first;
    if (!vec[(i + 1) % M].second) v -= vec[(i + 1) % M].first;
    ans = max(ans, v + 2);
  }

  return max(ans, 3);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) cout << Solve() << "\n";
}
