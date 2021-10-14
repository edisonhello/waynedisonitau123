#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M, T;
  cin >> N >> M >> T;
  vector<int> A(N);
  for (int i = 1; i < N; ++i) cin >> A[i];
  vector<vector<int>> g(N);
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vector<int> que(1, 0);
  vector<int> dist(N, -1);
  dist[0] = 0;
  for (int it = 0; it < que.size(); ++it) {
    int x = que[it];
    for (int u : g[x]) {
      if (dist[u] == -1) {
        dist[u] = dist[x] + 1;
        que.push_back(u);
      }
    }
  }
  vector<int> dp(T + 1, 0);
  for (int i = 1; i <= T; ++i) {
    for (int j = 1; j < N; ++j) {
      if (dist[j] != -1 && i >= 2 * dist[j]) {
        dp[i] = max(dp[i], dp[i - 2 * dist[j]] + A[j]);
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= T; ++i) {
    ans = max(ans, dp[i]);
    cout << ans << " ";
  }
  cout << "\n";
}
