#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <deque>
#include <iomanip>
using namespace std;

const double eps = 1e-9;

int64_t sign(int64_t x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}

bool same(double x, double y) {
  return abs(x - y) < eps;
}

struct P {
  double x, y;
  P() : x(0), y(0) {}
  P(double x, double y) : x(x), y(y) {}
  P operator+(P b) const { return P(x + b.x, y + b.y); }
  P operator-(P b) const { return P(x - b.x, y - b.y); }
  P operator*(double b) const { return P(x * b, y * b); }
  P operator/(double b) const { return P(x / b, y / b); }
  double operator*(P b) const { return x * b.x + y * b.y; }
  double operator^(P b) const { return x * b.y - y * b.x; }
  double abs() const { return hypot(x, y); }
};

struct PI {
  int64_t x, y;
  PI() : x(0), y(0) {}
  PI(int64_t x, int64_t y) : x(x), y(y) {}
  PI operator+(PI b) const { return PI(x + b.x, y + b.y); }
  PI operator-(PI b) const { return PI(x - b.x, y - b.y); }
  PI operator*(int64_t b) const { return PI(x * b, y * b); }
  PI operator/(int64_t b) const { return PI(x / b, y / b); }
  int64_t operator*(PI b) const { return x * b.x + y * b.y; }
  int64_t operator^(PI b) const { return x * b.y - y * b.x; }
  double abs() const { return hypot(x, y); }
};

ostream& operator<<(ostream &o, const P &p) {
  return o << "(" << p.x << ", " << p.y << ")";
}

struct L {
  double a, b, c, o;
  P pa, pb;
  L() : a(0), b(0), c(0), o(0), pa(), pb() {}
  L(P pa, P pb)
      : a(pa.y - pb.y),
        b(pb.x - pa.x),
        c(pa ^ pb),
        o(atan2(-a, b)),
        pa(pa),
        pb(pb) {}

  double get_ratio(P p) const { return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs()); }
};

P Intersect(L x, L y) { return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a);  }

bool jizz(L l1, L l2, L l3) {
  P p = Intersect(l2, l3);
  return ((l1.pb - l1.pa) ^ (p - l1.pa)) < -eps;
}

bool cmp(const L &a, const L &b) {
  return same(a.o, b.o) ? (((b.pb - b.pa) ^ (a.pb - b.pa)) > eps): a.o < b.o; 
}

vector<P> HPI(vector<L> &ls) {
  // cout << "ls: " << endl;
  // for (auto l : ls) {
  //   cout << l.pa << " -> " << l.pb << endl;
  // }

  sort(ls.begin(), ls.end(), cmp);

  // cout << "after sort ";
  // for (auto l : ls) {
  //   cout << l.pa << " -> " << l.pb << endl;
  // }

  vector<L> pls(1, ls[0]);
  for (int i = 0; i < (int)ls.size(); ++i) if (!same(ls[i].o, pls.back().o)) pls.push_back(ls[i]);

  // cout << "pls inclu ";
  // for (auto l : pls) {
  //   cout << l.pa << " -> " << l.pb << endl;
  // }

  deque<int> dq; dq.push_back(0); dq.push_back(1);
#define meow(a, b, c) while (dq.size() > 1u && jizz(pls[a], pls[b], pls[c]))
  for (int i = 2; i < (int)pls.size(); ++i) {
    meow(i, dq.back(), dq[dq.size() - 2]) dq.pop_back();
    meow(i, dq[0], dq[1]) dq.pop_front();
    dq.push_back(i);
  }
  meow(dq.front(), dq.back(), dq[dq.size() - 2]) dq.pop_back();
  meow(dq.back(), dq[0], dq[1]) dq.pop_front();

  // cout << "dq: ";
  // for (int i : dq) cout << i << ' ';
  // cout << endl;

  // cout << "lines: " << endl;
  // for (int i : dq) {
  //   cout << pls[i].pa << " <-> " << pls[i].pb << endl;
  // }

  if (dq.size() < 3u) return vector<P>();

  vector<P> rt;
  for (int i = 0; i < (int)dq.size(); ++i) rt.push_back(Intersect(pls[dq[i]], pls[dq[(i + 1) % dq.size()]]));
  return rt;
}

