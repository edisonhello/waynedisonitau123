#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;
const double PI = acos(-1);

bool same(double x, double y) {
  return abs(x - y) < eps;
}

struct P {
  double x, y;
  P() = default;
  P(double x, double y) : x(x), y(y) {}
  P operator+ (const P b) const { return P(x + b.x, y + b.y); }
  P operator- (const P &b) const { return P(x - b.x, y - b.y); }
  P operator/ (const double b) const { return P(x / b, y / b); }
  double operator^ (const P &b) const { return x * b.y - y * b.x; }
  bool operator< (const P &b) const { return same(x, b.x) ? same(y, b.y) ? false : y < b.y : x < b.x; }
  bool operator== (const P &b) const { return same(x, b.x) && same(y, b.y); }
};

ostream& operator<< (ostream &o, const P &p) {
  o << "(" << p.x << ", " << p.y << ")";
  return o;
}

struct L {
  double a, b, c, o;
  P pa, pb;
  L() = default;
  // L(double a, double b, double c) : a(a), b(b), c(c) {}
  L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), o(atan2(-a, b)), pa(pa), pb(pb) {}
};

ostream& operator<< (ostream &o, const L &l) {
  o << "[" << l.pa << ", " << l.pb << "]";
  return o;
}

P Intersect(L &x, L &y) {
  return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a);
}

bool Parallel(L &x, L &y) {
  return same(x.a * y.b, x.b * y.a);
}

bool jizz(L l1, L l2, L l3) {
  P p = Intersect(l2, l3);
  return ((l1.pb - l1.pa) ^ (p - l1.pa)) < -eps;
}

bool cmp(const L &a, const L &b) {
  return same(a.o, b.o) ? (((b.pb - b.pa) ^ (a.pb - b.pa)) > eps) : a.o < b.o;
}

vector<P> HPI(vector<L> &ls) {
  // cerr << "HPI ls: "; for (auto l : ls) cerr << l << ' '; cerr << '\n';
  sort(ls.begin(), ls.end(), cmp);
  vector<L> pls(1, ls[0]);
  for (int i = 0; i < (int)ls.size(); ++i) if (!same(ls[i].o, pls.back().o)) pls.push_back(ls[i]);
  deque<int> dq; dq.push_back(0); dq.push_back(1);
#define meow(a, b, c) while (dq.size() > 1u && jizz(pls[a], pls[b], pls[c]))
  for (int i = 2; i < (int)pls.size(); ++i) {
    meow(i, dq.back(), dq[dq.size() - 2]) dq.pop_back();
    meow(i, dq[0], dq[1]) dq.pop_front();
    dq.push_back(i);
  }
  meow(dq.front(), dq.back(), dq[dq.size() - 2]) dq.pop_back();
  meow(dq.back(), dq[0], dq[1]) dq.pop_front();
  if (dq.size() < 3u) return vector<P>();
  vector<P> rt;
  for (int i = 0; i < (int)dq.size(); ++i) rt.push_back(Intersect(pls[dq[i]], pls[dq[(i + 1) % dq.size()]]));
  return rt;
}

void solve() {
  int n, m; cin >> n >> m;

  vector<tuple<int, int, int>> inp;
  for (int i = 0; i < n; ++i) {
    int a, b, c; cin >> a >> b >> c;
    inp.emplace_back(a, b, c);
  }

  if (n >= 3) {
    cout << "100.000000%" << '\n';
    return;
  }

  double mn_area = 1e20;
  for (int z = 0; z < (1 << n); ++z) {
    vector<L> lines;
    lines.emplace_back(P(0, 0), P(m, 0));
    lines.emplace_back(P(m, 0), P(m, m));
    lines.emplace_back(P(m, m), P(0, m));
    lines.emplace_back(P(0, m), P(0, 0));
    for (int i = 0; i < n; ++i) {
      auto [a, b, c] = inp[i];
      P pa, pb;
      if (a) {
        pa = P((double)-c / a, 0);
      } else {
        pa = P(0, (double)-c / b);
      }
      pb = pa + P(-b, a);

      if (z & (1 << i)) {
        lines.emplace_back(pa, pb);
      } else {
        lines.emplace_back(pb, pa);
      }
    }
    auto pp = HPI(lines);
    if (pp.empty()) mn_area = 0;
    else {
      // cerr << "pp = "; for (auto p : pp) cerr << p << ' '; cerr << endl;
      double x = 0;
      for (int i = 0; i < (int)pp.size(); ++i) {
        int j = i == (int)pp.size() - 1 ? 0 : i + 1;
        x += pp[i] ^ pp[j];
      }
      // cerr << "x = " << x << endl;
      mn_area = min(mn_area, x / 2);
    }
  }

  double perc = (m * m - mn_area) / (m * m) * 100;
  cout << fixed << setprecision(6) << perc << "%" << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) solve();
}
