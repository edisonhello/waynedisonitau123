Poly Inverse(Poly f) {
  int n = f.size();
  Poly q(1, fpow(f[0], kMod - 2));
  for (int s = 2;; s <<= 1) {
    if (f.size() < s) f.resize(s);
    Poly fv(f.begin(), f.begin() + s);
    Poly fq(q.begin(), q.end());
    fv.resize(s + s);
    fq.resize(s + s);
    ntt::Transform(fv, s + s);
    ntt::Transform(fq, s + s);
    for (int i = 0; i < s + s; ++i) {
      fv[i] = 1LL * fv[i] * fq[i] % kMod * fq[i] % kMod;
    }
    ntt::InverseTransform(fv, s + s);
    Poly res(s);
    for (int i = 0; i < s; ++i) {
      res[i] = kMod - fv[i];
      if (i < (s >> 1)) {
        int v = 2 * q[i] % kMod;
        (res[i] += v) >= kMod ? res[i] -= kMod : 0;
      }
    }
    q = res;
    if (s >= n) break;
  }
  q.resize(n);
  return q;
}
Poly Divide(const Poly &a, const Poly &b) {
  int n = a.size(), m = b.size(), k = 2;
  while (k < n - m + 1) k <<= 1;
  Poly ra(k), rb(k);
  for (int i = 0; i < min(n, k); ++i) ra[i] = a[n - 1 - i];
  for (int i = 0; i < min(m, k); ++i) rb[i] = b[m - 1 - i];
  auto rbi = Inverse(rb);
  auto res = Multiply(rbi, ra);
  res.resize(n - m + 1);
  reverse(res.begin(), res.end());
  return res;
}
Poly Modulo(const Poly &a, const Poly &b) {
  if (a.size() < b.size()) return a;
  auto dv = Multiply(Divide(a, b), b);
  assert(dv.size() == a.size());
  for (int i = 0; i < dv.size(); ++i) {
    dv[i] = (a[i] + kMod - dv[i]) % kMod;
  }
  while (!dv.empty() && dv.back() == 0) dv.pop_back();
  return dv;
}
Poly Derivative(const Poly &f) {
  int n = f.size();
  vector<int> res(n - 1);
  for (int i = 0; i < n - 1; ++i) {
    res[i] = 1LL * f[i + 1] * (i + 1) % kMod;
  }
  return res;
}
Poly Integral(const Poly &f) {
  int n = f.size();
  vector<int> res(n + 1);
  for (int i = 0; i < n; ++i) {
    res[i + 1] = 1LL * f[i] * fpow(i + 1, kMod - 2) % kMod;
  }
  return res;
}
Poly Evaluate(const Poly &f, const vector<int> &x) {
  if (x.empty()) return Poly();
  int n = x.size();
  vector<Poly> up(n * 2);
  for (int i = 0; i < n; ++i) up[i + n] = {kMod - x[i], 1};
  for (int i = n - 1; i > 0; --i) up[i] = Multiply(up[i * 2], up[i * 2 + 1]);
  vector<Poly> down(n * 2);
  down[1] = Modulo(f, up[1]);
  for (int i = 2; i < n * 2; ++i) down[i] = Modulo(down[i >> 1], up[i]);
  vector<int> y(n);
  for (int i = 0; i < n; ++i) y[i] = down[i + n][0];
  return y;
}
Poly Interpolate(const vector<int> &x, const vector<int> &y) {
  int n = x.size();
  vector<Poly> up(n * 2);
  for (int i = 0; i < n; ++i) up[i + n] = {kMod - x[i], 1};
  for (int i = n - 1; i > 0; --i) up[i] = Multiply(up[i * 2], up[i * 2 + 1]);
  vector<int> a = Evaluate(Derivative(up[1]), x);
  for (int i = 0; i < n; ++i) {
    a[i] = 1LL * y[i] * fpow(a[i], kMod - 2) % kMod;
  }
  vector<Poly> down(n * 2);
  for (int i = 0; i < n; ++i) down[i + n] = {a[i]};
  for (int i = n - 1; i > 0; --i) {
    auto lhs = Multiply(down[i * 2], up[i * 2 + 1]);
    auto rhs = Multiply(down[i * 2 + 1], up[i * 2]);
    assert(lhs.size() == rhs.size());
    down[i].resize(lhs.size());
    for (int j = 0; j < lhs.size(); ++j) {
      down[i][j] = (lhs[j] + rhs[j]) % kMod;
    }
  }
  return down[1];
}
Poly Log(Poly f) {
  int n = f.size();
  if (n == 1) return {0};
  auto d = Derivative(f);
  f.resize(n - 1);
  d = Multiply(d, Inverse(f));
  d.resize(n - 1);
  return Integral(d);
}
Poly Exp(Poly f) {
  int n = f.size();
  Poly q(1, 1);
  f[0] += 1;
  for (int s = 1; s < n; s <<= 1) {
    if (f.size() < s + s) f.resize(s + s);
    Poly g(f.begin(), f.begin() + s + s);
    Poly h(q.begin(), q.end());
    h.resize(s + s);
    h = Log(h);
    for (int i = 0; i < s + s; ++i) {
      g[i] = (g[i] + kMod - h[i]) % kMod;
    }
    g = Multiply(g, q);
    g.resize(s + s);
    q = g;
  }
  assert(q.size() >= n);
  q.resize(n);
  return q;
}
Poly SquareRootImpl(Poly f) {
  if (f.empty()) return {0};
  int z = QuadraticResidue(f[0], kMod), n = f.size();
  constexpr int kInv2 = (kMod + 1) >> 1;
  if (z == -1) return {-1};
  vector<int> q(1, z);
  for (int s = 1; s < n; s <<= 1) {
    if (f.size() < s + s) f.resize(s + s);
    vector<int> fq(q.begin(), q.end());
    fq.resize(s + s);
    vector<int> f2 = Multiply(fq, fq);
    f2.resize(s + s);
    for (int i = 0; i < s + s; ++i) {
      f2[i] = (f2[i] + kMod - f[i]) % kMod;
    }
    f2 = Multiply(f2, Inverse(fq));
    f2.resize(s + s);
    for (int i = 0; i < s + s; ++i) {
      fq[i] = (fq[i] + kMod - 1LL * f2[i] * kInv2 % kMod) % kMod;
    }
    q = fq;
  }
  q.resize(n);
  return q;
}
Poly SquareRoot(Poly f) {
  int n = f.size(), m = 0;
  while (m < n && f[m] == 0) m++;
  if (m == n) return vector<int>(n);
  if (m & 1) return {-1};
  auto s = SquareRootImpl(vector<int>(f.begin() + m, f.end()));
  if (s[0] == -1) return {-1};
  vector<int> res(n);
  for (int i = 0; i < s.size(); ++i) res[i + m / 2] = s[i];
  return res;
}