vector<L> solve(P p0, P p1, P p2) {
  P d1 = p1 - p0;
  P d2 = p2 - p0;
  if ((d1 ^ d2) < 0) {
    swap(p1, p2);
  }

  // cout << "p0 1 2 " << p0 << ' ' << p1 << ' ' << p2 << endl;
  return vector<L>{L(p0, p1), L(p2, p0), L(p2, p1)};
}

bool parallel(PI p1, PI p2) {
  return (p1 ^ p2) == 0;
}

bool SegmentIntersect(PI p1, PI p2, PI p3, PI p4) {
  if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x)) return false;
  if (max(p1.y, p2.y) < min(p3.y, p4.y) || max(p3.y, p4.y) < min(p1.y, p2.y)) return false;
  return sign((p3 - p1) ^ (p4 - p1)) * sign((p3 - p2) ^ (p4 - p2)) <= 0 &&
    sign((p1 - p3) ^ (p2 - p3)) * sign((p1 - p4) ^ (p2 - p4)) <= 0;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  for (int T = 1; T <= t; ++T) {
    cout << "Case " << T << ": ";

    vector<L> ls;
    PI p1, p2, p3, p4;
    cin >> p1.x >> p1.y;
    cin >> p2.x >> p2.y;
    cin >> p3.x >> p3.y;
    cin >> p4.x >> p4.y;

    ls.emplace_back(P(p1.x, p1.y), P(p2.x, p2.y));
    ls.emplace_back(P(p3.x, p3.y), P(p4.x, p4.y));

    if (parallel(p2 - p1, p4 - p3)) {
      if (SegmentIntersect(p1, p2, p3, p4)) {
        cout << 0 << '\n';
        continue;
      }

      if (((p3 - p1) ^ (p4 - p1)) == 0) {
        cout << 0 << '\n';
        continue;
      }
    } else if (SegmentIntersect(p1, p2, p3, p4)) {
      P itx = Intersect(ls[0], ls[1]);

      double rt1 = ls[0].get_ratio(itx);
      double rt2 = ls[1].get_ratio(itx);

      bool mid1 = eps <= rt1 and rt1 <= 1 - eps;
      bool mid2 = eps <= rt2 and rt2 <= 1 - eps;

      if (mid1 && mid2) {
        cout << 0 << '\n';
        continue;
      }

      if (!mid1 && !mid2) {
        cout << "inf" << '\n';
        continue;
      }

      if (!mid1 && mid2) {
        cout << 0 << '\n';
        continue;
      }

      cout << "inf" << '\n';
      continue;
    }

    vector<L> hpls;

    for (auto L : solve(ls[1].pa, ls[0].pa, ls[0].pb)) {
      hpls.emplace_back(L);
    }

    for (auto L : solve(ls[1].pb, ls[0].pa, ls[0].pb)) {
      hpls.emplace_back(L);
    }

    hpls.emplace_back(P(-10000000, -10000000), P(10000000, -10000000));
    hpls.emplace_back(P(10000000, -10000000), P(10000000, 10000000));
    hpls.emplace_back(P(10000000, 10000000), P(-10000000, 10000000));
    hpls.emplace_back(P(-10000000, 10000000), P(-10000000, -10000000));

    auto res = HPI(hpls);

    // cout << "hpi: ";
    // for (auto p : res) cout << p << ' ';
    // cout << endl;

    if (res.size() == 0u) {
      cout << -1 << '\n';
    } else {
      double sum = 0;
      bool infi = false;
      for (int i = 0; i < (int)res.size(); ++i) {
        int j = (i + 1) % res.size();

        sum += res[i] ^ res[j];

        if (same(abs(res[i].x), 10000000) || same(abs(res[i].y), 10000000)) infi = true;
      }

      if (infi) {
        cout << "inf" << '\n';
        continue;
      }

      cout << fixed << setprecision(12);
      cout << abs(sum) / 2 << '\n';
    }
  }
}

