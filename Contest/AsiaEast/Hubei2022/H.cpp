#include <bits/stdc++.h>
using namespace std;

int main() {
  int64_t n;
  cin >> n;

  vector<int> factors = {2, 3, 5, 7};
  vector<int64_t> goods;

  auto Dfs = [&](auto dfs, int p, int64_t s) {
    if (s > n) {
      return;
    }
    if (s % 10 == 0) {
      return;
    }
    if (p == 4) {
      goods.push_back(s);
      return;
    }
    while (s <= n) {
      dfs(dfs, p + 1, s);
      if (s <= n / factors[p]) {
        s *= factors[p];
      } else {
        break;
      }
    }
  };

  Dfs(Dfs, 0, 1);

  sort(goods.begin(), goods.end());
  goods.resize(unique(goods.begin(), goods.end()) - goods.begin());

  vector<int> digs;
  for (int64_t m = n; m > 0; m /= 10) {
    digs.push_back(m % 10);
  }
  reverse(digs.begin(), digs.end());

  int M = goods.size();

  vector<vector<vector<int64_t>>> dp(
      digs.size() + 1, vector<vector<int64_t>>(M, vector<int64_t>(2)));

  dp[0][0][1] = 1;
  for (int i = 1; i < digs.size(); ++i) {
    dp[i][0][0] = 1;
  }
  for (int i = 0; i < digs.size(); ++i) {
    for (int j = 0; j < M; ++j) {
      for (int k = 1; k <= 9; ++k) {
        if (goods[j] % k != 0) {
          continue;
        }
        int64_t g = goods[j] / k;
        assert(binary_search(goods.begin(), goods.end(), g));
        int p = lower_bound(goods.begin(), goods.end(), g) - goods.begin();
        dp[i + 1][j][0] += dp[i][p][0];
        if (k < digs[i]) {
          dp[i + 1][j][0] += dp[i][p][1];
        }
        if (k == digs[i]) {
          dp[i + 1][j][1] += dp[i][p][1];
        }
      }
    }
  }

  int64_t ans = 0;
  for (int i = 0; i < goods.size(); ++i) {
    int64_t g = goods[i];
    while (g >= 10) {
      int64_t ng = 1;
      while (g > 0) {
        ng *= g % 10;
        g /= 10;
      }
      g = ng;
    }
    ans += g * (dp[digs.size()][i][0] + dp[digs.size()][i][1]);
  }
  cout << ans << "\n";
  return 0;
}
