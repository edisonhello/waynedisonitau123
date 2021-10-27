#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  cin >> N >> K;
  vector<int> r(N), p(N);
  for (int i = 0; i < N; ++i) {
    cin >> r[i] >> p[i];
  }
  
  constexpr int64_t kInf = 1'000'000'000'000'000;
  vector<vector<int64_t>> dp(N + 1, vector<int64_t>(K + 1, kInf));
  dp[0][0] = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < K; ++j) {
      if (dp[i][j] == kInf) continue;
      int64_t s = 0, t = 0;
      // int64_t lx = 0, ly = 0, lz = 0;
      int64_t rx = 0, ry = 0, rz = 0;
      for (int k = i; k < N; ++k) {
        s += 1LL * r[k] * p[k];
        t += p[k];
        rx += 1LL * r[k] * r[k] * p[k];
        ry += 1LL * r[k] * p[k];
        rz += p[k];
        int m = round(static_cast<double>(s) / t);
        int64_t v = dp[i][j] + 1LL * m * m * rz + rx - 2 * m * ry;
        dp[k + 1][j + 1] = min(dp[k + 1][j + 1], v);
      }
    }
  }
  cout << dp[N][K] << "\n";
}

