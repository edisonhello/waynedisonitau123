#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  vector<int> x(n);
  vector<double> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> x[i] >> v[i];
  }
  double bound = 1e18;
  for (int i = n - 1; i >= 0; --i) {
    double vv = sqrt(bound - 2LL * b * x[i]);
    v[i] = min(v[i], vv);
    bound = min(bound, 2LL * b * x[i] + v[i] * v[i]);
  }
  double px = 0;
  double pv = 0;
  double ans = 0.0;
  for (int i = 0; i < n; ++i) {
    double dist = x[i] - px;
    double l = 0.0, r = 1e9;
    for (int it = 0; it < 80; ++it) {
      double mid = 0.5 * (l + r);
      double vd = pv + mid * a;
      if ((vd + pv) * mid / 2 > dist) {
        r = mid;
        continue;
      }
      double d = dist - (vd + pv) * mid / 2;
      if (vd <= v[i]) {
        l = mid;
        continue;
      }
      double need = (vd - v[i]) / b;
      double e = (vd + v[i]) * need / 2;
      if (e <= d) l = mid;
      else r = mid;
    }
    px = x[i];
    double vd = pv + l * a;
    double d = dist - (vd + pv) * l / 2;
    if (vd <= v[i]) {
      pv = vd;
      ans += l;
    } else {
      double nd = (vd - v[i]) / b;
      double e = (vd + v[i]) * nd / 2;
      pv = v[i];
      ans += l + nd + (d - e) / vd;
    }
  }
  cout << fixed << setprecision(20) << ans << "\n";
  return 0;
}
