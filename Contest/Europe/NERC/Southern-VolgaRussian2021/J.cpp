#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K, X;
  cin >> N >> K >> X;
  vector<int> a(N), b(N), c(N), d(N);
  for (int i = 0; i < N; ++i) {
    cin >> a[i] >> b[i] >> c[i] >> d[i];
  }
  vector<vector<int64_t>> dp(N, vector<int64_t>(2 * K + 1, -1'000'000'000'000'000));
  for (int i = N - 1; i >= 0; --i) {
    for (int j = -K; j <= K; ++j) {
      // normal
      {
        int64_t r = X + j + (c[i] ? a[i] : -b[i]);
        int p = i + 1;
        while (r < X - K || r > X + K) {
          if (p >= N) {
            dp[i][j + K] = max(dp[i][j + K], r);
            break;
          }
          if (r < X - K) {
            r += (c[p] ? a[p] : -b[p]);
          } else {
            r += (d[p] ? a[p] : -b[p]);
          }
          p++;
        }
        if (p < N) {
          dp[i][j + K] = max(dp[i][j + K], dp[p][r - X + K]);
        } else {
          dp[i][j + K] = max(dp[i][j + K], r);
        }
      }
      // bongcloud
      {
        int64_t r = X + j + (d[i] ? a[i] : -b[i]);
        int p = i + 1;
        while (r < X - K || r > X + K) {
          if (p >= N) {
            dp[i][j + K] = max(dp[i][j + K], r);
            break;
          }
          if (r < X - K) {
            r += (c[p] ? a[p] : -b[p]);
          } else {
            r += (d[p] ? a[p] : -b[p]);
          }
          p++;
        }
        if (p < N) {
          dp[i][j + K] = max(dp[i][j + K], dp[p][r - X + K]);
        } else {
          dp[i][j + K] = max(dp[i][j + K], r);
        }
      }
    }
  }
  cout << dp[0][K] << "\n";
}
