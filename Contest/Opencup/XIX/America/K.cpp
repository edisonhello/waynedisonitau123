#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int V(int x) {
  return __builtin_ctz(x);
}

bool CanReach(int d, int t, int x, int y) {
  if (x % d != 0 || y % d != 0) {
    return false;
  }
  if (t == 0) {
    return true;
  }
  int cnt = (x / d) + (y / d);
  return cnt % 2 == 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  vector<int> r(N), c(N), a(N), b(N), p(N), g(N);
  vector<bool> t(N), vg(N);
  for (int i = 0; i < N; ++i) {
    cin >> r[i] >> c[i] >> a[i] >> b[i] >> p[i];
    g[i] = __gcd(a[i], b[i]);
    t[i] = (V(a[i]) == V(b[i]));
    vg[i] = V(g[i]);
  }
  constexpr int64_t kInf = 1'000'000'000'000'000;
  vector<int> idx(100000);
  int64_t ans = kInf;
  vector<int> vec;
  vec.reserve(100000);
  vector<vector<int64_t>> dp(100000, vector<int64_t>(2, kInf)); 
  for (int i = 1, j = 1; i < N; ++i) {
    if (r[i] == r[0] && c[i] == c[0]) {
      if (i != j) {
        swap(r[i], r[j]);
        swap(c[i], c[j]);
        swap(a[i], a[j]);
        swap(b[i], b[j]);
        swap(p[i], p[j]);
        swap(g[i], g[j]);
        swap(t[i], t[j]);
        swap(vg[i], vg[j]);
        j++;
      }
    }
  }
  vector<int> vc;
  for (int i = 0; i < N; ++i) {
    if (r[i] == r[0] && c[i] == c[0]) {
      vc.push_back(i);
    }
  }
  sort(vc.begin(), vc.end(), [&](int i, int j) { return p[i] < p[j]; });
  set<pair<int, int>> st;
  for (int i : vc) {
    if (st.count(make_pair(g[i], t[i]))) {
      continue;
    }
    st.insert(make_pair(g[i], t[i]));
    vec.clear();
    int ptr = 0;
    for (int d = 1; d * d <= g[i]; ++d) {
      if (g[i] % d == 0) {
        vec[ptr] = d;
        idx[d] = ptr++;
      }
    }
    for (int j = ptr - 1; j >= 0; --j) {
      if (vec[j] * vec[j] != g[i]) {
        vec[ptr++] = g[i] / vec[j];
      }
    }

    auto Get = [&](int y) -> int {
      if (1LL * y * y <= g[i]) {
        return idx[y];
      } else {
        return ptr - 1 - idx[g[i] / y];
      }
    };

    fill(dp.begin(), dp.begin() + ptr, vector<int64_t>(2, kInf));
    dp[ptr - 1][t[i]] = p[i];
    for (int j = ptr - 1; j >= 0; --j) {
      for (int k = 1; k >= 0; --k) {
        if (dp[j][k] != kInf) {
          if (dp[j][k] >= ans) continue;
          // cout << "dp[" << vec[j] << "][" << k << "] = " << dp[j][k] << endl;
          if (CanReach(vec[j], k, abs(r[i]), abs(c[i]))) {
            ans = min(ans, dp[j][k]);
          }
          for (int x = i + 1; x < N; ++x) {
            int dx = abs(r[i] - r[x]);
            int dy = abs(c[i] - c[x]);
            if (CanReach(vec[j], k, dx, dy)) {
              int v = __gcd(vec[j], g[x]);
              int r = Get(v);
              if (t[x] == k) {
                dp[r][k] = min(dp[r][k], dp[j][k] + p[x]);
              } else {
                int X = V(vec[j]), Y = vg[x];
                if (X == Y) {
                  dp[r][0] = min(dp[r][0], dp[j][k] + p[x]);
                } else if (X < Y) {
                  dp[r][k] = min(dp[r][k], dp[j][k] + p[x]);
                } else {
                  dp[r][t[x]] = min(dp[r][t[x]], dp[j][k] + p[x]);
                }
              }
            }
          }
        }
      }
    }
  }
  if (ans == kInf) ans = -1;
  cout << ans << "\n";
}
