#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<vector<int>> w(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      cin >> w[i][j];
      w[j][i] = w[i][j];
    }
  }
  constexpr int64_t kInf = 1'000'000'000'000'000;
  vector<vector<int64_t>> dp(1 << n, vector<int64_t>(n, kInf));
  vector<vector<int64_t>> best(1 << n, vector<int64_t>(n, kInf));
  for (int i = 0; i < n; ++i) {
    dp[1 << i][i] = 0;
    for (int j = 0; j < n; ++j) {
      best[1 << i][j] = min(best[1 << i][j], dp[1 << i][i] + (int64_t)w[i][j] * (n - 1));
    }
  }
  for (int s = 0; s < (1 << n); ++s) {
    if (__builtin_popcount(s) == 1) continue;
    for (int i = 0; i < n; ++i) {
      if ((s >> i & 1) == 0) continue;
      int t = s ^ (1 << i);
      for (int sub = t; sub > 0; sub = (sub - 1) & t) {
        dp[s][i] = min(dp[s][i], dp[s ^ sub][i] + best[sub][i]);
      }
      int g = __builtin_popcount(s);
      for (int j = 0; j < n; ++j) {
        best[s][j] = min(best[s][j], dp[s][i] + (int64_t)w[i][j] * g * (n - g));
      }
    }
  }
  int64_t res = kInf;
  for (int i = 0; i < n; ++i) {
    res = min(res, dp[(1 << n) - 1][i]);
  }
  cout << res << "\n";
  return 0;
}
