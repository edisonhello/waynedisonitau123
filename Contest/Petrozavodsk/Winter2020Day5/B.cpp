#include <bits/stdc++.h>
using namespace std;
#define double long double

double val[1 << 22];
vector<int> o;
vector<double> x;
vector<double> y;

int main() {
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  for (int mask = 2; mask < (1 << n); ++mask) {
    o.clear();
    int nn = __builtin_popcount(mask);
    for (int i = 0; i < n; ++i) if (mask & (1 << i)) o.push_back(i);

    if (nn == 1) continue;

    x.resize(nn);
    y.resize(nn);
    for (int i = 0; i < nn; ++i) {
      x[i] = val[mask ^ (1 << o[i])];
      y[i] = a[o[i]];
    }

    if (nn > 10) {
      bool same = 1;
      for (int i = 1; i < nn; ++i) {
        if (a[o[i - 1]] != a[o[i]]) same = 0;
      }

      if (same) { val[mask] = a[o[0]]; continue; }
    }

    double zu = 1, zd = 0;
    for (int i = 0; i < nn; ++i) if (x[i] < y[i]) {
      zu += y[i] / (x[i] - y[i]);
      zd += 1 / (x[i] - y[i]);
    }
    double z = zu / zd;

    while (true) {
      double nzu = 1, nzd = 0;
      for (int i = 0; i < nn; ++i) if (x[i] < y[i] && y[i] > z) {
        nzu += y[i] / (x[i] - y[i]);
        nzd += 1 / (x[i] - y[i]);
      }
      double nz = nzu / nzd;

      if (abs(nz - z) < 1e-9) break;
      z = nz;

      // cerr << "x = ";
      // for (double i : x) cerr << i << ' ';
      // cerr << endl;
      // cerr << "y = ";
      // for (double i : y) cerr << i << ' ';
      // cerr << endl;
      // cerr << "z = " << z << " = " << nzu << " / " << nzd << endl;
    }

    val[mask] = z;
  }

  cout << fixed << setprecision(12);
  cout << val[(1 << n) - 1] << '\n';
}
