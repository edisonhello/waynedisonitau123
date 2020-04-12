#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  vector<int> p(n);
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
    p[i]--;
  }

  vector<int64_t> fc(n + 1, 1);
  for (int i = 1; i <= n; ++i) fc[i] = fc[i - 1] * i;

  vector<int64_t> f(n + 1);

  auto Dfs = [&](auto self, int p, vector<int> v, int s) {
    if (p == n + 1) {
      if (s != n) return;
      int64_t ways = fc[n];
      map<int, int> cnt;
      for (int u : v) {
        ways /= u;
        cnt[u]++;
      }
      for (auto it : cnt) ways /= fc[it.second];
      f[n - v.size()] += ways;
      return;
    }
    while (s <= n) {
      self(self, p + 1, v, s);
      v.push_back(p);
      s += p;
    }
  };

  Dfs(Dfs, 1, vector<int>(), 0);
  vector<bool> vis(n);
  int cyc = 0;
  for (int i = 0; i < n; ++i) {
    if (vis[p[i]]) continue;
    for (int j = p[i]; !vis[j]; j = p[j]) vis[j] = true;
    cyc += 1;
  }
  double ans = a * (n - cyc);
  int64_t ways = fc[n] - 1;
  double h = 0.0;
  for (int x = 1; x < n; ++x) {
    double p = 1.0 * ways / fc[n];
    double e = (b + h) / (1 - p);
    h += x * (1.0 * f[x] / fc[n]) * a;
    ans = min(ans, e);
    ways -= f[x];
  }
  cout << fixed << setprecision(20) << ans << "\n";
  return 0;
}
