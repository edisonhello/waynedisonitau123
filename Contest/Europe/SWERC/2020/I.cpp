#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M;
  cin >> N >> M;
  vector<vector<int>> g(N);
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vector<int> dist(N, -1);
  vector<int> que;
  int D = 0;
  constexpr int kM = 2;
  int x = 0;
  for (int it = 0; it < kM; ++it) {
    fill(dist.begin(), dist.end(), -1);
    dist[x] = 0;
    que.clear();
    que.push_back(x);
    for (int it = 0; it < que.size(); ++it) {
      int x = que[it];
      for (int u : g[x]) {
        if (dist[u] == -1) {
          dist[u] = dist[x] + 1;
          D = max(D, dist[u]);
          que.push_back(u);
        }
      }
    }
    if (que.size() != N) {
      cout << "-1\n";
      return 0;
    }
    x = max_element(dist.begin(), dist.end()) - dist.begin();
  }
  int ans = 0;
  while ((1 << ans) < D) ans++;
  cout << ans << "\n";
}
