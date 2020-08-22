#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double pi = acos(-1);

bool same(double a, double b) {
  return abs(a - b) < eps;
}

struct P {
  double x, y;
  P() { x = y = 0; }
  P(double x, double y) : x(x), y(y) {}
  P operator + (P b) { return P(x + b.x, y + b.y); }
  P operator - (P b) { return P(x - b.x, y - b.y); }
  P operator * (double b) { return P(x * b, y * b); }
  P operator / (double b) { return P(x / b, y / b); }
  double operator * (P b) { return x * b.x + y * b.y; }
  double operator ^ (P b) { return x * b.y - y * b.x; }
  double abs() { return hypot(x, y); }
  P unit() { return *this / abs(); }
  P spin(double o) {
    double c = cos(o), s = sin(o);
    return P(c * x - s * y, s * x + c * y);
  }
  double angle() { return atan2(y, x); }
};

struct L {
  double a, b, c;
  P pa, pb;
  L() : a(0), b(0), c(0), pa(), pb() {}
  L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
  double angle() {
    return (pb - pa).angle();
  }
};

struct C {
  P c;
  double r;
  C(P c = P(0, 0), double r = 0) : c(c), r(r) {}
};

vector<L> tangent(C c, P p) {
  vector<L> z;
  double d = (p - c.c).abs();
  if (same(d, c.r)) {
    P i = (p - c.c).spin(pi / 2);
    z.emplace_back(p, p + i);
  } else if (d > c.r) {
    double o = acos(c.r / d);
    P i = (p - c.c).unit(), j = i.spin(o) * c.r, k = i.spin(-o) * c.r;
    z.emplace_back(c.c + j, p);
    z.emplace_back(c.c + k, p);
  } 
  return z;
}

int cs[305][3], a[3], b[3];

int main() {
  freopen("garden.in", "r", stdin);
  freopen("garden.out", "w", stdout);

  int n; cin >> n;
  for (int i = 1; i <= n; ++i) cin >> cs[i][0] >> cs[i][1] >> cs[i][2];
  cin >> a[0] >> a[1] >> a[2];
  cin >> b[0] >> b[1] >> b[2];

  if (n == 0) {
    cout << "YES" << endl;
    exit(0);
  }

  while (clock() < CLOCKS_PER_SEC * 2.9) {
    double o = rand();
    double c = cos(o), s = sin(o);
    double x = a[0] + c * a[2], y = a[1] + s * a[2];
    P st(x, y);

    P targ(b[0], b[1]);
    P dir = targ - st;
    double dir_o = dir.angle();

    auto PP = [&] (P p) {
      return (p - st).spin(-dir_o);
    };

    auto Get = [&] (C c) {
      vector<L> rt = tangent(c, P(0, 0));
      if (rt.size() == 1u) {
        double o = rt[0].angle();
        double o2 = o < 0 ? o + pi : o - pi;
        if (o > o2) swap(o, o2);
        return make_pair(o, o2);
      } else if (rt.size() == 2u) {
        double o = rt[0].angle();
        double o2 = rt[1].angle();
        if (o > o2) swap(o, o2);
        if (o2 - o > pi) {
          o += pi;
          o2 -= pi;
          swap(o, o2);
        }
        return make_pair(o, o2);
      } else return make_pair((double)0, (double)0);
    };

    auto Merge = [&] (vector<pair<double, double>> v) {
      sort(v.begin(), v.end(), [&] (const auto &a, const auto &b) {
        if (same(a.first, b.first)) {
          if (same(a.second, b.second)) return false;
          return a.second < b.second;
        }
        return a.first < b.first;
      });
      vector<pair<double, double>> res;
      double l = v[0].first, r = v[0].second;
      for (int i = 1; i < (int)v.size(); ++i) {
        auto &p = v[i];
        if (p.first > r + eps) {
          res.emplace_back(l, r);
          tie(l, r) = p;
        } else {
          r = max(r, p.second);
        }
      }
      res.emplace_back(l, r);
      return res;
    };

    vector<pair<double, double>> ps;
    for (int i = 1; i <= n; ++i) {
      ps.push_back(Get(C(PP(P(cs[i][0], cs[i][1])), cs[i][2])));
    }

    auto v1 = Merge(ps);
    ps.emplace_back(Get(C(PP(P(b[0], b[1])), b[2])));
    auto v2 = Merge(ps);
    
    if (v1 != v2) {
      cout << "YES" << endl;
      exit(0);
    }
  }

  cout << "NO" << endl;
}
