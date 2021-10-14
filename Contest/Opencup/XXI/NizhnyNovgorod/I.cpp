#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, S;
  cin >> N >> S;
  vector<pair<int, int>> vec(N);
  for (int i = 0; i < N; ++i) {
    cin >> vec[i].second;
  }
  for (int i = 0; i < N; ++i) {
    cin >> vec[i].first;
  }

  auto Check = [&](int T) {
    int64_t cost = 0;
    for (int i = N - T; i < N; ++i) {
      cost += vec[i].second + 1LL * vec[i].first * (i - N + T);
    }
    vector<int> convex;
    for (int i = N - 1; i >= 0; --i) {
    }
  };

  sort(vec.rbegin(), vec.rend());
  int ans = 0;
  for (int d = 20; d >= 0; --d) {
    if (ans + (1 << d) <= N) {
      if (Check(ans + (1 << d))) {
        ans += (1 << d);
      }
    }
  }
  cout << ans << "\n";
  return 0;
}
