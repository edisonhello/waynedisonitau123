#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int N, M, R;
  cin >> N >> M >> R;
  vector<int> d(N), k(N), c(N);
  for (int i = 0; i < N; ++i) {
    cin >> d[i] >> k[i] >> c[i];
  }
  vector<pair<int, int>> B(M);
  int sum = 0;
  for (int i = 0; i < M; ++i) {
    cin >> B[i].first >> B[i].second;
    sum += B[i].second;
  }
  sort(B.begin(), B.end());
  vector<int> D(sum);
  for (int i = 0, j = 0; i < M; ++i) {
    for (int k = 0; k < B[i].second; ++k) D[j++] = B[i].first;
  }
  vector<int64_t> dp(sum + 1);
  vector<int> ptr(N);
  for (int i = 1; i <= sum; ++i) {
    dp[i] = dp[i - 1] + R;
    for (int j = 0; j < N; ++j) {
      while (D[i - 1] - D[ptr[j]] >= d[j]) ptr[j]++;
      if (i - ptr[j] >= k[j]) {
        dp[i] = min(dp[i], dp[i - k[j]] + c[j]);
      } else {
        dp[i] = min(dp[i], dp[ptr[j]] + c[j]);
      }
    }
  }
  cout << dp[sum] << "\n";
}
