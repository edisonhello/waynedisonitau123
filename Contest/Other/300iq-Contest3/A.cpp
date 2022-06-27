#include <bits/stdc++.h>
using namespace std;

constexpr int kP = 998244353;

int fpow(int a, int n) {
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

namespace ntt {

constexpr int kN = 1048576;
constexpr int kMod = kP;
constexpr int kRoot = 3;
vector<int> omega;

void Init() {
  omega.resize(kN + 1);
  long long x = fpow(kRoot, (kMod - 1) / kN);
  omega[0] = 1;
  for (int i = 1; i <= kN; ++i) {
    omega[i] = 1LL * omega[i - 1] * x % kMod;
  }
}

void BitReverse(vector<int> &v, int n) {
  int z = __builtin_ctz(n) - 1;
  for (int i = 0; i < n; ++i) {
    int x = 0;
    for (int j = 0; j <= z; ++j) x ^= (i >> j & 1) << (z - j);
    if (x > i) swap(v[x], v[i]);
  }
}

void Transform(vector<int> &v, int n) {
  BitReverse(v, n);
  for (int s = 2; s <= n; s <<= 1) {
    int z = s >> 1;
    for (int i = 0; i < n; i += s) {
      for (int k = 0; k < z; ++k) {
        int x = 1LL * v[i + k + z] * omega[kN / s * k] % kMod;
        v[i + k + z] = (v[i + k] + kMod - x) % kMod;
        (v[i + k] += x) %= kMod;
      }
    }
  }
}

void InverseTransform(vector<int> &v, int n) {
  Transform(v, n);
  for (int i = 1; i < n / 2; ++i) swap(v[i], v[n - i]);
  const int kInv = fpow(n, kMod - 2);
  for (int i = 0; i < n; ++i) v[i] = 1LL * v[i] * kInv % kMod;
}

vector<int> Multiply(vector<int> a, vector<int> b) {
  int n = a.size(), m = b.size(), sz = 1;
  while (sz < n + m - 1) {
    sz <<= 1;
  }
  a.resize(sz);
  b.resize(sz);
  Transform(a, sz);
  Transform(b, sz);
  for (int i = 0; i < sz; ++i) {
    a[i] = 1LL * a[i] * b[i] % kMod;
  }
  InverseTransform(a, sz);
  a.resize(n + m - 1);
  return a;
}

}  // namespace ntt

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ntt::Init();
  int N, X;
  cin >> N >> X;
  int M = N + N - 1;
  vector<vector<int>> g(M);
  for (int i = 0; i < N - 1; ++i) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back(N + i);
    g[N + i].push_back(a);
    g[b].push_back(N + i);
    g[N + i].push_back(b);
  }

  vector<bool> vis(M);
  vector<int> tour;
  vector<int> sz(M), mx(M);

  auto DfsSize = [&](auto dfs, int x) -> void {
    vis[x] = true;
    tour.push_back(x);
    sz[x] = 1;
    mx[x] = 0;
    for (int u : g[x]) {
      if (!vis[u]) {
        dfs(dfs, u);
        sz[x] += sz[u];
        mx[x] = max(mx[x], sz[u]);
      }
    }
  };

  vector<vector<int>> dist(M);
  vector<int> fa(M, -1);
  vector<int> lv(M);

  auto DfsDist = [&](auto dfs, int x, int d = 0) -> void {
    dist[x].push_back(d);
    vis[x] = true;
    for (int u : g[x]) {
      if (!vis[u]) {
        dfs(dfs, u, d + 1);
      }
    }
  };

  auto Dfs = [&](auto dfs, int x, int level = 0, int p = -1) -> void {
    tour.clear();
    DfsSize(DfsSize, x);
    int cent = -1;
    int k = tour.size();
    for (int u : tour) {
      if (max(mx[u], k - sz[u]) * 2 <= k) {
        cent = u;
      }
      vis[u] = false;
    }
    DfsDist(DfsDist, cent);
    fa[cent] = p;
    lv[cent] = level;
    for (int u : tour) {
      vis[u] = false;
    }
    vis[cent] = true;
    for (int u : g[cent]) {
      if (!vis[u]) {
        dfs(dfs, u, level + 1, cent);
      }
    }
  };

  Dfs(Dfs, 0);

  auto GetCnt = [&](int D) {
    vector<vector<int>> sub(M);
    vector<vector<int>> sub2(M);
    for (int i = 0; i < N; ++i) {
      for (int x = i, d = lv[i], z = -1; x >= 0; z = x, x = fa[x], d--) {
        sub[x].push_back(dist[i][d]);
        if (z != -1) {
          sub2[z].push_back(dist[i][d]);
        }
      }
    }
    for (int i = 0; i < M; ++i) {
      sort(sub[i].begin(), sub[i].end());
      sort(sub2[i].begin(), sub2[i].end());
    }
    vector<int> cnt(M);
    for (int i = 0; i < M; ++i) {
      for (int x = i, d = lv[i], z = -1; x >= 0; z = x, x = fa[x], d--) {
        int target = D - dist[i][d];
        cnt[i] +=
            upper_bound(sub[x].begin(), sub[x].end(), target) - sub[x].begin();
        if (z != -1) {
          cnt[i] -= upper_bound(sub2[z].begin(), sub2[z].end(), target) -
                    sub2[z].begin();
        }
      }
    }
    return cnt;
  };

  vector<int> cnt_down(M);
  vector<vector<int>> dp(M);

  auto DfsDown = [&](auto dfs, int x, int p = -1) -> void {
    for (int u : g[x]) {
      if (u == p) {
        continue;
      }
      dfs(dfs, u, x);
      if (dp[x].size() < dp[u].size()) {
        dp[x].swap(dp[u]);
      }
      for (int i = 0; i < dp[u].size(); ++i) {
        dp[x][i + dp[x].size() - dp[u].size()] += dp[u][i];
      }
    }
    dp[x].push_back(x < N);
    if (dp[x].size() > X) {
      cnt_down[x] = dp[x][dp[x].size() - 1 - X];
    }
  };

  DfsDown(DfsDown, 0);

  vector<int> cnt_x = GetCnt(X);

  vector<int> fc(M + 1, 1), iv(M + 1, 1);

  for (int i = 1; i <= M; ++i) {
    fc[i] = 1LL * fc[i - 1] * i % kP;
    iv[i] = fpow(fc[i], kP - 2);
  }

  auto Choose = [&](int n, int k) -> int {
    if (n < k || k < 0) return 0;
    return 1LL * fc[n] * iv[k] % kP * iv[n - k] % kP;
  };

  auto Solve = [&](const vector<int> &a) {
    int K = *max_element(a.begin(), a.end());
    vector<int> cnt(N + 1);
    for (int u : a) {
      cnt[u]++;
    }
    for (int i = 0; i <= N; ++i) {
      cnt[i] = 1LL * fc[i] * cnt[i] % kP;
    }
    vector<int> poly(N + 1);
    for (int i = 0; i <= N; ++i) {
      poly[N - i] = iv[i];
    }
    vector<int> mult = ntt::Multiply(cnt, poly);
    vector<int> res(N + 1);
    for (int i = 1; i <= N; ++i) {
      res[i] = 1LL * mult[i + N] * iv[i] % kP;
    }
    return res;
  };

  cout << N << " ";
  vector<int> ans1 = Solve(cnt_x);
  for (int i = 0; i < M; ++i) {
    if (i != 0) {
      cnt_x[i] -= cnt_down[i];
    } else {
      cnt_x[i] = 0;
    }
  }
  vector<int> ans2 = Solve(cnt_x);
  for (int k = 2; k <= N; ++k) {
    cout << (ans1[k] + kP - ans2[k]) % kP << " ";
  }
  cout << "\n";
}
