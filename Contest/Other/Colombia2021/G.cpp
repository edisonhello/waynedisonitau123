#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<vector<int>> g(N);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  vector<int> tin(N), tout(N), dep(N);
  vector<vector<int>> up(N, vector<int>(20));
  vector<int> rev(N);
  int stamp = 0;

  auto Dfs = [&](auto self, int x, int p = -1) -> void {
    up[x][0] = p;
    for (int i = 1; (1 << i) <= dep[x]; ++i) {
      up[x][i] = up[up[x][i - 1]][i - 1];
    }
    tin[x] = stamp++;
    rev[tin[x]] = x;
    for (int u : g[x]) {
      if (u == p) {
        continue;
      }
      dep[u] = dep[x] + 1;
      self(self, u, x);
    }
    tout[x] = stamp;
  };

  Dfs(Dfs, 0);

  vector<__int128> tree(N * 4);
  vector<__int128> t0(N * 4), t1(N * 4), t2(N * 4);
  vector<__int128> s1(N * 4), s2(N * 4);

  auto Push = [&](int o) {
    for (int k = 1; k <= 2; ++k) {
      tree[o * 2 + k] += t0[o];
      tree[o * 2 + k] += s1[o * 2 + k] * t1[o];
      tree[o * 2 + k] += s2[o * 2 + k] * t2[o];
      t0[o * 2 + k] += t0[o];
      t1[o * 2 + k] += t1[o];
      t2[o * 2 + k] += t2[o];
    }
    t0[o] = t1[o] = t2[o] = 0;
  };

  auto Build = [&]() {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) {
      if (r - l == 1) {
        s1[o] = dep[rev[l]];
        s2[o] = 1LL * dep[rev[l]] * dep[rev[l]];
        return;
      }
      int m = (l + r) >> 1;
      dfs(dfs, l, m, o * 2 + 1);
      dfs(dfs, m, r, o * 2 + 2);
      s1[o] = s1[o * 2 + 1] + s1[o * 2 + 2];
      s2[o] = s2[o * 2 + 1] + s2[o * 2 + 2];
    };
    return dfs(dfs, 0, N);
  };

  auto Update = [&](int ql, int qr, __int128 v0, __int128 v1, __int128 v2) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) {
      if (l >= qr || ql >= r) return;
      if (l >= ql && r <= qr) {
        tree[o] += v0;
        tree[o] += s1[o] * v1;
        tree[o] += s2[o] * v2;
        t0[o] += v0;
        t1[o] += v1;
        t2[o] += v2;
        return;
      }
      Push(o);
      int m = (l + r) >> 1;
      dfs(dfs, l, m, o * 2 + 1);
      dfs(dfs, m, r, o * 2 + 2);
      tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
    };
    return dfs(dfs, 0, N);
  };

  auto Query = [&](int p) {
    auto dfs = [&](auto dfs, int l, int r, int o = 0) -> __int128 {
      if (r - l == 1) {
        return tree[o];
      }
      Push(o);
      int m = (l + r) >> 1;
      if (p < m) {
        return dfs(dfs, l, m, o * 2 + 1);
      } else {
        return dfs(dfs, m, r, o * 2 + 2);
      }
    };
    return dfs(dfs, 0, N);
  };

  auto LCA = [&](int x, int y) {
    if (dep[x] > dep[y]) {
      swap(x, y);
    }
    for (int i = 0; i < 20; ++i) {
      if ((dep[y] - dep[x]) >> i & 1) {
        y = up[y][i];
      }
    }
    if (x == y) {
      return x;
    }
    for (int i = 19; i >= 0; --i) {
      if (up[x][i] != up[y][i]) {
        x = up[x][i];
        y = up[y][i];
      }
    }
    return up[x][0];
  };

  Build();
  int Q;
  cin >> Q;

  auto Output = [&](__int128 v) {
    if (v == 0) {
      cout << "0\n";
    } else {
      string s = "";
      while (v > 0) {
        s += v % 10 + '0';
        v /= 10;
      }
      reverse(s.begin(), s.end());
      cout << s << "\n";
    }
  };

  while (Q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int u, v;
      cin >> u >> v;
      u--;
      v--;
      int t = LCA(u, v);
      __int128 ans = Query(tin[u]) + Query(tin[v]);
      ans -= Query(tin[t]);
      if (up[t][0] != -1) {
        ans -= Query(tin[up[t][0]]);
      }
      Output(ans / 2);
    } else {
      int u, v, k;
      cin >> u >> v >> k;
      u--;
      v *= 2;
      k *= 2;
      int d0 = dep[u];
      Update(tin[u], tout[u],
             -1LL * v * d0 + v + 1LL * (k / 2) * (1LL * d0 * d0 - d0),
             v + 1LL * (k / 2) * (-2 * d0 + 1), 1LL * (k / 2));
    }
  }
  return 0;
}
