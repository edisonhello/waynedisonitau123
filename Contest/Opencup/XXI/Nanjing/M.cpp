#include <bits/stdc++.h>
using namespace std;

void Solve() {
  int N;
  cin >> N;
  vector<vector<int>> g(N);
  for (int i = 1; i < N; ++i) {
    int p;
    cin >> p;
    g[p - 1].push_back(i);
  }
  vector<int> hp(N);
  for (int i = 0; i < N; ++i) cin >> hp[i];
  vector<vector<vector<int64_t>>> dp(N);
  vector<int> sz(N);

  constexpr int64_t kInf = 1'000'000'000'000'000'000;

  auto Dfs = [&](auto dfs, int x) -> void {
    sz[x] = 0;
    vector<vector<int64_t>> buffer(sz[x] + 1, vector<int64_t>(2));
    buffer[0][0] = 0;
    buffer[0][1] = kInf;
    int64_t sum = 0;
    for (int u : g[x]) {
      dfs(dfs, u);
      sum += hp[u];
      vector<vector<int64_t>> nbuffer(sz[x] + sz[u] + 1, vector<int64_t>(2, kInf));
      for (int i = 0; i <= sz[u]; ++i) {
        for (int j = 0; j <= sz[x]; ++j) {
          for (int k = 0; k < 2; ++k) {
            for (int l = 0; l < 2; ++l) {
              int64_t v = dp[u][i][k] - (k ? hp[u] : 0);
              nbuffer[i + j][k || l] = min(nbuffer[i + j][k || l], v + buffer[j][l]);
            }
          }
        }
      }
      sz[x] += sz[u];
      buffer = nbuffer;
    }
    sz[x]++;
    dp[x].resize(sz[x] + 1, vector<int64_t>(2, kInf));
    for (int m = 0; m <= sz[x]; ++m) {
      if (m < buffer.size()) dp[x][m][0] = min(buffer[m][0], buffer[m][1]) + hp[x] + sum;
      if (m > 0) dp[x][m][1] = buffer[m - 1][0];
    }
    for (int m = 0; m <= sz[x]; ++m) dp[x][m][0] = min(dp[x][m][0], dp[x][m][1]);
  };

  Dfs(Dfs, 0);
  for (int i = 0; i <= N; ++i) cout << min(dp[0][i][0], dp[0][i][1]) << " ";
  cout << "\n";
}

int main() {
  int T;
  cin >> T;
  while (T--) Solve();
}
