#include <bits/stdc++.h>
using namespace std;

pair<double, double> ps[3333];
double lfac[3333];

double cross(pair<double, double> &a, pair<double, double> &b) {
  return a.first * b.second - a.second * b.first;
}

double lgC(int n, int k) {
  return lfac[n] - lfac[k] - lfac[n - k];
}

int main() {
  int n, k; cin >> n >> k;

  for (int i = 0; i < n; ++i) {
    cin >> ps[i].first >> ps[i].second;
  }

  for (int i = 2; i <= 3330; ++i) lfac[i] = lfac[i - 1] + log(i);

  double ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        int d = (i - j - 1 + n) % n;
        if (d < k - 2) continue;
        double x = exp(lgC(d, k - 2) - lgC(n, k));
        double crx = cross(ps[i], ps[j]);
        // cerr << "i j d x crx " << i << ' ' << j << ' ' << d << ' ' << x << ' ' << crx << endl;
        ans += crx * x;
      }
    }
  }

  ans /= -2;

  cout << fixed << setprecision(12);
  cout << ans << endl;

}
