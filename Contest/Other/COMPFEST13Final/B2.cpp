#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

struct P {
  double x, y;

  P operator+ (const P b) const { return P{x + b.x, y + b.y}; }
  P operator- (const P b) const { return P{x - b.x, y - b.y}; }
  P operator* (const double b) const { return P{x * b, y * b}; }
  P operator/ (const double b) const { return P{x / b, y / b}; }
  double abs() const { return hypot(x, y); }
  double angle() const { return atan2(y, x); }
  P spin() const { return P{-y, x}; }
  P unit() const { return *this / abs(); }
};

int main() {
  int n, k; cin >> n >> k;
  vector<P> ps(n);
  for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;

  auto cover = [&](double r) {
    // cerr << "R = " <<r << endl;
    static vector<pair<double, int>> evs;
    evs.clear();
    for (int i = 0; i < n; ++i) {
      // cerr << "i = " << i << " abs " << ps[i].abs() << endl;
      if (ps[i].abs() < 1e-9) evs.emplace_back(-1000, 1);
      else {
        if (ps[i].abs() >= r - 1e-9) {
          // cerr << "abs " << ps[i].abs() << " skipped" << endl;
          continue;
        }

        double dd = sqrt(r * r - ps[i].abs() * ps[i].abs());
        P le = ps[i] + ps[i].spin().unit() * dd;
        P ri = ps[i] + ps[i].spin().spin().spin().unit() * dd;

        double o1 = ri.angle();
        double o2 = le.angle();
        if (o1 <= o2) {
          evs.emplace_back(o1, 1);
          evs.emplace_back(o2, -1);
        } else {
          evs.emplace_back(o1, 1);
          evs.emplace_back(pi, -1);
          evs.emplace_back(-pi, 1);
          evs.emplace_back(o2, -1);
        }
      }
    }

    sort(evs.begin(), evs.end());
    // for (auto [p, t] : evs) {
    //   cerr << "p t " << p << ' ' << t << endl;
    // }

    int now = 0, mx = 0;
    for (auto [o, t] : evs) {
      now += t;
      mx = max(mx, now);
    }

    return mx;
  };

  double L = 0, R = 1e9;
  for (int i = 0; i < 100; ++i) {
    double M = (L + R) / 2;

    if (cover(M) < k) L = M;
    else R = M;
  }

  cout << fixed << setprecision(12) << L / 2 << endl;
}
