#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n);
  vector<vector<int>> nxt(1, vector<int>(2, -1));
  vector<int> sz(1, 0);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    int x = 0;
    for (int j = m - 1; j >= 0; --j) {
      int bit = a[i] >> j & 1;
      if (nxt[x][bit] == -1) {
        nxt[x][bit] = nxt.size();
        nxt.emplace_back(2, -1);
        sz.push_back(0);
      }
      x = nxt[x][bit];
      sz[x]++;
    }
  }

  constexpr int64_t kInf = 1'000'000'000'000'000'000;
  vector<vector<int64_t>> dp(nxt.size(), vector<int64_t>(k + 1));

  auto Dfs = [&](auto self, int x, int d) -> void {
    fill(dp[x].begin(), dp[x].end(), -kInf);
    for (int i = 0; i < 2; ++i) {
      if (nxt[x][i] == -1) continue;
      self(self, nxt[x][i]);
    }
  };

  Dfs(Dfs, 0, m - 1);
  return 0;
}
