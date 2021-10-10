#include <bits/stdc++.h>
using namespace std;

#define double long double

const double eps = 1e-12;
const double pi = acos(-1);

bool same(double a, double b) {
  return abs(a - b) < eps;
}

struct P {
  double x, y;
  P operator+ (const P &b) const { return P{x + b.x, y + b.y}; }
  P operator- (const P &b) const { return P{x - b.x, y - b.y}; }
  P operator* (const double b) const { return P{x * b, y * b}; }
  P operator/ (const double b) const { return P{x / b, y / b}; }
  double abs() { return hypot(x, y); }
  bool operator== (const P &b) const { return same(x, b.x) && same(y, b.y); }
  P spin(double z) const { return P{-y, x}; }
  P unit() { return P{x, y} / abs(); }
  double operator^ (const P &b) const { return x * b.y - y * b.x; }
  double operator* (const P &b) const { return x * b.x + y * b.y; }
  bool operator< (const P &b) const { return same(x, b.x) ? same(y, b.y) ? 0 : y < b.y : x < b.x; }
};

struct L {
  double a, b, c, o;
  P pa, pb;
  L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb), o(atan2(-a, b)) {}
  P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
  double get_ratio(P p) { return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs()); }
  bool inseg(P p) {
    P pp = project(p);
    if (!(p == pp)) return false;
    double z = get_ratio(pp);
    return z >= -eps && z <= 1 + eps;
  }
};

P intersect(L x, L y) {
  // cerr << "divid " << (-x.a * y.b + x.b * y.a) << endl;
  return P{-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a} / (-x.a * y.b + x.b * y.a);
}

bool parallel(L x, L y) { return same(x.a * y.b, x.b * y.a); }

bool jizz(L l1, L l2, L l3) {
  P p = intersect(l2, l3);
  return ((l1.pb - l1.pa) ^ (p - l1.pa)) < -eps;
}

bool cmp(const L &a, const L &b) {
  return same(a.o, b.o) ? (((b.pb - b.pa) ^ (a.pb - b.pa)) > eps) : a.o < b.o;
}

vector<P> hpi(vector<L> &ls) {
  // cerr << "hpi lines" << endl;
  // for (L l : ls) {
  //   cerr << l.a << ' ' << l.b << 
  // }
  sort(ls.begin(), ls.end(), cmp);
  vector<L> pls(1, ls[0]);
  for (int i = 0; i < (int)ls.size(); ++i) if (!same(ls[i].o, pls.back().o)) pls.push_back(ls[i]);
  deque<int> dq = {0, 1};
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
  for (int i = 0; i < (int)dq.size(); ++i) rt.push_back(intersect(pls[dq[i]], pls[dq[(i + 1) % dq.size()]]));
  return rt;
}

double hpi_area(vector<L> &ls) {
  auto ps = hpi(ls);
  if (ps.empty()) return 0;
  // cerr << "hpi ps ";
  // for (auto p : ps) cerr << p.x << " " << p.y << ", ";
  // cerr << endl;
  double x = 0;
  for (int i = 0; i < (int)ps.size(); ++i) {
    int j = (i + 1) % ps.size();
    x += ps[i] ^ ps[j];
  }
  return abs(x) / 2;
}

double solve() {
  P s1, s2;
  cin >> s1.x >> s1.y >> s2.x >> s2.y;
  vector<L> ls;
  ls.push_back(L(s1, P{s2.x, s1.y}));
  ls.push_back(L(P{s2.x, s1.y}, s2));
  ls.push_back(L(s2, P{s1.x, s2.y}));
  ls.push_back(L(P{s1.x, s2.y}, s1));

  P l1a, l1b, l2a, l2b;
  cin >> l1a.x >> l1a.y;
  cin >> l1b.x >> l1b.y;
  if (l1b < l1a) swap(l1a, l1b);
  cin >> l2a.x >> l2a.y;
  cin >> l2b.x >> l2b.y;
  if (l2b < l2a) swap(l2a, l2b);
  if (l1a == l2a && l1b == l2b) {
    return (s2.x - s1.x) * (s2.y - s1.y);
  }
  L l1(l1a, l1b), l2(l2a, l2b);
  


  if (parallel(l1, l2)) {
    vector<P> ps;
    if (l1.inseg(l2.pa)) ps.push_back(l2.pa);
    if (l1.inseg(l2.pb)) ps.push_back(l2.pb);
    if (l2.inseg(l1.pa)) ps.push_back(l1.pa);
    if (l2.inseg(l1.pb)) ps.push_back(l1.pb);
    if (ps.empty()) return 0;
    sort(ps.begin(), ps.end());
    if (ps.size() == 3u) {
      if (l1.pb == l2.pa) l1 = L(l1b, l1a);
      if (l1.pa == l2.pb) l2 = L(l2b, l2a);
      if (l1.pb == l2.pb) l1 = L(l1b, l1a), l2 = L(l2b, l2a);
      if (l1.inseg(l2.pb)) {
        P pz = l2.pb;
        P dir = (l2.pb - l2.pa).spin(pi / 2);
        ls.push_back(L(pz, pz - dir));
        return hpi_area(ls);
      }

      if (l2.inseg(l1.pb)) {
        P pz = l1.pb;
        P dir = (l1.pb - l1.pa).spin(pi / 2);
        ls.push_back(L(pz, pz - dir));
        return hpi_area(ls);
      }
    } 
    ps.resize(unique(ps.begin(), ps.end()) - ps.begin());
    // assert(ps.size() <= 2u);
    if (ps.size() <= 1u) return 0;
    // cerr << "ps = ";
    // for (auto p : ps) {
    //   cerr << p.x << ' ' << p.y << ", ";
    // }
    // cerr << endl;
    P dir = (l1.pa - l1.pb).spin(pi / 2);
    auto ls2 = ls;
    ls.push_back(L(ps[0], ps[0] + dir));
    ls.push_back(L(ps[1], ps[1] - dir));
    ls2.push_back(L(ps[0], ps[0] - dir));
    ls2.push_back(L(ps[1], ps[1] + dir));
    double a1 = hpi_area(ls);
    double a2 = hpi_area(ls2);
    assert(same(min(a1, a2), 0));
    // cerr << "a1 a2 " << a1 << ' ' << a2 << endl;
    return max(a1, a2);
  } else {
    if (l1.pb == l2.pa) l1 = L(l1b, l1a);
    if (l1.pa == l2.pb) l2 = L(l2b, l2a);
    if (l1.pb == l2.pb) l1 = L(l1b, l1a), l2 = L(l2b, l2a);
    if (l1.pa == l2.pa) {
      P d1 = (l1.pb - l1.pa).spin(pi / 2);
      P d2 = (l2.pb - l2.pa).spin(pi / 2);
      L al1 = L(l1.pa, l1.pa + d1);
      L al2 = L(l2.pa, l2.pa + d2);
      ls.push_back(al1);
      ls.push_back(al2);
      return hpi_area(ls);
    }
    return 0;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) {
    auto x = solve();
    assert(!isnan(x));
    cout << fixed << setprecision(12) << x << '\n';
  }
}
