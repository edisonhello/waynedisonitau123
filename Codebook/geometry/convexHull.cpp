bool operator<(const P &a, const P &b) {
  return same(a.x, b.x) ? a.y < b.y : a.x < b.x;
}
bool operator>(const P &a, const P &b) {
  return same(a.x, b.x) ? a.y > b.y : a.x > b.x;
}

#define crx(a, b, c) ((b - a) ^ (c - a))

vector<P> convex(vector<P> ps) {
  vector<P> p;
  sort(ps.begin(), ps.end(), [&] (P a, P b) { return same(a.x, b.x) ? a.y < b.y : a.x < b.x; });
  for (int i = 0; i < ps.size(); ++i) {
    while (p.size() >= 2 && crx(p[p.size() - 2], ps[i], p[p.size() - 1]) >= 0) p.pop_back();
    p.push_back(ps[i]);
  }
  int t = p.size();
  for (int i = (int)ps.size() - 2; i >= 0; --i) {
    while (p.size() > t && crx(p[p.size() - 2], ps[i], p[p.size() - 1]) >= 0) p.pop_back();
    p.push_back(ps[i]);
  }
  p.pop_back();
  return p;
}

int sgn(double x) { return same(x, 0) ? 0 : x > 0 ? 1 : -1; }

P isLL(P p1, P p2, P q1, P q2) {
  double a = crx(q1, q2, p1), b = -crx(q1, q2, p2);
  return (p1 * b + p2 * a) / (a + b);
}

struct CH {
  int n;
  vector<P> p, u, d;
  CH() {}
  CH(vector<P> ps) : p(ps) {
    n = ps.size();
    rotate(p.begin(), min_element(p.begin(), p.end()), p.end());
    auto t = max_element(p.begin(), p.end());
    d = vector<P>(p.begin(), next(t));
    u = vector<P>(t, p.end()); u.push_back(p[0]);
  }
  int find(vector<P> &v, P d) {
    int l = 0, r = v.size();
    while (l + 5 < r) {
      int L = (l * 2 + r) / 3, R = (l + r * 2) / 3;
      if (v[L] * d > v[R] * d) r = R;
      else l = L;
    }
    int x = l;
    for (int i = l + 1; i < r; ++i) if (v[i] * d > v[x] * d) x = i;
    return x;
  }
  int findFarest(P v) {
    if (v.y > 0 || v.y == 0 && v.x > 0) return ((int)d.size() - 1 + find(u, v)) % p.size();
    return find(d, v);
  }
  P get(int l, int r, P a, P b) {
    int s = sgn(crx(a, b, p[l % n]));
    while (l + 1 < r) {
      int m = (l + r) >> 1;
      if (sgn(crx(a, b, p[m % n])) == s) l = m;
      else r = m;
    }
    return isLL(a, b, p[l % n], p[(l + 1) % n]);
  }
  vector<P> getLineIntersect(P a, P b) {
    int X = findFarest((b - a).rot(pi / 2));
    int Y = findFarest((a - b).rot(pi / 2));
    if (X > Y) swap(X, Y);
    if (sgn(crx(a, b, p[X])) * sgn(crx(a, b, p[Y])) < 0) return {get(X, Y, a, b), get(Y, X + n, a, b)};
    return {}; // tangent case falls here
  }
  void update_tangent(P q, int i, int &a, int &b) {
    if (sgn(crx(q, p[a], p[i])) > 0) a = i;
    if (sgn(crx(q, p[b], p[i])) < 0) b = i;
  }
  void bs(int l, int r, P q, int &a, int &b) {
    if (l == r) return;
    update_tangent(q, l % n, a, b);
    int s = sgn(crx(q, p[l % n], p[(l + 1) % n]));
    while (l + 1 < r) {
      int m = (l + r) >> 1;
      if (sgn(crx(q, p[m % n], p[(m + 1) % n])) == s) l = m;
      else r = m;
    }
    update_tangent(q, r % n, a, b);
  }
  int x = l;
  for (int i = l + 1; i < r; ++i) if (v[i] * d > v[x] * d) x = i;
  return x;
}
int findFarest(P v) {
  if (v.y > 0 || v.y == 0 && v.x > 0) return ((int)d.size() - 1 + find(u, v)) % p.size();
  return find(d, v);
}
P get(int l, int r, P a, P b) {
  int s = sgn(crx(a, b, p[l % n]));
  while (l + 1 < r) {
    int m = (l + r) >> 1;
    if (sgn(crx(a, b, p[m % n])) == s) l = m;
    else r = m;
  }
  return isLL(a, b, p[l % n], p[(l + 1) % n]);
}
vector<P> getIS(P a, P b) {
  int X = findFarest((b - a).spin(pi / 2));
  int Y = findFarest((a - b).spin(pi / 2));
  if (X > Y) swap(X, Y);
  if (sgn(crx(a, b, p[X])) * sgn(crx(a, b, p[Y])) < 0) return {get(X, Y, a, b), get(Y, X + n, a, b)};
  return {};
}
void update_tangent(P q, int i, int &a, int &b) {
  if (sgn(crx(q, p[a], p[i])) > 0) a = i;
  if (sgn(crx(q, p[b], p[i])) < 0) b = i;
}
void bs(int l, int r, P q, int &a, int &b) {
  if (l == r) return;
  update_tangent(q, l % n, a, b);
  int s = sgn(crx(q, p[l % n], p[(l + 1) % n]));
  while (l + 1 < r) {
    int m = (l + r) >> 1;
    if (sgn(crx(q, p[m % n], p[(m + 1) % n])) == s) l = m;
    else r = m;
  }
  update_tangent(q, r % n, a, b);
}
bool contain(P p) {
  if (p.x < d[0].x || p.x > d.back().x) return 0;
  auto it = lower_bound(d.begin(), d.end(), P(p.x, -1e12));
  if (it->x == p.x) {
    if (it->y > p.y) return 0;
  } else if (crx(*prev(it), *it, p) < -eps) return 0;
  it = lower_bound(u.begin(), u.end(), P(p.x, 1e12), greater<P>());
  if (it->x == p.x) {
    if (it->y < p.y) return 0;
  } else if (crx(*prev(it), *it, p) < -eps) return 0;
  return 1;
}
bool get_tangent(P p, int &a, int &b) { // b -> a
  if (contain(p)) return 0;
  a = b = 0;
  int i = lower_bound(d.begin(), d.end(), p) - d.begin();
  bs(0, i, p, a, b);
  bs(i, d.size(), p, a, b);
  i = lower_bound(u.begin(), u.end(), p, greater<P>()) - u.begin();
  bs((int)d.size() - 1, (int)d.size() - 1 + i, p, a, b);
  bs((int)d.size() - 1 + i, (int)d.size() - 1 + u.size(), p, a, b);
  return 1;
}
};
