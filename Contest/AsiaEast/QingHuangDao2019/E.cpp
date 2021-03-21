#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int to, cap, rev;
  Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};

int Flow(vector<vector<Edge>> g, int s, int t) {
  int n = g.size(), res = 0;
  vector<int> lev(n, -1), iter(n);
  while (true) {
    vector<int> que(1, s);
    fill(lev.begin(), lev.end(), -1);
    fill(iter.begin(), iter.end(), 0);
    lev[s] = 0;
    for (int it = 0; it < que.size(); ++it) {
      int x = que[it];
      for (Edge &e : g[x]) {
        if (e.cap > 0 && lev[e.to] == -1) {
          lev[e.to] = lev[x] + 1;
          que.push_back(e.to);
        }
      }
    }

    if (lev[t] == -1) break;

    auto Dfs = [&] (auto dfs, int x, int f = 1000000000) {
      if (x == t) return f;
      int res = 0;
      for (int &it = iter[x]; it < g[x].size(); ++it) {
        Edge &e = g[x][it];
        if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
          int p = dfs(dfs, e.to, min(f - res, e.cap));
          res += p;
          e.cap -= p;
          g[e.to][e.rev].cap += p;
        }
      }
      if (res == 0) lev[x] = -1;
      return res;
    };
    res += Dfs(Dfs, s);
  }
  return res;
}

void solve() {
  int n, m, x, y; cin >> n >> m >> x >> y;
  vector<vector<int>> udpi(n + 1, vector<int>(m, -1)), udpo = udpi;
  vector<vector<int>> lrpi(n, vector<int>(m + 1, -1)), lrpo = lrpi;
  vector<vector<int>> ipi(n, vector<int>(m, -1)), ipo = ipi;

  int nn = 0;
  int S = nn++;
  int T = nn++;
  for (auto &v : udpi) for (int &i : v) i = nn++;
  for (auto &v : udpo) for (int &i : v) i = nn++;
  for (auto &v : lrpi) for (int &i : v) i = nn++;
  for (auto &v : lrpo) for (int &i : v) i = nn++;
  for (auto &v : ipi) for (int &i : v) i = nn++;
  for (auto &v : ipo) for (int &i : v) i = nn++;

  vector<vector<Edge>> edg(nn);

  auto AddEdge = [&] (int u, int v, int bid = 0) {
    edg[u].emplace_back(Edge{v, 1, (int)edg[v].size() - 0});
    edg[v].emplace_back(Edge{u, bid, (int)edg[u].size() - 1});
    // cerr << "add edge " << u << ' ' << v << ' ' << bid << endl;
  };

  for (int i = 0; i < n + 1; ++i) for (int j = 0; j < m; ++j) AddEdge(udpi[i][j], udpo[i][j]);
  for (int i = 0; i < n; ++i) for (int j = 0; j < m + 1; ++j) AddEdge(lrpi[i][j], lrpo[i][j]);
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) AddEdge(ipi[i][j], ipo[i][j]);
  
  // cerr << "udpi: " << endl;
  // for (auto &v : udpi) { for (int i : v) cerr << i << ' '; cerr << endl; }
  // cerr << "udpo: " << endl;
  // for (auto &v : udpo) { for (int i : v) cerr << i << ' '; cerr << endl; }
  // cerr << "lrpi: " << endl;
  // for (auto &v : lrpi) { for (int i : v) cerr << i << ' '; cerr << endl; }
  // cerr << "lrpo: " << endl;
  // for (auto &v : lrpo) { for (int i : v) cerr << i << ' '; cerr << endl; }
  // cerr << "ipi: " << endl;
  // for (auto &v : ipi) { for (int i : v) cerr << i << ' '; cerr << endl; }
  // cerr << "ipo: " << endl;
  // for (auto &v : ipo) { for (int i : v) cerr << i << ' '; cerr << endl; }

  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    for (int j = 0; j < m; ++j) {
      if (s[j] == '0') {
        AddEdge(udpo[i][j], ipi[i][j]);
        AddEdge(ipo[i][j], udpi[i][j]);

        AddEdge(udpo[i + 1][j], ipi[i][j]);
        AddEdge(ipo[i][j], udpi[i + 1][j]);

        AddEdge(lrpo[i][j], ipi[i][j]);
        AddEdge(ipo[i][j], lrpi[i][j]);

        AddEdge(lrpo[i][j + 1], ipi[i][j]);
        AddEdge(ipo[i][j], lrpi[i][j + 1]);

        AddEdge(udpo[i][j], udpi[i + 1][j]);
        AddEdge(udpo[i + 1][j], udpi[i][j]);

        AddEdge(lrpo[i][j], lrpi[i][j + 1]);
        AddEdge(lrpo[i][j + 1], lrpi[i][j]);
      } else {

      }
    }
  }

  for (int i = 0; i < x; ++i) {
    int z; cin >> z; --z;
    AddEdge(S, udpi[0][z]);
  }
  for (int i = 0; i < y; ++i) {
    int z; cin >> z; --z;
    AddEdge(udpo[n][z], T);
  }

  int f = Flow(edg, S, T);
  cout << (f == x ? "Yes" : "No") << '\n';

}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) solve();
}

/*
 * 
 * ./a.out
 * 1
 * 1 4 2 2
 * 0000
 * 1 2
 * 3 4add edge 2 10 0
 * add edge 3 11 0
 * add edge 4 12 0
 * add edge 5 13 0
 * add edge 6 14 0
 * add edge 7 15 0
 * add edge 8 16 0
 * add edge 9 17 0
 * add edge 18 23 0
 * add edge 19 24 0
 * add edge 20 25 0
 * add edge 21 26 0
 * add edge 22 27 0
 * add edge 28 32 0
 * add edge 29 33 0
 * add edge 30 34 0
 * add edge 31 35 0
 * udpi:
 * 2 3 4 5
 * 6 7 8 9
 * udpo:
 * 10 11 12 13
 * 14 15 16 17
 * lrpi:
 * 18 19 20 21 22
 * lrpo:
 * 23 24 25 26 27
 * ipi:
 * 28 29 30 31
 * ipo:
 * 32 33 34 35
 * add edge 10 28 1
 * add edge 14 28 1
 * add edge 23 28 1
 * add edge 24 28 1
 * add edge 10 6 1
 * add edge 23 19 1
 * add edge 11 29 1
 * add edge 15 29 1
 * add edge 24 29 1
 * add edge 25 29 1
 * add edge 11 7 1
 * add edge 24 20 1
 * add edge 12 30 1
 * add edge 16 30 1
 * add edge 25 30 1
 * add edge 26 30 1
 * add edge 12 8 1
 * add edge 25 21 1
 * add edge 13 31 1
 * add edge 17 31 1
 * add edge 26 31 1
 * add edge 27 31 1
 * add edge 13 9 1
 * add edge 26 22 1
 * add edge 0 2 0
 * add edge 0 3 0
 *
 * add edge 16 1 0
 * add edge 17 1 0
 * Yes
 *
 *
 * */
