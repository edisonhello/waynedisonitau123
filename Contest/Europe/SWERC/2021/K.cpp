#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

struct P {
  double x, y;
  P() : x(0), y(0) {}
  P(double x, double y) : x(x), y(y) {}
  P operator+ (const P &b) { return P(x + b.x, y + b.y); }
  P operator- (const P &b) { return P(x - b.x, y - b.y); }
  P operator* (const double b) const { return P{x * b, y * b}; }
  P operator/ (const double b) const { return P{x / b, y / b}; }
  double operator*(const P &b) const { return x * b.x + y * b.y; }
  double operator^(const P &b) const { return x * b.y - y * b.x; }
  P spin(double o) const {
    double c = cos(o), s = sin(o);
    return P(c * x - s * y, s * x + c * y); 
  }
  double abs() const { return hypot(x, y); }
};

double angle(const P &b, const P &a) {
  return acos(a * b / (a.abs() * b.abs()));
}

double calc_val(P a, P b, P p) {
  double o = angle(a - p, b - p);
  if (o > 2 * pi / 3) return (a - p).abs() + (b - p).abs();
  P dir = (b - a);
  P d1 = dir.spin(pi / 3) + a;
  P d2 = dir.spin(-pi / 3) + a;
  return max((d1 - p).abs(), (d2 - p).abs());
}

double calc_val(const P &a, const P &b, const P &c, const P &p) {
  return max(max(calc_val(a, b, p),
        calc_val(a, c, p)),
      calc_val(b, c, p));
}

int main() {
  // cout << calc_val(P(-1, 0), P(1, 0), P(0, 0)) << endl;

  P a, b, c;
  cin >> a.x >> a.y;
  cin >> b.x >> b.y;
  cin >> c.x >> c.y;

  P ab = a - b;
  P ac = a - c;
  P bc = b - c;
  vector<double> len{ab.abs(), ac.abs(), bc.abs()};
  sort(len.begin(), len.end());
  if (len[2] * len[2] + 0.0000002 >= len[0] * len[0] + len[1] * len[1]) {
    cout << fixed << setprecision(12);
    cout << len[2] << endl;
    exit(0);
  }

  auto Check = [&](double x) {
    double l = -1e6, r = 1e6;
    for (int iter = 0; iter < 200; ++iter) {
      double ml = l + (r - l) / 3;
      double mr = r - (r - l) / 3;
      if (calc_val(a, b, c, P(x, ml)) > calc_val(a, b, c, P(x, mr))) {
        l = ml;
      } else {
        r = mr;
      }
    }
    return calc_val(a, b, c, P(x, l));
  };

  double l = -1e6, r = 1e6;
  for (int iter = 0; iter < 200; ++iter) {
    double ml = l + (r - l) / 3;
    double mr = r - (r - l) / 3;
    if (Check(ml) > Check(mr)) {
      l = ml;
    } else {
      r = mr;
    }
  }
  // cout << "p = " << p.x << ' ' << p.y << endl;

  cout << fixed << setprecision(12);
  cout << Check(l) << endl;
}

