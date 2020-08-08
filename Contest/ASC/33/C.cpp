#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-12;
bool same(double a, double b) {
  return abs(a - b) < eps;
}

struct P {
  double x, y;
  P() : x(0), y(0) {}
  P(double x, double y) : x(x), y(y) {}
};

P operator+ (const P &a, const P &b) {
  return P(a.x + b.x, a.y + b.y);
}
P operator- (const P &a, const P &b) {
  return P(a.x - b.x, a.y - b.y);
}
P operator/ (const P &a, const double b) {
  return P(a.x / b, a.y / b);
}

double operator^ (const P &a, const P &b) {
  return a.x * b.y - a.y * b.x;
}

struct L {
  double a, b, c;
  P pa, pb;
  L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) { 
    if (same(c, 0)) {
      if (same(b, 0)) {
        a = 1;
      } else {
        a /= b;
        b /= b;
        if (a < 0) a *= -1, b *= -1;
      }
    } else {
      a /= c;
      b /= c;
      c /= c;
      if (a < 0) a *= -1, b *= -1, c *= -1;
    }
  }
};

bool Parallel(L x, L y) {
  return same(x.a * y.b, x.b * y.a);
}

P Intersect(L x, L y) {
  return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a); 
}

P ps[150];

int main() {
  freopen("center.in", "r", stdin);
  freopen("center.out", "w", stdout);


  int n; cin >> n;
  n *= 2;
  
  set<pair<int, int>> exist;
  for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;
  for (int i = 0; i < n; ++i) {
    exist.insert(make_pair(round(ps[i].x), round(ps[i].y)));
  }

  set<pair<double, double>> anss;
  for (int i = 1; i < n; ++i) {
    // 0, i
    for (int j = 1; j < n; ++j) if (j != i) {
      for (int k = 2; k < n; ++k) if (k != j && k != i) {
        // j, k
        if (Parallel(L(ps[0], ps[i]), L(ps[j], ps[k]))) continue;
        P px = Intersect(L(ps[0], ps[i]), L(ps[j], ps[k]));
        // cerr << "px " << px.x << ' ' << px.y << endl;
        bool yes = 1;
        vector<tuple<double, double, double>> ls;
        for (int l = 0; l < n; ++l) {
          L li(ps[l], px);
          ls.emplace_back(li.a, li.b, li.c);
          // P op = px + px - ps[l];
          // if (abs(op.x - round(op.x)) > 1e-10) yes = 0;
          // if (abs(op.y - round(op.y)) > 1e-10) yes = 0;
          // if (!exist.count(make_pair(round(op.x), round(op.y)))) yes = 0;
        }
        sort(ls.begin(), ls.end(), [&] (const auto &a, const auto &b) -> bool {
          double q, w, e, r, t, y;
          tie(q, w, e) = a; tie(r, t, y) = b;
          if (same(q, r)) {
            if (same(w, t)) return same(e, y) ? 0 : e < y;
            else return w < t;
          } else return q < r;
        });

        for (int i = 0; i < (int)ls.size(); i += 2) {
          double q, w, e, r, t, y;
          // cerr << "i q w e r t y " << i << ' ' << q << ' ' << w << ' ' << e << ' ' << r << ' ' << t << ' ' << y << endl;
          tie(q, w, e) = ls[i]; tie(r, t, y) = ls[i + 1];
          if (!(same(q, r) && same(w, t) && same(e, y))) yes = 0;
          if (i) {
            double z, x, c; tie(z, x, c) = ls[i - 1];
            if (same(z, q) && same(x, w) && same(c, e)) yes = 0;
          }
        }
        if (yes) anss.insert(make_pair(px.x, px.y));
      }
      break;
    }
  }

  cout << fixed << setprecision(12);
  if (anss.size() == 0u) cout << "Impossible" << endl;
  else if (anss.size() == 1u) cout << "Center of the universe found at (" << anss.begin()->first << ", " << anss.begin()->second << ")" << endl;
  else cout << "Ambiguity" << endl;
}
