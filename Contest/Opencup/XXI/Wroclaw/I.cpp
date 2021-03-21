#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  constexpr int kC = 1'000'000;
  vector<vector<int>> dv(kC + 1);
  for (int i = 1; i <= kC; ++i) {
    for (int j = i + i; j <= kC; j += i) dv[j].push_back(i);
  }
  vector<pair<int, int>> pr;
  for (int i = 1; i <= kC; ++i) {
    for (int d : dv[i]) {
      int j = i - d;
      if (__gcd(i, j) == (i ^ j)) pr.emplace_back(i, j);
    }
  }
  vector<int> buf(kC + 1);
  while (T--) {
    int N;
    cin >> N;
    fill(buf.begin(), buf.end(), 0);
    for (int i = 0; i < N; ++i) {
      int x;
      cin >> x;
      buf[x]++;
    }
    int64_t ans = 0;
    for (auto [u, v] : pr) ans += 1LL * buf[u] * buf[v];
    cout << ans << "\n";
  }
  return 0;
}
