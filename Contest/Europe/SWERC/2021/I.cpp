#include <bits/stdc++.h>
using namespace std;
#define int int64_t


int32_t main() {
  int n, m; cin >> n >> m;
  vector<int> p(n), pp(n);
  for (int i = 0; i < n; ++i) cin >> p[i];
  pp[0] = p[0];
  for (int i = 1; i < n; ++i) pp[i] = pp[i - 1] + p[i];
  vector<int> x(m);
  for (int i = 0; i < m; ++i) cin >> x[i];

  sort(x.begin(), x.end());

  auto rangesum = [&](int l, int r) -> int {
    // cout << "q range sum " << l << ' ' << r << endl;
    if (r < l) return (int)0;
    if (l == r) {
      if (l < p.size()) return p[l];
      return (int)0;
    }
    return (r >= pp.size() ? pp.back() : pp[r]) - (l ? (l >= pp.size() ? pp.back() : pp[l - 1]) : 0);
  };

  int mx = 0;

  auto update = [&](int x) { mx = max(mx, x); }; 

  if (x[0] > 0)
    update(rangesum(0, (x[0] - 1) / 100));

  if (x.back() < (n - 1) * 100)
    update(rangesum(x.back() / 100 + 1, n - 1));

  for (int i = 1; i < m; ++i) {
    int x0 = x[i - 1];
    int x1 = x[i];
    int len = (x1 - x0) / 2;
    int cnt = len / 100 + 1;

    int fi = x0 / 100 + 1;
    int la = (x1 - 1) / 100;
    int fir = fi + cnt - 1;

    while (fir <= la) {
      update(rangesum(fi, fir));
      ++fi, ++fir;
    }
  }

  cout << mx << endl;

}

