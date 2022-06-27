#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int I, S, L, U;
  cin >> I >> S >> L >> U;
  vector<int> from(S), to(S);
  vector<vector<pair<int, int>>> g(I);
  for (int i = 0; i < S; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    from[i] = u;
    to[i] = v;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  vector<int> dist(I, U + 100);
  vector<bool> vis(I);
  dist[0] = 0;
  priority_queue<pair<int, int>> pq;
  pq.emplace(0, 0);
  while (!pq.empty()) {
    int x = pq.top().second;
    pq.pop();
    if (vis[x]) {
      continue;
    }
    vis[x] = true;
    for (auto [u, w] : g[x]) {
      if (dist[u] > dist[x] + w) {
        dist[u] = dist[x] + w;
        pq.emplace(-dist[u], u);
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < S; ++i) {
    int k = min(dist[from[i]], dist[to[i]]);
    if (k * 2 < U) {
      ans++;
    }
  }
  cout << ans << "\n";
}
