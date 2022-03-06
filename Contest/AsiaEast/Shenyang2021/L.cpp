#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<vector<int>> g(2 * N);
  for (int i = 0; i < 2 * N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  constexpr int kP = 998244353;
  vector<vector<vector<int>>> dp(2 * N,
                                 vector<vector<int>>(N + 2, vector<int>(2)));
  vector<int> sz(2 * N);
  vector<vector<int>> buffer(2 * N + 1, vector<int>(2));

  auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
    sz[x] = 0;
    dp[x][0][0] = 1;
    for (int u : g[x]) {
      if (u == p) {
        continue;
      }
      dfs(dfs, u, x);
      for (int i = 0; i <= (sz[u] + 1) / 2 + (sz[x] + 1) / 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          buffer[i][j] = 0;
        }
      }
      for (int i = 0; i <= (sz[u] + 1) / 2; ++i) {
        for (int j = 0; j <= (sz[x] + 1) / 2; ++j) {
          for (int a = 0; a < 2; ++a) {
            for (int b = 0; b < 2; ++b) {
              if (a + b <= 1) {
                buffer[i + j][a + b] += 1LL * dp[u][i][a] * dp[x][j][b] % kP;
                buffer[i + j][a + b] %= kP;
              }
            }
          }
        }
      }
      vector<vector<int>>().swap(dp[u]);
      for (int i = 0; i <= (sz[x] + 1) / 2 + (sz[u] + 1) / 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          dp[x][i][j] = buffer[i][j];
        }
      }
      sz[x] += sz[u];
    }
    for (int i = (sz[x] + 1) / 2; i >= 0; --i) {
      dp[x][i + 1][1] = dp[x][i][0];
      dp[x][i][0] = (dp[x][i][0] + dp[x][i][1]) % kP;
    }
    sz[x]++;
  };

  Dfs(Dfs, 0);
  vector<int> fc(2 * N + 1, 1);
  for (int i = 2; i <= 2 * N; ++i) {
    fc[i] = 1LL * fc[i - 2] * (i - 1) % kP;
  }
  int ans = fc[2 * N];
  for (int k = 1; k <= N; ++k) {
    int ways = 1LL * dp[0][k][0] * fc[2 * (N - k)] % kP;
    if (k & 1) {
      ans += kP - ways;
    } else {
      ans += ways;
    }
    ans %= kP;
  }
  cout << ans << "\n";
  return 0;
}
