#include <bits/stdc++.h>
using namespace std;

const int pi = acos(-1);

struct P {
  double x, y;

  P operator+ (const P b) const { return P{x + b.x, y + b.y}; }
  P operator- (const P b) const { return P{x - b.x, y - b.y}; }
  P operator* (const double b) const { return P{x * b, y * b}; }
  P operator/ (const double b) const { return P{x / b, y / b}; }
  P unit() const { return *this / abs(); }
  double abs() const { return hypot(x, y); }
  P spin() { return P{-y, x}; }
  double angle() const { return atan2(y, x); }
};



int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, k; cin >> n >> k;
  vector<P> ps(n);
  vector<double> d(n);
  for (int i = 0; i < n; ++i) {
    cin >> ps[i].x >> ps[i].y;
    d[i] = ps[i].abs();
  }

  auto covers = [&](double r) -> int {
    // cerr << "covers " << r << endl;
    static vector<pair<double, int>> evs;
    evs.clear();
    auto add_seg = [&](double l, double r) {
      // cerr << "addseg " << l << ' ' << r << endl;
      evs.emplace_back(l, 1);
      evs.emplace_back(r, -1);
    };
    int add = 0;
    for (int i = 0; i < n; ++i) {
      if (d[i] >= r - 1e-7) continue;
      if (d[i] < 1e-7) {
        ++add;
      }
      P le = ps[i].spin().unit();
      P ri = le.spin().spin();
      double extend = sqrt(r * r - d[i] * d[i]);
      le = ps[i] + le * extend;
      ri = ps[i] + ri * extend;
      double omn = ri.angle();
      double omx = le.angle();
      if (omn > omx) {
        add_seg(omn, pi);
        add_seg(-pi, omx);
      } else {
        add_seg(omn, omx);
      }
    }

    sort(evs.begin(), evs.end());
    // for (auto [o, t] : evs) {
    //   cerr << "o t " << o << ' ' << t << endl;
    // }

    int cnt = 0, mx = 0;
    for (auto [o, t] : evs) {
      cnt += t;
      mx = max(mx, cnt);
    }

    return mx + add;
  };

  double L = 0, R = 1e7;

  while (abs(L - R) > 2e-7) {
    double M = (L + R) / 2;

    if (covers(M) >= k) R = M;
    else L = M;
  }

  // if (L > 1e6) {
  //   cout << -1 << endl;
  //   exit(0);
  // }

  cout << fixed << setprecision(12) << L / 2 << endl;
}
