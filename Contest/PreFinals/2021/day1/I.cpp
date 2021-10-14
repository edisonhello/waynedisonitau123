#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<int> c(N);
    for (int i = 0; i < N; ++i) cin >> c[i];
    int V = c.back() * 2;
    vector<int> dp(V + 1, V + 1);
    dp[0] = 0;
    for (int i = 1; i <= V; ++i) {
      for (int u : c) if (i >= u) dp[i] = min(dp[i], dp[i - u] + 1);
    }
    vector<int> greedy(V + 1);
    for (int i = 1; i <= V; ++i) {
      int p = upper_bound(c.begin(), c.end(), i) - c.begin();
      assert(p > 0);
      greedy[i] = greedy[i - c[p - 1]] + 1;
    }
    bool ok = true;
    for (int i = 1; i <= V; ++i) ok &= greedy[i] == dp[i];
    cout << (ok ? "OK" : "WA") << "\n";
  }
}
