#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double pi = acos(-1);

int sign(double x) {
  return x < -eps ? -1 : x > eps ? 1 : 0;
}

struct P {
  double x, y;
  P() = default;
  P(double x, double y) : x(x), y(y) {}
  P operator+(const P &b) const { return P(x + b.x, y + b.y); }
  P operator-(const P &b) const { return P(x - b.x, y - b.y); }
  P operator*(const double b) const { return P(x * b, y * b); }
  double operator^(const P &b) const { return x * b.y - y * b.x; }
  P spin(double o) const {
    double c = cos(o), s = sin(o);
    return P(c * x - s * y, s * x + c * y);
  }
  double abs() const { return hypot(x, y); }
};

ostream& operator<<(ostream &o, const P &b) {
  return o << "(" << b.x << ", " << b.y << ")";
}

void solve() {
  P p1, p2, p3;
  cin >> p1.x >> p1.y;
  cin >> p2.x >> p2.y;
  cin >> p3.x >> p3.y;
  P dir = p2 - p1;
  double d = dir.abs();
  double o = acos(2 / d);
  P d1 = dir.spin(-o);
  P d2 = dir.spin(o);
  double d23 = (p3 - p2).abs();
  double o2 = acos(2 / d23);
  P dir23 = p3 - p2;
  double invo2 = pi / 2 - o2;
  P tan1 = dir23.spin(invo2);
  P tan2 = dir23.spin(-invo2);
  int cut = 5;
  for (int i = 0; i <= cut; ++i) {
    P chk = tan1 * i + tan2 * (cut - i);
    if (sign(d1 ^ chk) > 0 && sign(chk ^ d2) > 0) {
      cout << "yes" << '\n';
      return;
    }
  }
  cout << "no" << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t; while (t--) solve();
}

