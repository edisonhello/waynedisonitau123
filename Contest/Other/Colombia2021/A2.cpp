#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<vector<pair<int, int>>> g(N);
  for (int i = 0; i < M; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    g[u].emplace_back(v, w);
  }
  constexpr int kInf = 2'000'000'000;
  vector<int> dist(N, kInf);
  vector<bool> vis(N);
  while (Q--) {
    int s, t, x;
    cin >> s >> t >> x;
    s--;
    t--;
    fill(dist.begin(), dist.end(), kInf);
    fill(vis.begin(), vis.end(), false);
    dist[s] = x;
    priority_queue<pair<int, int>> pq;
    pq.emplace(0, s);
    while (!pq.empty()) {
      int y = pq.top().second;
      pq.pop();
      if (vis[y]) {
        continue;
      }
      vis[y] = true;
      for (auto [u, w] : g[y]) {
        if (dist[y] + w + x < dist[u]) {
          dist[u] = dist[y] + w + x;
          pq.emplace(-dist[u], u);
        }
      }
    }
    int ans = dist[t];
    if (ans == kInf) {
      ans = -1;
    }
    cout << ans << "\n";
  }
}
