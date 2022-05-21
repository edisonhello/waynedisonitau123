#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> fa(N, -1);
  vector<int> sz(N, 1);
  vector<vector<int>> g(N);
  for (int i = 1; i < N; ++i) {
    cin >> fa[i];
    fa[i]--;
    g[fa[i]].push_back(i);
  }

  auto DfsSz = [&](auto self, int x) -> void {
    sz[x] = 1;
    for (int u : g[x]) {
      self(self, u);
      sz[x] += sz[u];
    }
  };

  DfsSz(DfsSz, 0);

  int w;
  cin >> w;
  w--;
  vector<bool> mark(N);
  vector<int> up;
  int x = w;
  while (x >= 0) {
    up.push_back(x);
    mark[x] = true;
    x = fa[x];
  }
  reverse(up.begin(), up.end());
  constexpr int kP = 1'000'000'000 + 7;

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) {
        res = 1LL * res * a % kP;
      }
      a = 1LL * a * a % kP;
      n >>= 1;
    }
    return res;
  };

  vector<int> E(N);
  E[0] = 0;
  int sum_e = 0, sum = 0;
  int sum_b = 0;
  for (int i = 0; i + 1 < up.size(); ++i) {
    int x = up[i];
    int s = 1;
    int diff = 0;
    for (int u : g[x]) {
      if (mark[u]) {
        continue;
      }
      int other = (sum_e + 1LL * (N - sum - sz[u]) * E[up[i]] % kP + N) % kP;
      E[u] = 1LL * other * fpow(N - sz[u], kP - 2) % kP;
      (diff += 1LL * sz[u] * (E[up[i]] + kP - E[u]) % kP) %= kP;
      s += sz[u];
      sum_b += 1LL * E[u] * sz[u] % kP;
      sum_b %= kP;
    }
    (sum_b += E[up[i]]) %= kP;
    E[up[i + 1]] =
        1LL * (diff + 1LL * N * E[up[i]]) % kP * fpow(N, kP - 2) % kP;
    (sum_e += 1LL * E[up[i]] * s % kP) %= kP;
    sum += s;
  }
  int sum_a = sum;
  vector<int> ca(N), cb(N);
  for (int u : g[w]) {
    int t = fpow(N - sz[u], kP - 2);
    int a = 1LL * (N - sz[w]) * t % kP;
    int b = 1LL * (sum_e + N) * t % kP;
    ca[u] = a;
    cb[u] = b;
    (sum_a += 1LL * sz[u] * a % kP) %= kP;
    (sum_b += 1LL * sz[u] * b % kP) %= kP;
    // cerr << "u = " << u << " a = " << a << " b = " << b << endl;
  }
  (sum_b += N) %= kP;
  int ans_x = 1LL * sum_b * fpow((N + kP - sum_a), kP - 2) % kP;

  auto Dfs = [&](auto self, int x, int v) -> void {
    E[x] = v;
    for (int u : g[x]) {
      self(self, u, v);
    }
  };

  for (int i = 0; i < up.size(); ++i) {
    int x = up[i];
    E[x] = (ans_x + E[x]) % kP;
    for (int u : g[x]) {
      if (mark[u]) {
        continue;
      }
      Dfs(Dfs, u, (ans_x + E[u]) % kP);
    }
  }
  E[w] = 0;
  for (int u : g[w]) {
    E[u] = (1LL * ca[u] * ans_x + cb[u]) % kP;
    Dfs(Dfs, u, E[u]);
  }
  int64_t ans = 0;
  for (int i = 0; i < N; ++i) {
    ans += (E[i] ^ (i + 1));
  }
  cout << ans << "\n";
  return 0;
}
