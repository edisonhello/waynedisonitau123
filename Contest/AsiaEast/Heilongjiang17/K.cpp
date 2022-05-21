#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> a(N);
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
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

  constexpr int kP = 1'000'000'000 + 7;
  vector<int> sz(N);
  vector<int> tin(N), tout(N);
  vector<int> fa(N);
  int stamp = 0;

  auto Dfs = [&](auto self, int x, int p = -1) -> void {
    tin[x] = stamp++;
    sz[x] = 1;
    fa[x] = p;
    for (int u : g[x]) {
      if (u == p) {
        continue;
      }
      self(self, u, x);
      sz[x] += sz[u];
    }
    tout[x] = stamp;
  };

  Dfs(Dfs, 0);

  auto IsAnc = [&](int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  };

  vector<int> order(N);
  iota(order.begin(), order.end(), 0);

  sort(order.begin(), order.end(), [&](int i, int j) { return a[i] < a[j]; });

  vector<int> fw1(N + 1);
  vector<int> fw2(N + 1);

  auto Update = [&](auto& fw, int p, int v) {
    for (int i = p + 1; i <= N; i += i & -i) {
      fw[i] += v;
      fw[i] %= kP;
    }
  };

  auto Query = [&](const auto& fw, int p) {
    int res = 0;
    for (int i = p + 1; i > 0; i -= i & -i) {
      res += fw[i];
      res %= kP;
    }
    return res;
  };

  auto QueryRange = [&](const auto& fw, int l, int r) {
    return (Query(fw, r - 1) + kP - Query(fw, l - 1)) % kP;
  };

  int ans = 0;
  for (int x : order) {
    int s = N;
    int t = 0;
    for (int u : g[x]) {
      if (u == fa[x]) {
        continue;
      }
      int d = QueryRange(fw1, tin[u], tout[u]);
      // cerr << "u = " << u << " dp = " << d << endl;
      (s += 1LL * d * (N - sz[u]) % kP) %= kP;
      (t += d) %= kP;
    }
    t = (QueryRange(fw1, 0, N) + kP - t) % kP;
    if (fa[x] >= 0) {
      int d = QueryRange(fw2, 0, tin[x] + 1);
      // cerr << "u = " << fa[x] << " dp = " << d << endl;
      (s += 1LL * (d + t) * sz[x] % kP) %= kP;
    }
    int acc = 0;
    // cerr << "s = " << s << endl;
    for (int u : g[x]) {
      if (u == fa[x]) {
        continue;
      }
      (s += 1LL * sz[u] * acc % kP) %= kP;
      acc += sz[u];
    }
    if (fa[x] >= 0) {
      (s += 1LL * (N - sz[x]) * acc % kP) %= kP;
    }
    // cerr << "x = " << x << " s = " << s << endl;
    (ans += 1LL * s * a[x] % kP) %= kP;

    Update(fw1, tin[x], sz[x]);
    for (int u : g[x]) {
      if (u == fa[x]) {
        continue;
      }
      Update(fw2, tin[u], (N - sz[u] - sz[x] + kP) % kP);
      Update(fw2, tout[u], (kP - N + sz[u] + sz[x]) % kP);
    }
  }

  /*
  for (int i = 0; i < N; ++i) {
    int s = dp[i] + N;
    cerr << "i = " << i << endl;
    for (int j = 0; j < N; ++j) {
      cerr << "dp[" << j << "] = " << dp[j] << endl;
    }
    cerr << "s = " << s << endl;
    int acc = 0;
    for (int u : g[i]) {
      (s += 1LL * dp[u] * (N - sz[u] - 1) % kP) %= kP;
      (s += 1LL * sz[u] * acc % kP) %= kP;
      acc += sz[u];
    }
    cerr << "s = " << s << endl;
    ans += 1LL * s * a[i] % kP;
    ans %= kP;
  }
  */
  cout << ans << "\n";
}
