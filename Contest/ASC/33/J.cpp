#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("subtrees.in", "r", stdin);
  freopen("subtrees.out", "w", stdout);
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  vector<vector<vector<int>>> dp(n, vector<vector<int>>(n + 1, vector<int>(2)));
  vector<int> sz(n);

  constexpr int kMod = 1'000'000'000;

  auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
    sz[x] = 1;
    dp[x][0][0] = 1;
    for (int u : g[x]) {
      if (u == p) continue;
      dfs(dfs, u, x);
      vector<vector<int>> buf(sz[u] + sz[x], vector<int>(2));
      for (int i = 0; i <= sz[u]; ++i) {
        for (int j = 0; j < 2; ++j) {
          for (int k = 0; k < sz[x]; ++k) {
            for (int p = 0; p < 2; ++p) {
              buf[i + k][j || p] += 1LL * dp[u][i][j] * dp[x][k][p] % kMod;
              buf[i + k][j || p] %= kMod;
            }
          }
        }
      }
      sz[x] += sz[u];
      for (int i = 0; i < sz[x]; ++i) {
        for (int j = 0; j < 2; ++j) {
          dp[x][i][j] = buf[i][j];
        }
      }
    }
    vector<vector<int>> ndp(n + 1, vector<int>(2));
    for (int i = 0; i < sz[x]; ++i) {
      (ndp[i][1] += dp[x][i][1]) %= kMod;
      (ndp[i + 1][0] += dp[x][i][1]) %= kMod;
      (ndp[i][0] += dp[x][i][0]) %= kMod;
      (ndp[i + 1][0] += dp[x][i][0]) %= kMod;
      (ndp[i][1] += dp[x][i][0]) %= kMod;
    }
    dp[x] = ndp;
  };

  Dfs(Dfs, 0);
  for (int k = 1; k <= n; ++k) {
    cout << dp[0][k][0] << "\n";
  }
}
