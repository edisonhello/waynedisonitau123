#include <bits/stdc++.h>
using namespace std;
#define sq(x) ((x) * (x))

const double pi = acos(-1);
const double eps = 1e-15;

vector<pair<int, int>> ci;
vector<tuple<int, int, int>> hi;

vector<int> g[2005];

bool same(double x, double y) {
  return abs(x - y) < eps;
}

struct cmp_f {
  bool operator() (double x, double y) const {
    return same(x, y) ? 0 : x < y;
  }
};

// double norm_o(double x) {
//   if (x > pi) x -= 2 * pi;
//   if (x <= -pi) x += 2 * pi;
//   return x;
// }

void addedge(int u, int v) {
  // cerr << "Addedge " << u << ' ' << v << endl;
  g[u].push_back(v);
  g[v].push_back(u);
}

vector<int> GetCut(int n) {
  vector<int> dfn(n, -1), low(n);
  vector<vector<bool>> instk(n, vector<bool>(n));
  vector<pair<int, int>> stk;
  vector<vector<int>> bcc(n, vector<int>(n, -1));
  int stamp = 0, C = 0;

  auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
    dfn[x] = low[x] = stamp++;
    for (int u : g[x]) {
      if (u == p) continue;
      if (!instk[u][x]) {
        instk[u][x] = instk[x][u] = true;
        stk.push_back(minmax(u, x));
      }
      if (dfn[u] != -1) {
        low[x] = min(low[x], dfn[u]);
      } else {
        dfs(dfs, u, x);
        low[x] = min(low[x], low[u]);
        if (low[u] >= dfn[x]) {
          pair<int, int> e = minmax(u, x);
          while (!stk.empty()) {
            auto f = stk.back();
            stk.pop_back();
            bcc[f.first][f.second] = C;
            bcc[f.second][f.first] = C;
            if (e == f) break;
          }
          C++;
        }
      }
    }
  };

  for (int i = 0; i < n; ++i) {
    if (dfn[i] != -1) continue;
    stamp = 0;
    Dfs(Dfs, i);
  }

  vector<vector<pair<int, int>>> E(C);
  for (int i = 0; i < n; ++i) {
    for (int u : g[i]) {
      if (i > u) continue;
      E[bcc[i][u]].emplace_back(i, u);
    }
  }
  vector<vector<int>> dg(n);
  vector<bool> vis(n), bfs(n);
  for (int i = 0; i < C; ++i) {
    for (auto e : E[i]) {
      dg[e.first].push_back(e.second);
      dg[e.second].push_back(e.first);
    }
    vector<int> que(1, n - 1);
    vis[n - 1] = bfs[n - 1] = true;
    for (int it = 0; it < que.size(); ++it) {
      int x = que[it];
      for (int u : dg[x]) {
        if (!bfs[u]) {
          bfs[u] = true;
          vis[u] = true;
          que.push_back(u);
        }
      }
    }
    for (int u : que) bfs[u] = false;
    for (auto e : E[i]) {
      dg[e.first].clear();
      dg[e.second].clear();
    }
  }
  
  vector<int> res;
  for (int i = 0; i < n; ++i) {
    if (vis[i]) res.push_back(i);
  }

  return res;
}

int main() {
  int n, h; cin >> n >> h;
  
  for (int i = 0; i < n; ++i) {
    int x, y; cin >> x >> y;
    ci.emplace_back(x, y);
  }

  for (int i = 0; i < h; ++i) {
    int x, y, r; cin >> x >> y >> r;
    hi.emplace_back(x, y, r);
  }

  for (int i = 0; i < n; ++i) {
    // cerr << "base " << i << endl;
    auto [x, y] = ci[i];

    vector<tuple<double, double, int, int>> event;

    for (int j = 0; j < h; ++j) {
      auto [hx, hy, hr] = hi[j];
      double d = hypot(x - hx, y - hy);
      double dd = sqrt(d * d - hr * hr);
      double o = atan2(hy - y, hx - x);
      double oo = acos((d * d + dd * dd - hr * hr) / (2 * d * dd)) + eps;

      auto add_seg = [&] (double l, double r) {
        event.emplace_back(l, dd, -1, j);
        event.emplace_back(r, dd, -2, j);
      };

      if (o - oo < -pi) {
        add_seg(-pi, o + oo);
        add_seg(o - oo + 2 * pi, pi);
      } else if (o + oo > pi) {
        add_seg(o - oo, pi);
        add_seg(-pi, o + oo - 2 * pi);
      } else {
        add_seg(o - oo, o + oo);
      }
    }

    for (int j = 0; j < n; ++j) if (j != i) {
      auto [xx, yy] = ci[j];
      double d = hypot(xx - x, yy - y);
      double o = atan2(yy - y, xx - x);

      event.emplace_back(o - eps, d + eps, -1, -j);
      event.emplace_back(o + eps, d + eps, -2, -j);
    }

    for (int j = i + 1; j < n; ++j) {
      auto [xx, yy] = ci[j];
      double d = hypot(xx - x, yy - y);
      double o = atan2(yy - y, xx - x);

      event.emplace_back(o, d, 1, j);
    }

    sort(event.begin(), event.end());

    set<pair<double, int>> hill;
    for (auto [o, d, type, id] : event) {
      // cerr << "event o d t i " << o << ' ' << d << ' ' << type << ' ' << id << endl;
      if (type == 1) {
        if (hill.empty() || d < hill.begin()->first) {
          addedge(i, id);
        }
      } else if (type == -1) {
        hill.insert(make_pair(d, id));
      } else if (type == -2) {
        hill.erase(make_pair(d, id));
      }
    }
  }

  // n -  1;
  auto Cut = GetCut(n);

  for (int i : Cut) {
    if (i == n - 1) continue;
    cout << i + 1 << ' ';
  }
  cout << endl;
}
