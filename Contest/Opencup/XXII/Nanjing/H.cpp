#include <bits/stdc++.h>
using namespace std;

struct Max3 {
  pair<int64_t, int> best[3];

  Max3() {
    best[0] = best[1] = best[2] = {0, -2};
  }

  void Update(int64_t v, int x) {
    for (int i = 0; i < 3; ++i) {
      if (v > best[i].first) {
        for (int j = 2; j > i; --j) {
          best[j] = best[j - 1];
        }
        best[i] = {v, x};
        break;
      }
    }
  }

  int64_t Query(int x, int y) {
    for (int i = 0; i < 3; ++i) {
      if (best[i].second != x && best[i].second != y) {
        return best[i].first;
      }
    }
    assert(false);
  }

  bool Contains(int x) {
    for (int i = 0; i < 3; ++i) {
      if (best[i].second == x) {
        return true;
      }
    }
    return false;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<int> a(N), t(N);
    for (int i = 0; i < N; ++i) {
      cin >> a[i];
    }
    for (int i = 0; i < N; ++i) {
      cin >> t[i];
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

    // vector<vector<int64_t>> dp(N, vector<int64_t>(4));
    vector<int64_t> dp(N), dp2(N);

    constexpr int64_t kInf = 1'000'000'000'000'000'000;

    auto Dfs = [&](auto self, int x, int p = -1) -> void {
      vector<vector<int>> chs(3);
      int64_t s = 0;
      int best = 0;
      for (int u : g[x]) {
        if (u == p) {
          continue;
        }
        self(self, u, x);
        chs[t[u] - 1].push_back(u);
        s += dp[u] - a[u];
        dp2[x] += dp[u] - a[u];
        best = max(best, a[u]);
        // best.Update(a[u], u);
      } 
      dp[x] = a[x] + s + best;
      if (!chs[2].empty()) {
        pair<int, int> best1 = {0, -1};
        pair<int, int> best2 = {0, -1};
        for (int u : chs[2]) {
          if (a[u] > best1.first) {
            best2 = best1;
            best1 = {a[u], u}; 
          } else if (a[u] > best2.first) {
            best2 = {a[u], u};
          }
        }
        for (int u : g[x]) {
          if (u == p) continue;
          if (t[u] == 3 && chs[2].size() == 1) continue;
          int v = (u == best1.second ? best2.first : best1.first);
          dp[x] = max(dp[x], static_cast<int64_t>(a[x]) + 2 * a[u] + dp2[u] - dp[u] + v + s);
        }
      }
      // if (!chs[0].empty() && !chs[2].empty()) {
      //   int64_t e = -kInf, f = -kInf;
      //   for (int u : chs[0]) {
      //     if (!best.Contains(u)) {
      //       e = max(e, -(dp[u] - a[u]) + a[u]);
      //     }
      //   }
      //   for (int u : chs[2]) {
      //     if (!best.Contains(u)) {
      //       f = max(f, -(dp[u] - a[u]) + dp[u]);
      //     }
      //   }
      //   if (e != -kInf && f != -kInf) {
      //     dp[x] = max(dp[x], a[x] + s + e + f + best.Query(-1, -1));
      //   }
      //   for (int u : chs[0]) {
      //     if (best.Contains(u)) {
      //       dp[x] = max(dp[x], a[x] + s - (dp[u] - a[u]) + a[u] + f + best.Query(u, u));
      //     }
      //   }
      //   for (int u : chs[2]) {
      //     if (best.Contains(u)) {
      //       dp[x] = max(dp[x], a[x] + s - (dp[u] - a[u]) + dp[u] + e + best.Query(u, u));
      //     }
      //   }
      //   for (int u : {best.best[0].second, best.best[1].second, best.best[2].second}) {
      //     if (t[u] == 1) {
      //       for (int v : {best.best[0].second, best.best[1].second, best.best[2].second}) {
      //         if (t[v] == 3) {
      //           dp[x] = max(dp[x], a[x] + s - (dp[u] - a[u]) - (dp[v] - a[v]) + a[u] + dp[v] + best.Query(u, v));
      //         }
      //       }
      //     }
      //   }
      // }
    };

    Dfs(Dfs, 0);
    cout << dp[0] << "\n";
  }
}

