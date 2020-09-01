#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

void solve() {
  int n, m, k; cin >> n >> m >> k;
  vector<int> v(n * m);
  vector<int> cnt(n + m + 1, 0);
  auto id = [&] (int i, int j) { return i * m + j; };
  auto Dfs = [&] (auto self, int pos) {
    if (pos == n * m) {
      int g = 0;
      for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        bool yes = 1;
        for (int ii = 0; ii < n; ++ii) if (ii != i) {
          if (v[id(ii, j)] >= v[id(i, j)]) { yes = 0; break; }
        }
        if (yes) for (int jj = 0; jj < m; ++jj) if (jj != j) {
          if (v[id(i, jj)] >= v[id(i, j)]) { yes = 0; break; }
        }
        if (yes) ++g;
      }
      ++cnt[g];
      return;
    }
    for (int i = 1; i <= k; ++i) {
      v[pos] = i;
      self(self, pos + 1);
    }
  };

  Dfs(Dfs, 0);
  int sum = 0;
  for (int i = 0; i < (int)cnt.size(); ++i) sum = (sum + (i + 1ll) * cnt[i]) % mod;
  cout << sum << endl;
}

int main() {
  int t; cin >> t; for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": ";
    solve();
  }
}
