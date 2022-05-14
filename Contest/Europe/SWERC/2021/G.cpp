#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<vector<int>> g(N);
  for (int i = 1; i < N; ++i) {
    int p;
    cin >> p;
    p--;
    g[i].push_back(p);
    g[p].push_back(i);
  }

  vector<int> sz(N), mx(N), dep(N);
  auto Dfs = [&](auto dfs, int x, int p = -1, int d = 0) -> void {
    sz[x] = 1;
    dep[x] = d;
    for (int u : g[x]) {
      if (u == p) {
        continue;
      }
      dfs(dfs, u, x, d + 1);
      sz[x] += sz[u];
      mx[x] = max(mx[x], sz[u]);
    }
  };

  Dfs(Dfs, 0);
  int cent = -1;
  for (int i = 0; i < N; ++i) {
    int r = max(mx[i], N - sz[i]);
    if (r * 2 <= N) {
      cent = i;
    }
  }

  Dfs(Dfs, cent);
  vector<int> vec;
  for (int u : g[cent]) {
    vec.push_back(sz[u]);
  }
  vector<int> cnt(1000000 + 1);
  for (int u : vec) {
    cnt[u]++;
  }
  vector<bool> dp(N + 1);
  dp[0] = true;
  for (int i = 1; i <= 500; ++i) {
    if (cnt[i] > 0) {
      int x = cnt[i];
      for (int j = 0; (1 << j) <= x; ++j) {
        for (int k = N + 1; k >= i * (1 << j); --k) {
          if (dp[k - i * (1 << j)]) {
            dp[k] = true;
          }
        }
        x -= (1 << j);
      }
      if (x > 0) {
        for (int k = N + 1; k >= i * x; --k) {
          if (dp[k - i * x]) {
            dp[k] = true;
          }
        }
      }
    }
  }
  constexpr int kN = 1000000 + 1;
  bitset<kN> dd;
  for (int i = 0; i <= N; ++i) {
    if (dp[i]) {
      dd.set(i);
    }
  }
  for (int i = 500 + 1; i <= N; ++i) {
    for (int j = 0; j < cnt[i]; ++j) {
      dd |= dd << i;
    }
  }
  int64_t ans = 0;
  int64_t s = 0;
  for (int i = 0; i < N; ++i) {
    s += dep[i] + 1;
  }
  for (int i = 0; i <= N; ++i) {
    if (dd[i]) {
      ans = max<int64_t>(ans, 1LL * i * (N - 1 - i));
    }
  }
  cout << ans + s << "\n";
}

