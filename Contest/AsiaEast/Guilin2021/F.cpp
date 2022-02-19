#include <bits/stdc++.h>
using namespace std;
#define double long double

const double eps = 1e-13;

bool same(double a, double b) {
  return abs(a - b) < eps;
}

int sign(double x) {
  if (same(x, 0)) return 0;
  if (x > 0) return 1;
  return -1;
}

struct P {
  double x, y;
  P() : x(0), y(0) {}
  P(double x, double y) : x(x), y(y) {}
  P operator+(const P &b) const { return P{x + b.x, y + b.y}; }
  P operator-(const P &b) const { return P{x - b.x, y - b.y}; }
  P operator*(const double &b) const { return P{x * b, y * b}; }
  P operator/(const double &b) const { return P{x / b, y / b}; }
  double operator*(const P &b) const { return x * b.x + y * b.y; }
  double operator^(const P &b) const { return x * b.y - y * b.x; }

  double Abs() const { return hypot(x, y); }
};

struct L {
  double a, b, c;
  P pa, pb;
  L() = default;
  L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
  double GetRatio(const P &p) const {
    return (p - pa) * (pb - pa) / ((pb - pa).Abs() * (pb - pa).Abs());
  }
  double Length() const { return (pa - pb).Abs(); }
};

P Intersect(L x, L y) {
  return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a); 
}

bool SegmentIntersect(P p1, P p2, P p3, P p4) {
  if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x)) return false;
  if (max(p1.y, p2.y) < min(p3.y, p4.y) || max(p3.y, p4.y) < min(p1.y, p2.y)) return false;
  return sign((p3 - p1) ^ (p4 - p1)) * sign((p3 - p2) ^ (p4 - p2)) <= 0 &&
    sign((p1 - p3) ^ (p2 - p3)) * sign((p1 - p4) ^ (p2 - p4)) <= 0;
}

bool Parallel(L x, L y) { return same(x.a * y.b, x.b * y.a); }

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<P> out, in;

  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    out.emplace_back(x, y);
  }
  for (int i = 0; i < m; ++i) {
    int x, y; cin >> x >> y;
    in.emplace_back(x, y);
  }

  vector<L> outl, inl;
  for (int i = 0; i < n; ++i) {
    outl.emplace_back(out[i], out[(i + 1) % n]);
  }
  for (int i = 0; i < m; ++i) {
    inl.emplace_back(in[i], in[(i + 1) % m]);
  }

  int lcut = -1, rcut = -1;
  for (int i = 0; i < n; ++i) {
    if (!Parallel(inl[0], outl[i])) {
      P cros = Intersect(inl[0], outl[i]);
      double rto = outl[i].GetRatio(cros);
      if (rto < -eps || rto > 1 + eps) continue;

      double rt = inl[0].GetRatio(cros);
      if (rt < 0) lcut = i;
      else if (rt > 1) rcut = i;
      else assert(0);
    }
  }
  assert(lcut != -1);
  assert(rcut != -1);

  double inside_len = 0;
  for (int i = (lcut + 1) % n; i != rcut; i = (i + 1) % n) {
    inside_len += outl[i].Length();
  }
  
  auto TmpIntersect = [&](const L &in, const L &out, int type) {
    if (Parallel(in, out)) return false;
    P cros = Intersect(in, out);
    double o = out.GetRatio(cros);
    if (o < -eps || o > 1 + eps) return false;
      double rt = in.GetRatio(cros);
    if (type == 1) {
      if (rt < 0) return true;
      else return false;
    } else {
      if (rt > 1) return true;
      else return false;
    }
  };

  double sum = 0;
  for (int i = 0; i < m; ++i) {
    if (i) {
      while (!TmpIntersect(inl[i], outl[lcut], 1)) {
        inside_len -= outl[(lcut + 1) % n].Length();
        lcut = (lcut + 1) % n;
      }
      while (!TmpIntersect(inl[i], outl[rcut], 2)) {
        inside_len += outl[rcut].Length();
        rcut = (rcut + 1) % n;
      }
    }

    P lcros = Intersect(inl[i], outl[lcut]);
    P rcros = Intersect(inl[i], outl[rcut]);

    double me_len = inl[i].Length();
    double llen = (lcros - out[(lcut + 1) % n]).Abs();
    double rlen = (rcros - out[rcut]).Abs();

    sum += me_len * (llen + rlen + inside_len);
  }

  double outside_len = 0;
  for (int i = 0; i < n; ++i) {
    outside_len += outl[i].Length();
  }

  cout << fixed << setprecision(12);
  cout << sum / outside_len << endl;
}

