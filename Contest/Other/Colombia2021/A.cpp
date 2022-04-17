#include <bits/stdc++.h>
using namespace std;


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M, Q;
  cin >> N >> M >> Q;
  vector<vector<pair<int, int>>> rev(N);
  vector<vector<pair<int, int>>> g(N);
  vector<vector<vector<int>>> dp(N, vector<vector<int>>(N));
  vector<vector<int>> offset(N, vector<int>(N, -1));
  for (int i = 0; i < M; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    g[u].emplace_back(v, w);
    rev[v].emplace_back(u, w);
  }
  constexpr int64_t kInf = 2'000'000'000;
  for (int s = 0; s < N; ++s) {
    offset[s][s] = 0;
    dp[s][s] = {0};
    for (int d = 2; d <= N; ++d) {
      for (int i = 0; i < N; ++i) {
        int t = kInf;
        for (auto [u, w] : rev[i]) {
          if (offset[s][u] == -1 || d - 1 < offset[s][u]) {
            continue;
          }
          t = min(t, dp[s][u][d - 1 - offset[s][u]] + w);
        }
        if (t != kInf) {
          if (offset[s][i] == -1) {
            offset[s][i] = d;
          }
        }
        if (offset[s][i] != -1) {
          dp[s][i].push_back(t);
        }
      }
    }
  }
  while (Q--) {
    int u, v, x;
    cin >> u >> v >> x;
    u--;
    v--;
    if (u == v) {
      cout << x << "\n";
    } else {
      int ans = kInf;
      for (int d = 0; d <= N; ++d) {
        if (dp[u][v][d]) {
          ans = min(ans, dp[u][v][d] + (d + 1) * x);
        }
      }
      if (ans == kInf) ans = -1;
      cout << ans << "\n";
    }
  }
}
