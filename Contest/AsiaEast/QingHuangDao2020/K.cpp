#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 1'000'000;
vector<int> g[kN];
int dp[kN][2];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int N;
    cin >> N;
    for (int i = 1; i < N; ++i) {
      int f;
      cin >> f;
      g[f - 1].push_back(i);
    }

    vector<vector<int>> dp(N, vector<int>(2));

    auto Dfs = [&](auto self, int x, int d = 0) -> void {
      dp[x][0] = 0;
      dp[x][1] = 1'000'000'000;
      for (int u : g[x]) {
        self(self, u, d + 1);
        int nxt[2] = {1'000'000'000, 1'000'000'000};
        for (int i = 0; i < 2; ++i) {
          for (int j = 0; j < 2; ++j) {
            nxt[i | j] = min(nxt[i | j], dp[x][i] + dp[u][j]);
          }
        }
        dp[x][0] = nxt[0];
        dp[x][1] = nxt[1];
      }
      if (g[x].empty()) {
        dp[x][1] = d;
        dp[x][0] = 2;
      } else {
        dp[x][0] += 2;
      }
    };

    Dfs(Dfs, 0);
    cout << "Case #" << tc << ": " << min(dp[0][0], dp[0][1]) << "\n";
    for (int i = 0; i < N; ++i) {
      g[i].clear();
    }
  }
}

