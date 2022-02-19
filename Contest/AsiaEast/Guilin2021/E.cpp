#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M, c;
  cin >> N >> M >> c;
  vector<vector<pair<int, int>>> g(N);
  vector<vector<pair<int, int>>> r(N);
  bool zero = true;
  for (int i = 0; i < M; ++i) {
    int u, v, p;
    cin >> u >> v >> p;
    u--;
    v--;
    g[u].emplace_back(v, p);
    r[v].emplace_back(u, p);
    if (p <= c) {
      zero = false;
    }
  }
  if (zero) {
    cout << "0\n";
    return 0;
  }
  constexpr int kInf = 1'000'000'000;
  vector<int> dist(N, kInf);
  vector<bool> vis(N);
  for (int i = 0; i < N; ++i) {
    fill(dist.begin(), dist.end(), kInf);
    fill(vis.begin(), vis.end(), false);
    dist[i] = 0;
    priority_queue<pair<int, int>> pq;
    pq.emplace(0, i);
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
    for (auto [u, w] : r[i]) {
      if (w + dist[u] <= c) {
        cout << "2\n";
        return 0;
      }
    }
  }
  cout << "1\n";
  return 0;
}

