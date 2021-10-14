#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

struct P {
  double x, y;
  P() = default;
  P(double x, double y) : x(x), y(y) {}
  P operator+ (const P b) { return P{x + b.x, y + b.y}; }
  P operator- (const P b) { return P{x - b.x, y - b.y}; }
  double operator* (const P b) { return x * b.x + y * b.y; }
  double operator^ (const P b) { return x * b.y - y * b.x; }
  P operator* (const double b) { return P{x * b, y * b}; }
  P operator/ (const double b) { return P{x / b, y / b}; }
  bool operator== (const P b) { return x == b.x && y == b.y; }

  double abs() { return hypot(x, y); }
  P dir() {
    return unit();
    // int g = ::abs(__gcd(x, y));
    // return P{x / g, y / g};
  }
  P unit() { return P{x, y} / abs(); }
};

struct C {
  P p;
  int r;
};

struct L {
  int a, b;
  long long c;
  P pa, pb;
  L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
  double abs() { return hypot(a, b); }
  P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
  double get_ratio(P p) { return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs()); }
};

P city[2005];
C hill[2005];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, h; cin >> n >> h;
  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    city[i] = P{x, y};
  }

  for (int i = 0; i < h; ++i) {
    int x, y, r; cin >> x >> y >> r;
    hill[i] = C{P{x, y}, r};
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      // cerr << "i j " << i << ' ' << j << endl;
      bool block = false;
      L l(city[i], city[j]);
      P dir = city[j] - city[i];

      for (int k = 0; k < h; ++k) {
        P lp = l.project(hill[k].p);
        double r = l.get_ratio(lp);

        double dist = 1e20;
        if (0 <= r && r <= 1) dist = (lp - hill[k].p).abs();
        else dist = min((hill[k].p - city[i]).abs(), (hill[k].p - city[j]).abs());

        if (dist - eps <= hill[k].r) {
          block = true;
          // cerr << "block by hill " << k << endl;
        }
      }

      for (int k = 0; k < n; ++k) if (k != i && k != j) {
        P dir2 = city[k] - city[i];
        if (dir.dir() == dir2.dir() && dir2.abs() < dir.abs()) {
          block = true;
          // cerr << "block by city " << k << endl;
        }
      }

      if (!block) {
        cout << i << ' ' << j << endl;
      }
    }
  }
}
