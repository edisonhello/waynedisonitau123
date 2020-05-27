#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, k;
  int64_t t;
  cin >> n >> k >> t;
  vector<int> x(n);
  for (int i = 0; i < n; ++i) cin >> x[i];

  auto Transform = [&](vector<int> x, int64_t t) {
    vector<int> y(n);
    vector<int> to(n);
    for (int i = 0; i < n; ++i) {
      to[i] = (i + t) % n;
    }
    vector<bool> vis(n);
    for (int i = 0; i < n; ++i) {
      if (vis[i]) continue;
      vector<int> cycle;
      int base = 0;
      for (int j = i; !vis[j]; j = to[j]) {
        vis[j] = true;
        cycle.push_back(j);
        base ^= x[j];
      }
      int g = cycle.size();
      if ((k / g) % 2 == 0) base = 0;
      for (int j = 0; j < g; ++j) cycle.push_back(cycle[j]);
      int z = k % g;
      int sum = 0;
      for (int j = 0; j < z; ++j) sum ^= x[cycle[j]];
      for (int j = 0; j < g; ++j) {
        y[cycle[j]] = base ^ sum;
        sum ^= x[cycle[j]];
        sum ^= x[cycle[j + z]];
      }
    }
    // for (int i = 0; i < n; ++i) {
      // for (int j = 0; j < k; ++j) {
        // y[i] ^= x[(i + j * t) % n];
      // }
    // }
    return y;
  };

  for (int bit = 60; bit >= 0; --bit) {
    if (t >> bit & 1) {
      x = Transform(x, (1LL << bit));
    }
  }
  for (int i = 0; i < n; ++i) cout << x[i] << " ";
  cout << "\n";
  return 0;
}
