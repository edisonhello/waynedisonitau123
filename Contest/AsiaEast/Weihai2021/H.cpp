#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> w(N);
  for (int i = 0; i < N; ++i) {
    cin >> w[i];
  }
  vector<int> v(N);
  for (int i = 0; i < N; ++i) {
    cin >> v[i];
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

  constexpr int kInf = 1'000'000'000;
  vector<vector<vector<int>>> dp(N, vector<vector<int>>(2 * N + 1, vector<int>(2 * N + 1, -kInf)));

  auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
    int child = 0;
    for (int u : g[x]) {
      if (u == p) continue;
      child++;
    }
    if (child == 0) {
      // leaf
      for (int i = 1; i <= 2 * N; ++i) {
        for (int j = 0; j <= 2 * N; ++j) {
          dp[x][i][j] = v[min(j, N - 1)] - w[x];
        }
      }
      for (int j = 0; j <= 2 * N; ++j) {
        dp[x][0][j] = 0;
      }
      // for (int i = 0; i <= 2 * N; ++i) {
      //   for (int j = 0; j <= N; ++j) {
      //     if (dp[x][i][j] != -kInf) {
      //       cerr << "dp[" << x << "][" << i << "][" << j << "] = " << dp[x][i][j] << endl;
      //     }
      //   }
      // }
      return;
    }
    for (int i = 0; i <= 2 * N; ++i) {
      for (int j = 0; j <= 2 * N; ++j) {
        dp[x][i][j] = 0;
      }
    }
    int s = 0;
    for (int u : g[x]) {
      if (u == p) continue;
      dfs(dfs, u, x);
      // take
      for (int i = 2 * N; i >= 0; --i) {
        for (int j = 0; j <= 2 * N; ++j) {
          if (i + 1 <= 2 * N) {
            dp[u][i][j] = max(dp[u][i][j], dp[u][i + 1][j]);
          }
          if (j > 0) {
            dp[u][i][j] = max(dp[u][i][j], dp[u][i][j - 1]);
          }
        }
      }
      for (int i = 0; i <= 2 * N; ++i) {
        for (int j = 0; j <= 2 * N; ++j) {
          dp[x][i][j] += dp[u][i][j];
          dp[x][i][j] = max(dp[x][i][j], -kInf);
        }
      }
      int best = -kInf;
      for (int i = 0; i <= 2 * N; ++i) {
        best = max(best, dp[u][i][0]);
      }
      s += best;
      s = max(s, -kInf);
    } 
    // for (int i = 0; i <= 2 * N; ++i) {
    //   for (int j = 0; j <= 2 * N; ++j) {
    //     if (dp[x][i][j] != -kInf) {
    //       cerr << "dp[" << x << "][" << i << "][" << j << "] = " << dp[x][i][j] << endl;
    //     }
    //   }
    // }
    if (child > 1) {
      for (int i = 0; i <= 2 * N; ++i) {
        for (int j = 0; j <= 2 * N; ++j) {
          if (j - 1 > i) {
            dp[x][i][j] = -kInf;
          }
        }
      }
      for (int i = 2 * N - 1; i > 0; --i) {
        for (int j = 0; j <= 2 * N; ++j) {
          dp[x][i][j] = dp[x][i - 1][min(2 * N, j + 1)];   
        }
      }
      for (int i = 0; i <= 2 * N; ++i) {
        dp[x][0][i] = -kInf;
      }
      dp[x][0][0] = s;
    } else {
      for (int i = 2 * N - 1; i > 0; --i) {
        for (int j = 0; j <= 2 * N; ++j) {
          dp[x][i][j] = dp[x][i - 1][min(2 * N, j + 1)];   
        }
      }
      for (int i = 0; i <= 2 * N; ++i) {
        dp[x][0][i] = s;
      }
    }
    for (int i = 1; i <= 2 * N; ++i) {
      for (int j = 0; j <= 2 * N; ++j) {
        if (dp[x][i][j] != -kInf) {
          dp[x][i][j] += v[min(N - 1, min(i - 1, j))] - w[x];
        }
      }
    }
    // for (int i = 0; i <= 2 * N; ++i) {
    //   for (int j = 0; j <= 2 * N; ++j) {
    //     if (dp[x][i][j] != -kInf) {
    //       cerr << "dp[" << x << "][" << i << "][" << j << "] = " << dp[x][i][j] << endl;
    //     }
    //   }
    // }
  };

  Dfs(Dfs, 0);

  int ans = -kInf;
  for (int i = 0; i <= 2 * N; ++i) {
    for (int j = 0; j <= 2 * N; ++j) {
      ans = max(ans, dp[0][i][j]);
    }
  }
  cout << ans << "\n";
  return 0;
}

