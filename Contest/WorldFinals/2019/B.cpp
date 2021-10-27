#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr double kEps = 1E-9;

int main() {
  int N, H, A, B;
  cin >> N >> H >> A >> B;
  vector<int> x(N), y(N);
  for (int i = 0; i < N; ++i) {
    cin >> x[i] >> y[i];
  }

  constexpr int64_t kInf = 1'000'000'000'000'000'000;
  vector<int64_t> dp(N, kInf);
  dp[0] = 1LL * A * (H - y[0]);
  for (int i = 0; i < N; ++i) {
    long double left = -1E10, right = 1E10;
    priority_queue<pair<int, int>> pq;
    for (int j = i; j < N; ++j) {
      pq.emplace(y[j], j);
      while (!pq.empty() && 2 * pq.top().first >= 2 * H - (x[j] - x[i])) {
        int u = pq.top().second;
        pq.pop();
        long double s = sqrt(static_cast<long double>(2LL * (x[u] - x[i]) * (H - y[u])));
        left = max(left, (x[u] - x[i]) + (H - y[u]) - s);
        right = min(right, (x[u] - x[i]) + (H - y[u]) + s);
      }
      if (2 * left <= x[j] - x[i] + kEps && x[j] - x[i] <= 2 * right + kEps) {
        dp[j] = min<int64_t>(dp[j], dp[i] + 1LL * A * (H - y[j]) + 1LL * B * (x[j] - x[i]) * (x[j] - x[i]));
      }
    }
  }
  if (dp[N - 1] == kInf) {
    cout << "impossible\n";
    return 0;
  }
  cout << dp[N - 1] << "\n";
  return 0;
}

