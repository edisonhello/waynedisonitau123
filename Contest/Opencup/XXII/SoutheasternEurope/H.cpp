#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> c(N);
  vector<int> cnt(N);
  for (int i = 0; i < N; ++i) {
    cin >> c[i];
    c[i]--;
    cnt[c[i]]++;
  }

  vector<vector<int>> g(N);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  constexpr int kP = 998244353;

  int ans = 0;

  for (int k = 0; k < N; ++k) {
    if (cnt[k] == 0) {
      continue;
    }

    const int C = cnt[k];

    // cout << "k = " << k << endl;

    vector<vector<int>> dp(N, vector<int>(C * 2 + 1));
    vector<pair<int, int>> range(N);
    vector<int> buffer(C * 2 + 1);

    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
      range[x] = {0, 0};
      dp[x][C] = 1;
      for (int u : g[x]) {
        if (u == p) {
          continue;
        }
        dfs(dfs, u, x);
        int L = max(-C, range[x].first + range[u].first);
        int R = min(C, range[x].second + range[u].second);
        fill(buffer.begin() + L + C, buffer.begin() + R + C + 1, 0);
        for (int i = range[u].first; i <= range[u].second; ++i) {
          for (int j = max(range[x].first, -C - i); j <= range[x].second && i + j <= C; ++j) {
            buffer[i + j + C] += 1LL * dp[u][i + C] * dp[x][j + C] % kP;
            buffer[i + j + C] %= kP;
          }
        }
        copy(buffer.begin() + L + C, buffer.begin() + R + C + 1, dp[x].begin() + L + C);
        range[x] = {L, R};
      }

      if (c[x] == k) {
        for (int i = C - 1; i >= -C; --i) {
          dp[x][i + 1 + C] = dp[x][i + C];
        }
        dp[x][0] = 0;
        range[x].first = clamp(range[x].first + 1, -C, C);
        range[x].second = clamp(range[x].second + 1, -C, C);
      } else {
        for (int i = -C + 1; i <= C; ++i) {
          dp[x][i - 1 + C] = dp[x][i + C];
        }
        dp[x][C + C] = 0;
        range[x].first = clamp(range[x].first - 1, -C, C);
        range[x].second = clamp(range[x].second - 1, -C, C);
      }
      dp[x][C]++;
      if (0 < range[x].first) {
        range[x].first = 0;
      }
      if (0 > range[x].second) {
        range[x].second = 0;
      }

      // cout << "range[x] = {" << range[x].first << ", " << range[x].second << "}\n";
      // for (int i = range[x].first; i <= range[x].second; ++i) {
      //   cout << "dp[" << x << "][" << i << "] = " << dp[x][i + k] << "\n";
      // }
    };

    Dfs(Dfs, 0);

    for (int x = 0; x < N; ++x) {
      for (int i = 1; i <= C; ++i) {
        ans += dp[x][i + C];
        ans %= kP;
      }
    }
  }
  cout << ans << "\n";
}

