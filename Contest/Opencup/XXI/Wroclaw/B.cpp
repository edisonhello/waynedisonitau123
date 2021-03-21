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
  double a, b, c;
  L() = default;
  L(double a, double b, double c) : a(a), b(b), c(c) {}
};

P Intersect(L &x, L &y) {
  return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a);
}

bool Parallel(L &x, L &y) {
  return same(x.a * y.b, x.b * y.a);
}

void solve() {
  int n, m; cin >> n >> m;
  vector<L> lines;

  for (int i = 0; i < n; ++i) {
    int a, b, c; cin >> a >> b >> c;
    lines.emplace_back(a, b, c);
  }

  bool full = 0;

  if (n >= 3) full = 1;
  if (full) { 
    cout << "100.000000%" << '\n';
    return;
  }

  vector<P> intersects;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      L &x = lines[i], &y = lines[j];
      if (x.b * y.a == x.a * y.b) {
        full = 1;
        if (full) {
          cout << "100.000000%" << '\n';
          return;
        }
        continue;
      } else {
        intersects.push_back(Intersect(x, y));
      }
    }
  }

  sort(intersects.begin(), intersects.end());
  for (int i = 0, j; i < (int)intersects.size(); i = j) {
    for (j = i; j < (int)intersects.size() && intersects[i] == intersects[j]; ++j);

    if (j - i >= 3) full = 1;
    for (int k = i; k < j; ++k) {
      if (intersects[k].x < eps || intersects[k].y < eps || intersects[k].x >= m - eps || intersects[k].y >= m - eps) full = 1;
    }
  }

  if (n == 1) {
    L l = lines[0];
    long long v1 = 0 * l.a + 0 * l.b + l.c;
    long long v2 = 0 * l.a + m * l.b + l.c;
    long long v3 = m * l.a + m * l.b + l.c;
    long long v4 = m * l.a + 0 * l.b + l.c;

    if (v1 >= 0 && v2 >= 0 && v3 >= 0 && v4 >= 0) {
      full = 1;
    } else if (v1 <= 0 && v2 <= 0 && v3 <= 0 && v4 <= 0) {
      full = 1;
    }
  }

  if (full) {
    cout << "100.000000%" << '\n';
    return;
  }

  lines.emplace_back(1, 0, -m);
  lines.emplace_back(0, 1, -m);
  lines.emplace_back(1, 0, 0);
  lines.emplace_back(0, 1, 0);

  vector<vector<P>> appearp(lines.size());

  for (int i = 0; i < (int)lines.size(); ++i) {
    for (int j = i + 1; j < (int)lines.size(); ++j) {
      if (Parallel(lines[i], lines[j])) continue;
      P p = Intersect(lines[i], lines[j]);
      // cerr << "intersect p = " << p << endl;
      if (p.x < -eps || p.y < -eps || p.x > m + eps || p.y > m + eps) continue;
      appearp[i].push_back(p);
      appearp[j].push_back(p);
    }
  }

  map<P, int> point_id;
  vector<P> ps;
  auto get_id = [&] (const P &p) -> int {
    auto it = point_id.find(p);
    if (it == point_id.end()) {
      int new_id = point_id.size();
      ps.push_back(p);
      // cerr << "new point at " << p << endl;
      return point_id[p] = new_id;
    }
    return it->second;
  };

  for (auto &v : appearp) for (auto &p : v) get_id(p);

  int pn = point_id.size();
  vector<vector<pair<double, int>>> g(pn); // [ angle, to_id ]
  vector<map<int, int>> reverseg(pn); // [ come_id, to_idx ]

  for (auto &v : appearp) {
    sort(v.begin(), v.end()); 
    for (int i = 1; i < (int)v.size(); ++i) {
      int pi = get_id(v[i - 1]);
      int pj = get_id(v[i]);
      double o = atan2(v[i].y - v[i - 1].y, v[i].x - v[i - 1].x);
      
      g[pi].emplace_back(o, pj);
      g[pj].emplace_back(o > 0 ? o - PI : o + PI, pi);
    }
  }

  // cerr << "g: " << endl;
  // for (auto &v : g) {
  //   for (auto [o, to] : v) {
  //     cerr << "[" << to << ", " << o << "] ";
  //   }
  //   cerr << endl;
  // }

  for (auto &v : g) sort(v.begin(), v.end());
  for (int i = 0; i < pn; ++i) {
    for (int j = 0; j < (int)g[i].size(); ++j) {
      reverseg[i][g[i][j].second] = j;
    }
  }

  set<pair<int, int>> walked;
  double mn_area = 1e20;

  for (int i = 0; i < pn; ++i) {
    for (auto [o, to] : g[i]) {
      if (walked.count(make_pair(i, to))) continue;

      vector<int> walkedp;
      int now = i, next = to;
      while (true) {
        walkedp.push_back(now);
        int new_now = next;
        next = g[next][(reverseg[next][now] + g[next].size() - 1) % g[next].size()].second;
        now = new_now;

        if (now == i) break;
      }

      double area = 0;
      for (int i = 0; i < (int)walkedp.size(); ++i) {
        int j = i + 1;
        if (j >= (int)walkedp.size()) j -= walkedp.size();
        walked.insert(make_pair(walkedp[i], walkedp[j]));

        P pi = ps[walkedp[i]], pj = ps[walkedp[j]];
        area += pi ^ pj;
      }

      if (area < 0) continue;

      // cerr << "area = " << area << endl;
      // cerr << "walkedp = "; for (int i : walkedp) cerr << i << ' '; cerr << endl;
      // cerr << " => "; for (int i : walkedp) cerr << ps[i] << ' '; cerr << endl;
      mn_area = min(mn_area, area / 2);
    }
  }

  double perc = (m * m - mn_area) / (m * m) * 100;
  cout << fixed << setprecision(6) << perc << "%" << '\n';
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) solve();
}
