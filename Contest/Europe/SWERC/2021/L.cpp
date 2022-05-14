#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, v;
  cin >> N >> v;
  vector<int> t(N), a(N);
  for (int i = 0; i < N; ++i) {
    cin >> t[i];
  }
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
  }
  vector<int64_t> x(N), y(N);
  for (int i = 0; i < N; ++i) {
    x[i] = 1LL * t[i] * v - a[i];
    y[i] = 1LL * t[i] * v + a[i];
  }
  vector<int> order(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return make_pair(x[i], t[i]) < make_pair(x[j], t[j]);
  });
  vector<int64_t> ds = y;
  sort(ds.begin(), ds.end());
  ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

  vector<int> fw(N + 1, -1);

  auto Update = [&](int p, int v) {
    for (int i = p + 1; i <= N; i += i & -i) {
      fw[i] = max(fw[i], v);
    }
  };

  auto Query = [&](int p) {
    int res = -1;
    for (int i = p + 1; i > 0; i -= i & -i) {
      res = max(res, fw[i]);
    }
    return res;
  };
  int ans = 0;
  for (int u : order) {
    int p = lower_bound(ds.begin(), ds.end(), y[u]) - ds.begin();
    int d = (1LL * t[u] * v >= abs(a[u]));
    d = max(d, Query(p) + 1);
    if (d > 0) {
      Update(p, d);
    }
    ans = max(ans, d);
  }
  cout << ans << "\n";
}

