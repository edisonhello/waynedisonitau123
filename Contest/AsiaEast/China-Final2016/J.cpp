#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Edge {
  int to, cap, rev, w;

  Edge(int a, int b, int c, int d) : to(a), cap(b), rev(c), w(d) {}
};

int64_t Flow(vector<vector<Edge>> g, int S, int T) {
  int n = g.size();
  vector<bool> inq(n);
  vector<int> pv(n), ed(n);
  vector<int64_t> dist(n);
  constexpr int64_t kInf = 1'000'000'000'000'000'000;
  int64_t cost = 0;
  while (true) {
    fill(inq.begin(), inq.end(), false);
    fill(dist.begin(), dist.end(), kInf);
    queue<int> que;
    que.push(S);
    dist[S] = 0;
    while (!que.empty()) {
      int x = que.front();
      que.pop();
      inq[x] = false;
      // cout << "x = " << x << endl;
      for (int i = 0; i < g[x].size(); ++i) {
        Edge &e = g[x][i];
        if (e.cap == 0) continue;
        if (dist[e.to] > dist[x] + e.w) {
          dist[e.to] = dist[x] + e.w;
          pv[e.to] = x;
          ed[e.to] = i;
          if (!inq[e.to]) {
            inq[e.to] = true;
            que.push(e.to);
          }
        }
      }
    }
    if (dist[T] == kInf) break;
    int dlt = 1e9;
    for (int x = T; x != S; x = pv[x]) dlt = min(dlt, g[pv[x]][ed[x]].cap);
    for (int x = T; x != S; x = pv[x]) {
      Edge &e = g[pv[x]][ed[x]];
      e.cap -= dlt;
      g[e.to][e.rev].cap += dlt;
    }
    cost += dlt * dist[T];
  }
  return cost;
}

void solve() {
  vector<vector<Edge>> g(10000);
  auto AddEdge = [&](int a, int b, int c, int d) {
    g[a].emplace_back(b, c, (int)g[b].size() - 0, +d);
    g[b].emplace_back(a, 0, (int)g[a].size() - 1, -d);
  };

  int n, m; cin >> n >> m;
  vector<vector<int>> sc(n + 1, vector<int>(m + 1, 0));
  vector<vector<int>> sr(n + 1, vector<int>(m + 1, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m - 1; ++j) {
      cin >> sc[i][j];
      sc[i][j] *= -1;
    }
  }
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> sr[i][j];
      sr[i][j] *= -1;
    }
  }
  cerr << "asdf" << endl;

  int e; cin >> e;
  for (int i = 0; i < e; ++i) {
    int x, y; cin >> x >> y; --x, --y;
    sc[x][y] -= 1e9;
    sc[x][y + 1] -= 1e9;
    sr[x][y] -= 1e9;
    sr[x + 1][y] -= 1e9;
  }

  cerr << "Afe" << endl;

  int nowid = 0;
  int SOURCE = nowid++, DIST = nowid++;

  vector<vector<vector<int>>> cpids(n + 1, vector<vector<int>>(m + 1, vector<int>(8, -1)));
  vector<vector<vector<int>>> rpids(n + 1, vector<vector<int>>(m + 1, vector<int>(8, -1)));
  for (int i = 0; i <= n; ++i) for (int j = 0; j < m; ++j) {
    for (int z = 0; z < 8; ++z) cpids[i][j][z] = nowid++;
    AddEdge(SOURCE, cpids[i][j][0], 1, 0);
    AddEdge(cpids[i][j][0], cpids[i][j][7], 1, 0);
    AddEdge(cpids[i][j][7], cpids[i][j][1], 1, 0);
    AddEdge(cpids[i][j][1], cpids[i][j][2], 1, 0);
    AddEdge(cpids[i][j][2], cpids[i][j][3], 1, 0);
    AddEdge(cpids[i][j][7], cpids[i][j][5], 1, 0);
    AddEdge(cpids[i][j][4], cpids[i][j][5], 1, i == 0 || i == n ? 0 : sr[i - 1][j]);
    AddEdge(cpids[i][j][5], cpids[i][j][6], 1, 0);
    AddEdge(cpids[i][j][6], DIST, 1, 0);
  }
  for (int i = 0; i < n; ++i) for (int j = 0; j <= m; ++j) {
    for (int z = 0; z < 8; ++z) rpids[i][j][z] = nowid++;
    AddEdge(SOURCE, rpids[i][j][0], 1, 0);
    AddEdge(rpids[i][j][0], rpids[i][j][7], 1, 0);
    AddEdge(rpids[i][j][7], rpids[i][j][1], 1, 0);
    AddEdge(rpids[i][j][1], rpids[i][j][2], 1, 0);
    AddEdge(rpids[i][j][2], rpids[i][j][3], 1, 0);
    AddEdge(rpids[i][j][7], rpids[i][j][5], 1, 0);
    AddEdge(rpids[i][j][4], rpids[i][j][5], 1, j == 0 || j == m ? 0 : sc[i][j - 1]);
    AddEdge(rpids[i][j][5], rpids[i][j][6], 1, 0);
    AddEdge(rpids[i][j][6], DIST, 1, 0);
  }
  cerr << "here1" << endl;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    int TMP1 = nowid++;
    int TMP2 = nowid++;
    AddEdge(SOURCE, TMP1, 1, 0);
    AddEdge(TMP1, cpids[i][j][1], 1, 0);
    AddEdge(TMP1, cpids[i + 1][j][2], 1, 0);
    AddEdge(cpids[i][j][2], TMP2, 1, 0);
    AddEdge(cpids[i + 1][j][3], TMP2, 1, 0);
    AddEdge(TMP2, DIST, 1, 0);

    TMP1 = nowid++;
    TMP2 = nowid++;
    AddEdge(SOURCE, TMP1, 1, 0);
    AddEdge(TMP1, rpids[i][j][1], 1, 0);
    AddEdge(TMP1, rpids[i][j + 1][2], 1, 0);
    AddEdge(rpids[i][j][2], TMP2, 1, 0);
    AddEdge(rpids[i][j + 1][3], TMP2, 1, 0);
    AddEdge(TMP2, DIST, 1, 0);
  }
  cerr << "here2" << endl;

  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    AddEdge(cpids[i][j][3], rpids[i][j][4], 1, 0);
    AddEdge(cpids[i][j][3], rpids[i][j + 1][4], 1, 0);
    AddEdge(cpids[i + 1][j][3], rpids[i][j][4], 1, 0);
    AddEdge(cpids[i + 1][j][3], rpids[i][j + 1][4], 1, 0);

    AddEdge(rpids[i][j][4], cpids[i][j][3], 1, 0);
    AddEdge(rpids[i][j + 1][4], cpids[i][j][3], 1, 0);
    AddEdge(rpids[i][j][4], cpids[i + 1][j][3], 1, 0);
    AddEdge(rpids[i][j + 1][4], cpids[i + 1][j][3], 1, 0);
  }

  cout << "nowid = " << nowid << endl;
  int res = -(Flow(g, SOURCE, DIST) + e * 2 * 1000000000);
  if (res < -500000000) {
    cerr << "Res = " <<res << endl;
    cout << "Impossible" << endl;
  } else {
    cout << res << endl;
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; for (int T = 1; T <= t; ++T) {
    cout << "Case #" << T << ": ";
    solve();
  }
}
