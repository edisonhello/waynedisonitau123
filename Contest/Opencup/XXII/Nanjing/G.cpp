#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    N++;
    vector<int> A(N - 1);
    for (int i = 0; i < N - 1; ++i) {
      cin >> A[i];
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

    vector<int> sz(N);
    vector<int> fr(N);
    vector<vector<int>> between(N, vector<int>(N));
    vector<vector<int>> from(N, vector<int>(N));

    auto Dfs = [&](auto self, int x, int p = -1, int f = -1) -> void {
      sz[x] = 1;
      fr[x] = f;
      for (int u : g[x]) {
        if (u == p) {
          continue;
        }
        self(self, u, x, (f == -1 ? u : f));
        sz[x] += sz[u];
      }
    };

    for (int i = 0; i < N; ++i) {
      Dfs(Dfs, i);
      for (int j = 0; j < N; ++j) {
        if (i != j) {
          between[i][j] = sz[fr[j]] - sz[j] + 1;
          from[i][j] = fr[j];
        }
      }
    }

    constexpr int64_t kInf = 1'000'000'000'000'000'000;
    vector<vector<vector<int64_t>>> dp(N, 
        vector<vector<int64_t>>(N, vector<int64_t>(N, -kInf)));
    for (int i = 0; i < N; ++i) {
      for (int u : g[i]) {
        for (int v : g[u]) {
          if (i != v) {
            dp[i][v][0] = 0;
          }
        }
      }
    }
    // for (int x = 0; x < N; ++x) {
    //   for (int y = 0; y < N; ++y) {
    //     if (x != y) {
    //       cout << "from[" << x << "][" << y << "] = " << from[x][y] << endl;
    //       cout << "between[" << x << "][" << y << "] = " << between[x][y] << endl;
    //     }
    //   }
    // }
    for (int e = 0; e + 1 < N; ++e) {
      for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
          if (dp[x][y][e] == -kInf) {
            continue;
          }
          if (e < between[x][y]) {
            if (e < between[x][y] - 2) {
              dp[x][y][e + 1] = max(dp[x][y][e + 1], dp[x][y][e]);
            }
            for (int u : g[x]) {
              if (u == from[x][y]) {
                continue;
              }
              dp[u][y][e + 1] = max(dp[u][y][e + 1], dp[x][y][e] + A[e]);
            }
            for (int u : g[y]) {
              if (u == from[y][x]) {
                continue;
              }
              dp[x][u][e + 1] = max(dp[x][u][e + 1], dp[x][y][e] + A[e]);
            }
          }
        }
      }
    }

    vector<int> best(N - 1, -2'000'000'001);
    int e1 = -1, e2 = -1;
    for (int i = N - 2; i >= 0; --i) {
      if (A[i] > e1) {
        e2 = e1;
        e1 = A[i];
      } else if (A[i] > e2) {
        e2 = A[i];
      }
      if (e2 != -1) {
        best[i] = e1 + e2;
      }
    }

    int64_t ans = *max_element(A.begin(), A.end());
    for (int x = 0; x < N; ++x) {
      for (int y = 0; y < N; ++y) {
        for (int e = 0; e < N - 1; ++e) {
          ans = max(ans, dp[x][y][e] + best[e]);
        }
      }
    }
    cout << ans << "\n";
  }
}

