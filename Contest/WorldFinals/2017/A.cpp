#include <bits/stdc++.h>
using namespace std;
#define double long double

const double eps = 1e-14;

int sign(double x) {
  if (x < -eps) return -1;
  if (x > eps) return 1;
  return 0;
}

bool same(double x, double y) {
  return abs(x - y) < eps;
}

struct P {
  double x, y;

  P() : x(0), y(0) {}
  P(double x, double y) : x(x), y(y) {}

  P operator- (const P b) const { return P{x - b.x, y - b.y}; }
  P operator/ (double b) const { return P{x / b, y / b}; }
  double operator* (const P b) const { return x * b.x + y * b.y; }
  double operator^ (const P b) const { return x * b.y - y * b.x; }
  double abs() { return hypot(x, y); }
  P unit() { return *this / abs(); }
  bool operator< (const P &b) const { return same(x, b.x) ? same(y, b.y) ? 0 : y < b.y : x < b.x; }
};

ostream& operator<< (ostream &o, P p) {
  return o << "(" << p.x << "," << p.y << ")";
}

struct L {
  double a, b, c;
  P pa, pb;
  L (P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
  // P project
  double get_ratio(P p) { return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs()); }
  bool inside(P p) {
    double z = get_ratio(p);
    return -eps <= z && z <= 1 + eps;
  }
};

bool SegmentIntersect(P p1, P p2, P p3, P p4) {
  if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x)) return false;
  if (max(p1.y, p2.y) < min(p3.y, p4.y) || max(p3.y, p4.y) < min(p1.y, p2.y)) return false;
  return sign((p3 - p1) ^ (p4 - p1)) * sign((p3 - p2) ^ (p4 - p2)) <= 0 &&
    sign((p1 - p3) ^ (p2 - p3)) * sign((p1 - p4) ^ (p2 - p4)) <= 0;
}

P Intersect(L x, L y) {
  return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a);
}

bool parallel(L x, L y) { return same(x.a * y.b, x.b * y.a); }

int main() {
  int n; cin >> n;

  vector<P> ps(n);
  for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;

  double mx = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      L l(ps[i], ps[j]);
      P dd = (ps[j] - ps[i]).unit();

      vector<pair<P, int>> allp;
      for (int k = 0; k < n; ++k) {
        int kk = (k + 1) % n;
        L ll(ps[k], ps[kk]);
        if (parallel(l, ll)) continue;
        P pp = Intersect(l, ll);
        if (ll.inside(pp)) {
          allp.emplace_back(pp, k);
        }
      }

      sort(allp.begin(), allp.end());

      //for (auto p : allp) {
      //  cout << p.first << endl;
      //}
      //vector<pair<P, int>> tmpp;
      //for (auto p : allp) {
      //  if (tmpp.size() && same((tmpp.back().first - p.first).abs(), 0)) {
      //    tmpp.pop_back();
      //  } else {
      //    tmpp.push_back(p);
      //  }
      //}
      //allp = tmpp;
      //for (auto p : allp) {
      //  cout << "-> " << p.first << endl;
      //}

      P prevp;
      bool first = 0;
      double curlen = 0;
      int in_pos = 0, in_neg = 0;
      vector<pair<double, int>> events;
      for (auto [cp, k] : allp) {
        int kk = (k + 1) % n;

        double v1 = dd ^ (ps[k] - ps[i]).unit();
        double v2 = dd ^ (ps[kk] - ps[i]).unit();

        int update_pos = sign(v1) == 1 || sign(v2) == 1;
        int update_neg = sign(v1) == -1 || sign(v2) == -1;

        if (first) {
          curlen = (cp - prevp).abs();
        } else {
          first = 1;
          prevp = cp;
        }

        // in_pos ^= update_pos;
        // in_neg ^= update_neg;

        events.emplace_back(curlen, (update_pos << 1) | update_neg);
      }

      sort(events.begin(), events.end());

      int state = 0;
      double start = -1000;
      double prev = -100;
      for (auto [cur, change] : events) {
        if (!same(cur, prev)) {
          if (state) {
            // cerr << "cur start " << cur << ' ' << start << endl;
            mx = max(mx, cur - start);
          }
        }

        state ^= change;
        if (state == change) start = cur;

        prev = cur;
      }
    }
  }

  cout << fixed << setprecision(10) << mx << endl;

}

