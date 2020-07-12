#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q, d;
  cin >> n >> q >> d;
  const int m = (n + 63) >> 6;
  vector<vector<uint64_t>> bs(q, vector<uint64_t>(m));
  vector<vector<int>> ev(d * 4);

  auto Modify = [&](int ql, int qr, int v) {
    auto _ = [&](auto self, int l, int r, int o = 0) {
      if (l >= qr || ql >= r) return;
      if (l >= ql && r <= qr) {
        ev[o].push_back(v);
        return;
      }
      int m = (l + r) >> 1;
      self(self, l, m, o * 2 + 1);
      self(self, m, r, o * 2 + 2);
    };

    _(_, 0, d);
  };

  for (int i = 0; i < q; ++i) {
    int l, r;
    string s;
    cin >> l >> r >> s;
    l--;
    for (int j = 0; j < n; j += 64) {
      for (int k = 0; k < 64 && j + k < n; ++k) {
        if (s[j + k] == '1') {
          bs[i][j >> 6] |= 1ULL << k;
        }
      }
    }
    Modify(l, r, i);
  }
  vector<int> pw(n + 1, 1);
  constexpr int kMod = 1'000'000'000 + 7;
  for (int i = 1; i <= n; ++i) {
    pw[i] = (pw[i - 1] + pw[i - 1]) % kMod;
  }

  vector<vector<uint64_t>> basis;

  auto Dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
    int sz = basis.size();
    for (int u : ev[o]) {
      vector<uint64_t> cur(bs[u].begin(), bs[u].end());
      for (auto &s : basis) {
        vector<uint64_t> xr(cur.begin(), cur.end());
        for (int i = 0; i < m; ++i) xr[i] ^= s[i];
        cur = min(cur, xr);
      }
      if (*max_element(cur.begin(), cur.end()) > 0) {
        basis.push_back(cur);
      }
    }
    if (r - l == 1) {
      cout << pw[basis.size()] << " ";
    } else {
      int m = (l + r) >> 1;
      dfs(dfs, l, m, o * 2 + 1);
      dfs(dfs, m, r, o * 2 + 2);
    }
    while (basis.size() > sz) basis.pop_back();
  };

  Dfs(Dfs, 0, d);
  cout << "\n";
}
