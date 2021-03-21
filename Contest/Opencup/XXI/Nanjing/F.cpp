#include <bits/stdc++.h>
using namespace std;

double pw(double b, int n) {
  double a = 1;
  while (n) {
    if (n & 1) a = a * b;
    b = b * b; n >>= 1;
  }
  return a;
}

double solve() {
  int n, m, p; cin >> n >> m >> p;
  double x = (double)p / 10000;

  double mn = 1e20;
  long long lb = 1, rb = 1000000000;

  auto calc = [&] (int t) -> double {
    return (double)(1ll * t * n + m) / (1 - pw(1 - x, t));
  };


  while (rb - lb > 5) {
    int m1 = (lb + rb) / 2;
    int m2 = m1 + 1;
    double a1 = calc(m1);
    double a2 = calc(m2);
    if (a1 < a2) rb = m2;
    else lb = m1;
    mn = min(mn, min(a1, a2));
  }
  // cerr << "lb rb: " << lb << ' ' << rb << endl;

  for (int i = lb; i <= rb; ++i) {
    mn = min(mn, calc(i));
  }

  return mn;
}

int main() {
  int t; cin >> t; while (t--) {
    double ans = solve();
    cout << fixed << setprecision(10) << ans << '\n';
  }
}
