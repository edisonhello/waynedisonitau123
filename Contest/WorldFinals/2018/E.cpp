#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

bool same(double x, double y) {
  return abs(x - y) < eps;
}

struct P {
  double x, y;

  P() : x(0), y(0) {}
  P(double x, double y) : x(x), y(y) {}
  double abs() const { return hypot(x, y); }

  P operator- (const P b) const { return P(x - b.x, y - b.y); }
  P operator/ (const double b) const { return P(x / b, y / b); }
  double operator^ (const P b) const { return x * b.y - y * b.x; }
};

ostream& operator<< (ostream &o, P p) {
  return o << "(" << p.x << ", " << p.y << ")";
}

struct L {
  double a, b, c;
  P pa, pb;

  L(P pa, P pb): a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
};

P intersect(L x, L y) { return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a); }

const double g = 9.80665;

int hi[22][22];
vector<int> gra[444];
int dist[444];
int vis[444];

int main() {
  int n, m; cin >> m >> n;
  int w; cin >> w;
  int v; cin >> v;
  int lx, ly; cin >> ly >> lx; --lx, --ly;

  auto gid = [&] (int i, int j) { return i * m + j; };

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> hi[i][j];
    }
  }

  auto cango = [&] (int i, int j, int ii, int jj) -> bool {
    // cerr << "cango " << i << ' ' << j << ' ' << ii << ' ' << jj << endl;

    auto solve_theta = [&] (double x, double y) -> pair<double, int> {
      double a = g * x * x / (2 * v * v);
      double b = -x;
      double c = y + (g * x * x) / (2 * v * v);
      double D = b * b - 4 * a * c;
      if (D < -eps) {
        return make_pair((double)0, 1);
      }
      D = max(D, (double)0);

      double tano = (-b + sqrt(D)) / (2 * a);
      double o = atan(tano);

      // cerr << "solve theta give tan = " << tano << " o = " << o << endl;

      return make_pair(o, 0);
    };

    int x_diff = abs(ii - i) * w;
    int y_diff = abs(jj - j) * w;
    auto [theta, error] = solve_theta(hypot(x_diff, y_diff), hi[ii][jj] - hi[i][j]);

    if (error) return false;

    double tot_dist = hypot(x_diff, y_diff);
    P pa(i * w + (double)w / 2, j * w + (double)w / 2);
    P pb(ii * w + (double)w / 2, jj * w + (double)w / 2);
    int start_h = hi[i][j];
    L lab(pa, pb);
    
    // cerr << "pa pb " << pa << ' ' << pb << endl;

    auto get_height = [&] (P p, int z) -> double {
      // cerr << "get_height p = " << p << " z = " << z << endl;

      int mx = 0;

      auto add = [&] (int i, int j) {
        mx = max(mx, hi[i][j]);
      };

      if (z == 1) {
        int x = round(p.x / w);
        double y = p.y / w;

        int fy = floor(y + eps);
        
        add(x, fy);
        add(x - 1, fy);

        if (same(fy, y)) {
          add(x, fy - 1);
          add(x - 1, fy - 1);
        }
      } else {
        int y = round(p.y / w);
        double x = p.x / w;

        int fx = floor(x + eps);
        
        add(fx, y);
        add(fx, y - 1);

        if (same(fx, x)) {
          add(fx - 1, y);
          add(fx - 1, y - 1);
        }
      }

      // cerr << "height = " << mx << endl;

      return mx;
    };

    auto is_higher = [&] (P p, double t_h) -> bool {
      // cerr << "p = " << p << " t_h " << t_h << endl;
      double d = (p - pa).abs();
      // cerr << "* d v theta " << d << ' ' << v << ' ' << theta << endl;
      double t = d / (v * cos(theta));
      double hh = v * sin(theta) * t - g * t * t / 2 + start_h;
      // cerr << "d t hh " << d << ' ' << t << ' ' << hh << endl;
      return hh >= t_h + eps;
    };

    bool hit = 0;

    int il = min(i, ii), ir = max(i, ii);
    for (int xx = il + 1; xx <= ir; ++xx) {
      P p1(xx * w, 0), p2(xx * w, 1);
      L lbound(p1, p2);

      // cerr << "p1 p2 " << p1 << ' ' << p2 << endl;

      P px = intersect(lab, lbound);

      double height = get_height(px, 1);
      
      if (!is_higher(px, height)) {
        hit = 1;
      }
    }

    int jl = min(j, jj), jr = max(j, jj);
    for (int yy = jl + 1; yy <= jr; ++yy) {
      // cerr << "jl jr yy " << jl << ' ' << jr << ' ' << yy << endl;
      P p1(0, yy * w), p2(1, yy * w);
      L lbound(p1, p2);

      // cerr << "p1 p2 " << p1 << ' ' << p2 << endl;

      P px = intersect(lab, lbound);

      double height = get_height(px, 2);
      
      if (!is_higher(px, height)) {
        hit = 1;
      }
    }

    return !hit;
  };

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int id = gid(i, j);
      for (int ii = 0; ii < n; ++ii) {
        for (int jj = 0; jj < m; ++jj) {
          int iid = gid(ii, jj);
          if (id == iid) continue;

          if (cango(i, j, ii, jj)) {
            // cerr << "add edge " << id << ' ' << iid << endl;
            gra[id].push_back(iid);
            // gra[iid].push_back(id);
          }
        }
      }
    }
  }

  int start = gid(lx, ly);

  queue<int> q; q.push(start);
  vis[start] = 1;

  while (q.size()) {
    int now = q.front(); q.pop();
    for (int i : gra[now]) {
      if (!vis[i]) {
        vis[i] = 1;
        dist[i] = dist[now] + 1;
        q.push(i);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (!vis[gid(i, j)]) cout << "X";
      else cout << dist[gid(i, j)];
      cout << " \n"[j == m - 1];
    }
  }
}

